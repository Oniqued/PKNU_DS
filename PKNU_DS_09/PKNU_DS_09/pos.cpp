#include "pos.h"

//����
//UP 0
//RIGHT_UP 1
//RIGHT 2
//RIGHT_DOWN 3
//DOWN 4
//LEFT_DOWN 5
//LEFT 6
//LEFT_UP 7

//Ư�� �������� �̵��� �� x,y ��ǥ�� ��ȭ��
int offset[8][2] = { 
	{-1,0}, //0
	{-1,1}, //1
	{0,1},  //2
	{1,1},  //3
	{-1,0}, //4
	{1,-1}, //5
	{0,-1}, //6
	{-1,-1} //7
};

Position moveTo(Position pos, int dir) {
	Position next;
	next.x = pos.x + offset[dir][0];
	next.y = pos.y + offset[dir][1];
	return next;
}
