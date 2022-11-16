#ifndef POS_H
#define POS_H
#include <stdbool.h>

//πÊ«‚
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define RIGHT_UP 4
#define RIGHT_DOWN 5
#define LEFT_DOWN 6
#define LEFT_UP 7

typedef struct pos {
	int x, y;
}Position;

Position moveTo(Position pos, int dir);

#endif POS_H