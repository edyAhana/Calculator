#ifndef PARSER_H
#define PARSER_H

#include "BinaryTree.h"
#include <vector>

class Parser {
private:
    using tokens = std::vector<BinaryTree::Token>;

    bool lexicalAnalyser(std::string expression);
    tokens tokinizer(std::string_view expression);
    BinaryTree syntacticAnalyser(const tokens& tokens);
    bool sintaticAnalyser(const BinaryTree& syntacticTree);
public:
    static BinaryTree Parse(std::string_view expression); 
};

#endif