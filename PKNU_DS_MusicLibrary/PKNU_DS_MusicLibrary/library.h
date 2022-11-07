#ifndef LIBRARY_H
#define LIBRARY_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct song Song;
typedef struct snode SNode;
typedef struct artist Artist;

struct song
{
	Artist* artist;
	char* title;
	char* path;
	int index;
};

struct snode
{
	struct snode* next, * prev;
	Song* song;
};

struct artist
{
	char* name;
	struct artist* next; // 이름의 초성이 동일한 가수들을 단방향 리스트로 연결
	SNode* head, * tail;
};

void initialize();
Artist* create_artist_instance(char* name);
Artist* add_artist(char* name);
Song* create_song_instance(Artist* ptr_artist, char* title, char* path);
void insert_node(Artist* ptr_artist, SNode* ptr_snode);
void status();
void add_song(char* artist, char* title, char* path);
Artist* find_artist(char* name);
void print_artist(Artist* p);
void print_song(Song* ptr_song);
void load(FILE* fp);
void search_song(char* artist);
void search_song(char* artist, char* title);
void play(int index);
void save(FILE* fp);
void save_artist(Artist* p, FILE* fp);
void save_song(Song* ptr_song, FILE* fp);
void remove(int index);
SNode* find_song(int index);
void remove_snode(Artist* ptr_artist, SNode* ptr_snode);
void destroy_song(Song* ptr_song);
#endif // !1