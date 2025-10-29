#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <memory>
#include <string>

struct Token {
    enum class Type {
        UnOperator,
        BinOperator,
        Number,
        LeftBracket,
        RightBracket,
    };
    
    Type type;
    std::string_view token;
};

class BinaryTree {
public:
    using Pointer = std::shared_ptr<BinaryTree>;


private:
    Token token;
    Pointer left;
    Pointer right;

public:
    BinaryTree() = delete;
    BinaryTree(const Token& token);
    BinaryTree(const BinaryTree& other);
    BinaryTree(BinaryTree&& other) noexcept;
    ~BinaryTree();

    BinaryTree& operator=(const BinaryTree& other);
    BinaryTree& operator=(BinaryTree&& other) noexcept;

    Pointer Left() noexcept;     
    Pointer Right() noexcept; 

    const Pointer CLeft() const noexcept;     
    const Pointer CRight() const noexcept; 
};

#endif