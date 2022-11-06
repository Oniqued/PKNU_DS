#ifndef LIBRARY_H
#define LIBRARY_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct song Song;
typedef struct snode SNode;
typedef struct artist Artist;

struct song {
	struct artist* artist;
	char* title;
	char* path;
	int index;
};

struct snode {
	struct snode* next, * prev;
	Song* song;
};

struct artist {
	char* name;
	struct artist* next;
	SNode* head, * tail;
};

void initialize();
void add_song(char* artist, char* title, char* path);
void status();

#endif