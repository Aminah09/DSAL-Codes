
/*
Assignment 2.
Implement stack as an abstract data type using singly linked list
and use this ADT for conversion of infix expression to postfix,
prefix and evaluation of postfix and prefix expression.
*/

#include<iostream>
#include<math.h>
#include"stackh.h"

using namespace std;

class Conversion
{
    string expr, output;
    char *token;
public:
    Conversion()
    {
        token = NULL;
    }
    void getExpr();
    bool validExpr();
    void display();
    bool isOperator(char);
    int priority(char);
    bool IsAssoRL(char);
    void PostfixConversion();
    void PrefixConversion();
    void EvalPostfix();
    void EvalPrefix();
};

//Accept Infix Expression
void Conversion::getExpr()
{
    output="";
    cout << "\nEnter an Infix expression: ";
    cin >> expr;
}

//Display the Output Expression
void Conversion::display()
{
    cout << "OUTPUT: ";
    cout << output << endl;
}

//Checking for operator
bool Conversion::isOperator(char ch)
{
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' )
        return true;
    return false;
}

//Check if the entered infix expression is a valid expression
//no. of operators should be 1 less than no. of operands
//no. of opening and closing parenthesis should tally
bool Conversion::validExpr()
{
    int pcount=0, oper=0, operand=0, scount=0;
    for(token = &expr[0]; *token != '\0'; token++)
    {
        if(*token == '(')
            pcount++;
        else if(*token == ')')
            pcount--;
        else if(isOperator(*token))
            oper++;
        else if(isalnum(*token))   //isalpha() isdigit()
            operand++;
        //else
            //scount++;
    }
    if((pcount != 0) || (operand != oper+1))// || (scount != 0))
    {
        cout << "Invalid Expression. ";
        return false;
    }
    return true;
}

//Assign Priority to operators
int Conversion::priority(char oper)
{
    if(oper == '+' || oper == '-')
        return 1;
    else if(oper == '*' || oper == '/' || oper == '%')
        return 2;
    else if(oper == '^')
        return 3;
    return 0;
}


//Check for right to left associativity
bool Conversion::IsAssoRL(char oper)
{
    if(oper == '^')
        return true;
    return false;
}


//Convert infix expression to postfix expression
void Conversion::PostfixConversion()
{
    ClassStack <char> s;
    for(token = &expr[0]; *token != '\0'; token++)
    {
        if(isalnum(*token))
            output += *token;
        else if(*token == '(')
           s.Push(*token);
        else if(*token == ')')
        {
            while(s.StackTop() != '(')
                output += s.Pop();
            s.Pop();
        }
        else if(isOperator(*token))
        {
            while(!s.IsEmpty() && priority(*token) <= priority(s.StackTop()))
            {
                if(priority(*token) == priority(s.StackTop())&& IsAssoRL(*token))
                    break;
                output +=s.Pop();
            }
            s.Push(*token);
        }
    }
    while(!s.IsEmpty())
        output +=s.Pop();
}

//Convert infix expression to prefix expression
void Conversion::PrefixConversion()
{
    ClassStack <char> s;
    int cnt=0;
    string tempres;
    for(token = &expr[0]; *token != '\0'; token++, cnt++);
    token--;
    for(token = &expr[cnt]; cnt>=0; cnt--,token--)
    //while(cnt > 0)
    {
        if(isalnum(*token))
            tempres += *token;
        else if(*token == ')')
           s.Push(*token);
        else if(*token == '(')
        {
            while(s.StackTop() != ')')
                tempres += s.Pop();
            s.Pop();
        }
        else if(isOperator(*token))
        {
            while(!s.IsEmpty() && priority(*token) <= priority(s.StackTop()))
            {
                if(priority(*token) == priority(s.StackTop()) && IsAssoRL(*token))
                    tempres +=s.Pop();
                else if(priority(*token) < priority(s.StackTop()))
                    tempres +=s.Pop();
                else
                    break;
            }
            s.Push(*token);
        }
        //cnt--;
        //token--;
    }
    while(!s.IsEmpty())
        tempres +=s.Pop();
    for(token = &tempres[0]; *token != '\0'; token++)
        s.Push(*token);
    while(!s.IsEmpty())
        output += s.Pop();
}


//Calculator
int claculate(int op1, char oper, int op2)
{
    switch(oper)
    {
        case '+': return(op1+op2); //break;
        case '-': return(op1-op2); //break;
        case '*': return(op1*op2); //break;
        case '/': return(op1/op2); //break;
        case '^': return(pow(op1, op2)); //break;
    }
}

//Evaluate Postfix expression
void Conversion::EvalPostfix()
{
    ClassStack <int> s;
    int res=0, op1, op2;
    for(token = &output[0]; *token != '\0'; token++)
    {
        if(isalpha(*token))
        {
            cout << "Enter the value of " << *token << ": ";
            cin >> op1;
            s.Push(op1);
        }
        else if(isdigit(*token))
            s.Push(*token-48);
        else if(isOperator(*token))
        {
            op2 = s.Pop();
            op1 = s.Pop();
            res = claculate(op1, *token, op2);
            s.Push(res);
        }
    }
    res = s.Pop();
    cout << "Evaluated value is : "<< res << endl;
}


////Evaluate Prefix expression
void Conversion::EvalPrefix()
{
    ClassStack <int> s;
    int res=0, op1, op2, cnt=0;
    for(token = &output[0]; *token != '\0'; token++, cnt++);
    token--;
    while(cnt > 0)
    {
        if(isalpha(*token))
        {
            cout << "Enter the value of " << *token << ": ";
            cin >> op1;
            s.Push(op1);
        }
        else if(isdigit(*token))
            s.Push(*token-48);
        else if(isOperator(*token))
        {
            op1 = s.Pop();
            op2 = s.Pop();
            res = claculate(op1, *token, op2);
            s.Push(res);
        }
        cnt--;
        token--;
    }
    res = s.Pop();
    cout << "Evaluated value is : "<< res << endl;
}

int main()
{
    Conversion e, p;
    bool res;
    int ch;

   do
    {   cout<< "\n\nConversions\n";
        cout << "1. Infix to Postfix Conversion\n";
        cout << "2. Infix to Prefix Conversion\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;
        switch(ch)
        {
            case 1: do
                    {
                        e.getExpr();
                        res=e.validExpr();
                    }while(res == 0);
                    e.PostfixConversion();
                    e.display();
                    e.EvalPostfix();
                    break;
            case 2:do
                    {
                        p.getExpr();
                        res=p.validExpr();
                    }while(res == 0);
                    p.PrefixConversion();
                    p.display();
                    p.EvalPrefix();
                    break;

            case 3:
                    return 0;
        }
    }while(ch != 3);
}
