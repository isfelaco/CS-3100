def DFS(currentNode, visited, G, nodes, size):
    visited.append(currentNode)

    if currentNode == "T":
        return

    index = nodes.index(currentNode)

    for i in range(size):
        if nodes[i] not in visited and G[index][i] != 0:
            G[index][i] -= 1
            G[i][index] += 1
            return DFS(nodes[i], visited, G, nodes, size)


def scheduling(r, c, n):
    r = int(r)  # num student registration request
    c = int(c)  # num courses
    n = int(n)  # num classes per student
    
    valid = "Yes"
    # if r == 0 or n == 0:
    #     valid = "No"
    if r == 0:
        # print("huh")
        for i in range(0, c):
            input()
        input()
        print(valid)
        return
    else:
        # print("here", r, c, n)
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
        # for row in G:
        #     print(row)
        # print()

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
                # G.append([0]*size)
                # print(index, size-1)
                G[index][size-1] = int(row[1])
        visited = []
        while len(visited) != 1:
            visited = []
            DFS(nodes[0], visited, G, nodes, size)

    # valid = "Yes"
        # for row in G:
        #     print(row)
        for student in students:
            index = nodes.index(student)
            if G[0][index] != 0:
                valid = "No"
        if n == 0:
            valid = "Yes"
        print(valid)
        input()
        return

def main():
    while True:
        line = input()
        # print(line)

        if line == "0 0 0":
            break
        else:
            r, c, n = line.split()
            scheduling(r, c, n)
    return

main()