/*
 * PreToPost.h
 *
 *  Created on: Sep 29, 2016
 *      Author: cheng hong
 */
#include <iostream>
#include "MyStack.h"

using namespace std;
#ifndef PRETOPOST_H_
#define PRETOPOST_H_

/*
 *   argument : To determine whether the characters read into the operator
 *   return : boolean value --true or false
 *   action : if the char is an operator, then return 1 ,otherwise return 0;
 */
bool isoperator(char op) {
	switch (op) {
	case '+':
	case '-':
	case '*':
	case '/':
		return 1;
	default:
		return 0;
	}
}

/*
 *   argument : Set operator priority
 *   return : integer number
 *   action : The bigger the number, the higher the priority
 */
int priority(char op) {
	switch (op) {
	case '#':
		return -1;
	case '(':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	default:
		return -1;
	}
}

/*
 *   argument :Convert infix expressions to postfix expression, return postfix expression length (including spaces)
 *                    把中缀表达式转换为后缀表达式，返回后缀表达式的长度（包括空格）
 *   return : void (The value of the char post[] and n will be upgrades)
 *   action :
 */
void postfix(char pre[], char post[], int &n) {

	int i = 0, j = 0;
	MyStack<char> stack;
	stack.init(); // Initialize the stack that  storages the operators初始化存储操作符的栈

	stack.push('#'); //the mark that it is the end of postfix2(char pre[], string post[], int &n)

	while (pre[i] != '\0') {
		if (pre[i] == '  ') {
			continue;
		}
		if ((pre[i] >= 65 && pre[i] <= 90)) // 遇到大写字母直接写入后缀表达式，带数字控制
		{ //Encountered numbers   directly to the suffix expression
			/*post[j++] = ' '; // Separate operands with spaces 用空格分开操作数
			 n++;*/
			post[j++] = pre[i];
			n++;
		} else if (pre[i] == '(') // Encounter "(" no comparing and push directly into the stack 遇到“（”不用比较直接入栈
				{
			stack.push(pre[i]);
		} else if (pre[i] == ')') // if there is a right parenthesis, all of the corresponding left parenthesis after operator (in the stack)would be writed into the  postfix expression遇到右括号将其对应左括号后的操作符（操作符栈中的）全部写入后缀表达式
				{
			while (stack.gettop() != '(') {
				post[j++] = stack.pop();
				n++;
			}
			stack.pop(); // pop the '(' and there is no parentheses in the postfix equation  将“（”出栈，后缀表达式中不含小括号
		} else if (isoperator(pre[i])) {
			/*post[j++] = ' '; // Separate operands with spaces 用空格分开操作数
			 n++;*/
			while (priority(pre[i]) <= priority(stack.gettop())) {
				// When the current operator's priority is lower than or equal to the priority of the top-of-stack operator,
				//the stack operator is written to the postfix expression and this process will be repeated.
				//当前的操作符小于等于栈顶操作符的优先级时，将栈顶操作符写入到后缀表达式，重复此过程
				post[j++] = stack.pop();
				n++;
			}

			stack.push(pre[i]); // If the priority of the current operator is higher than that of the top-of-stack operator, push the operator onto the stack
								//当前操作符优先级大于栈顶操作符的优先级，将该操作符入栈
		}

		i++;
	}
	while (!stack.empty()) // Add all operators to the postfix expression将所有的操作符加入后缀表达式
	{
		post[j++] = stack.pop();
		n++;
	}
	/*//empty the stack   清空栈
	 while (!stack.empty())
	 stack.pop();*/
}

/*
 *   argument :
 *   return :
 *   action :
 */
int priority2(char op) {

	int num = 0;
	switch (op) {
	case '+':
		num = 1;
		break;
	case '-':
		num = 2;
		break;
	case '*':
		num = 3;
		break;
	case '/':
		num = 4;
		break;
	}
	return num;
}

/*
 *   argument :
 *   return :
 *   action :
 */
string priorityToChar(char op) {
	string operators;
	switch (op) {
	case '+':
		operators = "ADD";
		break;
	case '-':
		operators = "SUB";
		break;
	case '*':
		operators = "MUL";
		break;
	case '/':
		operators = "DIV";
		break;
	}
	return operators;
}

/*
 *   argument :Convert  postfix expression to the  assembly code , return  the size of  the assembly code array
 *   return : void (the  assembly code array and n will be upgrades)
 *   action :
 */
void postfix2(char postfix[], string sAssemblyCode[], int &n) {

	int i = 0;
	int j = 0;
	char cR1 = ' ';
	char cR2 = ' ';
	bool flag1 = false; //it means that the value of R1 is null
	bool flag2 = false;
	char tempNum = '0';
	string operators = "";
	string sR1 = "";
	string sR2 = "";
	string ST = "";
	string lN = "\n";
	string move = "MOVE\t";
	string r1T = "R1,\t\t";
	string r2T = "R2,\t\t";
	string tR2 = ", \tR2 \n";
	string temp = "TEMP";
	string oR21 = "\t\tR2 ,\t\tR1\n";

	MyStack<char> stack2;
	stack2.init(); // Initializes the stack that storages operators 初始化存储操作符的栈

	while (postfix[i] != '#') {

		if ((postfix[i] >= 65 && postfix[i] <= 90)) // Encountered upper letter，directly write it to the postfix expression遇到字母直接把它写入后缀表达式
		{
			stack2.push(postfix[i]);

		} else if (priority2(postfix[i]) > 0) {
			//Assignment to R1  对R1赋值
			if (!flag1) {

				cR1 = stack2.pop();
				flag1 = true;
				if (cR1 == '$') {
					sR1 = move + r1T + temp + stack2.pop() + lN; //	cout << "MOVE\tR2,\t" << R2 << endl;
				} else {
					sR1 = move + r1T + cR1 + lN;
				}

				sAssemblyCode[j++] = sR1;
				n++;

			}
			//Assignment to R2  对R2赋值
			if (!flag2) {
				cR2 = stack2.pop();
				flag2 = true;

				if (cR2 == '$') {
					sR2 = move + r2T + temp + stack2.pop() + lN; // cout << "MOVE\tR2,\t" << R2 << endl;
				} else {
					sR2 = move + r2T + cR2 + lN;
				}
				sAssemblyCode[j++] = sR2;
				n++;
			}

			//Judge the operator and output   判断操作符
			operators = priorityToChar(postfix[i]);
			sAssemblyCode[j++] = operators + oR21; //	cout << operators << "\tR2,\tR1" << endl;
			n++;
			flag1 = true;

			//The handling of temp values   对短暂值的处理
			tempNum += 1;
			ST = temp + tempNum;
			stack2.push(tempNum);
			stack2.push('$');
			flag1 = false;
			sAssemblyCode[j++] = move + ST + tR2;
			n++;
			flag2 = false;

		}
		i++;

	}

	/*//empty the stack   清空栈
	 while (!stack2.empty())
	 stack2.pop();*/

}

#endif /* PRETOPOST_H_ */
