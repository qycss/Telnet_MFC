#include <iostream>
#include <stack> 
#include <vector>
#include <string>
using namespace std;


int getPri(char c);
float calculate(float opDataL,float opDataR, char operation);

float main2(string line)
{	
	stack<char> opStack;
	stack<float> dataStack;
	
	vector<string> lineVector;
	//getline(cin,line);

	while (line.size() > 0)
	{
		if (line[0] == '+' || line[0] == '-' || line[0] == '*' || line[0] == '/' || line[0] == '(' || line[0] == ')')
		{
			string str(1, line[0]);
			lineVector.push_back(str);
			line.erase(0, 1);
		}
		else
		{
			int i;
			for (i = 0; i < line.size(); i++)
			{
				if ((line[i] != '.') && (line[i]<'0' || line[i]>'9'))
					break;
			}
			lineVector.push_back(line.substr(0, i));
			line.erase(0, i);
		}
	}
	//显示
	/*for (auto str : lineVector)
		cout << str<<endl;*/

	string str;
	vector<string>::iterator it;
	for(it=lineVector.begin(); it != lineVector.end(); it++)
	{
		str = *it;
		if (str == "+" || str == "-" || str == "*" || str == "/" || str == "(" || str == ")")      //若为操作符
		{
			while (true)
			{
				if (opStack.empty() == true)
				{
					opStack.push(str[0]);
					cout << "操作符入栈 "<<str[0]<<" "<<endl;
					break;
				}
				else
				{
					if ( getPri(str[0]) > getPri(opStack.top()) || str[0] == '(' )   //若将要插入的操作符的优先级比栈顶操作符的优先级要高，则插入;
					{
						opStack.push(str[0]);
						cout << "操作符入栈 " << str[0] << " " << endl;
						break;
					}						
					else                                          //否则，栈顶操作符出栈，进行计算;
					{
						char operation = opStack.top();
						opStack.pop();
						cout << "操作符出栈 " << operation << " " << endl;
						if (operation == '(')
							break;
						else
						{
							float opdataR = dataStack.top();  dataStack.pop();   cout << "操作数出栈 " << opdataR << " " << endl;
							float opdataL = dataStack.top();  dataStack.pop();   cout << "操作数出栈 " << opdataL << " " << endl;
							float opAnswer = calculate(opdataL, opdataR, operation);
							dataStack.push(opAnswer);    cout << "操作数入栈 " << opAnswer << " " << endl;
						}
					}
				}
			}			
		}
		else     //否则为操作数;
		{
			dataStack.push(stof(str));     cout << "操作数入栈 " << stof(str) << " " << endl;
		}				
	}

	//清仓
	while (opStack.empty() == false)
	{
		char operation = opStack.top();     opStack.pop();      cout << "操作符出栈 " << operation << " " << endl;
		float opdataR = dataStack.top();  dataStack.pop();      cout << "操作数出栈 " << opdataR << " " << endl;
		float opdataL = dataStack.top();  dataStack.pop();      cout << "操作数出栈 " << opdataL << " " << endl;
		float opAnswer = calculate(opdataL, opdataR, operation);
		dataStack.push(opAnswer);                               cout << "操作数入栈 " << opAnswer << " " << endl;
	}

	//cout << "THe answer is " << dataStack.top() << ";" << endl;

	/*cout << "操作数栈：" << endl;
	while (dataStack.empty() != true)
	{
		cout<<dataStack.top()<<" ";
		dataStack.pop();
	}

	cout <<endl<< "操作符栈：" << endl;
	while (opStack.empty() != true)
	{
		cout << opStack.top() << " ";
		opStack.pop();
	}*/

	return dataStack.top();
}


int getPri(char c)   
{  
	switch(c)   
	{  
	case '+':  
	case '-':  
		return 0;   //如果是加减，返回0  
	case '*':  
	case '/':  
		return 1;   //如果是乘除，返回1  
	case '(':  
	case ')':  
		return -1;  //注意，这里将括号设为最低优先级，因此括号不会被弹出，除非遇到右括号  

	}  
}  

float calculate(float opDataL, float opDataR, char operation)
{
	switch (operation)
	{
	case '+': return opDataL + opDataR;
	case '-': return opDataL - opDataR;
	case '*': return opDataL * opDataR;
	case '/': return opDataL / opDataR;
	}

}

