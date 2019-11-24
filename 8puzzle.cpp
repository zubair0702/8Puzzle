#include <iostream>
#include <queue>
using namespace std;

bool solvable(int temp[9])
{
	int count=0;
	for(int i=0;i<9;i++) 
	{
		if(temp[i]==0){continue;}
		
		for(int j=i+1;j<9;j++)
		{
			if(temp[j]==0){continue;}
			if(temp[i]>temp[j])
			{
				count++;
			}
		}
	}
	
	if(count%2==0)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
 
class Node 
{
	public:
		Node* parent; 
		int mat[3][3];  
		int x,y;  
		int mandist;
		int depth; 
}; 
 
void print(int mat[3][3]) 
{ 
	for(int i=0;i<3;i++) 
	{ 
		for(int j=0;j<3;j++)
		{
			cout<<mat[i][j]<<" ";
		} 
		cout<<endl;
	}
} 


Node* newNode(int mat[3][3], int x,int y,int X,int Y,int depth, Node* parent) 
{ 
	Node* node = new Node; 
	node->parent = parent;  
	
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			node->mat[i][j]=mat[i][j];
		}
	}
 
	swap(node->mat[x][y], node->mat[X][Y]); 
	node->mandist = INT_MAX;  
	node->depth = depth; 
	node->x = X; 
	node->y = Y; 

	return node; 
} 

int row[] = { 1, 0, -1, 0 }; 
int col[] = { 0, -1, 0, 1 }; 
 
int manhattanDist(int start[3][3], int ans[3][3]) 
{ 
	int count=0; 
	for (int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(start[i][j] && start[i][j] != ans[i][j])
			{
				count++;
			}	
		}
	}  
	return count; 
} 

int valid(int x, int y) 
{ 
	return(x>=0 && x<3 && y>=0 && y<3); 
} 
 
void printX(Node* root) 
{ 
	if (root == NULL)
	{
		return;	
	} 
	printX(root->parent); 
	print(root->mat);
	cout<<endl; 
} 

struct compare 
{ 
	bool operator()(Node* n1,Node* n2)
	{ 
		return (n1->mandist+n1->depth)>(n2->mandist+n2->depth); 
	} 
}; 

 
void solve(int start[3][3], int x, int y, int ans[3][3]) 
{ 
	priority_queue <Node*, vector<Node*> ,compare> pq;
	
	Node* root=newNode(start,x,y,x,y,0,NULL);
	root->mandist=manhattanDist(start, ans); 
 
	pq.push(root); 
	while (!pq.empty()) 
	{  
		Node* t=pq.top();  
		pq.pop(); 

		if(t->mandist == 0) 
		{ 
			printX(t); 
			return; 
		} 
 
		for(int i=0;i<4;i++) 
		{
			if(valid(t->x + row[i], t->y + col[i])) 
			{
				Node* child = newNode(t->mat, t->x, t->y, t->x + row[i], t->y + col[i], t->depth + 1, t);
				child->mandist = manhattanDist(child->mat, ans); 
				pq.push(child); 
			} 
		} 
	} 
} 

int main() 
{  
	int start[3][3];
	
	/*
	{1, 2, 3}, 
	{5, 6, 0}, 
	{7, 8, 4}
	*/
	
	cout<<"Enter Puzzle (0 at blank):\n";
	int k=0,x,y,temp[9];
	for(int i=0;i<3;i++) 
	{ 
		for(int j=0;j<3;j++)
		{
			cin>>start[i][j];
			if(start[i][j]==0)
			{
				x=i;y=j;
			}
			temp[k]=start[i][j];
			k++;
		}
	}cout<<"----------------------------------------------------------------"<<endl;
	
	if(!solvable(temp))
	{
		cout<<"Puzzle is not solvable.";
		return(0);
	}
	 
	int ans[3][3] = 
	{ 
		{1, 2, 3}, 
		{4, 5, 6}, 
		{7, 8, 0} 
	};

	solve(start, x, y, ans); 

	return 0; 
} 

