#include <iostream>
#include <vector>
#include <stack>
#include<ctime>
#define N 10
#define M 10

struct Cell {
    int x, y;
    bool visited;
    bool walls[4]; // top, right, bottom, left
};

std::vector<std::vector<Cell>> grid(N, std::vector<Cell>(M));
std::stack<Cell*> stack;

void removeWall(Cell& a, Cell& b) {
    int dx = a.x - b.x;
    if (dx == 1) {
        a.walls[3] = false;
        b.walls[1] = false;
    } else if (dx == -1) {
        a.walls[1] = false;
        b.walls[3] = false;
    }

    int dy = a.y - b.y;
    if (dy == 1) {
        a.walls[0] = false;
        b.walls[2] = false;
    } else if (dy == -1) {
        a.walls[2] = false;
        b.walls[0] = false;
    }
}

void generateMaze() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            grid[i][j].x = i;
            grid[i][j].y = j;
            grid[i][j].visited = false;
            for (int k = 0; k < 4; k++)
                grid[i][j].walls[k] = true;
        }
    }

    Cell* start = &grid[0][0];
    start->visited = true;
    stack.push(start);

    while (!stack.empty()) {
        Cell* current = stack.top();
        std::vector<Cell*> unvisitedNeighbors;

        // Check all four neighbors
        if (current->y > 0 && !grid[current->x][current->y - 1].visited)
            unvisitedNeighbors.push_back(&grid[current->x][current->y - 1]);
        if (current->y < M - 1 && !grid[current->x][current->y + 1].visited)
            unvisitedNeighbors.push_back(&grid[current->x][current->y + 1]);
        if (current->x > 0 && !grid[current->x - 1][current->y].visited)
            unvisitedNeighbors.push_back(&grid[current->x - 1][current->y]);
        if (current->x < N - 1 && !grid[current->x + 1][current->y].visited)
            unvisitedNeighbors.push_back(&grid[current->x + 1][current->y]);

        if (!unvisitedNeighbors.empty()) {
            Cell* chosen = unvisitedNeighbors[rand() % unvisitedNeighbors.size()];
            removeWall(*current, *chosen);
            chosen->visited = true;
            stack.push(chosen);
        } else {
            stack.pop();
        }
    }
}

void printMaze() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i == 0 && j == 0)
                std::cout << "S "; // Start position
            else if (i == N - 1 && j == M - 1 && grid[i][j].walls[0])
                std::cout << "E "; // End position
            else
                std::cout << (grid[i][j].walls[0] ? "# " : "  ");
        }
        std::cout << "\n";
        for (int j = 0; j < M; j++) {
            if (i == N - 1 && j == M - 1)
                continue;
            else {
                std::cout << (grid[i][j].walls[3] ? "#" : " ");
                std::cout << (grid[i][j].walls[1] ? "#" : " ");
            }
        }
        std::cout << "\n";
    }
}


int main() {
    srand(time(0));
    generateMaze();
    printMaze();
    return 0;
}
