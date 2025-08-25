#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


void print_map(int h, int w, int board[h][w])
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			printf("%d ", board[i][j]);
		}
		printf("\n");
	}
}

void print_map_c(int h, int w, char **board)
{
	printf("mapa\n");
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			printf("%c", board[i][j]);
		}
		printf("\n");
	}
}


void duplicate_map(int h, int w, int board[h][w], int submap[h][w])
{
	for(int i = 0; i < h; i++)
	{
		for(int j = 0; j < w; j++)
		{
			submap[i][j] = board[i][j];
		}
	}	
}

	void print_neighbors(int l, int ltop, int lbot, int top, int rtop, int r, int rbot, int bot) {
		printf("l=%d ltop=%d lbot=%d top=%d rtop=%d r=%d rbot=%d bot=%d",
			l, ltop, lbot, top, rtop, r, rbot, bot);
	}

int sum_nbrs(int h, int w, int board[h][w], int i, int j)
{
	int l = board[i][j-1];
	int ltop = board[i-1][j-1];
	int lbot = board[i+1][j-1];
	int top = board[i-1][j];
	int rtop = board[i-1][j+1];
	int r = board[i][j+1];
	int rbot = board[i+1][j+1];
	int bot = board[i+1][j];

	int sum = 0;
	if (i-1 < 0)
	{
		ltop = 0;
		top = 0;
		rtop = 0;
	}
	if (j-1 < 0)
	{
		ltop = 0;
		l = 0;
		lbot = 0;
	}
	if (i+1 > h-1)
	{
		lbot = 0;
		bot = 0;
		rbot = 0;
	}
	if (j+1 > w-1)
	{
		r = 0;
		rtop = 0;
		rbot = 0;
	}

	sum = l + ltop + lbot + top + rtop + r + rbot + bot;
	//printf("kordy: (%i, %i) ", j, i);
	//print_neighbors(l, ltop, lbot, top, rtop, r, rbot, bot);
	//printf(" sum %i\n", sum);
	return (sum);
}

void int_to_char_map(int h, int w, char **map, int board[h][w])
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (board[i][j] == 0)
			{
				map[i][j] = ' ';
			}
			else if (board[i][j] == 1)
			{
				map[i][j] = '0';
			}
		}
	}
}

int main(int argc, char** argv)
{
	if (argc != 4)
		return (printf("zla ilosc arg"));
	int w = atoi(argv[1]);
	int h = atoi(argv[2]);
	int iter = atoi(argv[3]);

	int board[h][w];

	for(int i = 0; i < h; i++)
	{
		for(int j = 0; j < w; j++)
		{
			board[i][j] = 0;
		}
	}
	//board[h][w] = 1;
	//print_map(board, h, w);
	//printf("%i %i %i", w, h, iter);
	//printf("%i", board[h][w]);
	int y = 0;
	int x = 0;
	int pen_up = -1;
	char cmd;
	while(read(0,&cmd,1) == 1)
	{
		printf("%c ", cmd);
		if (cmd == 'x')
		{
			pen_up *= -1;
		}
		else if (cmd == 'w')
		{
			if (y > 0) y--;
		}
		else if (cmd == 'a' && x > 0)
		{
			if (x > 0) x--;
		}
		else if (cmd == 's' && y < h)
		{
			if (y < h) y++;
		}
		else if (cmd == 'd' && x < w)
		{
			if (x < w) x++;
		}
		if (pen_up == 1)
			board[y][x] = 1;
		printf("x: %i, y: %i\n", x, y);
	}
	printf("startowa mapa: \n");
	print_map(h, w, board);
	printf("\n");

	int submap[h][w];

	duplicate_map(h, w, board, submap);
	//print_map(h, w, submap);

	char **mapa = malloc(h * sizeof(char *));
	for (int i = 0; i < h; i++)
	{
    	mapa[i] = malloc(w * sizeof(char));
	}

	for (int i = 0; i < h; i++)
	{
	    for (int j = 0; j < w; j++)
		{
	        mapa[i][j] = ' ';
	    }
	}
	for (int i = 0; i < iter; i++)
	{
		duplicate_map(h, w, board, submap);
		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w; x++)
			{
				if (submap[y][x] == 1 && (sum_nbrs(h, w, submap, y, x) == 2 || sum_nbrs(h, w, submap, y, x) == 3))
				{
					board[y][x] = 1;
				}
				else if (submap[y][x] == 1 && (sum_nbrs(h, w, submap, y, x) != 2 && sum_nbrs(h, w, submap, y, x) != 3))
				{
					board[y][x] = 0;
				}
				else if (submap[y][x] == 0 && sum_nbrs(h, w, submap, y, x) == 3)
					board[y][x] = 1;
				//printf("kordy: (%i,%i), wartosc: %i, %i\n", x, y, board[y][x], sum_nbrs(h, w, board, y, x));
			}
		}
		int_to_char_map(h, w, mapa, board);

		printf("zmiany iteracji (%i): \n", i);
		//print_map(h, w, board);
		print_map_c(h, w, mapa);
	}
	printf("\nmapa koniec\n");
	print_map_c(h, w, mapa);
	//print_map(h, w, board);
}
