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
    PLUGIN_API double add(double lhs, double rhs);
    PLUGIN_API double minus(double lhs, double rhs);
    PLUGIN_API double mult(double lhs, double rhs);
    PLUGIN_API double dev(double lhs, double rhs);
    PLUGIN_API double minus(double arg);
}

#endif