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

    void kruskals_mst(int size, node *root, int switchCount, bool lightPresent)
    {
        // Sort all edges
        sort(edgelist.begin(), edgelist.end());

        DSU s(V);
        int ans = 0;
        int edgesAccepted = 0;
        node *current = root;
        int switchesFound = 0;

        // cout << "Following are the edges in the constructed MST" << endl;

        while (edgesAccepted < 6)
        {
            int minWeight = 0;
            edge *least = NULL;
            while (least == NULL)
            {
                for (auto edge : edgelist)
                {
                    // cout << edge->known << endl;
                    // cout << minWeight << endl;
                    bool c = (edge->first->num == current->num || edge->second->num == current->num);
                    // cout << c << endl;
                    // cout << edge->first->name << ", " << edge->second->name << ": " << edge->known << ", weight: " << edge->weight << endl;
                    bool s = edge->second->type == "light" && switchesFound != switchCount;
                    bool o = edge->first->type == "switch" && edge->second->type == "outlet";
                    // cout << s << endl;
                    /**
                     * if you find a light and not all switches have been found, don't pick that edge
                     */
                    // if (edge->second->type == "switch" && s)
                    //     cout << "idk" << endl;
                    if (!o && !s && c && edge->weight == minWeight && edge->known == false)
                    {
                        // cout << "SOMETHING" << endl;
                        least = edge;
                        break;
                    }
                }
                minWeight++;
            }
            int w = least->weight;
            // cout << "minWeight: " << w << endl;
            node *u = least->first;
            node *v = least->second;

            if (least->first != current)
                current = least->first;
            else
                current = least->second;

            if (least->second->type == "switch")
                switchesFound++;

            if (s.find(u->num) != s.find(v->num))
            {
                s.unite(u->num, v->num);
                least->known = true;
                ans += w;
                // cout << u->name << " -- " << v->name << " == " << w << endl;
                edgesAccepted++;
                least->known = true;
            }
        }
        // cout << "Minimum Cost Spanning Tree: " << ans;
        cout << ans << endl;
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
    int switchCount = 0;
    bool lightPresent = false;
    for (int i = 0; i < junctions; i++)
    {
        string name;
        string type;
        cin >> name;
        cin >> type;
        node *n = new node(name, type, i);
        if (type == "breaker")
            root = n;
        if (type == "switch")
            switchCount++;
        if (type == "light")
            lightPresent = true;
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

    g.kruskals_mst(junctions, root, switchCount, lightPresent);
    // g.print();
    return 0;
}
