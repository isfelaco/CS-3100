#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

typedef struct Vertex {
	string value;
	int num;
	int topologicalNum;
	int indegree;
	Vertex(string v, int n);
} vertex;
Vertex::Vertex(string v, int n) {
	value = v;
	num = n;
	topologicalNum = 0;
	indegree = 0;
};

void topSort(vector<vertex*> arr, int adj[100][100], int count) {
	queue<vertex*> q;
	int counter = 0;
	vertex* v;

	// q.makeEmpty(); // initialize the queue
	for (auto v : arr) {
		if (v->indegree == 0) {
			q.push(v);
		}
	}
	// q is just vertices with indegree = 0
	// if multiple vertices have the same in degree, their order can be swapped
	while (!q.empty()) {
		v = q.front();
		q.pop(); // get vertex of indegree 0
		v->topologicalNum = ++counter;
		int index = v->num;
		for (auto w : arr) {
			int index2 = w->num;
			if (adj[index][index2] == 1) {
				if (--w->indegree == 0) {
					q.push(w);
				}
			}
		}
	}
}

bool sortIndegree (vertex* i,vertex* j) {
	if (i->indegree == j->indegree && i->indegree == 0) {
		return (i->value < j->value);
	}
	return (i->indegree < j->indegree);
}


int main() {
	string line1;
	string line2;
	cin >> line1;
	cin >> line2;
	int num_options = stoi(line1);
	int num_dependencies = stoi(line2);

	int size = 100;
    int adj[100][100];
    for (int i = 0; i < size; i++) {
    	for (int j = 0; j < size; j++) {
    		adj[i][j] = 0;
    	}
    }

    vector<vertex*> arr;

	// add all vertices to arr
    string line;
	for (int j = 0; j < num_options; j++){
		cin >> line;
		vertex* node = new vertex(line, j);
		arr.push_back(node);
	}

    int count = 0;
	for(int k = 0; k < num_dependencies; k++) { // update adjacency matrix based on dependencies
		string first;
		string second;
		cin >> first;
		cin >> second;
		int i1;
    	int i2;
		for (auto x : arr) {
			if (first == x->value) {
				i1 = x->num;
			}
			if (second == x->value) {
				i2 = x->num;
			}
		}
		adj[i1][i2] = 1;
	}		

    // finding indegree of each vertex from the adj matrix
    for (auto x : arr) {
    	int index = x->num;
    	int indegree = 0;
    	for (int i = 0; i < size; i++) {
    		indegree += adj[i][index];
    	}
    	x->indegree = indegree;
    }

	sort(arr.begin(), arr.end(), sortIndegree);

	topSort(arr, adj, count);

	int least = 1;

	string output = "";
	int c = 0;
	while (least < size) {
		for (auto x : arr) {
			if (x->topologicalNum == least) {
				output += x->value;
				output += " ";
				c++;
				break;
			}
		}
		least++;
	}
	if (c == num_options) {
		cout << output;
	}
	else cout << "IMPOSSIBLE";

	return 0;
}