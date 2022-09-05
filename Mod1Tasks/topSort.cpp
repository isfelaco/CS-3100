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

bool sortIndegree (vertex* i,vertex* j) {
	return (i->value < j->value);
}


void topSort(vector<vertex*> arr, int adj[100][100]) {
	queue<vertex*> q;
	int counter = 0;
	vertex* v;

	for (auto v : arr) {
		if (v->indegree == 0) {
			q.push(v);
		}
	}

	while (!q.empty()) {
		v = q.front();
		q.pop();
		v->topologicalNum = ++counter;
		int index = v->num;
		for (auto w : arr) {
			int index2 = w->num;
			if (adj[index][index2] == 1) {
				if (--w->indegree == 0) {
					q.push(w);
				}
			}

			vector<vertex*> V;
			while(!q.empty()) {
				V.push_back(q.front());
				q.pop();
			}

			sort(V.begin(), V.end(), sortIndegree);

			for (auto v : V) {
				q.push(v);
			}
		}
	}
}

int main() {
	string line1;
	string line2;
	cin >> line1;
	cin >> line2;
	int num_options = stoi(line1);
	int num_dependencies = stoi(line2);

	// initialize adjacency matrix
	int size = 100;
    int adj[100][100];
    for (int i = 0; i < size; i++) {
    	for (int j = 0; j < size; j++) {
    		adj[i][j] = 0;
    	}
    }

	// add all vertices  arr
    vector<vertex*> arr;
    string line;
	for (int j = 0; j < num_options; j++){
		cin >> line;
		vertex* node = new vertex(line, j);
		arr.push_back(node);
	}

	// update adjacency matrix based on dependencies
	for(int k = 0; k < num_dependencies; k++) {
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

	topSort(arr, adj);

	int least = 1;

	string output = "";
	int count = 0;
	while (least < size) {
		for (auto x : arr) {
			if (x->topologicalNum == least) {
				output += x->value;
				output += " ";
				count++;
				break;
			}
		}
		least++;
	}
	if (count == num_options) {
		cout << output;
	}
	else cout << "IMPOSSIBLE";

	return 0;
}