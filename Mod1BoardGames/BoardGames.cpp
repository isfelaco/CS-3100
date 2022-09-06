#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

typedef struct Vertex
{
	int num;
	string color;
	Vertex(int n);
} vertex;
Vertex::Vertex(int n)
{
	num = n;
	color = "WHITE";
};

bool mySort(vertex *i, vertex *j)
{
	return i->num < j->num;
}

vector<int> invalVerts;
vector<string> solutions;

int t = 0;
int path[100];

void DFS_VISIT(vector<vertex *> arr, vector<vertex *> adj[100], vertex *u, vertex *d)
{
	u->color = "GRAY";
	path[t] = u->num;
	t++;

	if (u->num == d->num)
	{
		string output = "";
		bool valid = true;
		for (int i = 0; i < t; i++)
		{
			output += to_string(path[i]);
			output += "-";
			for (auto x : invalVerts)
			{
				if (path[i] == x)
				{
					valid = false;
				}
			}
		}
		if (valid)
		{
			output = output.substr(0, output.length() - 1);
			solutions.push_back(output);
		}
	}
	else
	{
		for (auto v : adj[u->num])
		{
			if (v->color == "WHITE")
			{
				DFS_VISIT(arr, adj, v, d);
			}
		}
	}
	u->color = "WHITE";
	t--;
}

int main()
{
	int num_ints;
	int num_roads;
	cin >> num_ints;
	cin >> num_roads;

	// add all vertices to arr
	vector<vertex *> arr;
	for (int i = 0; i < num_ints; i++)
	{
		vertex *v = new vertex(i);
		arr.push_back(v);
	}

	// create adjacency matrix
	vector<vertex *> adj[num_ints];
	vertex *a;
	vertex *b;
	for (int i = 0; i < num_roads; i++)
	{
		int first;
		int second;
		cin >> first;
		cin >> second;
		for (auto x : arr)
		{
			if (first == x->num)
			{
				a = x;
			}
			if (second == x->num)
			{
				b = x;
			}
		}

		// checking for duplicate edges
		bool addf = true;
		bool adds = true;
		for (auto x : adj[a->num])
		{
			if (x->num == b->num)
			{
				adds = false;
			}
		}
		for (auto x : adj[b->num])
		{
			if (x->num == a->num)
			{
				addf = false;
			}
		}
		if (addf && adds)
		{
			adj[a->num].push_back(b);
			adj[b->num].push_back(a);
		}
	}

	// sorting for lexigraphical order
	for (int i = 0; i < num_ints; i++)
	{
		sort(adj[i].begin(), adj[i].end(), mySort);
	}

	// creating a list of all invalid vertices
	int num_inval;
	cin >> num_inval;
	for (int i = 0; i < num_inval; i++)
	{
		int d;
		cin >> d;
		invalVerts.push_back(d);
	}

	DFS_VISIT(arr, adj, arr.front(), arr.back());

	for (auto s : solutions)
	{
		cout << s << endl;
	}
}