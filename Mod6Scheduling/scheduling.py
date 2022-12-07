def BFS(G, s, t, parent, size, nodes):
        visited = [False]*(size)
        queue = []
        queue.append(s)
        visited[s] = True

        while queue:
            u = queue.pop(0)
     
            for ind, val in enumerate(G[u]):
                if visited[ind] == False and val > 0:
                    queue.append(ind)
                    visited[ind] = True
                    parent[ind] = u
                    if ind == t:
                        return True
        return False

def FordFulkerson(source, sink, G, nodes, size): 
        parent = [-1]*(size)
        max_flow = 0

        while BFS(G, source, sink, parent, size, nodes):
            path_flow = float("Inf")
            s = sink

            while(s != source):
                path_flow = min (path_flow, G[parent[s]][s])
                s = parent[s]
 
            max_flow +=  path_flow
            v = sink
            while(v !=  source):
                u = parent[v]
                G[u][v] -= path_flow
                G[v][u] += path_flow
                v = parent[v]
 
        return max_flow


def scheduling(r, c, n):
    r = int(r)  # num student registration request
    c = int(c)  # num courses
    n = int(n)  # num classes per student
    
    valid = "Yes"
    if r == 0:
        for i in range(0, c):
            input()
        input()
        print(valid)
        return
    else:
        nodes = ["S"]
        students = []
        edges = []
        for i in range(r):
            name, course = input().split(" ")
            course = course.strip()
            if name not in nodes:
                nodes.append(name)
            if name not in students:
                students.append(name)
            if course not in nodes:
                nodes.append(course)
            i1 = nodes.index(name)
            i2 = nodes.index(course)
            edges.append([i1, i2])
        nodes.append("T")

        size = len(students) + c + 2
        G = []	
        for i in range(size):	
            G.append([0]*size)

        for student in students:
            index = nodes.index(student)
            G[0][index] = n
        for edge in edges:
            i1 = edge[0]
            i2 = edge[1]
            G[i1][i2] = 1
        if c != 0:
            for i in range(c):
                row = input().split()
                course = row[0]
                if course not in nodes:
                    nodes.append(course)
                index = nodes.index(course)
                G[index][size-1] = int(row[1])

        max_flow = FordFulkerson(0, size-1, G, nodes, size)
        if max_flow != len(students) * n:
            valid = "No"

        if n == 0:
            valid = "Yes"
        print(valid)

        input()
        return

def main():
    while True:
        line = input()
        if line == "0 0 0":
            break
        else:
            r, c, n = line.split()
            scheduling(r, c, n)
    return

main()