#include <bits/stdc++.h>
using namespace std;

struct DSU
{
    int *rank;
    int *parent;
    int size;
    DSU(int n);
    int Find(int i)
    {
        if (parent[i] != -1)
            return parent[i] = Find(parent[i]);
        return i;
    };
    void Union(int x, int y)
    {
        int s1 = Find(x);
        int s2 = Find(y);

        if (rank[s1] > rank[s2])
            parent[s2] = s1;
        else
        {
            parent[s1] = s2;
            if (rank[s1] == rank[s2])
                rank[s2] = rank[s2] + 1;
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
    Node *parentSwitch;
    bool seen;
    Node(string i, string t, int n);
} node;
Node::Node(string i, string t, int n)
{
    id = i;
    type = t;
    num = n;
    parentSwitch = NULL; // if the node is a switch, what switch does it have to connect to
    seen = false;
};

typedef struct Edge
{
    node *n1;
    node *n2;
    int weight;
    bool known;
    Edge(int w, node *f, node *s);
} edge;
Edge::Edge(int w, node *f, node *s)
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
    if (preSwitch(type1) && preSwitch(type2))
        return true;
    if (preSwitch(type1) && isSwitch(type2) && n2->seen == false)
        return true;
    if (preSwitch(type2) && isSwitch(type1) && n1->seen == false)
        return true;
    if (postSwitch(type1) && postSwitch(type2) && n1->parentSwitch == n2->parentSwitch)
        return true;
    if (isSwitch(type1) && postSwitch(type2) && n1 == n2->parentSwitch)
        return true;
    if (isSwitch(type2) && postSwitch(type1) && n2 == n1->parentSwitch)
        return true;
    return false;
}

bool compareEdges(edge *e1, edge *e2)
{
    return e1->weight <= e2->weight;
}
struct Graph
{
    vector<edge *> edgelist;

    void kruskals(DSU s, int size)
    {
        sort(edgelist.begin(), edgelist.end(), compareEdges);

        int ans = 0;
        int edgesAccepted = 0;
        int minWeight = 0;

        while (edgesAccepted < size - 1)
        {
            edge *least = NULL;

            while (least == NULL)
            {
                minWeight++;
                for (auto edge : edgelist)
                {
                    if (edge->weight == minWeight && edge->known == false && validEdge(edge->n1, edge->n2))
                    {
                        least = edge;
                        break;
                    }
                }
            }

            int w = least->weight;
            node *u = least->n1;
            node *v = least->n2;

            if (s.Find(u->num) != s.Find(v->num))
            {
                s.Union(u->num, v->num);
                ans += w;
                edgesAccepted++;
                least->known = true;
                minWeight = w - 1;

                if (isSwitch(u->type) && preSwitch(v->type))
                    u->seen = true;
                if (isSwitch(v->type) && preSwitch(u->type))
                    v->seen = true;
            }
        }
        cout << ans << endl;
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
        edge *e = new edge(weight, node1, node2);

        if (validEdge(node1, node2))
        {
            Edges.push_back(e);
        };
    };

    Graph graph;
    DSU s(junctions);
    graph.edgelist = Edges;
    graph.kruskals(s, junctions);

    return 0;
}
