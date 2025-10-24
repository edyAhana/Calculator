#include "BinaryTree.h"

BinaryTree::BinaryTree() = default;

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
    if(!left) {
        return std::shared_ptr<BinaryTree>();
    }
    return left;
}

BinaryTree::Pointer BinaryTree::Right()  noexcept {
    if(!right) {
        return std::shared_ptr<BinaryTree>();
    }
    return right;
}

const BinaryTree::Pointer BinaryTree::CLeft() const noexcept {
    if(!left) {
        return std::shared_ptr<BinaryTree>();
    }
    return left;
}

const BinaryTree::Pointer BinaryTree::CRight() const noexcept {
    if(!right) {
        return std::shared_ptr<BinaryTree>();
    }
    return right;
}