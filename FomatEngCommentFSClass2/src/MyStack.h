// assignment number : 1
// Name       : Hong Cheng
// StudentID    : 2016160602
// Due :29/9/16

//			    MyStack
//		It is a template class , and this class defines the main data structure used in the program.
//     As showed from the class name , it is a Stack with the essential functions to push and
//		pop data such as void push(ElemType x) ,ElemType pop() and so on.

#include <iostream>
using namespace std;
#ifndef MYSTACK_H_
#define MYSTACK_H_

template<class ElemType> class MyStack {
private:
	const static int MAXSIZE = 100; //the maximum of the stack's size
	ElemType data[MAXSIZE];         //the data value of the stack
	int top;                                     //the number of the top element

public:
	void init();                                //Initialize the stack. 初始化栈
	bool empty();             // To determine whether the stack is empty.判断栈是否为空
	ElemType gettop(); // Read the top element of the stack (not out of the stack)读取栈顶元素(不出栈)
	void push(ElemType x);         // push the element into the stack进栈
	ElemType pop();                     // pop the element out of the stack 出栈
};
/*
 *   argument : the realization of the function in the definition of the Stack
 *   return : void
 *   action :
 */
template<class T> void MyStack<T>::init() {
	this->top = 0;
}

/*
 *   argument : To determine whether the stack is empty.判断栈是否为空
 *   return : boolean
 *   action :
 */
template<class T> bool MyStack<T>::empty() {
	return this->top == 0 ? true : false;
}

/*
 *   argument : Read the top element of the stack (not out of the stack)读取栈顶元素(不出栈)
 *   return : the top data of the stack
 *   action :
 */
template<class T> T MyStack<T>::gettop() {
	if (empty()) {
		cout << "The stack is empty！\n";
	}
	return this->data[this->top - 1];
}
/*
 *   argument : push the element into the stack进栈
 *   return : void
 *   action : If the stack is not full then the variable x willed be pushed into the stack and the top data updates into the variable x
 */
template<class T> void MyStack<T>::push(T x) {
	if (this->top == MAXSIZE) {
		cout << "The stack is full！\n";
	}
	this->data[this->top] = x;
	this->top++;
}

/*
 *   argument : pop the element out of the stack 出栈
 *   return : the popped variable on the top of the stack
 *   action : the size of stack will minus 1
 */
template<class T> T MyStack<T>::pop() {
	if (this->empty()) {
		cout << "The stack is empty！\n";
		return 0;
	}
	T e = this->data[this->top - 1];
	this->top--;
	return e;
}

#endif /* MYSTACK_H_ */
