#ifndef EXECUTER_H
#define EXECUTER_H

#include "PluginManager.h"
#include "AbstractSyntaxTree.h"

class Executer {
public:
    static double execute(PluginManager& pm, const std::unique_ptr<BasicNode>& expression);
};
#endif