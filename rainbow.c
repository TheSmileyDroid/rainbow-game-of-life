#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define ITERNUM 100
#define DEFAULT_N 10

float getCell(float **grid, int i, int j, int N)
{
    if (i < 0)
    {
        i = N - 1;
    }
    else if (i >= N)
    {
        i = 0;
    }
    if (j < 0)
    {
        j = N - 1;
    }
    else if (j >= N)
    {
        j = 0;
    }
    return grid[i][j];
}

int getNeighbors(float **grid, int i, int j, int N)
{
    int neighbors = 0;
    if (getCell(grid, i - 1, j - 1, N) > 0.0)
    {
        neighbors++;
    }
    if (getCell(grid, i - 1, j, N) > 0.0)
    {
        neighbors++;
    }
    if (getCell(grid, i - 1, j + 1, N) > 0.0)
    {
        neighbors++;
    }
    if (getCell(grid, i, j - 1, N) > 0.0)
    {
        neighbors++;
    }
    if (getCell(grid, i, j + 1, N) > 0.0)
    {
        neighbors++;
    }
    if (getCell(grid, i + 1, j - 1, N) > 0.0)
    {
        neighbors++;
    }
    if (getCell(grid, i + 1, j, N) > 0.0)
    {
        neighbors++;
    }
    if (getCell(grid, i + 1, j + 1, N) > 0.0)
    {
        neighbors++;
    }
    return neighbors;
}

void swap(float ***grid, float ***newgrid)
{
    float **temp = *grid;
    *grid = *newgrid;
    *newgrid = temp;
}

void iterate(float **grid, float **newgrid, int x, int y)
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            int neighbors = getNeighbors(grid, i, j, x);
            if (grid[i][j] > 0.0)
            {
                if (neighbors < 2)
                {
                    newgrid[i][j] = 0.0;
                }
                else if (neighbors == 2 || neighbors == 3)
                {
                    newgrid[i][j] = 1.0;
                }
                else if (neighbors > 3)
                {
                    newgrid[i][j] = 0.0;
                }
            }
            else
            {
                if (neighbors == 3)
                {
                    newgrid[i][j] = 1.0;
                }
                else
                {
                    newgrid[i][j] = 0.0;
                }
            }
        }
    }
}

int numberOfCells(float **grid, int N)
{
    int cells = 0;
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - 1; j++)
        {
            if (grid[i][j] > 0.0)
            {
                cells++;
            }
        }
    }
    return cells;
}

void clearStdout() { printf("\033[H\033[J"); }

void printGrid(float **grid, int N, int i)
{
    clearStdout();
    printf("Número de Células: %d \n", numberOfCells(grid, N));
    for (int i = 0; i < N; i++)
    {
        printf("|");
        for (int j = 0; j < N; j++)
        {
            if (grid[i][j] == 0.0)
            {
                printf("\033[1;30m██\033[0m");
            }
            else if (grid[i][j] == 1.0)
            {
                printf("\033[1;31m██\033[0m");
            }
            else
            {
                printf("\033[1;32m██\033[0m");
            }
        }
        printf("|\n");
    }
    printf("Iteração: %d\n", i);
}

void addGlider(float **grid, int x, int y)
{
    grid[x][y + 1] = 1.0;
    grid[x + 1][y + 2] = 1.0;
    grid[x + 2][y] = 1.0;
    grid[x + 2][y + 1] = 1.0;
    grid[x + 2][y + 2] = 1.0;
}

int main(int argc, char *argv[])
{
    int N;

    if (argc <= 2)
    {
        N = DEFAULT_N;
    }
    else
    {
        N = atoi(argv[1]);
    }

    float **grid = (float **)malloc(sizeof(float *) * N);
    float **newgrid = (float **)malloc(sizeof(float *) * N);

    for (int i = 0; i < N; i++)
    {
        grid[i] = (float *)malloc(sizeof(float) * N);
        newgrid[i] = (float *)malloc(sizeof(float) * N);

        for (int j = 0; j < N; j++)
        {
            grid[i][j] = 0.0;
            newgrid[i][j] = 0.0;
        }
    }

    addGlider(grid, 1, 1);

    printGrid(grid, N, 0);
    sleep(1);

    for (int i = 0; i < ITERNUM; i++)
    {
        iterate(grid, newgrid, N, N);
        printGrid(newgrid, N, i);
        swap(&grid, &newgrid);
        usleep(200000);
    }

    printf("Número de Células: %d \n", numberOfCells(newgrid, N));

    for (int i = 0; i < N; i++)
    {
        free(grid[i]);
        free(newgrid[i]);
    }
    free(grid);
    free(newgrid);

    return 0;
}
