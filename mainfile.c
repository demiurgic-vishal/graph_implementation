
#include<stdio.h>
#include<stdlib.h>
#include<time.h>


#define V 7	



int** createGraph()
{
	int i;

	int **a;
	a = (int**)malloc(V*sizeof(int*) );
	for(i=0;i<V;i++)
		a[i] = (int*)calloc(V, sizeof(int));

	int num1,num2, weight;
		
	FILE *f1;
	f1=fopen("input1", "r");	
	
	while( !feof(f1) )
	{
		fscanf(f1," %d %d %d", &num1, &num2, &weight);
		a[num1-1][num2-1] =weight;
		a[num2-1][num1-1] =weight;		
		
	}
	fclose(f1);	

	return 	a;
	
}

// createdigraph.h
int** createDiGraph()
{
	int i;

	int **a;
	a = (int**)malloc(V*sizeof(int*) );
	for(i=0;i<V;i++)
		a[i] = (int*)calloc(V, sizeof(int));

	int num1,num2, weight;
		
	FILE *f1;
	f1=fopen("input1", "r");
	
	while( !feof(f1) )
	{
		fscanf(f1," %d %d %d", &num1, &num2, &weight);
		a[num1-1][num2-1] =weight;
				
		
	}
	fclose(f1);

	return 	a;	
}
//create_random_graph.h
int** createRandom_graph()
{
	int i,j;
	
	srand(time(NULL));
	
	int **a;
	a = (int**)malloc(V*sizeof(int*) );
	for(i=0;i<V;i++)
		a[i] = (int*)calloc(V, sizeof(int));
	
	for(i=0;i<V;i++)
		for(j=i;j<V;j++)
		{	
			if(rand()%100 > 90 && j!=i )			
				a[i][j] = rand()%20;
			else a[i][j]=0;
			
			a[j][i] = a[i][j];
		}
	
 	return a;
}
//create randomdigraph.h
int** createRandom_digraph()
{
	int i,j;
	
	srand(time(NULL));
	
	int **a;
	a = (int**)malloc(V*sizeof(int*) );
	for(i=0;i<V;i++)
		a[i] = (int*)calloc(V, sizeof(int));
	
	for(i=0;i<V;i++)
		for(j=0;j<V;j++)
		{	
			if(rand()%100 > 70 && i!=j)			
				a[i][j] = rand()%20;
			else a[i][j]=0;
		}
	
 	return a;
}

//create bfs.h
////////////////////Queue using array/////////////////////////////////////////////
int front2 =-1, rear2=-1, queue2[V];

void enq2(int n)
{
	rear2++;
	queue2[rear2]=n;
}

int deq2( )
{
	if(front2>= rear2)
		return -1;

	front2++;
	return queue2[front2];
}
///////////////////////////////////////////////////////////////////////
void visitnode(int i, int visited[])
{
	visited[i]=1;
	printf("%d ", i+1);
}


void BFS(int **a , int start)
{
	int i,j;

	int visited[V]={0};
	
	visitnode(start, visited);
	enq2(start);
	
	while( front2<rear2 )
	{
		i= deq2();
		for(j=0;j<V;j++)
		{
			if(!a[i][j] ||  visited[j] )
				continue;
			
			visitnode(j, visited);
			enq2(j);
		}
	}	
}

// dfs.h

void visitnode2(int i, int visited[])
{
	visited[i]=1;
	printf("%d ", i+1);
}

void DFS(int **a, int i)
{
	int j;
	static int visited[V]={0};
	
	visitnode2(i, visited);
	
	for(j=0;j<V;j++)
	{
		if(!a[i][j] ||  visited[j] )	//vertices adjacent to i and not been visited
			continue;
		
		DFS(a, j);
	}
}

// iscyclic_directed.h
//////////////////Stack///////////////////////////////////
int top9=-1, stack9[V];
int flag9;

void push9(int n)
{
	top9++;
	stack9[top9]=n;
}

int pop9()
{
	if(top9<0) return -1;
	
	top9--;
	return stack9[top9 +1];
}

int search_stack9(int j)
{
	int i;
	for(i=0;i<=top9;i++)
		if(j==stack9[i])
			return 5;
}
/////////////////////////////////////////////////////////////

