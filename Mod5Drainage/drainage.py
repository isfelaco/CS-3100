def drainage(grid, solution, x, y, r, c, p):
    if x < 0 or y < 0 or x >= r or y >= c or grid[x][y] <= p:
        return 0
    elif solution[x][y] != -1:
        return solution[x][y]
    else:
        up = drainage(grid, solution, x-1, y, r, c, grid[x][y])
        down = drainage(grid, solution, x+1, y, r, c, grid[x][y])
        left = drainage(grid, solution, x, y-1, r, c, grid[x][y])
        right = drainage(grid, solution, x, y+1, r, c, grid[x][y])

        solution[x][y] = max(up, down, left, right) + 1
        return solution[x][y]

def main():
    num_inputs = int(input())
    results = []
    cities = []
    
    for i in range (0, num_inputs):
        city, r, c = input().split()
        cities.append(city)
        r = int(r)
        c = int(c)
        grid = []
        solution = [[-1] * c for _ in range(r)]
        for j in range (0, r):
            row = []
            for num in input().split():
                row.append(int(num))
            grid.append(row)
        result = -1
        for i in range (r):
            for j in range(c):
                result = max(result, drainage(grid, solution, i, j, r, c, -1))
        if c == 1:
            result = result - 1
        results.append(result)

    for i in range(0, len(cities)):
        print(cities[i] + ": " + str(results[i]))
    return 0

main()