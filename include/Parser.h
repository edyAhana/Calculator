#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <memory>

#include "AbstractSyntaxTree.h"

struct Token {
    enum class Type {
        Function,
        BinFunction,
        UnFunction,
        Number,
        LeftBracket,
        RightBracket,
    };
    
    Type type;
    std::string token;
};

class Parser {
private:
    using tokens = std::vector<Token>;
    static std::size_t getPriority(const Token& token);
public:
    static std::unique_ptr<BasicNode> parse(const tokens& tokens);
    static tokens tokenize(const std::string& expression);
    static std::unique_ptr<BasicNode> Parse(const std::string& expression); 
};

#endif