dfs9(int **a, int visited[], int i)
{
	int j;
		
	visited[i]=1;
	
	for(j=0;j<V;j++)
	{
		if(a[i][j] == 0)
			continue;
		
		
		
		if( visited[j] ==1)
		{	if( search_stack9(j)==5)
			{//	printf("\n###top9 = %d-> %d,%d--------i=%d j=%d	",top9,stack9[0]+1, stack9[1]+1,i+1, j+1);
				flag9=1;
			}
		}	
		else{
			
			
			push9(j);
			dfs9(a, visited, j);
			pop9();
		}
	}
}


int isCyclic_directed( int** a)
{
	int visited[V] ={0};
	flag9=0;

	push9(0);
	dfs9(a, visited,0);
	
	if(flag9 ==1)
	{
		printf("\n\nisCyclic_directed: The Graph contains cycle(s).\n"); 
		 return 1;
	}
	else{
		printf("\n\nisCyclic_directed: The Graph does NOT contain  any cycles.\n");
		return 0;
	}
}

// iscyclicundirected.h
dfs2(int **a, int visited[], int i, int* flag)
{
	int j;
		
	visited[i]=1;
	
	for(j=0;j<V;j++)
	{
		if(a[i][j] == 0)
			continue;
		
		
		
		if( visited[j] ==1)
		{	*flag=1;	}	
		else{
			
			dfs2(a, visited, j, flag);
		}
	}
}


int isCyclic_undirected( int** a)
{
	int visited[V] ={0};
	int flag=0;
	
	dfs2(a, visited,0, &flag);
	
	if(flag ==1)
	{
		printf("\n\nisCyclic_undirected: The Graph contains cycle(s).\n"); 
		 return 1;
	}
	else{
		printf("\n\nisCyclic_undirected: The Graph does NOT contain  any cycles.\n");
		return 0;
	}
}

// prims2.h




int** prims( int **a )		//returns a Vx3 dimensional array where  V[i][2] gives the weight of the i-th edge
{
	int i,j,k, count;

	int visited[V]={0};

	int **Enew;
	Enew = (int**)malloc(V*sizeof(int*) );
	for(i=0;i<V;i++)
		Enew[i] = (int*)malloc(3*sizeof(int));
		
	
	int min, im,jm;

	visited[0]=1; count=1;	//initialising the first element
	
	while(count<V)	//running the loop for selecting each new edge, total edges would be v-1
	{
		
		for(k=0,min=9999;k<V;k++)		//running the loop for each element in visited set
		{
			if(visited[k] ==1)	
				for(j=0;j<V;j++)	//examining neighbours
				{
					if( a[k][j]== 0) continue;
						
					if( visited[j]==1) continue;	//looking for unvisited neighbours
						
					if(min > a[k][j] )	//checking if the edge weight is minimum
					{ 	min=a[k][j];
						im=k;jm=j;
						
					}
				}
		}
		
		if(min==9999)
			break;
		
		visited[jm]=1;	count++;
		
		Enew[count-2][0]=im;	Enew[count-2][1]=jm;	Enew[count-2][2] = a[im][jm];
			
			printf("Min: %d-------%d--%d\n", min, im+1,jm+1);
	}
	
		int sum=0;
		printf("\n--------------------------\nPrim's MST: \n");
		for(i=0;i<count-1;i++)
		{	
			printf("\t%d--%d\n", Enew[i][0]+1, Enew[i][1]+1);
			sum+=Enew[i][2];
		}
		printf("\nSum: %d\n", sum);

	return Enew;
}

//kruskal2.h


void selection_sort2 (int** a,  int n)
{
    int i, j, m, t;
    int temp1, temp2, temp3;
    
    for (i = 0; i < n; i++)
    {
        for (j = i, m = i; j < n; j++)
	  {
            if (a[j][2] < a[m][2])
                m = j;
        }
      temp1 = a[i][2];			temp2=a[i][0];		temp3=a[i][1];
	a[i][2] = a[m][2];		a[i][0]=a[m][0];		a[i][1]=a[m][1];
      a[m][2] = temp1;			a[m][0]=temp2;		a[m][1]=temp3;
    }
}


