#include "../lib/io.c"

#define GRID_LENGTH 10
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#define MIN(X, Y) ((X) > (Y) ? (Y) : (X))

typedef unsigned int Grid[GRID_LENGTH][GRID_LENGTH];


void read_grid(Grid grid) {
    int row = 0;
    int col = 0;
    while(read_char()) {
        if(current_char() == '\n') {
            col = 0;
            row += 1;
        } else {
            grid[row][col] = (unsigned int) current_char() - '0';
            col += 1;
        }
    }
}

void print_grid(Grid grid) {
    char row[GRID_LENGTH + 1];
    row[GRID_LENGTH] = '\n';
    write_char('\n');
    for(int i = 0; i < GRID_LENGTH; i++) {
        for(int j = 0; j < GRID_LENGTH; j++) {
            row[j] = (char) grid[i][j] + '0';
        }
        write_char_array(row, GRID_LENGTH + 1);
    }
}

void bump_neighbors(Grid grid, int row, int col) {
    for(int r = MAX(0, row - 1); r < MIN(GRID_LENGTH, row + 2); r++){
        for(int c = MAX(0, col - 1); c < MIN(GRID_LENGTH, col + 2); c ++){
            if (r == row && c == col) continue;
            grid[r][c] += 1;
        }
    }
}

int step_grid(Grid grid) {
    int new_flashes = 0;

    Grid flashed;
    for(int i = 0; i < GRID_LENGTH; i++) {
        for(int j = 0; j < GRID_LENGTH; j++) {
            grid[i][j] += 1;
            if (grid[i][j] > 9) {
                new_flashes += 1;
                flashed[i][j] = 1;
                bump_neighbors(grid, i, j);
            } else {
                flashed[i][j] = 0;
            }
        }
    }

    int total_flashes = 0;
    while(new_flashes) {
        total_flashes += new_flashes;
        new_flashes = 0;
        for(int i = 0; i < GRID_LENGTH; i++) {
            for(int j = 0; j < GRID_LENGTH; j++) {
                if(flashed[i][j]) continue;
                if(grid[i][j] > 9) {
                    new_flashes += 1;
                    flashed[i][j] = 1;
                    bump_neighbors(grid, i, j);
                }
            }
        }
    }

    for(int i = 0; i < GRID_LENGTH; i++) {
        for(int j = 0; j < GRID_LENGTH; j++) {
            if(flashed[i][j]) {
                grid[i][j] = 0;
            }
        }
    }
    return total_flashes;

}

int main() {
    Grid grid;
    read_grid(grid);
    int flashes = 0;
    int steps = 100;
    for(int step = 0; step < steps; step++) {
        flashes += step_grid(grid);
    }
    write_int(flashes);
}
