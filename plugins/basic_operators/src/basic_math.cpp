#define PLUGIN_EXPORT
#include "basic_math.h"

extern "C" {
    PLUGIN_API double add_plugin(double lhs, double rhs) {
        return lhs + rhs;
    }

    PLUGIN_API double minus_plugin(double lhs, double rhs) {
        return lhs - rhs;
    }

    PLUGIN_API double mult_plugin(double lhs, double rhs) {
        return lhs * rhs;
    }

    PLUGIN_API double dev_plugin(double lhs, double rhs) {
        return lhs / rhs;
    }

    PLUGIN_API double Uminus_plugin(double arg) {
        return -arg;
    }
}
