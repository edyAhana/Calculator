#include <memory>
#include <iostream>

#include "Parser.h"
#include "PluginManager.h"
#include "Executer.h"




int main() {
    PluginManager pm;
    pm.LoadPlugins("./plugins");
    bool isExit = false;

    while(!isExit) {
        pm.LoadPlugins("./plugins");
        std::string expression;
        std::cout << "\nenter the expression:\n";
        std::cout << "<<< ";
        std::getline(std::cin, expression);

        if(expression == "q") {
            isExit = true;
            continue;
        }

        std::cout << "\nsolution:\n";
        std::cout << "<<< ";
        
        double solution = 0;
        try {
            solution = Executer::execute(
                pm, Parser::parse(Parser::tokenize(expression))
            );
        } catch (const std::exception& e) {
            std::cerr << e.what();
            continue;
        }

        std::cout << solution << "\n";
    }

    return 0;
}

