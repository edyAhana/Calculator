#define PLUGIN_EXPORT
#include "basic_math.h"

extern "C" {
    PLUGIN_API double add(double lhs, double rhs) {
        return lhs + rhs;
    }

    PLUGIN_API double minus(double lhs, double rhs) {
        return lhs - rhs;
    }

    PLUGIN_API double mult(double lhs, double rhs) {
        return lhs * rhs;
    }

    PLUGIN_API double dev(double lhs, double rhs) {
        return lhs / rhs;
    }

    PLUGIN_API double Uminus(double arg) {
        return -arg;
    }
}
