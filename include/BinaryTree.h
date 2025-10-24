#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <memory>
#include <string>

class BinaryTree {
public:
    using Pointer = std::shared_ptr<BinaryTree>;

    struct Token {
        enum class Type {
            Operator,
            Number,
        };
        
        Type type;
        std::string token;
    };

private:
    Token token;
    Pointer left;
    Pointer right;

public:
    BinaryTree();
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