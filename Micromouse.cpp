#include "stdafx.h"
#include <fstream>
#include "Micromouse.h"

using namespace std;

/*
Maze DataMaze;
Maze PathMaze;
_Mouse Mouse;
*/
void NewMaze(Maze *pMaze)	//Return a maze that is known to the mouse before the run
{
	unsigned char x;
	unsigned char y;
	for(x = 0; x < 16; x++)
	{
		for(y = 0; y < 16; y++)
		{
			pMaze->ucCell[y][x] = 0;
		}
	}
	for(x = 0; x < 16; x++)
	{
		pMaze->ucCell[0][x] |= SOUTH;
		pMaze->ucCell[15][x] |= NORTH;
	}
	for(y =0; y <16; y++)
	{
		pMaze->ucCell[y][0] |= WEST;
		pMaze->ucCell[y][15] |= EAST;
	}
}


void InterruptHandler(int Mode)
{
	Maze MemoryMaze;
	Maze PathMaze;
	_Mouse Mouse;

	switch(Mode)
	{
	case StartFresh:
		Mouse.Status = Initializing;
		Mouse.Head = NORTH;
		Mouse.X = 0;
		Mouse.Y = 0;
		NewMaze(&MemoryMaze);
		//Some Function
		break;
	case ReRun:
		Mouse.Status = Initializing;
		Mouse.Head = NORTH;
		Mouse.X = 0;
		Mouse.Y = 0;
		//ReadMaze(&MemoryMaze);
		//Some Function
		break;
	case Caliberate:
		//Sensor Calliberation Module
		break;
	case SaveMaze:
		//SaveMaze(&MemoryMaze);
		break;
	}
}


		


void AnalyzePath(unsigned char ucSourcePointx, unsigned char ucSourcePointy, unsigned char ucDestinationPointx, unsigned char ucDestinationPointy, Maze *pPathMaze, Maze *pDataMaze, _Mouse *pMouse)
{
	Maze *pTempMaze = new Maze;
	unsigned char ucCurrentLevel = pPathMaze->ucCell[ucSourcePointy][ucSourcePointx] & 0x7F;
	unsigned char x;
	unsigned char y;
	for(x = 0; x < 16; x++)
	{
		for(y = 0; y <16; y++)
		{
			pTempMaze->ucCell[y][x] = 0;
		}
	}
	
	pTempMaze->ucCell[ucSourcePointy][ucSourcePointx] = ucCurrentLevel | PATHASSIGNED;
	x = ucSourcePointx;
	y = ucSourcePointy;
	while(ucCurrentLevel--)
	{
		if(!(pPathMaze->ucCell[y][x] & PATHASSIGNED))
			continue;
		if((x+1)<16)
		{
			if(((pPathMaze->ucCell[y][x+1] & 0x7F) == ucCurrentLevel)&&(!(pDataMaze->ucCell[y][x]&EAST)))
			{
				pTempMaze->ucCell[y][x+1] = ucCurrentLevel | PATHASSIGNED;
				x++;
				continue;
			}
		}
		if((y+1)<16)
		{
			if(((pPathMaze->ucCell[y+1][x] & 0x7F) == ucCurrentLevel)&&(!(pDataMaze->ucCell[y][x]&NORTH)))
			{
				pTempMaze->ucCell[y+1][x] = ucCurrentLevel | PATHASSIGNED;
				y++;
				continue;
			}
		}
		if((x-1)>=0)
		{
			if(((pPathMaze->ucCell[y][x-1] & 0x7F) == ucCurrentLevel)&&(!(pDataMaze->ucCell[y][x]&WEST)))
			{
				pTempMaze->ucCell[y][x-1] = ucCurrentLevel | PATHASSIGNED;
				x--;
				continue;
			}
		}
		if((y-1)>=0)
		{			
			if(((pPathMaze->ucCell[y-1][x] & 0x7F) == ucCurrentLevel)&&(!(pDataMaze->ucCell[y][x]&SOUTH)))
			{
				pTempMaze->ucCell[y-1][x] = ucCurrentLevel | PATHASSIGNED;
				y--;
				continue;
			}
		}
	}
	for(x = 0; x < 16; x++)
	{
		for(y = 0; y <16; y++)
		{
			pPathMaze->ucCell[y][x] = pTempMaze->ucCell[y][x];
		}
	}
	delete pTempMaze;
}

