#include <iostream>
#include <cctype>
#include <stack>
#include <exception>
#include <string>

#include "Parser.h"

Parser::tokens Parser::tokenize(const std::string& expression) {
    std::size_t i = 0;
    tokens result;
    while(i < expression.size()) {
        char character = expression[i];

        if(isspace(character)) {
            ++i;
            continue;
        }

        if(isdigit(character)) {
            std::size_t start = i;
            ++i;
            while (i <= expression.size() - 1 && isdigit(expression[i])) {
                ++i;
            }
            if(i<expression.size() && expression[i] == '.') {
                ++i;
                while (i < expression.size() && isdigit(expression[i])) {
                    ++i;
                }
            }
            result.push_back(
                Token {
                    Token::Type::Number
                    , expression.substr(start, i - start)
                }
            );
            continue;
        } 

        if(character == '(') {
            result.push_back(
                Token {
                    Token::Type::LeftBracket
                    , expression.substr(i, 1)
                }
            );
            ++i;
            continue;
        }

        if(character == ')') {
            result.push_back(
                Token {
                    Token::Type::RightBracket
                    , expression.substr(i, 1)
                }
            );
            ++i;
            continue;
        }

        if(isprint(character)) {
            std::size_t start = i;
            ++i;
            while(i < expression.size() 
                && isprint(expression[i]) 
                && expression[i] != ')' 
                && expression[i] != '(' 
                && expression[i] != ' '
                && !isdigit(expression[i])
            ) {
                ++i;
            }
            
            result.push_back(
                Token {
                    Token::Type::Function
                    , expression.substr(start, i - start)
                }
            );
            continue;
        }
    }
    return result;
}

std::size_t Parser::getPriority(const Token& token) {
    auto op = token.token;
    if(op == "+" || op == "-") {
        return 1;
    } else if(op == "*" || op == "/") {
        return 2;
    } else if(op == "^") {
        return 3;
    }
    return 0;
}

std::unique_ptr<BasicNode> Parser::parse(const tokens& tokens) {
    std::stack<Token> funcs;
    std::stack<std::unique_ptr<BasicNode>> nodes;
    bool is_last_left_bracket = false;
    for(const auto& token: tokens) {
        switch (token.type) {
            case Token::Type::Number:
                nodes.push(
                    std::make_unique<NumberNode>(std::atof(token.token.c_str()))
                );
                is_last_left_bracket = false;
                break;

            case Token::Type::LeftBracket:
                funcs.push(token);
                is_last_left_bracket = true;
                break;

            case Token::Type::Function:
                {
                bool isUnary = false;

                isUnary |= is_last_left_bracket;
                isUnary |= funcs.empty() && nodes.empty();
                
                is_last_left_bracket = false;

                if(isUnary) {
                    funcs.emplace(
                        Token::Type::UnFunction, token.token
                    );
                    continue;                    
                }
                
                while(!funcs.empty() && getPriority(funcs.top()) >= getPriority(token)) {
                    std::unique_ptr<BasicNode> rhs = std::move(nodes.top());
                    nodes.pop();
                    if(funcs.top().type == Token::Type::BinFunction) {
        
                        std::unique_ptr<BasicNode> lhs = std::move(nodes.top());
                        nodes.pop();
                        nodes.push(
                            std::make_unique<BinaryOperatorNode>(funcs.top().token, std::move(lhs), std::move(rhs))
                        );
                    } else {
                        nodes.push(
                            std::make_unique<UnaryOperatorNode>(funcs.top().token, std::move(rhs))
                        );
                    }
                    funcs.pop();
                } 

                funcs.emplace(
                    Token::Type::BinFunction, token.token
                );
                break;
                }

            case Token::Type::RightBracket:
                if(is_last_left_bracket) {
                    throw std::runtime_error("[Parser] empty brackets");
                }

                if(funcs.top().type == Token::Type::LeftBracket) {
                    funcs.pop();
                    std::unique_ptr<BasicNode> rhs = std::move(nodes.top());
                    nodes.pop();
                    if(funcs.top().type == Token::Type::BinFunction) {
                        std::unique_ptr<BasicNode> lhs = std::move(nodes.top());
                        nodes.pop();
                        nodes.push(
                            std::make_unique<BinaryOperatorNode>(funcs.top().token, std::move(lhs), std::move(rhs))
                        );
                    } else {
                        nodes.push(
                            std::make_unique<UnaryOperatorNode>(funcs.top().token, std::move(rhs))
                        );
                    }
                    funcs.pop();
                    continue;
                }

                while (!funcs.empty() && funcs.top().type != Token::Type::LeftBracket) {
                    std::unique_ptr<BasicNode> rhs = std::move(nodes.top());
                    nodes.pop();
                    if(funcs.top().type == Token::Type::BinFunction) {
                        std::unique_ptr<BasicNode> lhs = std::move(nodes.top());
                        nodes.pop();
                        nodes.push(
                            std::make_unique<BinaryOperatorNode>(funcs.top().token, std::move(lhs), std::move(rhs))
                        );
                    } else {
                        nodes.push(
                            std::make_unique<UnaryOperatorNode>(funcs.top().token, std::move(rhs))
                        );
                    }
                    funcs.pop();
                }
                
                if(funcs.empty()) {
                    throw std::runtime_error("[Parser] count of right brackets is greater than left ones");
                }
                
                funcs.pop();

                if(!funcs.empty() && funcs.top().type == Token::Type::UnFunction) {
                    std::unique_ptr<BasicNode> rhs = std::move(nodes.top());
                    nodes.pop();
                    nodes.push(
                        std::make_unique<UnaryOperatorNode>(funcs.top().token, std::move(rhs))
                    );
                    funcs.pop();
                }
            break;
        }        
    }

    while(!funcs.empty() && !nodes.empty()) {
        std::unique_ptr<BasicNode> rhs = std::move(nodes.top());
        nodes.pop();
        if(funcs.top().type == Token::Type::BinFunction) {
            std::unique_ptr<BasicNode> lhs = std::move(nodes.top());
            nodes.pop();
            nodes.push(
                std::make_unique<BinaryOperatorNode>(funcs.top().token, std::move(lhs), std::move(rhs))
            );
        } else {
            nodes.push(
                std::make_unique<UnaryOperatorNode>(funcs.top().token, std::move(rhs))
            );
        }
        funcs.pop();
    }


    if(!funcs.empty() || nodes.size() > 1) {
        throw std::runtime_error("[Praser] not corret expression");
    }

    return std::move(nodes.top());
}

std::unique_ptr<BasicNode> Parser::Parse(const std::string& expression) {
    auto v = tokenize(expression);
    for(auto t : v) {
        std::cout << t.token << "\n";
    }
    return {};
}