// Sudoku.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <stdio.h>
#include <cstring>
#include <cmath>

const int width = 9;
const int height = 9;

bool fillGrid(int *grid, int index);	//Recursive function to find solution
bool testValue(int *grid, int input, int index);	//Check the three conditions for a valid input (row, column, and square)
bool testRow(int *grid, int input, int index);	//Compare input value at index location with other cells in its row
bool testColumn(int *grid, int input, int index);	//Compare input value at index location with other cells in its column
bool testSquare(int *grid, int input, int index);	//Compare input value at index location with other cells within its 3x3 square
void printGrid(int *grid, int cursor);	//Print out grid with known values. If a cursor index location is given, draw a cursor at said location.

int _tmain(int argc, _TCHAR* argv[])
{
	int grid[width*height];
	memset(grid, 0, width*height*sizeof(int)); //Fill grid array with 0
	for (int i = 0; i < width*height; ++i)	//Iterate through each square of the grid to recieve input
	{
		printf("\n\n\n");
		printGrid(grid,i);	//Print the Sudoku grid with its current values in the terminal. 'i' represents the cursor location
		printf("\nEnter Numbers into Sudoku Grid: ");
		int input;
		do{
			input = getc(stdin) - 48;	//Convert stdin char to int by subtracting 48
			if (input == -16)	//ASCII for space - 48 == -16
			{
				input = 0;	//0 represents an empty square
			}
			if (!(testValue(grid, input, i)) && input != 0)	//Check if the new value interferes with existing values or if the value is zero.
			{
				printf("\n\n\n");
				printGrid(grid, i);	//Print the Sudoku grid with its current values in the terminal. 'i' represents the cursor location
				printf("%d interferes with existing numbers.\n", input);
				printf("Enter Numbers into Sudoku Grid: ");
				input = -1;	//Set input to an invalid value (-1) so the while loop continues.
			}
		}while (!(input >= 0 && input <= 9));	//Don't accept the input until it is 0-9
		grid[i] = input;	//Once a valid input is recognised, add it to the grid
	}
	if (fillGrid(grid, 0))	//Run the recursive fill function, starting at index 0. If it returns true, the grid filled successfully. If false, no solution exists.
	{
		printf("\n\n\nSolution:\n\n");
		printGrid(grid,width*height);	//Print the final grid. Place the cursor at index width*height so that it cannot be seen.
	}
	else {
		printf("\n\n\n");
		printf("No possible solution.\n");
	}
	while (true);
	return 0;
}

bool fillGrid(int *grid, int index)	//Starting with one index, try each number until no interference is found. Then, call this function on the next index. If that cell cannot find a possible value, it will return false.
{									//If so, try the next possible value. Continue through the cells until either a solution is found or none is possible.
	if (index > width*height) //Reached end of grid, index exceeded
	{
		return true;	//Return true, indicating that the grid has been solved.
	}
	if (grid[index] != 0)	//If the current cell is not empty, check if it's valid, then call this function on the next index.
	{
		if (testValue(grid, grid[index], index))	//Check validity of cell
		{
			if (fillGrid(grid, index + 1))	//Call fillGrid() on the following index
			{
				return true;	//If the following index returned true, the grid has been solved, so this function can also return true.
			}else{
				return false;	//If the following index returned false, there are no possible solutions given the previous cells' configurations.
			}
		}else{
			return false;	//If the current cell was already filled and deemed to be not valid, the initial conditions are not valid. Return false.
		}
	}
	for (int num = 1; num <= 9; ++num)	//Iterate through the 9 possible values to be added to the cell.
	{
		if (testValue(grid, num, index))	//Verify if a number does not interfere with any existing cells
		{
			grid[index] = num;	//Set the current index to the new number
			if (fillGrid(grid, index + 1))	//Call the recursive function on the next cell. If it returns true, the grid has been solved.
			{
				return true;
			}
			else{	//If the function returns false, no possible solution exists for the current configuration. Reset the current cell to blank, so the next number can be tried.
				grid[index] = 0;
			}
		}
	}
	return false;	//If all the numbers have been tried and no return function has been met, there exists no solution given the current configuration.
}

bool testValue(int *grid, int input, int index)
{
	return testRow(grid, input, index) && testColumn(grid, input, index) && testSquare(grid, input, index);	//Return true if all three checks return true, false if there are any interferences
}

bool testRow(int *grid, int input, int index)
{
	int y = floor(index / height);	//Determine the y-coordinate of the index on a 9x9 grid.
	for (int i = 9 * y; i < 9 * (y + 1); ++i)	//Beginning on the leftmost cell of the current row, iterate through the 9 cells of the row.
	{
		if (i != index && grid[i] == input)	//If the value being checked matches any of the other cells, return false, indicating that the input is invalid.
			return false;
	}
	return true;	//Return true if none of the cells in the row match the value.
}

bool testColumn(int *grid, int input, int index)
{
	int x = index % width;	//Determine the x-coordinate of the index on a 9x9 grid.
	for (int i = x; i < 72 + x; i += 9)	//Beginning at the topmost cell of the current column, iterate through the 9 cells of the column.
	{
		if (i != index && grid[i] == input) //If the value being checked matches any of the other cells, return false, indicating that the input is invalid.
			return false;
	}
	return true;	//Return true if none of the cells in the column match the value.
}

bool testSquare(int *grid, int input, int index)
{
	int x = fmod(floor(index / 3), 3);	//Determine the x-coordinate of the cell's box in the 3x3 grid
	int y = floor(floor(index/9)/3);	//Determine the y-coordinate of the cell's box in the 3x3 grid
	for (int row = 0; row < 3; ++row)	//Iterate through the 9 cells within the box
	{
		for (int column = 0; column < 3; ++column)
		{
			int i = 27 * y + 9 * row + 3 * x + column;	//Determine the original index within the sudoku grid given the cell's position within its box
			if (i != index && grid[i] == input)	//If the value being checked matches any of the other cells, return false, indicating that the input is invalid.
				return false;
		}
	}
	return true;	//Return true if none of the cells in the column match the value.
}

void printGrid(int *grid, int cursor)
{
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

