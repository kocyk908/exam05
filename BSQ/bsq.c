#include "bsq.h"

t_map *loadMap(char *filename)
{
	t_map 	*map = malloc(sizeof(t_map));
	FILE	*file = fopen(filename, "r");
	if (!file)
		return (printf("map error"), free(map), NULL);

	char *line;
	int	len = 0;
	size_t buf = 0;
	
	if (fscanf(file, "%d %c %c %c\n", &map->height, &map->empty, &map->obstacle, &map->full) != 4)
	{
		printf("map error");
        return (map);
    }
	if (map->empty == map->full || map->empty == map->obstacle || map->full == map->obstacle)
	{
		return (printf("map error\n"), free(map), fclose(file), NULL);
	}
	if ((map->empty <= 32 || map->empty >= 127) || (map->full <= 32 || map->full >= 127) || (map->obstacle <= 32 || map->obstacle >= 127))
	{
		return (printf("map error\n"), free(map), fclose(file), NULL);
	}
	//printf("%d, %c, %c, %c\n", map->height, map->empty, map->obstacle, map->full);

	map->grid = calloc(map->height + 1, sizeof(char *));
	
	for (int i = 0; i < map->height; i++)
	{
		line = NULL;
		len = getline(&line, &buf, file);
		//printf("len %i\n", len);
		if (line[len-1] == '\n')
			line[len-1] = '\0'; 
		if (i == 0)
		{
			map->width = strlen(line);
			if (map->width < 1)
				return (printf("map error\n"), free(map), fclose(file), NULL);
		}
		else if (strlen(line) != map->width)
		{
			return (printf("map error\n"), free(map), fclose(file), NULL);
		}
		map->grid[i] = line;
	}
	fclose(file);
	map->map = map->grid;

	return(map);
}

int min_val(int l, int ltop, int top)
{
	int min;

	min = l;
	if (ltop < min)
		min = ltop;
	if (top < min)
		min = top;
	return (min);
}

void bsq(t_map *map)
{
	t_sqr *sqr= malloc(sizeof(t_sqr));

	sqr->y = 0;
	sqr->x = 0;
	sqr->size = 0;

	int** work_map;
	work_map = malloc(map->height * sizeof(int *));
 	for (int i = 0; i < map->height; i++)
 	{
 		work_map[i] = malloc(map->width * sizeof(int));
 	}

	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->width; j++)
		{
			if (map->grid[i][j] == map->obstacle)
				work_map[i][j] = 0;
			else if (i == 0 || j == 0)
				work_map[i][j] = 1;
			else
				work_map[i][j] = min_val(work_map[i][j - 1], work_map[i - 1][j - 1], work_map[i - 1][j]) + 1;
			if (work_map[i][j] > sqr->size)
			{
				sqr->size = work_map[i][j];
				sqr->y = i;
				sqr->x = j;
			}
		}
	}
	//printf("wierzcholek (x %i, y %i), size %i, map width %i, map height %i \n", sqr->x, sqr->y, sqr->size, map->width, map->height);
	
	for(int i = 0; sqr->size > i; i++)
	{
		//printf("hello\n")
		for(int j = 0; sqr->size > j; j++)
		{
			map->map[sqr->y - i][sqr->x - j] = map->full;
		}
	}
}

void print_map(t_map *map)
{
	//printf("----wypis\n");
	for (int i = 0; i < map->height; i++)
	{
		printf("%s\n", map->map[i]);
	}
}

void print_int_map(int **map, int height, int width)
{
	//printf("----wypis workmap\n");
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			printf("%i ", map[i][j]);
		}
		printf("\n");
	}
}


int main(int argc, char *argv[])
{
	if (argc != 2)
		return (printf("map error\n"), 0);

	t_map *map = loadMap(argv[1]);
	if (map)
		bsq(map);
	if (map)
		print_map(map);
}