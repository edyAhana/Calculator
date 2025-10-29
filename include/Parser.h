#ifndef PARSER_H
#define PARSER_H

#include "BinaryTree.h"
#include <vector>

class Parser {
private:
    using tokens = std::vector<Token>;

    static tokens tokinizer(std::string_view expression);
    static BinaryTree::Pointer getAbstractSyntaxTree(const tokens& tokens);
    static std::size_t getPriority(const Token& token);
    static BinaryTree::Pointer getAbstractSyntxTreeHelper(const tokens& tokens);
public:
    static BinaryTree Parse(std::string_view expression); 
};

#endif