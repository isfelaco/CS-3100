#include <bits/stdc++.h>
using namespace std;

// DSU data structure
// path compression + rank by union

class DSU
{
    int *rank;

public:
    int *parent;
    DSU(int n)
    {
        parent = new int[n];
        rank = new int[n];

        for (int i = 0; i < n; i++)
        {
            parent[i] = -1;
            rank[i] = 1;
        }
    }

    // Find function
    int find(int i)
    {
        if (parent[i] == -1)
            return i;
        else
            return parent[i] = find(parent[i]);
    }

    // Union function
    void unite(int x, int y)
    {
        int s1 = find(x);
        int s2 = find(y);

        if (s1 != s2)
        {
            if (rank[s1] < rank[s2])
            {
                parent[s1] = s2;
                rank[s2] += rank[s1];
            }
            else
            {
                parent[s2] = s1;
                rank[s1] += rank[s2];
            }
        }
    }
};

typedef struct Node
{
    string name;
    string type;
    int num;
    bool known;
    Node(string n, string t, int num);
} node;
Node::Node(string n, string t, int number)
{
    name = n;
    type = t;
    num = number;
    known = false;
};

typedef struct Edge
{
    node *first;
    node *second;
    int weight;
    bool known;
    Edge(node *f, node *s, int w);
} edge;
Edge::Edge(node *f, node *s, int w)
{
    first = f;
    second = s;
    weight = w;
    known = false;
};

class Graph
{
    vector<edge *> edgelist;
    int V;

public:
    Graph(int V) { this->V = V; }

    void addEdge(node *u, node *v, int w)
    {
        edge *e = new edge(u, v, w);
        edgelist.push_back(e);
    }

    void print()
    {
        for (auto e : edgelist)
        {
            cout << e->first->name << endl;
        }
    }

    void kruskals_mst(int size, node *root)
    {
        // Sort all edges
        sort(edgelist.begin(), edgelist.end());

        // Initialize the DSU
        DSU s(V);
        int ans = 0;
        int edgesAccepted = 0;
        // s.parent[root->num] = 0;
        node *current = root;

        cout << "Following are the edges in the "
                "constructed MST"
             << endl;

        while (edgesAccepted < size - 1)
        {
            int minWeight = 0;
            edge *least = NULL;
            while (least == NULL)
            {
                for (auto edge : edgelist)
                {
                    bool c = (edge->first->num == current->num || edge->second->num == current->num);
                    if (c && edge->weight == minWeight && edge->known == false)
                    {
                        least = edge;
                        break;
                    }
                }
                minWeight++;
            }
            int w = least->weight;
            node *u = least->first;
            node *v = least->second;

            if (s.find(u->num) != s.find(v->num))
            {
                s.unite(u->num, v->num);
                least->known = true;
                ans += w;
                cout << u->name << " -- " << v->name << " == " << w
                     << endl;
                edgesAccepted++;
            }
        }

        cout << "Minimum Cost Spanning Tree: " << ans;
    }
};

int main()
{
    int junctions;
    int connections;
    cin >> junctions;
    cin >> connections;
    Graph g(junctions);

    vector<node *> V;
    node *root;
    for (int i = 0; i < junctions; i++)
    {
        string name;
        string type;
        cin >> name;
        cin >> type;
        node *n = new node(name, type, i);
        if (type == "breaker")
        {
            root = n;
        }
        V.push_back(n);
    }

    vector<edge *> Edges;
    for (int i = 0; i < connections; i++)
    {
        string first;
        string second;
        int weight;
        cin >> first;
        cin >> second;
        cin >> weight;
        int num1;
        int num2;
        node *node1;
        node *node2;
        for (auto v : V)
        {
            if (first == v->name)
            {
                num1 = v->num;
                node1 = v;
            }
            if (second == v->name)
            {
                num2 = v->num;
                node2 = v;
            }
        };
        g.addEdge(node1, node2, weight);
    };

    g.kruskals_mst(junctions, root);
    // g.print();
    return 0;
}
