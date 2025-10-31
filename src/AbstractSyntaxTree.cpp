#include "AbstractSyntaxTree.h"

NumberNode::NumberNode(double value): value(value) {}

FunctionNode::FunctionNode(const std::string& name)
    : op(std::make_unique<FunctionWrapper>(name)) {}

void FunctionNode::setFunction(std::unique_ptr<IFunction> func) {
    op->setFunction(std::move(func));
}

std::size_t FunctionNode::arity() const {
    if(op->isFunc()) {
        return op->arity();
    }
    return 0;
}

std::string FunctionNode::Name() const {
    return op->Name();
}

BinaryOperatorNode::BinaryOperatorNode
    (
        const std::string& name
        , std::unique_ptr<BasicNode> lhs
        , std::unique_ptr<BasicNode> rhs
    )
        : FunctionNode(name)
        , lhs(std::move(lhs))
        , rhs(std::move(rhs)) {}
        
UnaryOperatorNode::UnaryOperatorNode
    (
        const std::string& name
        , std::unique_ptr<BasicNode> arg
    )    
        : FunctionNode(name)
        , arg(std::move(arg)) {}


