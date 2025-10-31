#ifndef ABSTRACT_SYNTAX_TREE
#define ABSTRACT_SYNTAX_TREE

#include <memory>
#include "ExecuteStrategy.h"

class BasicNode {
public:
    BasicNode() = default;
    virtual ~BasicNode() = default;
    virtual double exec() const = 0;
};

class NumberNode : public BasicNode {
private:
    double value;
public:
    NumberNode(double value): value(value) {}
    ~NumberNode() = default;
    double exec() const override { return value; };
};


class FunctionNode : public BasicNode {
protected:
    std::unique_ptr<FunctionWrapper> op;
public:
    FunctionNode(const std::string& name)
        : op(std::make_unique<FunctionWrapper>(name)) {}
    void setFunction(std::unique_ptr<IFunction> func) {
        op->setFunction(std::move(func));
    }
    std::size_t arity() const {
        if(op) {
            return op->arity();
        }
        return 0;
    }
    std::string Name() const { return op->Name(); }
};

class BinaryOperatorNode : public FunctionNode {
private:
    std::unique_ptr<BasicNode> lhs;
    std::unique_ptr<BasicNode> rhs;
public:
    BinaryOperatorNode
    (
        const std::string& name
        , std::unique_ptr<BasicNode> lhs
        , std::unique_ptr<BasicNode> rhs
    )
        : FunctionNode(name)
        , lhs(std::move(lhs))
        , rhs(std::move(rhs)) {}

    ~BinaryOperatorNode() = default;

    double exec() const override { 
        return op->exec(
            lhs->exec(), rhs->exec()
        );
    }
};

class UnaryOperatorNode : public FunctionNode {
private:
    std::unique_ptr<BasicNode> arg;
public:
    UnaryOperatorNode(
        const std::string& name
        , std::unique_ptr<BasicNode> arg
    )
        : FunctionNode(name)
        , arg(std::move(arg)) {}

    ~UnaryOperatorNode() = default;

    double exec() const override {
        return op->exec(arg->exec());
    }
};




#endif