#ifndef _Micromouse_H
#define _Micromouse_H

//Path Maze Details
#define NORTH			0x01
#define EAST			0x02
#define SOUTH			0x04
#define WEST			0x08
#define VISITED			0x10
#define PATHASSIGNED	0x80
#define SPEEDINGSECTION 0x80

//Mouse Details

//Head
#define NORTH			0x01
#define EAST			0x02
#define SOUTH			0x04
#define WEST			0x08

//Status
#define Initializing	0
#define SAVINGMAZE		1
#define SOLVING			2
#define SOLVED			3
#define LOST			4
#define FrontSensing	5
#define LeftSensing		6
#define	RightSensing	7
#define	Sensing			8

//MazeRun Mode
#define StartFresh		0
#define ReRun			1
#define GoForCenter		2
#define Caliberate		3
#define SaveMaze		4

struct Maze
{
	unsigned char ucCell[16][16];
};

struct _Mouse
{
	unsigned char X;
	unsigned char Y;
	unsigned char Head;
	unsigned char Status;
};

void FindPath(unsigned char ucSourcePointx, unsigned char ucSourcePointy, unsigned char ucDestinationPointx, unsigned char ucDestinationPointy, Maze *pPathMaze, Maze *pDataMaze, _Mouse *pMouse);
void AnalyzePath(unsigned char ucSourcePointx, unsigned char ucSourcePointy, unsigned char ucDestinationPointx, unsigned char ucDestinationPointy, Maze *pPathMaze, Maze *pDataMaze, _Mouse *pMouse);
bool ReadMazeFile(char *pFileName, Maze *pMaze);


#endif

