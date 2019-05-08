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
	//��ʾ
	/*for (auto str : lineVector)
		cout << str<<endl;*/

	string str;
	vector<string>::iterator it;
	for(it=lineVector.begin(); it != lineVector.end(); it++)
	{
		str = *it;
		if (str == "+" || str == "-" || str == "*" || str == "/" || str == "(" || str == ")")      //��Ϊ������
		{
			while (true)
			{
				if (opStack.empty() == true)
				{
					opStack.push(str[0]);
					cout << "��������ջ "<<str[0]<<" "<<endl;
					break;
				}
				else
				{
					if ( getPri(str[0]) > getPri(opStack.top()) || str[0] == '(' )   //����Ҫ����Ĳ����������ȼ���ջ�������������ȼ�Ҫ�ߣ������;
					{
						opStack.push(str[0]);
						cout << "��������ջ " << str[0] << " " << endl;
						break;
					}						
					else                                          //����ջ����������ջ�����м���;
					{
						char operation = opStack.top();
						opStack.pop();
						cout << "��������ջ " << operation << " " << endl;
						if (operation == '(')
							break;
						else
						{
							float opdataR = dataStack.top();  dataStack.pop();   cout << "��������ջ " << opdataR << " " << endl;
							float opdataL = dataStack.top();  dataStack.pop();   cout << "��������ջ " << opdataL << " " << endl;
							float opAnswer = calculate(opdataL, opdataR, operation);
							dataStack.push(opAnswer);    cout << "��������ջ " << opAnswer << " " << endl;
						}
					}
				}
			}			
		}
		else     //����Ϊ������;
		{
			dataStack.push(stof(str));     cout << "��������ջ " << stof(str) << " " << endl;
		}				
	}

	//���
	while (opStack.empty() == false)
	{
		char operation = opStack.top();     opStack.pop();      cout << "��������ջ " << operation << " " << endl;
		float opdataR = dataStack.top();  dataStack.pop();      cout << "��������ջ " << opdataR << " " << endl;
		float opdataL = dataStack.top();  dataStack.pop();      cout << "��������ջ " << opdataL << " " << endl;
		float opAnswer = calculate(opdataL, opdataR, operation);
		dataStack.push(opAnswer);                               cout << "��������ջ " << opAnswer << " " << endl;
	}

	//cout << "THe answer is " << dataStack.top() << ";" << endl;

	/*cout << "������ջ��" << endl;
	while (dataStack.empty() != true)
	{
		cout<<dataStack.top()<<" ";
		dataStack.pop();
	}

	cout <<endl<< "������ջ��" << endl;
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
		return 0;   //����ǼӼ�������0  
	case '*':  
	case '/':  
		return 1;   //����ǳ˳�������1  
	case '(':  
	case ')':  
		return -1;  //ע�⣬���ｫ������Ϊ������ȼ���������Ų��ᱻ��������������������  

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

