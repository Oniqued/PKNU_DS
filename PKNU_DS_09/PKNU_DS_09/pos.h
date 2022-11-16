#ifndef POS_H
#define POS_H
#include <stdbool.h>

//πÊ«‚
#define UP 0
#define RIGHT_UP 1
#define RIGHT 2
#define RIGHT_DOWN 3
#define DOWN 4
#define LEFT_DOWN 5
#define LEFT 6
#define LEFT_UP 7

typedef struct pos {
	int x, y;
}Position;

Position moveTo(Position pos, int dir);

#endif POS_H