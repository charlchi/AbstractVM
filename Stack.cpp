
#include "Stack.hpp"

#define STACK_MAX (1000)

void Stack::push(IOperand*) {}
IOperand* Stack::pop(void) {}
IOperand* Stack::peek(void) {}

Stack::Stack() {
	this->values = new Stack*[STACK_MAX];
}

Stack::~Stack() {
	delete[] this->values;
}

#endif // STACK_HPP