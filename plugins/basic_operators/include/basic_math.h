#ifndef ADD_H
#define ADD_H

#ifdef _WIN32
    #ifdef PLUGIN_EXPORT
        #define PLUGIN_API __declspec(dllexport)
    #else
        #define PLUGIN_API __declspec(dllimport)
    #endif
#elif __linux__
    #define PLUGIN_API __attribute__((visibility("default")))
#endif

extern "C" {
    PLUGIN_API double add_plugin(double lhs, double rhs);
    PLUGIN_API double minus_plugin(double lhs, double rhs);
    PLUGIN_API double mult_plugin(double lhs, double rhs);
    PLUGIN_API double dev_plugin(double lhs, double rhs);
    PLUGIN_API double Uminus_plugin(double arg);
}

#endif