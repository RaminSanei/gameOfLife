#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

void draw(void *u, int w, int h)
{
    char (*world)[w] = u;
    printf("\033[H");
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            printf(world[y][x] ? "@" : " ");
        }
        printf("\n");
    }
}

void evolution(void *u, int w, int h)
{
    char(*world)[w] = u;
    char new[h][w];

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            int n = 0;

            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    if (dx == 0 && dy == 0) continue;

                    int nx = (x + dx + w) % w;  
                    int ny = (y + dy + h) % h; 
                    n += world[ny][nx];       
                }
            }

            new[y][x] = (n == 3 || (n == 2 && world[y][x]));
        }
    }

    memcpy(world, new, sizeof(char) * h * w);
}


int main()
{
    const int w = 50, h = 50;
    char world[h][w];
    const int threshold = RAND_MAX / 10;

    srand(time(0));  
    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            world[y][x] = (rand() < threshold) ? 1 : 0;
        }
    }

    while (1)
    {
        draw(world, w, h);
        evolution(world, w, h);
        usleep(200000); 
    }

    return 0;
}
