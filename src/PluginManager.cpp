#include "PluginManager.h"

PluginManager::PluginManager() = default;

PluginManager::~PluginManager() {
    for(auto lib : libraryList) {
#ifdef _WIN32
        FreeLibrary(lib);
#elif __linux
        dlclose(lib);
#endif
    }
}

void PluginManager::LoadPlugins(const Path& directory) {
    for(auto& entry : fs::directory_iterator(directory)) {
        if(!entry.is_regular_file()) {
            continue;
        }

        const auto path = entry.path();

        LibraryHandle handle = nullptr;
#ifdef _WIN32
        if(path.extension() != ".dll") {
            continue;
        }
        
        handle = LoadLibraryA(path.string().c_str());
        if(!handle) {
            std::cerr << "[ PluginManager ] failed to open " << path << "\n";
            continue;
        }
#elif __linux__
        if(path.extension() != ".so") {
            continue;
        }

        handle = dlopen(path.string().c_str(), RTLD_NOW);

        if(!handle) {
            std::cerr << "[ PluginManager ] failed to open " << path << dlerror() << "\n";
            continue;
        }
#endif
        std::cout << "[ PluginManager ] loaded plugin :" << path.filename().string() << "\n";
        libraryList.push_back(handle);
    }
}

bool PluginManager::HasFunction(const std::string& func) {
    return functionList.contains(func);
}

bool PluginManager::HasOperator(const std::string& op) {
    return functionList.contains(op);
}

double PluginManager::CallFunction(const std::string& func, double lhs) {
    return functionList[func](lhs);
}

double PluginManager::CallOperator(const std::string& func, double lhs, double rhs) {
    return operatorList[func](lhs, rhs);
}

void PluginManager::RegistreFunction(const std::string& func) {
    for(auto lib : libraryList) {
        Function funcPtr = nullptr;
#ifdef _WIN32
        funcPtr = reinterpret_cast<Function>(GetProcAddres(lib, func.c_str()));
#elif __linux__
        funcPtr = reinterpret_cast<Function>(dlsym(lib, func.c_str()));
#endif
        if(funcPtr) {
            functionList[func] = funcPtr;
            return;
        }
    }
    throw std::runtime_error("[ PluginManager ] no function called " + func + "\n");
}

void PluginManager::RegistreOperator(const std::string& op) {
    for(auto lib : libraryList) {
        Operator operPtr = nullptr;
#ifdef _WIN32
        operPtr = reinterpret_cast<Operator>(GetProcAddres(lib, op.c_str()));
#elif __linux__
        operPtr = reinterpret_cast<Operator>(dlsym(lib, op.c_str()));
#endif
        if(operPtr) {
            operatorList[op] = operPtr;
            return;
        }
    }
    throw std::runtime_error("[ PluginManager ] no operator called " + op + "\n");
}