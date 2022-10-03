#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

/**
 * breaker box: start node
 * switch:
 * light: must be one switch between light and breaker box
 */

/**
 * input:
 * J C : junction points, possible connections
 * J lines : list of junction points
 * C lines : connections and their costs
 */

typedef struct Node
{
    string name;
    string type;
    int num;
    bool known;
    int weight;
    int rank;
    Node *parent;
    Node(string n, string t, int num);
} node;
Node::Node(string n, string t, int number)
{
    name = n;
    type = t;
    num = number;
    known = false;
    weight = 0;
    rank = 0;
};

typedef struct Edge
{
    node *first;
    node *second;
    int weight;
    Edge(node *f, node *s, int w);
} edge;
Edge::Edge(node *f, node *s, int w)
{
    first = f;
    second = s;
    weight = w;
};

// void Prim(vector<node *> V, int E[100][100], node *root, int size)
// {
//     priority_queue<node *> pq;
//     pq.push(root); // add root node
//     // parent[root] = NULL;     // root->parent ?
//     while (!pq.empty())
//     {
//         node *n = pq.top();
//         for (int i = 0; i < size; i++)
//         {
//             int weight = E[n->num][i];
//             for (auto v : V)
//             {
//                 if (v->num == i && weight != -1)
//                 {
//                     if (!v->known)
//                     {
//                         pq.push(v);
//                         v->parent = n;
//                     }
//                 }
//             }
//         }
//         pq.pop();
//     }
// }
void makeSet(node *x)
{
    x->parent = x;
    x->rank - 0;
}
node *findSet(node *x)
{
    if (x != x->parent)
    {
        x->parent = findSet(x->parent);
    }
    return x->parent;
}
void linkSet(node *x, node *y)
{
    if (x->rank > y->rank)
    {
        y->parent = x;
    }
    else
    {
        x->parent = y;
        if (x->rank == y->rank)
        {
            y->rank = y->rank + 1;
        }
    }
}
void unionSet(node *x, node *y)
{
    linkSet(findSet(x), findSet(y));
}

void Kruskal(vector<node *> V, int E[100][100], vector<edge *> Edges, node *root, int size)
{
    int edgesAccepted = 0;
    // disjointSet s(NUM_VERTICES)
    edge *edge;
    node *u;
    node *v;
    while (edgesAccepted < size - 1)
    {
        // edge(u,v) = smallest weight edge not deleted yet
        int least = 0;
        for (auto e : Edges)
        {
            if (e->weight == least)
            {
                cout << e->first->name << e->second->name << endl;
                edge = e;
                u = e->first;
                v = e->second;
                break;
            }
            least += 1;
        };

        // node *uset = findSet(u);
        // node *vset = findSet(v);
        // if (uset != vset)
        // {
        edgesAccepted++;
        // unionSet(uset, vset);
        // };
    }
}

int main()
{
    int junctions;
    int connections;
    cin >> junctions;
    cin >> connections;

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

    int E[100][100];
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            E[i][j] = -1;
        }
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
        E[num1][num2] = weight;
        E[num2][num1] = weight;

        Edges.push_back(new edge(node1, node2, weight));
    };
    // Prim(V, E, root, junctions);
    Kruskal(V, E, Edges, root, junctions);
}
