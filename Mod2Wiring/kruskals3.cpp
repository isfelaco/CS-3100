#include <bits/stdc++.h>
using namespace std;

// DSU data structure
// path compression + rank by union

struct DSU
{
    int *rank;
    int *parent;
    int size;
    DSU(int n);
    int Find(int i)
    {
        if (parent[i] == -1)
            return i;
        else
            return parent[i] = Find(parent[i]);
    };
    void Union(int x, int y)
    {
        int s1 = Find(x);
        int s2 = Find(y);

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
    };
};
DSU::DSU(int n)
{
    size = n;
    parent = new int[n];
    rank = new int[n];
    for (int i = 0; i < n; i++)
    {
        parent[i] = -1;
        rank[i] = 1;
    }
};

typedef struct Node
{
    string id;
    string type;
    // list of edges
    int num;
    Node *parent;
    Node *parentSwitch;
    bool seen;
    Node(string i, string t, int n);
} node;
Node::Node(string i, string t, int n)
{
    id = i;
    type = t;
    num = n;
    parent = NULL;       // which node does it come from
    parentSwitch = NULL; // if the node is a switch, what switch does it have to connect to
    seen = false;
};

typedef struct Edge
{
    node *n1;
    node *n2;
    int weight;
    bool known; // might not be necessary
    Edge(node *f, node *s, int w);
} edge;
Edge::Edge(node *f, node *s, int w)
{
    n1 = f;
    n2 = s;
    weight = w;
    known = false;
};

bool preSwitch(string type)
{
    return type == "breaker" || type == "outlet" || type == "box";
}

bool postSwitch(string type)
{
    return type == "light";
}

bool isSwitch(string type)
{
    return type == "switch";
}

bool validEdge(node *n1, node *n2)
{
    string type1 = n1->type;
    string type2 = n2->type;
    // cout << n1->id << ": " << n1->seen << ", " << n2->id << ": " << n2->seen << endl;
    if (preSwitch(type1) && preSwitch(type2))
        return true;
    if (preSwitch(type1) && isSwitch(type2) && n2->seen == false)
        return true;
    if (postSwitch(type1) && postSwitch(type2) && n1->parentSwitch == n2->parentSwitch)
        return true;
    if (isSwitch(type1) && postSwitch(type2) && n1 == n2->parentSwitch)
        return true;
    return false;
}

struct Graph
{
    vector<edge *> edgelist;
    int ans = 0;

    DSU kruskals(DSU s, int size)
    {
        sort(edgelist.begin(), edgelist.end());

        int edgesAccepted = 0;

        while (edgesAccepted < size - 1)
        {
            int minWeight = 0;
            edge *least = NULL;
            while (least == NULL)
            {
                for (auto edge : edgelist)
                {
                    // cout << edge->n1->id << ", " << edge->n2->id << ": " << edge->known << ", weight: " << edge->weight << endl;
                    if (edge->weight == minWeight && edge->known == false && validEdge(edge->n1, edge->n2))
                    {
                        least = edge;
                        break;
                    }
                }
                minWeight++;
            }
            int w = least->weight;
            node *u = least->n1;
            node *v = least->n2;

            if (s.Find(u->num) != s.Find(v->num))
            {
                s.Union(u->num, v->num);
                ans += w;
                // cout << u->id << " -- " << v->id << " == " << w << endl;
                edgesAccepted++;
                least->known = true;
                if (!isSwitch(u->type))
                    u->seen = true;
                v->seen = true;
            }
        }
        cout << ans << endl;
        return s;
    }
};

int main()
{
    int junctions;
    int connections;
    cin >> junctions;
    cin >> connections;

    vector<node *> Vertices;
    node *lastSwitch = NULL;
    int size2 = 0;
    for (int i = 0; i < junctions; i++)
    {
        string id;
        string type;
        cin >> id;
        cin >> type;
        node *n = new node(id, type, i);
        if (isSwitch(type))
            lastSwitch = n; // if you see a switch, set the last seen switch
        if (lastSwitch != NULL && !postSwitch(type))
            lastSwitch == NULL; // if lastSwitch has been set but we are no longer looking at lights, set to NULL
        if (postSwitch(type))
            n->parentSwitch = lastSwitch; // if lastSwitch is set and we're looking at a light, set the light's parent
        Vertices.push_back(n);
    }

    vector<edge *> Edges;
    vector<edge *> preSwitches;
    vector<edge *> switchesLights;
    vector<edge *> bridges;
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
        for (auto v : Vertices)
        {
            if (first == v->id)
            {
                num1 = v->num;
                node1 = v;
            }
            if (second == v->id)
            {
                num2 = v->num;
                node2 = v;
            }
        };
        if (validEdge(node1, node2))
        {
            edge *e = new edge(node1, node2, weight);
            Edges.push_back(e);
        };
    };

    Graph graph;
    DSU s(junctions);
    graph.edgelist = Edges;
    graph.kruskals(s, junctions);

    return 0;
}
