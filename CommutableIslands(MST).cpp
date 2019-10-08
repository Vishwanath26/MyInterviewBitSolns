#include<bits/stdc++.h>
using namespace std;
struct Node 
{
	int rank;
	long data;
	Node* parent;
};
bool comp(vector<int>a, vector<int>b)
{
    return a[2]<b[2];
}
map<long, Node*>m;
void makeSet(int data)
{
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node->rank = 0;
	node->data = data;
	node->parent = node;
	m.insert(make_pair(data, node));
}

Node* findSet(long data)
{
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	auto i = m.find(data);
	node = i->second;
	if(node->parent->data == node->data)
	{
		return node;
	}
	node->parent = findSet(node->parent->data);
	return node->parent;
}
void Union(long data1, long data2)
{
	Node* parent1 = findSet(data1)->parent;
	Node* parent2 = findSet(data2)->parent;
	if(parent1 == parent2)
	{
		return;
	}
	if(parent1->rank>=parent2->rank)
	{
		parent1->rank = (parent1->rank==parent2->rank)?parent1->rank+1:parent1->rank;
		parent2->parent = parent1;
	}
	else
	parent1->parent = parent2;
	return ;
}

int main()
{
	vector< vector<int> > B{{1, 2, 10}, 
                                {2, 3, 5}, 
                                {1, 3, 9}}; 
	sort(B.begin(), B.end(), comp);
    set<int>s;
    for(int i=0;i<B.size();i++)
    {
        if(s.find(B[i][0])==s.end()) {
             s.insert(B[i][0]);
             makeSet(B[i][0]);
        }
        if(s.find(B[i][1])==s.end()) {
             s.insert(B[i][1]);
             makeSet(B[i][1]);    
        }
    }
    int cost=0;
    for(int i=0;i<B.size();i++)
    {
        if(findSet(B[i][0])!=findSet(B[i][1]))
        {
            cost+=B[i][2];
            Union(B[i][0], B[i][1]);
        }
    }
    m.clear();
    cout<<cost;
	return 0;
}
