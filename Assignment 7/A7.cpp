/*ASSIGNMENT # 7
Represent a graph of your college campus using adjacency list /adjacency matrix.
Nodes should represent the various departments/institutes and
links should represent the distance between them.
Find minimum spanning tree using Prims’s algorithm.
*/

#include<iostream>
#define inf 9999 //assuming that the edges will not have weights greater than 9999
#define MAX 10
using namespace std;

struct node
{
	int dv;
	int pv;
	int ver_no;
	bool known;
};

class prims
{
	int cost[MAX][MAX], span[MAX][MAX];
	struct node t[MAX];
	int mini,source,numv,cnt,k,weight;
	void display(int[MAX][MAX]);
	void display_table();
	void spanning();
	public:
	void accept();
	void prims_algo();
};

void prims::accept()
{
	char ans;
	int i, j;
	cout<<"\nEnter the number of vertices : ";
	cin >> numv;

	for(i=0;i<=numv;i++)
		for(j=0;j<=numv;j++)
			cost[i][j] = inf;

	cout<<"\nEnter the edges \n";
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

void prims::display(int a[MAX][MAX])
{
	int i, j;
	for(i=0;i<numv;i++)
		cout<<"\t"<< i;
	cout<<"\n";

	for(i=0;i<numv;i++)
	{
		cout<< i;
		for(j=0;j<numv;j++)
		{
			cout<<"\t"<< a[i][j];
		}
		cout<<"\n";
	}
}

void prims:: display_table()
{
	int i;
	cout<<"\nVERTEX\tDV\tKNOWN\tPV\n";
	for(i=0;i<numv;i++)
	{
		cout<< t[i].ver_no<<"\t"<<t[i].dv<<"\t"<<t[i].known<<"\t"<<t[i].pv;
		cout<<"\n";
	}
}

void prims::prims_algo()
{
	int i,j, total=0;
	for(i=0;i<numv;i++)  //initalize the values
	{
		t[i].pv=-1;
		t[i].ver_no=i;
		t[i].known=false;
		t[i].dv=inf;
	}
	cout<<"\nInitially the table is:\n";
	display_table();
	cout<<"\nEnter the source vertex\n";
	cin>>source;
	while(source < 0 || source >= numv)
	{
		cout<<"\nSorry!!Wrong source\nPlease re-enter the correct one\n";
		cin >> source;
	}
	for(i=0;i<numv;i++)
	{
		if(cost[source][i] != 9999) //update values of adjacent nodes of source in table
		{
			t[i].pv=source;
			t[i].ver_no=i;
			t[i].known=false;
			t[i].dv=cost[source][i];
		}
	}

	t[source].pv=source;	//update values of source node in table
	t[source].known=true;
	t[source].dv=0;
	display_table();
	cnt=1;
	while(cnt<numv)
	{
		mini=inf;
		for(i=0;i<numv;i++)   // find the next mini distance
		{
			if(!t[i].known && t[i].dv<mini)
			{
				mini=t[i].dv;
				k=i;
			}
		}
		t[k].known=true;
		for(i=0;i<numv;i++)	//update values in table after new node is known
		{			// check if a better path exists
			if(!t[i].known)
			{
				if(cost[k][i]<t[i].dv)
				{
					t[i].dv=cost[k][i];
					t[i].pv=k;
				}
			}
		}
		cnt++;
		display_table();
	}
	spanning();
}

void prims::spanning()
{
	int i, j, l, m, total=0, value;
	for(i=0;i<numv;i++)	//initialize the 2D array to 0
		for(j=0;j<numv;j++)
			span[i][j]=0;
	for(i=0;i<numv;i++)//store the weight of the edge included in the spanning tree from the table
	{
		for(j=0;j<numv;j++)
		{
			l=t[i].ver_no;
			m=t[i].pv;
			value=t[i].dv;
			span[l][m]=value;
			span[m][l]=value;
		}
		total=total+span[l][m];//calculate total minimum cost of edges included in MST
	}
	cout << "Minimum cost of the MST is "<< total <<"\n";
	cout<<"Spanning graph is : \n";
	display(span);
}

int main()
{
	prims p;
	p.accept();
	p.prims_algo();
	return(0);
}
