#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


typedef struct Vertex {
	string value;
	int num;
	int topologicalNum;
	int indegree;
    string color;
    Vertex* parent;
    int d;
    int f;
	Vertex(string v, int n);
} vertex;
Vertex::Vertex(string v, int n) {
	value = v;
	num = n;
	topologicalNum = 0;
	indegree = 0;
    color = "WHITE";
    d = 0;
    f = 0;
};

int t = 0;
vector<vertex*> topsort_list;
void DFS_VISIT(vector<vertex*> arr, vector<vertex*> adj[100], vertex* u) {
	t++;
	u->d = t; // discovery time of u
	u->color = "GRAY";
	for (auto v : adj[u->num]) { // for each adjacent node explore edge
		if (v->color == "WHITE") { // if unseen
			v->parent = u;
			DFS_VISIT(arr, adj, v); // explore paths out of that adjacent node
        }
    }
	u->color = "BLACK";
	t++;
	u->f = t; // finish time of u
	topsort_list.push_back(u);
}

void DFS(vector<vertex*> arr, vector<vertex*> adj[100]) {
	for (auto u: arr) {
		u->color = "WHITE";
		u->parent = NULL;
    }
	for (auto u : arr) {
		if (u->color == "WHITE") {
			DFS_VISIT(arr, adj, u);
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


    // creating array of vertices
    vector<vertex*> arr;
    string line;
    for (int j = 0; j < num_options; j++){
		cin >> line;
		vertex* node = new vertex(line, j);
		arr.push_back(node);
	}

    vector<vertex*> adj[num_options];
    // update adjacency matrix based on dependencies
    int count = 0;
	for(int k = 0; k < num_dependencies; k++) {
		string first;
		string second;
		cin >> first;
		cin >> second;
		int i1;
    	int i2;
        int count = 0;
		for (auto x : arr) {
            if (first == x->value) {
                for (auto y : arr) {
                    if (second == y->value) {
                        adj[x->num].push_back(y);
                    }
                }
            }
		}        
	}	

    DFS(arr, adj);

    string output[num_options];
    // reversing the output
    int c = num_options - 1;
    for (auto x : topsort_list) {
        output[c] = x->value;
         c--;
    }
    for (auto x : output) {
        cout << x << " ";
    }
}