int** kruskal( int **a)
{
	int i,j,k;
	int c,d;
	
	int E=0;
	
	for(i=0;i<V;i++)
		for(j=0;j<V;j++)
			if(j>i && a[i][j] )
				E++;
	
	int **edges;
	edges = (int**)malloc( E*sizeof(int*) );
	for(i=0;i<E;i++)
		edges[i] = (int*)malloc(4*sizeof(int));
	
	int e=0;
	
	for(i=0;i<V;i++)		//storing the data in edges array
		for(j=0;j<V;j++)
		if(j>i && a[i][j])	//check for upper triangular matrix
			{
				edges[e][0]=i;	edges[e][1]=j;	
				edges[e][2]= a[i][j];	//weight of edges
				edges[e][3]=-1;		//id of edges
				e++;
			}
		
		
		
	///////////sorting the edges
	selection_sort2(edges, E);
	
	
	int treeid[V];			//id's of trees in the forest
	for(i=0;i<V;i++)	treeid[i]=i;		//initialising treeid's to vertex number only 
	
	
	for(i=0; i<E ; i++)
	{
		c=treeid[ edges[i][0] ];	d= treeid[ edges[i][1] ];
		
		if(c != d )	//if the two ends of an edge belong to different trees
		{
			for(j=0;j<V;j++)	//re-assigning tree id's of all those nodes with treeid=b
				if(treeid[j] == d )
					treeid[j] = c;
						
			edges[i][3] = c;		//assigning flag id's to edges included in MST
			
			for(j=0;j< E;j++)
				if( edges[j][3] == d)
					edges[j][3] = c;
		}
	}
	
	
	
	
	
	int id[V], x=0;
	int num=-1;
	for(i=0;i<E;i++)
		if( edges[i][3] > num )
		{	num=edges[i][3]; id[x]=num; x++; }
			
	
	
	
	printf("\n--------------*** Kruskal's MSTs ***--------------------------\n");
	
	for(k=0;k<x;k++)
	{
		printf("\n#%d MST edges:\n", k+1);
		int sum=0;	
		for(i=0;i<E;i++)
			if(edges[i][3] == id[k] )
			{	
				printf("\t%d -- %d\n", edges[i][0]+1, edges[i][1]+1 );
				sum+= edges[i][2];
			}
				printf("\n>> Total Cost/weight of this MST= %d\n-------------------\n", sum);
	}
	
	
	for(i=0;i<V;i++)
	{
		for(j=0;j<x;j++)
			if ( treeid[i] == id[j] )  break;
	
		if ( treeid[i] == id[j] )  continue;
	
		printf("\n#%d MST:\n", k+1);	k++;
		
		printf("\t(Loner) MST: %d\n---------------\n", i+1);
	}
		
		
	return edges;
	
}



//#include "topsort.h"




////////Stack///////////////////////////////
int top5=-1, stack5[V];

void push5(int n)
{
	top5++;
	stack5[top5]=n;
}

int pop5()
{
	if(top5<0) return -1;
	
	top5--;
	return stack5[top5+1];
}
/////////////////////////////////////////



int indegree(int **a, int node)
{
	int i,in_deg = 0;
	for(i = 0;i < V;i++)
		if(a[i][node] > 0)
			in_deg++;
	return in_deg;
}


int* topsort( int **a )
{
	
	int *sorted,indeg[V];
	sorted=(int*)malloc(V*sizeof(int));
	
	int i,k,t=0, count=0;

	for(i=V-1;i>=0;i--)		//initial step to find indegree of each node
	{
		indeg[i]= indegree(a, i);
		if(indeg[i]==0)		//pushing in the stack the source nodes
			push5(i);
	}

	
	while(top5>=0)
	{
		k= pop5();			//poping a node each time
		sorted[t++]=k;
		
		for(i=0;i<V;i++)		//running the loop over adjaceent nodes to the popped node
		{
			if(a[k][i]==0)
				continue;
			
			indeg[i]--;	
			
			if( indeg[i] ==0)	
				push5(i);			
		}
		count++;
	}
	
	if(count!= V)
		printf("\n\n**** Topological oredering NOT possible in this graph due to internal cycles\n");
	else
	{	printf("\n\nNodes after topological sorting are:\n");
		for(i=0;i<V;i++)
			printf("%d \t",sorted[i]+1);
		printf("\n");
	}
	
	return sorted;
	
}


// #include "dijkstraw.h"




int dijkstraw(int **a, int p, int q)
{
	int i,j,k;
	
	//initialising few arrays
	
		int visited[V]={0};
			
		int dist[V] = {[0 ... V-1] = 9999 };

		dist[p]=0;
	
	k=p;
	
	while(1)
	{
		printf("node: %d\n", k+1);
		
			if(k==q)	break;	//if destination node is reached
			if (k==-1)	return 7777;	//no path exists between the given pair
				
		for(i=0;i<V;i++)		//examining the neighbours.
		{
			if(a[k][i] <= 0 || visited[i] ==1) 		//skip the node in case of a visited neighbour
				continue;
			
			if( a[k][i]+ dist[k] < dist[i] )	//update the distances if they are shorter
				dist[i] = a[k][i]+ dist[k];
		}
		
		visited[k]=1;	//mark the node visted
				
			//choose the shortest path node from the unvisted set to be the next node
			int min=9999, minnode=-1;
			for(i=0;i<V;i++)
			{
				if(visited[i]==1)
					continue;
				
				if(dist[i] < min)
				{	min = dist[i]; minnode= i;	}
			}
			//can also use heaps to find the minimum, though this will make the code a bit complex to comprehend 
			
		k = minnode;
	}
	
	return dist[q];
}

