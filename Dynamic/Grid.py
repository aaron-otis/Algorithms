files = ["custom1", "test1.txt", "test2.txt", "test3.txt", "demo1.txt", "demo2.txt", "demo3.txt"]

def read_file(filename):
    with open(filename) as f:
        m = []

        next(f)
        next(f)
        for line in f:
            m.append([int(i) for i in line[:-1].split()])

        return m

def prompt():
    for i in range(len(files)):
        print(str(i + 1) + ": " + files[i])

    return int(input("Choose a file. Enter 0 to exit: "))

def get_max(grid, table, x, y):
    m = 0

    if y > 0:
        if x > 0:
            m = max(table[x][y - 1][0], table[x - 1][y][0])
            if m == table[x][y - 1][0]:
                p = 2
            else:
                p = 1
        else:
            m = table[x][y - 1][0]
            p = 2
    elif x > 0:
        m = table[x - 1][y][0]
        p = 1

    m = max(m + grid[x][y], grid[x][y])
    if m > grid[x][y]:
        ret = m, p
    else:
        ret = m , 0

    return ret

def get_path(table, pos):
    path = [pos]
    x = pos[0]
    y = pos[1]

    while table[x][y][1]:
        if table[x][y][1] == 1:
            x -= 1
        elif table[x][y][1] == 2:
            y -= 1
        else:
            ValueError("This shouldn't be happening!")

        path.insert(0, (x, y))

    return path

val = prompt()
while(val):
    if val <= len(files) and val > 0:
        solution = 0
        position = 0, 0

        grid = read_file(files[val - 1])
        table = [[0 for x in range(len(grid[0]))] for x in range(len(grid))]
        for x in range(len(grid)):
            for y in range(len(grid[x])):
                table[x][y] = get_max(grid, table, x, y)

        for x in range(len(table)):
            if table[x][len(table[0]) - 1][0] > solution:
                solution = table[x][len(table[0]) - 1][0]
                position = x, len(table[0]) - 1

        for y in range(len(table[0]) - 1):
            if table[len(table) - 1][y][0] > solution:
                solution = table[len(table) - 1][y][0]
                position = len(table) - 1, y

        print("Solution: " + str(solution))
        path = get_path(table, position)

        if len(path) > 10:
            print(path[:4])
            print(path[-4:])
        else:
            print(path)
    else:
        print(str(val) + " is not a valid selection")

    print
    val = prompt();
