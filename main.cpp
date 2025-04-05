#include <iostream>
#include "expression.h"


int main(int argc, char* argv[]) {
    expression* e2 = new unop('-', new constant(3));
    std::cout << "Evaluate: " << e2->eval() << std::endl;
    std::cout << "Infix: " << e2->infix() << std::endl;
    std::cout << "Postfix: " << e2->postfix() << std::endl;

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