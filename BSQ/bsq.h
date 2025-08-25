#ifndef BSQ_H
# define BSQ_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>

typedef struct s_map
{
	int height;
	int width;
	char **grid;
	char **map;
	char obstacle;
	char empty;
	char full;
	int lines;
} t_map;

typedef struct s_sqr
{
	int y;
	int x;
	int size;
} t_sqr;

void firstline(char *line, t_map map);
void print_map(t_map *map);
void print_int_map(int **map, int height, int width);

#endif