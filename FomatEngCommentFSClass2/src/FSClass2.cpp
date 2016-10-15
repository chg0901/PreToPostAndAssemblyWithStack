// assignment number : 1
// Name       : Hong Cheng
// StudentID    : 2016160602
// Due :29/9/16

// program description :

// 1. summary :
//		  In this program , a machine is designed with two register and five instructions ,
//       when the accepted prefix expression that is read from the file named 'mp1.in'
//		  will be converted into intermediate postfix expression. Then based on the postfix
//		  expressions ,the machine will produce sequences of machine instructions.In the end
//		  all of the results will be written into the output text file named 'mp1.out'.

// 2. explanation of class used in program :
//			    MyStack
//		It is a template class , and this class defines the main data structure used in the program.
//     As showed from the class name , it is a Stack with the essential functions to push and
//		pop data such as void push(ElemType x) ,ElemType pop() and so on.





#include <iostream>
#include <fstream>
#include "MyStack.h"
#include "PreToPost.h"

using namespace std;

/*
 *   argument :
 *   return :
 *   action :
 */
int main() {
	MyStack<int> stack;
	stack.init();
	int n = 0; //Returns the length of the postfix expression   返回后缀表达式的长度
	int m = 0;
	char buffer[80];

	ifstream readFile; //Declare the file stream, but  not bind the file 声明文件流，但没有绑定文件
	readFile.open("mp1.in", ios::in); //Read the file in read-only mode 以只读形式读取文件

	if (!readFile) {
		cerr << "open the mp1.in file wrong" << endl;
		return 0;
	}
	ofstream writeFile; //Declare the file stream, but  not bind the file 声明文件流，但没有绑定文件

	writeFile.open("mp1.out", ios::trunc);
	//ios::trunc indicates that the make the file empty before you open the file, if the file does not exist, then the file is created.
	//ios::trunc表示在打开文件前将文件清空再写入,文件不存在则创建
	//ios::app "append",it indicates that the content is not covered by the original content, but is appended to the file.
	//ios::app 表示写入的内容不会覆盖原文内容，而是追加到文件后面
	//ios::in Read the file in read-only mode 表示以只读的方式读取文件

	while (!readFile.eof()) {	//Get rid of spaces, not branches.去掉空格，不能分行
		readFile.getline(buffer, 80, '\n'); //getline(char *,int,char) Indicates that the line  ends when it  reaches 256 characters or there is a line break.
											 //getline(char *,int,char)表示该行字符达到256个或遇到换行就结束
		if (buffer[0] == '\0') {	//Skips when a row is read empty当读入一行为空时，跳过
			continue;
		}
		cout
				<< "---------------------------------------------------------------------------------------------\n";
		writeFile
				<< "---------------------------------------------------------------------------------------------\n";
		cout << buffer;
		writeFile << buffer;
		cout << "=>";
		writeFile << "=>";

		char *post = new char[80];
		postfix(buffer, post, n);

		for (int i = 0; i < n; i++) {
			if (post[i] == '#') {
				writeFile << '\n';
				break;
			}
			cout << post[i];
			writeFile << post[i];

		}
		cout
				<< "\n---------------------------------------------------------------------------------------------";
		writeFile
				<< "---------------------------------------------------------------------------------------------\n";

		n = 0; //To prevent the last formula is so long that it has a bad influence on the output.
			   //防止上一个公式太长，n较大，影响输出

		//The stack should also be emptied.   应该对stack进行清空
		string *sAssemblyCode = new string[1000];
		postfix2(post, sAssemblyCode, m);
		delete[] post;			      // ok

		cout << endl;
		for (int i = 0; i < m; i++) {
			cout << sAssemblyCode[i];
			writeFile << sAssemblyCode[i];

		}
		delete[] sAssemblyCode;
		m = 0;
		cout
				<< "---------------------------------------------------------------------------------------------\n"
				<< endl;
		writeFile
				<< "---------------------------------------------------------------------------------------------\n"
				<< endl;

	}
	readFile.close(); //close the file
	writeFile.close();

	return 0;
}
