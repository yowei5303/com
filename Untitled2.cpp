#include <stdio.h> 
#include <stdlib.h> 
#include <stack>
#include <iostream>
#include <string.h>
#include <strstream>
#include <cmath>
#define MAX 80
//考
using namespace std;
void inToPostfix(char*, char*); // 中序轉後序 
int priority(char); // 運算子優先權
double todouble(string);
bool error;
int count=0;
int main(void) { 
    char infix[MAX] = {'\0'}; 
    char postfix[MAX]= {'\0'}; 

    printf("中序運算式："); 
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
        case '(':              // 運算子堆疊 
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
            stack[++top] = infix[i]; // 存入堆疊 
            break; 
        case ')': 
        	if(F==true)
        	{
        		postfix[j++]=']';
        		F=false;
			}
            while(stack[top] != '(') { // 遇 ) 輸出至 ( 
                postfix[j++] = stack[top--];
                if(top==0) error=0;
            } 
            top--;  // 不輸出 ( 
            break; 
        default:  // 運算元直接輸出
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

