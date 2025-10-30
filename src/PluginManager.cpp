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

