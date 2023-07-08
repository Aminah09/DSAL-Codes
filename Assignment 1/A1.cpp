/*Assignment 1
Consider a student database of SEIT class (at least 15 records). Database contains
different fields of every student like Roll No, Name and SGPA.(array of structure)
a) Design a roll call list, arrange list of students according to roll numbers
in ascending order (Use Bubble Sort)
b) Arrange list of students alphabetically. (Use Insertion sort)
c) Arrange list of students to find out first ten toppers from a class.
(Use Quick sort)
d) Search students according to SGPA(Linear Search). If more than one student having same SGPA,
then print list of all students having same SGPA.
e) Search a particular student according to name using binary search. */


#include<iostream>
#include<string>
#define MAX 5

using namespace std;

//defining a class
class student
{
    struct stud_data
    {
        int roll_no;
        string name;
        float sgpa;
    }stud[MAX];
     int n;    //no.of students
public:
    void accept()
    {
        cout << "How many students? ";
        cin >> n;
        cout << "Enter the data\n";
        for(int i=0; i<n; i++)
        {
            cout << "Enter the Roll No.: ";
            cin >> stud[i].roll_no;
            cout << "Enter the name: ";
            cin.ignore();
            getline(cin, stud[i].name);
            cout << "Enter the SGPA: ";
            cin >> stud[i].sgpa;
        }
    }

    void display()
    {
        cout << "Roll No.  Name\t SGPA\n";
        for(int i=0;i<n;i++)
        {
            cout << stud[i].roll_no << "\t" << stud[i].name << "\t" << stud[i].sgpa << endl;
        }
    }

    void bubble_sort()
    {
        for(int pass=1; pass<n; pass++)
        {
            int swapped=0;
            for(int i=0; i<=n-1-pass; i++)
            {
                if(stud[i].roll_no > stud[i+1].roll_no)
                {
                    stud_data tmp = stud[i];
                    stud[i] = stud[i+1];
                    stud[i+1] = tmp;
                    swapped++;
                }
            }
            if(swapped == 0)
                break;
        }
        cout << "Records Sorted by Roll No. using Bubble Sort:\n";
        display();
    }

    void insertion_sort()
    {
        for(int pass=1; pass<n; pass++)
        {
            stud_data s = stud[pass];
            string ele = stud[pass].name;
            int i=pass-1;
            while ((i>=0) && (stud[i].name > ele))
            {
                stud[i+1] = stud[i];
                i--;
            }
            stud[i+1] = s;
        }
        cout<<"Records sorted by Name using Insertion Sort:\n";
        display() ;
    }

    void linear_search(float key)
    {
        int sr=0;
       for(int i=0; i<n; i++)
       {
           if(stud[i].sgpa == key)
           {
               cout << i+1 <<"\t"<< stud[i].roll_no <<"\t" << stud[i].name << "\t"<< stud[i].sgpa <<endl;
               sr++;
           }

       }
       if(sr == 0)
        cout << "Invalid Search\n";
    }

    int part(int l, int h)
    {
        int i, j;
        float pivot;
        stud_data temp;

        pivot = stud[l].sgpa;
        i=l+1;
        j=h;
        while(i<=j)
        {
            while(stud[i].sgpa >=pivot)
                i++;
            while(stud[j].sgpa < pivot)
                j--;
            if(i<=j)
            {
                temp = stud[i];
                stud[i] = stud[j];
                stud[j] = temp;
                i++;
                j--;
            }
        }
        temp = stud[j];
        stud[j] = stud[l];
        stud[l] = temp;
        return(j);
    }

    void quicksort(int l, int h)
    {
        int p;
        if(l < h)
        {
            p = part(l,h);
            quicksort(l, p-1);
            quicksort(p+1, h);
        }
    }

    void quick()
    {
        quicksort(0,n-1);
        cout << "R.No <<\t<< Name << << SGPA" << endl;
        for(int i=0; i<3;i++)
            cout << stud[i].roll_no << "\t" << stud[i].name << "\t" << stud[i].sgpa << endl;
    }

    int bin_search(string key)
    {
        int mid, lb=0, ub=n-1;
        while(lb <= ub)
        {
            mid = (lb + ub) /2;
            if(stud[mid].name == key)
            {
                cout << "Record Found at index " << mid << "\n";
                cout << mid+1 << "\t" << stud[mid].roll_no << "\t" << stud[mid].name << "\t" << stud[mid].sgpa << endl;
                return mid;
            }

            else if (stud[mid].name > key)
                ub = mid-1;
            else
                lb = mid+1;
        }
        return -1;
    }
};

int main()
{
    int ch, index;
    student s;
    float sg;
    string key;

    do
    {
        cout << "Operations on Database\n";
        cout << "1.Accept Data\n";
        cout << "2.Display Data\n";
        cout << "3.Sort by Roll No. (Bubble Sort)\n";
        cout << "4.Sort alphabetically (Insertion sort)\n";
        cout << "5.First 3 Toppers\n";
        cout << "6.Search by SGPA (Linear Search)\n";
        cout << "7.Search by Name (Binary Search)\n";
        cout << "8.Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;
        switch(ch)
        {
            case 1: s.accept();
            break;

            case 2: s.display();
            break;

            case 3: s.bubble_sort();
            break;

            case 4: s.insertion_sort();
            break;

            case 5: s.quick();
            break;

            case 6: cout << "Enter the SGPA: ";
                    cin >> sg;
                    s.linear_search(sg);
                    break;

            case 7: cout << "Enter Name: ";
                    cin.ignore();
                    getline(cin, key);
                    s.insertion_sort();
                    index = s.bin_search(key);
                    if(index == -1)
                        cout << "Record Not Found\n";
            break;

            case 8: return(0);

            default: cout <<"Wrong Choice\n";


        }
    }while(ch !=8);
}
