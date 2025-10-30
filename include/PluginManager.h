#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include <unordered_map>
#include <vector>
#include <functional>
#include <string>
#include <filesystem>
#include <iostream>
#include <exception>

using Path = std::filesystem::path;
namespace fs = std::filesystem;

#ifdef _WIN32
#include <windows.h>
using LibraryHandle = HMODULE;
#elif __linux__
#include <dlfcn.h>
using LibraryHandle = void*;
#endif


class PluginManager {
private:
    using Function = double (*) (double); 
    using Operator = double (*) (double, double);

    std::unordered_map<std::string, Function> functionList; 
    std::unordered_map<std::string, Operator> operatorList;
    std::vector<LibraryHandle> libraryList;

public:
    PluginManager();
    ~PluginManager();

    void LoadPlugins(const Path& directory);

    bool HasFunction(const std::string& func);
    bool HasOperator(const std::string& op);

    double CallFunction(const std::string& func, double lhs);
    double CallOperator(const std::string& op, double lhs, double rhs);

    void RegistreFunction(const std::string& func);
    void RegistreOperator(const std::string& op);
};




#endif