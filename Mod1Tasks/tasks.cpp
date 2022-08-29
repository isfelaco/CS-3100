#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

struct Vertex {
	string value;
	int num;
	int topologicalNum;
	int indegree;
	Vertex(string v, int n);
};
Vertex::Vertex(string v, int n) {
	value = v;
	num = n;
	topologicalNum = 0;
	indegree = 0;
};


/**
 * @brief Performs Topological Sort on a graph
 * 
 * This function implements the topological sort algorithm by taking in a vector vertices and their corresponding adjacency matrix.
 * 
 * @param arr The vector that contains all of the vertices
 * @param adj The adjacency matrix for the vertices
 * @param count The number of vertices in arr
 * 
 */
void topSort(vector<struct Vertex*> arr, int adj[100][100], int count) {
	queue<struct Vertex*> q;
	int counter = 0;
	struct Vertex* v;


	// q.makeEmpty(); // initialize the queue
	for (auto v : arr) {
		if (v->indegree == 0) {
			q.push(v);
		}
	}
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




int main(int argc, char *argv[]) {
	string file_name = argv[1];

	int size = 100;
    int adj[100][100];
    for (int i = 0; i < size; i++) {
    	for (int j = 0; j < size; j++) {
    		adj[i][j] = 0;
    	}
    }

    vector<struct Vertex*> arr;

	ifstream(myfile);
    myfile.open(file_name);
    string line;
    int count = 0;
	while(getline(myfile,line) && line != "0") {
		string first = "";
		string second = "";
		int i = 0;
		int i1 = -1;
    	int i2 = -1;
		if (line.length() != 3) {
			while (line[i] != ' ') {
				first += line[i];
				i++;
			}
			i++;
			while (i < line.length()) {
				second += line[i];
				i++;
			}
            if (second != "") {
			for (auto x : arr) {
				if (first == x->value) {
					i1 = x->num;
				}
				if (second == x->value) {
					i2 = x->num;
				}
			}
			if (i1 == -1) {
				struct Vertex *node1 = new struct Vertex(first, count);
				arr.push_back(node1);
				i1 = count;
				count++;
			}
			if (i2 == -1) {
				struct Vertex *node2 = new struct Vertex(second, count);
				arr.push_back(node2);
				i2 = count;
				count++;
			}
			adj[i1][i2] = 1;
            }
		}		
	}
	myfile.close();

    // finding indegree of each vertex from the adj matrix
    for (auto x : arr) {
    	int index = x->num;
    	int indegree = 0;
    	for (int i = 0; i < size; i++) {
    		indegree += adj[i][index];
    	}
    	x->indegree = indegree;
    }

	topSort(arr, adj, count);

	int least = 1;

	while (least < size) {
		for (auto x : arr) {
			if (x->topologicalNum == least) {
				cout << x->value << " ";
				break;
			}
		}
		least++;
	}
	cout << endl;
	

	return 0;
}