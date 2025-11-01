#include "PluginManager.h"

PluginManager::PluginManager() = default;

PluginManager::~PluginManager() {
    for(auto lib : libraryDescriptors) {
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

        if(libraryList.contains(path.filename())) {
            continue;
        }

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
        std::cout << "[ PluginManager ] load plugin :" << path.filename().string() << "\n";
        libraryDescriptors.push_back(handle);
        libraryList.insert(path.filename().string());
    }
}

bool PluginManager::HasFunction(const std::string& func) {
    return functionList.contains(func);
}

bool PluginManager::HasOperator(const std::string& op) {
    return operatorList.contains(op);
}

PluginManager::Function PluginManager::GetFunction(const std::string& func) {
    if(HasFunction(func)) {
         return functionList[func];
    }
    return nullptr;
}

PluginManager::Operator PluginManager::GetOperator(const std::string& op) {
    if(HasOperator(op)) {
        return operatorList[op];
    }
    return nullptr;
}

void PluginManager::RegistreFunction(const std::string& func) {
    if(HasFunction(func)) {
        return;
    }

    for(auto lib : libraryDescriptors) {
        Function funcPtr = nullptr;
#ifdef _WIN32
        funcPtr = reinterpret_cast<Function>(GetProcAddres(lib, nameMap(func).c_str()));
#elif __linux__
        funcPtr = reinterpret_cast<Function>(dlsym(lib,nameMap(func).c_str()));
#endif
        if(funcPtr) {
            functionList[func] = funcPtr;
            return;
        }
    }
}

void PluginManager::RegistreOperator(const std::string& op) {
    if(HasOperator(op)) {
        return;
    }
    
    for(auto lib : libraryDescriptors) {
        Operator operPtr = nullptr;
#ifdef _WIN32
        operPtr = reinterpret_cast<Operator>(GetProcAddres(lib, nameMap(op).c_str()));
#elif __linux__
        operPtr = reinterpret_cast<Operator>(dlsym(lib, nameMap(op).c_str()));
#endif
        if(operPtr) {
            operatorList[op] = operPtr;
            return;
        }
    }
}

std::string PluginManager::nameMap(const std::string& name) {
    if(name == "+") {
        return "add";
    } else if(name == "-") {
        return "minus";
    } else if(name == "*") {
        return "mult";
    } else if(name == "/") {
        return "dev";
    } else if(name == "^") {
        return "deg";
    } 

    return name;
} 