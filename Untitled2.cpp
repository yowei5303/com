#include <stdio.h> 
#include <stdlib.h> 
#include <stack>
#include <iostream>
#include <string.h>
#include <strstream>
#include <cmath>
#define MAX 80
//��
using namespace std;
void inToPostfix(char*, char*); // �������� 
int priority(char); // �B��l�u���v
double todouble(string);
bool error;
int count=0;
int main(void) { 
    char infix[MAX] = {'\0'}; 
    char postfix[MAX]= {'\0'}; 

    printf("���ǹB�⦡�G"); 
    scanf("%s", infix);
    inToPostfix(infix, postfix);
    
    std::stack<double> num;
    std::string s="";
    double date=0;
    double a;
    for(int i=0;i<strlen(postfix);i++)
    {
    	cout << postfix[i];
	}
	cout << endl<<"-----" << endl;
	for(int i=0;i<strlen(postfix);i++){
		switch(postfix[i]) { 
	        case '[':
				 s="";
				 break;        
	        case '+':
	        	a=num.top();
	        	num.pop();
	        	date=num.top()+a;
	        	num.pop();
	        	num.push(date);
	        	break;
			case '-':
				a=num.top();
	        	num.pop();
	        	date=num.top()-a;
	        	num.pop();
	        	num.push(date);
	        	break;
			case '*':
			 	a=num.top();
	        	num.pop();
	        	date=num.top()*a;
	        	num.pop();
	        	num.push(date);
	        	break;
			case '/':
			 	a=num.top();
	        	num.pop();
	        	if(a==0) error=0;
	        	date=num.top()/a;
	        	num.pop();
	        	num.push(date);
	        	break;
	        case '^':
	        	a=num.top();
	        	num.pop();
	        	date=pow(num.top(),a);
	        	num.pop();
	        	num.push(date);
	        	break;
	        case ']':
	        	if(!s.empty())
	        	{
					cout << "?" << s << endl;
					num.push(todouble(s));
				}
				s="";
				break;
	        default:
	        		s+=postfix[i];
	        		break;	
		}
		if(!num.empty())
		{
			cout << endl << "----------" << endl;
			cout << "<" << date << ">" << endl;	
			cout << "( " << num.top() << endl;
			cout << "-----------" << endl;
		}
		
    
	}
	if(!error) cout<<"N/A";
	else cout<<date;
	return 0; 
}

bool F;
void inToPostfix(char* infix, char* postfix) { 
    char stack[MAX] = {'\0'};
    int i, j, top;
    for(i = 0, j = 0, top = 0; infix[i] != '\0'; i++) switch(infix[i]) { 
        case '(':              // �B��l���| 
        	if(F==true)
        	{
        		postfix[j++]=']';
        		F=false;
			}
            stack[++top] = infix[i]; 
            break; 
        case '+': case '-': case '*': case '/':case '^': 
        	if(F==true)
        	{
        		postfix[j++]=']';
        		F=false;
			}
            while(priority(stack[top]) >= priority(infix[i])) { 
                postfix[j++] = stack[top--];
            } 
            stack[++top] = infix[i]; // �s�J���| 
            break; 
        case ')': 
        	if(F==true)
        	{
        		postfix[j++]=']';
        		F=false;
			}
            while(stack[top] != '(') { // �J ) ��X�� ( 
                postfix[j++] = stack[top--];
                if(top==0) error=0;
            } 
            top--;  // ����X ( 
            break; 
        default:  // �B�⤸������X
        	if(F==false)
        	{
        		postfix[j++]='[';
        		F=true;
			}
            postfix[j++] = infix[i];
            
    }
    if(F==true)
    {
    	postfix[j++]=']';
        F=false;
	}
    while(top > 0) {
		if(stack[top]=='(') error=0;
        postfix[j++] = stack[top--];
    }
} 

int priority(char op) { 
    switch(op) { 
        case '+': case '-': return 1;
        case '*': case '/': case '^': return 2;
        default:            return 0;
    } 
} 
double todouble(string a){
	double val;
    std::strstream ss;
    ss << a;
    ss >> val;
    return val;
}

