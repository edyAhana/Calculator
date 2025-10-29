#include "BinaryTree.h"

BinaryTree::BinaryTree(const Token& token)
        : token(token)
        , left(nullptr)
        , right(nullptr) {}

BinaryTree::BinaryTree(const BinaryTree& other)
        : token(other.token)
        , left(other.left)
        , right(other.right) {}

BinaryTree::BinaryTree(BinaryTree&& other) noexcept
        : token(std::move(other.token))
        , left(std::move(other.left))
        , right(std::move(other.right)) {}

BinaryTree::~BinaryTree() = default;

BinaryTree& BinaryTree::operator=(const BinaryTree& other) {
    if(this == &other) {
        return *this;
    }

    token = other.token;
    left = other.left;
    right = other.right;
    return *this;
}

BinaryTree& BinaryTree::operator=(BinaryTree&& other) noexcept {
    if(this == &other) {
        return *this;
    }

    token = std::move(other.token);
    left = std::move(other.left);
    right = std::move(other.right);
    return *this;
}

BinaryTree::Pointer BinaryTree::Left() noexcept {
    return left;
}

BinaryTree::Pointer BinaryTree::Right()  noexcept {
    return right;
}

const BinaryTree::Pointer BinaryTree::CLeft() const noexcept {
    return left;
}

const BinaryTree::Pointer BinaryTree::CRight() const noexcept {
    return right;
}