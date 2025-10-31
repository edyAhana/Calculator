#ifndef ABSTRACT_SYNTAX_TREE
#define ABSTRACT_SYNTAX_TREE

#include <memory>
#include "ExecuteStrategy.h"

struct BasicNode {
public:
    BasicNode() = default;
    virtual ~BasicNode() = default;
};

struct NumberNode : BasicNode {
    double value;

    NumberNode(double value);
    ~NumberNode() = default;
};


struct FunctionNode : BasicNode {
    std::unique_ptr<FunctionWrapper> op;

    FunctionNode(const std::string& name);
    
    void setFunction(std::unique_ptr<IFunction> func); 

    std::size_t arity() const;
    
    std::string Name() const;
};

struct BinaryOperatorNode : FunctionNode {

    std::unique_ptr<BasicNode> lhs;
    std::unique_ptr<BasicNode> rhs;

    BinaryOperatorNode
    (
        const std::string& name
        , std::unique_ptr<BasicNode> lhs
        , std::unique_ptr<BasicNode> rhs
    );

    ~BinaryOperatorNode() = default;

};

struct UnaryOperatorNode : FunctionNode {
    
    std::unique_ptr<BasicNode> arg;
    
    UnaryOperatorNode(
        const std::string& name
        , std::unique_ptr<BasicNode> arg
    );

    ~UnaryOperatorNode() = default;

};




#endif