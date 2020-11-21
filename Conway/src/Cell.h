#pragma once

#include <glad/glad.h>
#include <vector>

#define WINDOW_SIZE 900

#define CELL_COUNT_X 75
#define CELL_COUNT_Y 75

unsigned int CellTexture;
float* pixels;


bool CellGrid[CELL_COUNT_X][CELL_COUNT_Y];

void Cell_Initialize()
{
	pixels = new float[CELL_COUNT_X * CELL_COUNT_Y * 3];

	glGenTextures(1, &CellTexture);
	glBindTexture(GL_TEXTURE_2D, CellTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Cell_Update()
{
	std::vector<std::pair<int, int>> changes;
	for (int y = 0; y < CELL_COUNT_Y; y++)
	{
		for (int x = 0; x < CELL_COUNT_X; x++)
		{
			if (CellGrid[x][y])	// If cell is alive
			{
				int aliveNeighbours = 0;
				for (int i = -1; i <= 1; i++)
				{
					for (int j = -1; j <= 1; j++)
					{
						int tmpy = y;
						int tmpx = x;
						if (x + i < 0) tmpx = CELL_COUNT_X;
						else if (x + i >= CELL_COUNT_X) tmpx = -1;
						if (y + j < 0) tmpy = CELL_COUNT_Y;
						else if (y + j >= CELL_COUNT_Y) tmpy = -1;
						if (i == 0 && j == 0) continue;
						if (CellGrid[tmpx +i][tmpy +j]) aliveNeighbours++;
					}
				}
				if (aliveNeighbours != 2 && aliveNeighbours != 3)
					changes.push_back({ x, y });
			}
			else
			{
				int aliveNeighbours = 0;
				for (int i = -1; i <= 1; i++)
				{
					for (int j = -1; j <= 1; j++)
					{
						int tmpy = y;
						int tmpx = x;
						if (x + i < 0) tmpx = CELL_COUNT_X;
						else if (x + i >= CELL_COUNT_X) tmpx = -1;
						if (y + j < 0) tmpy = CELL_COUNT_Y;
						else if (y + j >= CELL_COUNT_Y) tmpy = -1;
						if (i == 0 && j == 0) continue;
						if (CellGrid[tmpx + i][tmpy + j]) aliveNeighbours++;
					}
				}
				if (aliveNeighbours == 3)
					changes.push_back({ x, y });
			}
		}
	}
	for (std::pair<int, int> p : changes)
	{
		CellGrid[p.first][p.second] = !CellGrid[p.first][p.second];
	}
}
void Cell_GenerateCellTexture(int texture_unit = GL_TEXTURE0)
{
	for (int y = 0; y < CELL_COUNT_Y; y++)
	{
		for (int x = 0; x < CELL_COUNT_X; x++)
		{
			glm::vec3 Color = (CellGrid[x][y]) ? glm::vec3(0.1f, 0.1f, 0.1f) : glm::vec3(1.0f, 1.0f, 1.0f);
			int xdiff = (x * 3);
			int rowsize = (CELL_COUNT_X * 3);
			int ydiff = (y * CELL_COUNT_X * 3);
			pixels[xdiff + ydiff] = Color.x;
			pixels[xdiff + ydiff + 1] = Color.y;
			pixels[xdiff + ydiff + 2] = Color.z;
		}
	}

	glActiveTexture(texture_unit);
	glBindTexture(GL_TEXTURE_2D, CellTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, CELL_COUNT_X , CELL_COUNT_Y , 0, GL_RGB, GL_FLOAT, pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
}
