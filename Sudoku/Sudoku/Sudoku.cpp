// Sudoku.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <stdio.h>
#include <cstring>
#include <cmath>

const int width = 9;
const int height = 9;

bool fillGrid(int *grid, int index);
bool testRow(int *grid, int input, int index);
bool testColumn(int *grid, int input, int index);
bool testSquare(int *grid, int input, int index);
void printGrid(int *grid, int cursor);

int _tmain(int argc, _TCHAR* argv[])
{
	
	int grid[width*height];
	memset(grid, 0, width*height*sizeof(int)); //Fill grid array with 0
	for (int i = 0; i < width*height; ++i)	//Iterate through each square of the grid to recieve input
	{
		printf("Enter Numbers into Sudoku Grid:\n");
		printGrid(grid,i);	//Print the Sudoku grid with its current values in the terminal
		int input;
		do{
			input = getc(stdin) - 48;	//Convert stdin char to in by subtracting 48
			if (input == -16)	//ASCII for space - 48 = -16
			{
				input = 0;	//0 represents an empty square
			}
		}while (!((input >= 0 && input <= 9)));	//Don't accept the input until it is either 0-9 or a space
		grid[i] = input;
	}
	if (fillGrid(grid, 0))
	{
		printGrid(grid,width*height);
	}else
		printf("No possible solution.\n");
	while (true);
	return 0;
}

bool fillGrid(int *grid, int index)
{
	if (index > width*height) //Reached end of grid, index exceeded
	{
		return true;
	}
	if (grid[index] != 0)
	{
		if (testRow(grid, grid[index], index) && testColumn(grid, grid[index], index) && testSquare(grid, grid[index], index))
		{
			if (fillGrid(grid, index + 1))
				return true;
			else
				return false;
		}else{
			return false;
		}
	}
	for (int num = 1; num <= 9; ++num)
	{
		if (testRow(grid, num, index) && testColumn(grid, num, index) && testSquare(grid, num, index))
		{
			grid[index] = num;
			if (fillGrid(grid, index + 1))
			{
				return true;
			}
			else{
				grid[index] = 0;
			}
		}
	}
	return false;
}

bool testRow(int *grid, int input, int index)
{
	int x = index % width;
	int y = floor(index / height);
	for (int i = 9 * y; i < 9 * (y + 1); ++i)
	{
		if (i != index && grid[i] == input)
			return false;
	}
	return true;
}

bool testColumn(int *grid, int input, int index)
{
	int x = index % width;
	int y = floor(index / height);
	for (int i = x; i < 72 + x; i += 9)
	{
		if (i != index && grid[i] == input)
			return false;
	}
	return true;
}

bool testSquare(int *grid, int input, int index)
{
	int x = fmod(floor(index / 3), 3);
	int y = floor(floor(index/9)/3);
	for (int row = 0; row < 3; ++row)
	{
		for (int column = 0; column < 3; ++column)
		{
			int i = 27 * y + 9 * row + 3 * x + column;
			if (i != index && grid[i] == input)
				return false;
		}
	}
	return true;
}

void printGrid(int *grid, int cursor)
{
	printf("\n\n\n");
	for (int w = 0; w < width; ++w)
	{
		printf("+---");
	}
	printf("+\n");

	for (int h = 0; h < height; ++h)
	{
		for (int w = 0; w < width; ++w)
		{
			if (w % 3 != 0 && w != 0)
				printf("  ");
			else
				printf("| ");
			if (grid[h*width + w] != 0)
			{
				printf("%d ", grid[h*width + w]);
			}
			else if (h*width + w == cursor)
			{
				printf("%c ",219);
			}
			else{
				printf("  ");
			}
		}
		printf("|\n");
		for (int w = 0; w < width; ++w)
		{
			if (h % 3 == 2)
				printf("+---");
			else
				printf("+   ");
		}
		printf("+\n");
	}
}

