/*Implement Heap sort to sort given set of values using max heap. */

#include<iostream>
#define MAX 10
using namespace std;

class heapsort
{
    int heap[MAX], n;

    public:
    heapsort()  //constructor
    {
        n = 0;
    }

    //accept the no. of elements and the elements
    void accept()
    {
        cout << "Enter the no. of elements: ";
        cin >> n;
        cout << "Enter the integer elements: \n";
        for(int i=0; i<n; i++)
            cin >> heap[i];
    }

    //Display the elements
    void display()
    {
        for(int i=0; i<n; i++)
            cout << heap[i] << "\t" ;
        cout << "\n";
    }

    void heapify(int root, int n) //root of subtree and no.of elements to be sorted
    {
        int largest = root;   // Initialize largest as root
        int l = 2 * root + 1; // left = 2*i + 1
        int r = 2 * root + 2; // right = 2*i + 2

        // If left child is larger than root
        if (l < n && heap[l] > heap[largest])
            largest = l;

        // If right child is larger than largest so far
        if (r < n && heap[r] > heap[largest])
            largest = r;

        // If largest is not root, swap root and largest
        if (largest != root)
        {
            int temp = heap[root];
            heap[root] = heap[largest];
            heap[largest] = temp;

            // Recursively heapify the affected sub-tree
            heapify(largest, n);
        }
    }

    void sorting()
    {
        int i, temp;
        //Building heap staring from the last non-leaf
        for(i=n/2-1; i>=0; i--)
            heapify(i,n);

        //delete the root node and again heapify
        for(i=n-1; i>0; i--)
        {
            temp = heap[i];   //swap first and last value of unsorted elements
            heap[i] = heap[0];
            heap[0] = temp;
            heapify(0,i);
        }
    }
};

int main()
{
    heapsort h;
    h.accept();
    h.sorting();
    cout << "Sorted List is: \n";
    h.display();
    return 0;
}


