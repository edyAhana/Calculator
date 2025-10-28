#ifndef PARSER_H
#define PARSER_H

#include "BinaryTree.h"
#include <vector>

class Parser {
private:
    using tokens = std::vector<Token>;

    static bool lexicalAnalyser(std::string_view expression);
    static tokens tokinizer(std::string_view expression);
    static BinaryTree getAbstractSyntaxTree(const tokens& tokens);
    static bool sintaticAnalyser(const BinaryTree& syntacticTree);
public:
    static BinaryTree Parse(std::string_view expression); 
};

#endif