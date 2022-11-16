#include "pos.h"

//방향
//UP 0
//RIGHT 1
//DOWN 2
//LEFT 3
//RIGHT_UP 4
//RIGHT_DOWN 5
//LEFT_DOWN 6
//LEFT_UP 7

//특정 방향으로 이동할 때 x,y 좌표의 변화량
int offset[8][2] = { 
	{-1,0}, //0
	{0,1}, //1
	{1,0},  //2
	{0,-1},  //3
	{-1,1}, //4
	{1,1}, //5
	{1,-1}, //6
	{-1,-1} //7
};

Position moveTo(Position pos, int dir) {
	Position next;
	next.x = pos.x + offset[dir][0];
	next.y = pos.y + offset[dir][1];
	return next;
}
