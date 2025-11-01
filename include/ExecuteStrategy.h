#ifndef EXECUTE_STRATEGY_H
#define EXECUTE_STRATEGY_H

#include <memory>
#include <string>
#include <exception>

class IFunction {
public:
    IFunction() = default;
    virtual ~IFunction() = default;
    virtual double exec(double lhs, double rhs = 0) const = 0;
    virtual std::size_t arity() const = 0;
};

class IBinaryOperator : public IFunction {
public:
    using BinaryOp = double (*) (double, double);
private:
    BinaryOp op;
public:
    IBinaryOperator(BinaryOp op): op(op) {}
    ~IBinaryOperator() = default;
    double exec(double lhs, double rhs = 0) const override { return op(lhs , rhs); }
    std::size_t arity() const override { return 2; }
};

class IUnaryOperator : public IFunction {
public:
    using UnaryOp = double (*) (double);
private:
    UnaryOp op;
public:
    IUnaryOperator(UnaryOp op): op(op) {}
    ~IUnaryOperator() = default;
    double exec(double lhs, double rhs = 0) const override { return op(lhs); }
    std::size_t arity() const override { return 1; }
};


class FunctionWrapper {
private:
    std::unique_ptr<IFunction> func;
    std::string name;
public: 
    FunctionWrapper() = default;
    FunctionWrapper(std::unique_ptr<IFunction> func, const std::string& name)
        : func(std::move(func))
        , name(name) {}
    FunctionWrapper(const std::string& name)
        : func(nullptr)
        , name(name) {}

    void setFunction(std::unique_ptr<IFunction> newFunc) { func = std::move(newFunc); }
    void setName(const std::string& newName) { name = newName; }
    std::string Name() const { return name; }
    std::size_t arity() const { return func->arity(); }
    bool isFunc() const { return func != nullptr; }

    double exec(double lhs, double rhs = 0) const {
        if(!func) {
            throw std::runtime_error("[FunctionWrapper] need to specify function");
        }
    
        if(func->arity() == 1) {
            return func->exec(lhs);
        } 
        
        return func->exec(lhs, rhs);
    }

};

#endif