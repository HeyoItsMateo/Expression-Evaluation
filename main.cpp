#include <iostream>
#include "expression.h"


int main(int argc, char* argv[]) {
    expression* e = new binop('*',
        new unop('-', new constant(3)),
        new binop('+',
            new constant(4),
            new binop('/',
                new constant(9),
                new constant(3)
            )
        )
    );

    std::cout << "Evaluate: " << e->eval() << std::endl;
    std::cout << "Infix: " << e->infix() << std::endl;
    std::cout << "Postfix: " << e->postfix() << std::endl;

	return 0;
}