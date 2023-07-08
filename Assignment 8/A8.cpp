/*Represent a graph of city using adjacency matrix.
Nodes should represent the various landmarks and links should represent
the distance between them. Find the shortest path using
Dijkstra's algorithm from single source to all destination. */


#include<iostream>
#define inf 9999
#define MAX 10
using namespace std;

struct node
{
	int ver_no;  //vertex no
	bool known;  //vertex is known or not
	int dv;      //distance from source vertex
	int pv;      //previous vertex
};


class dijkstra
{
	int cost[MAX][MAX]; //Adjacency Matrix
	struct node t[MAX]; //table
	int mini,source,numv,cnt,weight;
	void display(int [MAX][MAX]);
	void display_table();

	public:
	void accept();
	void dijkstra_algo();
	void path();
};

void dijkstra::accept()
{
	char ans;
	int i, j;
	cout << "\nEnter the number of vertices : ";
	cin >> numv;

	//initialize all the entries in the adjacency matrix to infinity
	for(i=0;i<=numv;i++)
		for(j=0;j<=numv;j++)
			cost[i][j] = inf;


    //accept and set the weight for the edges in the graph
	cout<<"\nEnter the weight to connect different pairs of vertices\n";
	for(i=0;i<numv;i++)
	{
		for(j=i+1;j<numv;j++)
		{
			cout << "Is there an edge between vertex " << i << " and vertex " << j << " ?(y/n) : ";
			cin >> ans;
			if(ans == 'y' || ans =='Y')
			{
				cout << "Enter the weight: ";
				cin >> weight;
				cost[i][j] = weight;
				cost[j][i] = weight;
			}
		}
	}
	cout<<"\nThe cost matrix is \n";
	display(cost);
}

void dijkstra::display(int a[MAX][MAX])
{
	int i, j;
	//display the column vertices
	for(i=0;i<numv;i++)
		cout<<"\t"<< i;
	cout<<"\n";

	//in each row display the vertex and the weights for it
	for(i=0;i<numv;i++)
	{
		cout << i;
		for(j=0;j<numv;j++)
		{
			cout<<"\t"<<a[i][j];
		}
		cout<<"\n";
	}
}

void dijkstra:: display_table()
{
	int i;
	cout<<"\nVERTEX\tDV\tKNOWN\tPV\n";
	for(i=0;i<numv;i++)
	{
		cout<<t[i].ver_no<<"\t"<<t[i].dv<<"\t"<<t[i].known<<"\t"<<t[i].pv;
		cout<<"\n";
	}
}

void dijkstra::dijkstra_algo()
{
	int i,j,nextnode, total=0;
	for(i=0;i<numv;i++)  //initalize the values of the table
	{
		t[i].pv=-1;
		t[i].ver_no=i;
		t[i].known=false;
		t[i].dv=inf;
	}
	cout << "\nInitially the table is:\n";
	display_table();
	cout << "\nEnter the source vertex\n";
	cin >> source;
	while(source < 0 || source >= numv) //check for valid source
	{
		cout << "\nSorry!!Wrong source\nPlease re-enter the correct one\n";
		cin >> source;
	}

	for(i=0;i<numv;i++)
	{

		if(cost[source][i] != 9999) //update values of adjacent nodes of source in table
		{
			t[i].pv = source;
			t[i].ver_no = i;
			t[i].known = false;
			t[i].dv = cost[source][i];
		}
	}

	t[source].pv = source;	//update values of source node in table
	t[source].known = true;
	t[source].dv = 0;
	display_table();

	cnt=1;
	while(cnt < numv)
	{
		mini = inf;
		for(i=0;i<numv;i++)   //find an unknown node with smallest weight
		{
			if(!t[i].known && t[i].dv < mini)
			{
				mini = t[i].dv;
				nextnode = i;
			}
		}
		t[nextnode].known = true; //mark it as known

		for(i=0;i<numv;i++)	//update values in table after new node is known
		{
			if(!t[i].known)
			{
				if(mini+cost[nextnode][i] < t[i].dv)
				{
				    //a better path exists to node i thru node nextnode, update
					t[i].dv = mini+cost[nextnode][i];
					t[i].pv = nextnode;
				}
			}
		}
		cnt++;
		display_table();
	}
}

void dijkstra::path()
{
	int i, j;
	char onode[15], prevnode[15];
	for(i=0;i<numv;i++)  //Print the path and distance for each node
	{
		if(i != source)     //for all nodes except source
		{
			cout << "\nDistance of " << i << " from " << source << " = " << t[i].dv;
			cout << "\nPath is : " << i;
			j=i;
			do           //print the predecessor node
			{
				j = t[j].pv;
				cout << " <- " << j;
			}
			while(j !=source);
			cout << "\n";
		}
	}
}


int main()
{
	dijkstra d;
	d.accept();
	d.dijkstra_algo();
	d.path();
	return(0);
}
