#include <string>
#include <cstdio>  // Includes declaration of sprintf() 

/// ------- Requiremensts ------- ///
/*
- Handle:
	- Binary Operators (a + b, a * b, a - b, a / b):
		"+", "-", "*", "/"
	- Unary Operators (-a, -b, -c):
		"-"
- Constants are always integers.
*/
/// ------- Notes --------------- ///
/*
An infix expression places the operator between two operands, or in front of a single operand
	(e.g. 1 + 2, or - 3).
A postfix expression always puts the operator after the operands
	(e.g. 1 2 +, or 3 ~).
To avoid confusion, when printing a unary "–" in postfix format, use the notation "~".
When printing infix, use parentheses liberally.
//------------------------------//
To test your classes, run the main program provided with the assignment:
	expression_main.cpp
This program creates the following expression, evaluates it, and then prints it in infix and postfix formats:
	-3 * (4 + (9 / 3))
//------------------------------//
sprintf() is a function like printf() that uses a format string to create a string with a desired layout.
For example :
	char expr_str[100];
	sprintf(expr_str, "(%s %c %s)", e1.infix(), op, e2.infix());
*/
/// ----------------------------- ///

class expression {
public:
	virtual int eval() = 0;
	virtual std::string infix() = 0;
	virtual std::string postfix() = 0;
};

class constant : public expression {
public:
	// Constructor
	constant(int i) {
		this->i = i;
	}
	// Destructor
	~constant() {};

	// Expression evalutation
	virtual int eval() override {
		return i;
	}
	// Infix expression
	virtual std::string infix() override {
		char cstr[100];
		std::string s = std::to_string(i);
		if (i >= 0) {
			std::sprintf(cstr, "%s", s.c_str());
			return cstr;
		}
		else {
			std::sprintf(cstr, "(%c %s)", '-', s.erase(0, 1).c_str());
			return  cstr;
		}
	}
	// Postfix expression
	virtual std::string postfix() override {
		char cstr[100];
		std::string s = std::to_string(i);
		if (i >= 0) {
			std::sprintf(cstr, "%s", s.c_str());
			return cstr;
		}
		else {
			std::sprintf(cstr, "%s %c", s.erase(0, 1).c_str(), '~');
			return cstr;
		}
	}
private:
	int i;
};

class unop : public expression {
public:
	// Constructor
	unop(char op, expression* e) {
		this->op = op;
		this->e = e;
	}
	// Destructor
	~unop() {};

	// Expression evalutation
	virtual int eval() override {
		if (op == '-') {
			return -e->eval();
		}
		return e->eval();
	}
	// Infix expression
	virtual std::string infix() override {
		char cstr[100];
		if (op == '-') {
			std::sprintf(cstr, "(%c %s)", op, e->infix().c_str());
			return cstr;
		}
		else {
			std::sprintf(cstr, "%s", e->infix().c_str());
			return  cstr;
		}
	}
	// Postfix expression
	virtual std::string postfix() override {
		char cstr[100];
		if (op == '-') {
			std::sprintf(cstr, "%s %c", e->postfix().c_str(), '~');
			return cstr;
		}
		else {
			std::sprintf(cstr, "%s", e->postfix().c_str());
			return cstr;
		}
	}
private:
	char op;
	expression* e;
};

class binop : public expression {
public:
	// Constructor
	binop(char op, expression* e1, expression* e2) {
		this->op = op;
		this->e1 = e1;
		this->e2 = e2;
	}
	// Destructor
	~binop() {};

	// Expression evalutation
	virtual int eval() override {
		switch (op) {
		case '-':
			return e1->eval() - e2->eval();
		case '+':
			return e1->eval() + e2->eval();
		case '*':
			return e1->eval() * e2->eval();
		case '/':
			return e1->eval() / e2->eval();
		default:
			return 0;
		}
	}
	// Infix expression
	virtual std::string infix() override {
		char cstr[100];
		std::sprintf(cstr, "(%s %c %s)", e1->infix().c_str(), op, e2->infix().c_str());
		return cstr;
	}
	// Postfix expression
	virtual std::string postfix() override {
		char cstr[100];
		std::sprintf(cstr, "%s %s %c", e1->postfix().c_str(), e2->postfix().c_str(), op);
		return cstr;
	}
private:
	char op;
	expression* e1;
	expression* e2;
};