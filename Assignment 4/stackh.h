#include<iostream>
using namespace std;

template <typename T>
struct StructStack
{
    T Data;
    StructStack *Next;
};

template <typename T>
class ClassStack
{
    StructStack<T> *Top;
public:
    ClassStack();
    bool IsFull();
    bool IsEmpty();
    bool Push(T);
    T Pop();
    T StackTop();
    ~ClassStack();
};

template <typename T>
ClassStack<T>::ClassStack()
{
    Top=NULL;
}

template <typename T>
bool ClassStack<T>::IsFull()
{
    StructStack<T> *Temp;
    Temp = new StructStack<T>;
    if(Temp == NULL)
        return true;
    else
    {
        delete Temp;
        return false;
    }
}

template <typename T>
bool ClassStack<T>::IsEmpty()
{
    if(Top == NULL) // return(Top == NULL);
        return true;
    else
        return false;
}

template <typename T>
bool ClassStack<T>::Push(T data)
{
    if(IsFull())
        return false;
    else
    {
        StructStack<T> *Temp;
        Temp = new StructStack<T>;
        Temp->Data = data;
        Temp->Next = Top;
        Top = Temp;
        return true;
    }

}

template <typename T>
T ClassStack<T>::Pop()
{
    if(IsEmpty())
        return NULL;
    else
    {
        T data;
        StructStack<T> *Temp;
        Temp = Top;
        data = Temp->Data;
        Top = Top->Next;
        delete Temp;
        return data;
    }
}

template <typename T>
T ClassStack<T>::StackTop()
{
    if(IsEmpty())
        return -1;
    else
        return(Top->Data);
}

template <typename T>
ClassStack<T>::~ClassStack()
{
    while(Top != NULL)
    {
        StructStack<T> *Temp;
        Temp = Top;
        Top = Top->Next;
        delete Temp;
    }
}
