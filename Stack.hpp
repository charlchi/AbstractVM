
#ifndef STACK_HPP
#define STACK_HPP

class Stack
{
	int top;
	IOperand** values;
public:
	void push(IOperand*);
	IOperand* pop(void);
	IOperand* peek(void);
	Stack();
	Stack(const Stack& rhs);
	Stack& operator=(const Stack& rhs);
	~Stack();
};

#endif // STACK_HPP