void FindPath(unsigned char ucSourcePointx, unsigned char ucSourcePointy, unsigned char ucDestinationPointx, unsigned char ucDestinationPointy, Maze *pPathMaze, Maze *pDataMaze, _Mouse *pMouse)
{
	unsigned char ucLevel = 0, ucCellData, ucNextLevel = 0;
	char x, y;
	bool Continue = true;

	for(x = 0; x < 16; x++)
	{
		for(y = 0; y < 16; y++)
		{
			pPathMaze->ucCell[y][x] = 0;
		}
	}	
	
	pPathMaze->ucCell[ucDestinationPointy][ucDestinationPointx] = PATHASSIGNED;

	while(Continue)
	{
		for(x = 0; x < 16; x++ && Continue)
		{
			for(y = 15; y >= 0; y--)
			{
				if(pPathMaze->ucCell[ucSourcePointy][ucSourcePointx] & PATHASSIGNED)
				{
					Continue = false;
					break;
				}
				
				ucCellData = ucLevel|PATHASSIGNED;

				if(ucCellData == pPathMaze->ucCell[y][x])
				{
					ucNextLevel = ucLevel + 1;

					if(!(pDataMaze->ucCell[y][x] & NORTH))
					{
						if((pPathMaze->ucCell[y+1][x] & PATHASSIGNED))
						{	
							if((pPathMaze->ucCell[y+1][x] & 0x7F) > ucNextLevel)
							{
								pPathMaze->ucCell[y+1][x] = PATHASSIGNED | ucNextLevel;
							}
						}
						else
						{
							pPathMaze->ucCell[y+1][x] = PATHASSIGNED | ucNextLevel;
							
						}
					}

					if(!(pDataMaze->ucCell[y][x] & SOUTH))
					{
						if((pPathMaze->ucCell[y-1][x] & PATHASSIGNED))
						{	
							if((pPathMaze->ucCell[y-1][x] & 0x7F) > ucNextLevel)
							{
								pPathMaze->ucCell[y-1][x] = PATHASSIGNED | ucNextLevel;
								
							}
						}
						else
						{
							pPathMaze->ucCell[y-1][x] = PATHASSIGNED | ucNextLevel;
							
						}
					}

					if(!(pDataMaze->ucCell[y][x] & EAST))
					{
						if((pPathMaze->ucCell[y][x+1] & PATHASSIGNED))
						{	
							if((pPathMaze->ucCell[y][x+1] & 0x7F) > ucNextLevel)
							{
								pPathMaze->ucCell[y][x+1] = PATHASSIGNED | ucNextLevel;
								
							}
						}
						else
						{
							pPathMaze->ucCell[y][x+1] = PATHASSIGNED | ucNextLevel;
							
						}
					}

					if(!(pDataMaze->ucCell[y][x] & WEST))
					{
						if((pPathMaze->ucCell[y][x-1] & PATHASSIGNED))
						{	
							if((pPathMaze->ucCell[y][x-1] & 0x7F) > ucNextLevel)
							{
								pPathMaze->ucCell[y][x-1] = PATHASSIGNED | ucNextLevel;
								
							}
						}
						else
						{
							pPathMaze->ucCell[y][x-1] = PATHASSIGNED | ucNextLevel;
							
						}
					}
				}
			}
			
		}
		ucLevel++;
	}
	AnalyzePath(ucSourcePointx, ucSourcePointy, ucDestinationPointx, ucDestinationPointy, pPathMaze, pDataMaze, pMouse);
}


bool ReadMazeFile(char *pFileName, Maze *pMaze /*= &DataMaze*/)
{
	unsigned char ucFileData[256];
	fstream file;
	int i, j, k;

	file.open(pFileName, ios::binary | ios::in | ios::_Nocreate);
	
	file.seekg(0,ios::end);
	i = file.tellg();
	
	if(i != 256)
	{
		return false;
	}
	file.seekg(0, ios::beg);
	file.read((char*)&ucFileData, sizeof(Maze));
	file.close();
	
	k = 0;
	for( j = 0; j < 16; j++)
	{
		for( i = 0; i < 16; i++)
		{
			pMaze->ucCell[i][j] = ucFileData[k++];
			pMaze->ucCell[i][j] |= VISITED;
		}
	}
	return true;
}