//#include "floyd.h"

#include<stdio.h>
#include<stdlib.h>


int ** floyd( int **a )
{
	int i, j, k;	

	int **dist;
	dist= (int**) malloc( V*sizeof(int*) );
	for(i=0;i<V;i++)
		dist[i] = (int*) malloc( V*sizeof(int) );

//////////////Initialising////////////////////////////////////////	
	
	for(i=0;i<V;i++)
		for(j=0;j<V;j++)
		{	dist[i][j]=9999;
			if(i==j)	dist[i][j]=0;
			
			if(a[i][j] > 0)	dist[i][j] = a[i][j];
		}

/////////////////Execution//////////////////////////////////////////
		
	for( k=0;k<V;k++)
		for( i=0;i<V;i++)
			for( j=0;j<V;j++)
				if( dist[k][i] + dist[i][j] < dist [k][j])
					dist[k][j] = dist[k][i] + dist[i][j];
				
///////////////// printing ////////////////////////////////////////////////

	printf("\n\nFloyd all pairs shortest path matrix:\n\n");		
		for(i=0;i<V;i++)
			printf("\t%5d", i+1);
		printf("\n");
				
		for(i=0;i<V;i++)
		{	printf("\n\n%d\t", i+1);
			for(j=0;j<V;j++)
				printf("%6d\t", dist[i][j]);
		}
		printf("\n\n");
				
	return dist;
}


// #include "generic.h"

void printmatrix(int **a)
{
	int i, j;


printf("\n-------------------------------------\n");
	for(i=0;i<V;i++)
		printf("\t%5d", i+1);
		
	printf("\n");
				
		for(i=0;i<V;i++)
		{	printf("\n%d\t", i+1);
			for(j=0;j<V;j++)
				printf("%6d\t", a[i][j]);
		}
		printf("\n");
printf("-------------------------------------\n");
}


///////Description of functions//////////////////////
/*
void BFS(int **a , int start)
void DFS(int **a, int start)

int isCyclic_undirected(a);	//checks for an undirected graph....returns 1 if the graph contains any cycle.
int isCyclic_directed(a);	//checks for an directed graph....returns 1 if the graph contains any cycle.

int** prims( int **a )	//returns a Vx3 dimensional array where V[i][0] and V[i][1] has nodes of an edge of MST and  V[i][2] gives the weight of the i-th edge
int** kruskal( int **a)	//E = number of edges...Returns a Vx4 dimensional array.

int* topsort( int **a )	//returns the topologically sorted array pointer and also prints the array.

int dijkstraw(int **a, int p, int q)	//returns the shortest path length between nodes p and q
int ** floyd( int **a )			//returns the pointer to the VxV matrix containing all pairs shortest paths and also prints the matrix
*/
/////////////////////////////////////////////////////



main()
{
	int **u = createGraph();	//creates an undirected graph in form an adjcanecy matrix from a specified file
	int **d = createDiGraph();	//directed graph

//	int **u = createRandom_graph();	//creates a undirected graph randomly
//	int **d = createRandom_digraph();	//creates a directed graph randomly
	

//	printmatrix(u);		//prints the adjacency matrix for the graph.
//	printmatrix(d);


	printf("BFS of the graph: \n");	BFS(d, 0);	
	
	printf("\nDFS of the graph: \n");	DFS(d,0);
	printf("\n");

//	isCyclic_undirected(u);
	
	isCyclic_directed(d);

	prims(u);		//the input has to be an undirected graph for computing MST
		
	kruskal(u);		//the input has to be an undirected graph for computing MST

	topsort(d);		//the input has to be directed graph for computing topological oredring

/*	int p, q;
	printf("\n\nDjkstraw Algorithm: Enter the source and destination nodes to find the shortest path(1-17) : ");
	scanf("%d %d", &p,&q);
	printf("\nShortest path = %d\n", dijkstraw(d,p,q) );
*/	

//	floyd(d);


}
