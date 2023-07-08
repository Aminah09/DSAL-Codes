/*Assignment 3
Implement Circular Queue using Array. Perform following operations on it.
a) Insertion (Enqueue) b) Deletion (Dequeue) c) Display
*/

#include<iostream>
#define MAX 5
using namespace std;

class CQ_array
{
    int CQ[MAX], f, r;
public:
    CQ_array()
    {
        f = r = -1;
    }

    bool queueEmpty()
    {
        return(f==-1 && r==-1);
    }

    bool queueFull()
    {
        return((r+1)%MAX == f);
    }

    int queueFront()
    {
        cout << "Front Index = " << f << endl;
        return CQ[f];
    }

    int queueRear()
    {
        cout << "Rear Index = " << r << endl;
        return CQ[r];
    }

    bool enqueue(int data)
    {
        if(!queueFull())
        {
            if(f==-1) // 1st element
                f++;
            r = (r+1)%MAX;
            CQ[r] = data;
            return 1;
        }
        return 0;
    }

    int dequeue()
    {
        if(!queueEmpty())
        {
            int data = CQ[f];
            f = (f+1)% MAX;
            if(f == ((r+1)%MAX))
                f = r = -1;
            return data;
        }
        return -1;
    }

    void display()
    {
        if(queueEmpty())
            cout << "Queue is Empty!!\n";
        else
        {
            cout << "Elements are: ";
            if(r>=f)
                for(int i=f; i<=r; i++)
                    cout << CQ[i] << " ";
            else
            {
                for(int i=f; i!=r; i=(i+1)%MAX)
                    cout << CQ[i] << " ";
                cout << CQ[r] << " ";
            }
        }

    }
};

int main()
{
    int ch, data;
    CQ_array q;
    bool res;
    do
    {
        cout << "Circular Queue Operations\n";
        cout << "1. Insert (Enqueue)\n";
        cout << "2. Delete (Dequeue)\n";
        cout << "3. Queue Full\n";
        cout << "4. Queue Empty\n";
        cout << "5. Queue Front (1st element)\n";
        cout << "6. Queue Rear (last element)\n";
        cout << "7. Display Queue elements\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;
        switch(ch)
        {
            case 1: cout << "Enter the data: ";
                    cin >> data;
                    res = q.enqueue(data);
                    if(res == 1)
                        cout << "Data Stored in the Queue\n";
                    else
                        cout << "Queue is Full!!\n";
            break;
            case 2: if(q.queueEmpty())
                        cout << "Queue is Empty!!\n";
                    else
                    {
                        data = q.dequeue();
                        cout << "The element deleted is: " << data << endl;
                    }
            break;
            case 3: if(q.queueFull())
                        cout << "Queue is Full!!\n";
                    else
                        cout << "Queue is Not Full!!\n";
            break;
            case 4: if(q.queueEmpty())
                        cout << "Queue is Empty!!\n";
                    else
                        cout << "Queue is Not Empty!!\n";
            break;
            case 5: if(!q.queueEmpty())
                    {
                        data = q.queueFront();
                        cout << "1st Element is: " << data << endl;
                    }
                    else
                        cout << "Queue is Empty!!\n";
            break;
            case 6: if(!q.queueEmpty())
                    {
                        data = q.queueRear();
                        cout << "Last Element is: " << data << endl;
                    }
                    else
                        cout << "Queue is Empty!!\n";
            break;
            case 7: if(!q.queueEmpty())
                        q.display();
            break;
            case 8: return 0;
       }
    }while(ch!=8);
}
