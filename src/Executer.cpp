#include "Executer.h"

double Executer::execute(PluginManager& pm, const std::unique_ptr<BasicNode>& expression) {
    double res = 0;
    auto raw_ptr = expression.get();

    if(auto ptr = dynamic_cast<NumberNode*>(raw_ptr)) {
        res = ptr->value;
    } else if(auto ptr = dynamic_cast<BinaryOperatorNode*>(raw_ptr)) {
        std::string name = ptr->Name();

        pm.RegistreOperator(name);

        if(pm.HasOperator(name)) {
            ptr->setFunction(
                std::make_unique<IBinaryOperator>(pm.GetOperator(name))
            );
        }

        res = ptr->op->exec(
            execute(pm, ptr->lhs), execute(pm, ptr->rhs)
        );
    } else if(auto ptr = dynamic_cast<UnaryOperatorNode*>(raw_ptr)) {
        std::string name = ptr->Name();
        if(name == "-") {
            name = "Uminus";
        }

        pm.RegistreFunction(name);

        if(pm.HasFunction(name)) {
            ptr->setFunction(
                std::make_unique<IUnaryOperator>(pm.GetFunction(name))
            );
        }

        res = ptr->op->exec(
            execute(pm, ptr->arg)
        );
    }
    return res;
}

