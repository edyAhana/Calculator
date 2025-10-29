#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include <unordered_map>
#include <vector>
#include <functional>
#include <string>


class PluginManager {
private:
    using function = std::function<double(const std::vector<double>&)>;

    std::unordered_map<std::string, function> functionList; 

public:
    PluginManager();
    ~PluginManager();

    void LoadPlugins();

    bool HasFunction();
    double CallFunction();

    void RegistreFunction();
};




#endif