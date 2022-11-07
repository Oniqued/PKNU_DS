#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include "library.h"
#include "string_tools.h"

#define NUM_CHARS 256 //2^8 = 256
#define SIZE_INDEX_TABLE 100
#define BUFFER_LENGTH 200

Artist* artist_directory[NUM_CHARS];
SNode* index_directory[100];

int num_index = 0;

Artist* find_artist(char* name);
Song* create_song_instance(Artist* ptr_artist, char* title, char* path);
void insert_node(Artist* ptr_artist, SNode* ptr_snode);
void print_artist(Artist* p);
void print_song(Song* ptr_song);
SNode* find_snode(Artist* ptr_artist, char* title);
void insert_to_index_directory(Song* ptr_song);
void save_artist(Artist* p, FILE* fp);
void save_song(Song* ptr_song, FILE* fp);
void destroy_song(Song* ptr_song);
void remove_snode(Artist* ptr_artist, SNode* ptr_snode);

void initialize() // Aritst 배열과 INDEX 배열을 초기화
{
	for (int i = 0; i < NUM_CHARS; i++)
		artist_directory[i] = NULL;

	for (int i = 0; i < SIZE_INDEX_TABLE; i++)
		index_directory[i] = NULL;
}

void load(FILE* fp)
{
	char buffer[BUFFER_LENGTH];
	char* name, * title, * path;

	while (1)
	{
		if (read_line(fp, buffer, BUFFER_LENGTH) <= 0)
			break;
		name = strtok(buffer, "#");	// 공백문자 전까지 tokenize하여 저장
		if (strcmp(name, " ") == 0) // 이름이 존재하지 않는다면
			name = NULL;
		else
			name = strdup(name); // 이름을 복제하여 저장

		title = strtok(NULL, "#");	// 공백문자 전까지 tokenize하여 저장
		if (strcmp(title, " ") == 0) // 이름이 존재하지 않는다면
			title = NULL;
		else
			title = strdup(title); // 이름을 복제하여 저장

		path = strtok(NULL, "#");	// 공백문자 전까지 tokenize하여 저장
		if (strcmp(path, " ") == 0) // 이름이 존재하지 않는다면
			path = NULL;
		else
			path = strdup(path); // 이름을 복제하여 저장
		//printf("%s %s %s\n", name, title, path);
		add_song(name, title, path);
	}
}

Artist* create_artist_instance(char* name) // Artist 객체를 생성하는 함수
{
	Artist* ptr_artist = (Artist*)malloc(sizeof(Artist));
	ptr_artist->name = name;
	ptr_artist->head = NULL;
	ptr_artist->tail = NULL;
	ptr_artist->next = NULL;
	return ptr_artist;
}

Artist* add_artist(char* name)
{
	// Artist 객체를 만드는 일을 함수에게 맡김
	Artist* ptr_artist = create_artist_instance(name);
	Artist* p = artist_directory[(unsigned char)name[0]]; // 새롭게 만들 연결리스트의 첫 번째(배열의 이름)
	Artist* q = NULL;	// 연결 리스트에서 p를 따라가며 위치를 기억하는 용도

	while (p != NULL && strcmp(p->name, name) < 0)	// ordered list에서 p보다 작은 값이 나타날 때 까지
	{
		q = p;
		p = p->next;
	}

	if (p == NULL && q == NULL) // 리스트가 비어있을 때. 즉 p가 유일한 노드가 됨
	{
		artist_directory[(unsigned char)name[0]] = ptr_artist;
	}
	else if (q == NULL)	// p가 맨 앞에 위치함
	{
		ptr_artist->next = artist_directory[(unsigned char)name[0]];
		artist_directory[(unsigned char)name[0]] = ptr_artist;
	}
	else
	{
		ptr_artist->next = p;
		q->next = ptr_artist;
	}

	return ptr_artist;
}

Song* create_song_instance(Artist* ptr_artist, char* title, char* path)
{
	Song* ptr_song = (Song*)malloc(sizeof(Song));
	ptr_song->artist = ptr_artist;
	ptr_song->title = title;
	ptr_song->path = path;
	ptr_song->index = num_index;
	num_index++;

	return ptr_song;
}

void insert_node(Artist* ptr_artist, SNode* ptr_snode)
{
	SNode* p = ptr_artist->head;

	// head에 저장된 값보다 ptr_snode에 저장된 제목이 클 때까지 while문 반복
	while (p != NULL && strcmp(p->song->title, ptr_snode->song->title) < 0)
		p = p->next;
	// p가 ptr_snode가 들어갈 자리보다 한 자리 뒤에 있기 때문에 p의 앞 위치에 새로운 snode를 대입
	// 1. 연결리스트가 비어있을 때 2. 맨 앞에 대입할 때 3. 맨 뒤에 대입할 때 4. 노래 사이에 대입
	if (ptr_artist->head == NULL) { // 1번 케이스
		ptr_artist->head = ptr_snode;
		ptr_artist->tail = ptr_snode;	// 리스트의 유일한 곡이기 때문에 이중연결리스트의 head와 tail이 모두 ptr_snode
	}
	else if (p == ptr_artist->head) { // 2번 케이스.
		ptr_snode->next = ptr_artist->head;
		ptr_artist->head->prev = ptr_snode;
		ptr_artist->head = ptr_snode; // 새로운 곡이 곡 리스트의 첫 번째 곡 자리에 위치함
	}
	else if (p == NULL) { // 3번 케이스. 
		ptr_snode->prev = ptr_artist->tail;
		ptr_artist->tail->next = ptr_snode;
		ptr_artist->tail = ptr_snode;
	}
	else {	// 4번 케이스. p 앞에 노래를 추가
		ptr_snode->next = p;
		ptr_snode->prev = p->prev;
		p->prev->next = ptr_snode;
		p->prev = ptr_snode;
	}
}

void insert_to_index_directory(Song* ptr_song)	// 단방향 연결리스트
{
	SNode* ptr_snode = (SNode*)malloc(sizeof(SNode));
	ptr_snode->song = ptr_song;
	ptr_snode->next = NULL;
	ptr_snode->prev = NULL;

	int index = ptr_song->index % SIZE_INDEX_TABLE; // 노래의 인덱스를 배열의 크기로 나눈 나머지
	// add the snode into the single linked list at index_table[index]
	SNode* p = index_directory[index];	// 해당 인덱스의 첫 번째 곡의 주소
	SNode* q = NULL; // 단방향 연결리스트를 ordered list로 만들기 위한 조건
	while (p != NULL && strcmp(p->song->title, ptr_song->title) < 0) {	// 알파벳순 정렬
		q = p;	// p보다 한 순서 뒤에 있는 노드
		p = p->next;
	}
	if (q == NULL) { // 첫 번째 위치에 저장
		ptr_snode->next = p;
		index_directory[index] = ptr_snode; // 해당 인덱스의 첫 번째 곡이 됨
	}
	else {	// add after q
		ptr_snode->next = p;
		q->next = ptr_snode;
	}
}

void add_song(char* artist, char* title, char* path)
{
	// 가수가 이미 존재하는 경우
	// 존재하지 않는다면 NULL return
	Artist* ptr_artist = find_artist(artist);	// 가수를 찾아서 Artist 포인터를 return
	if (ptr_artist == NULL)	// 만약 가수가 플레이리스트에 존재하지 않는다면
	{
		ptr_artist = add_artist(artist); // artist라는 이름을 가진 Artist 객체를 하나 추가하여 그 주소를 리턴
	}

	Song* ptr_song = create_song_instance(ptr_artist, title, path);
	SNode* ptr_snode = (SNode*)malloc(sizeof(SNode));
	ptr_snode->song = ptr_song;	// SNode들끼리 이중연결리스트로 연결되는 구조.
	ptr_snode->next = NULL; // 의도치 않은 실수를 방지하기 위해 구조체의 포인터 값은 null로 설정해주는 것도 좋음

	// insert node
	insert_node(ptr_artist, ptr_snode);
	insert_to_index_directory(ptr_song);
}

Artist* find_artist(char* name)
{
	Artist* p = artist_directory[(unsigned char)name[0]]; // 찾는 가수가 속한 초성 그룹의 첫 번째 가수. 배열의 이름이 곧 주소이기 때문!
	/* name[0] : 00000000 ~ 11111111 */
	// int에서 첫 비트 1은 음수를 나타냄
	// 때문에 unsigned char로 형변환
	// char = 8bit, int = 32bit

	while (p != NULL && strcmp(p->name, name) < 0)	// 알파벳 순으로 더 큰 이름이 나온다면 굳이 끝까지 읽을 필요x
		p = p->next; // 이름을 찾을 때 까지 p는 다음 노드로 이동

	if (p != NULL && strcmp(p->name, name) == 0)
		return p;	// p가 NULL이라면 NULL return, name을 찾으면 p를 return
	else
		return NULL;
}

void status()
{
	for (int i = 0; i < NUM_CHARS; i++)
	{
		Artist* p = artist_directory[i];	// 배열의 이름이 곧 주소이기 때문에, 배열의 
		while (p != NULL)
		{
			print_artist(p);
			p = p->next;
		}
	}
}

void print_artist(Artist* p)
{
	printf("%s\n", p->name);
	SNode* ptr_snode = p->head;
	while (ptr_snode != NULL)
	{
		print_song(ptr_snode->song);
		ptr_snode = ptr_snode->next;
	}
}

void print_song(Song* ptr_song)
{
	printf("    %d: %s, %s\n", ptr_song->index, ptr_song->title, ptr_song->path);
}

void search_song(char* artist) {
	Artist* ptr_artist = find_artist(artist);
	if (ptr_artist == NULL) {	// 가수가 존재하지 않음
		printf("No such artist exists.\n");
		return;
	}
	print_artist(ptr_artist);
}

SNode* find_snode(Artist* ptr_artist, char* title)
{
	SNode* ptr_snode = ptr_artist->head;
	while (ptr_snode != NULL && strcmp(ptr_snode->song->title, title) < 0)	// ptr_snode의 노래 제목이 title보다 더 크더라도 더 이상 돌 이유가 없음
		ptr_snode = ptr_snode->next;

	if (ptr_snode != NULL && strcmp(ptr_snode->song->title, title) == 0) // 곡을 찾았을 때
		return ptr_snode;
	else	// 곡을 찾지 못 했을 때
		return NULL;
}

void search_song(char* artist, char* title) {
	Artist* ptr_artist = find_artist(artist);
	if (ptr_artist == NULL) {	// 가수가 존재하지 않음
		printf("No such artist exists.\n");
		return;
	}

	SNode* ptr_snode = find_snode(ptr_artist, title);	// 독립된 함수로 만들어서 사용함
	if (ptr_snode != NULL) {
		printf("Found:\n");
		print_song(ptr_snode->song);
	}
	else {
		printf("No such song exists.\n");
		return;
	}
}

SNode* find_song(int index)
{
	SNode* ptr_snode = index_directory[index % SIZE_INDEX_TABLE]; // 해당 index의 첫 번째 노래
	while (ptr_snode != NULL && ptr_snode->song->index != index)
		ptr_snode = ptr_snode->next;

	return ptr_snode;
}

void play(int index)
{
	SNode* ptr_snode = find_song(index);
	if (ptr_snode == NULL) {
		printf("No such song exists.\n");
	}
	printf("Play the song: %s \n", ptr_snode->song->title);
}

void save_song(Song* ptr_song, FILE* fp)
{
	if (ptr_song->artist != NULL)
		fprintf(fp, "%s#", ptr_song->artist->name); // 파일에 출력
	else
		fprintf(fp, " #");

	if (ptr_song->title != NULL)
		fprintf(fp, "%s#", ptr_song->title);
	else
		fprintf(fp, " #");

	if (ptr_song->path != NULL)
		fprintf(fp, "%s\n", ptr_song->path);
	else
		fprintf(fp, " #\n"); // 파일 저장 경로가 저장되어있지 않을 때
}

void save_artist(Artist* p, FILE* fp)
{
	SNode* ptr_snode = p->head;
	while (ptr_snode != NULL)
	{
		save_song(ptr_snode->song, fp);
		ptr_snode = ptr_snode->next;
	}
}

void save(FILE* fp)
{
	for (int i = 0; i < NUM_CHARS; i++)
	{
		Artist* p = artist_directory[i];	// 배열의 이름이 곧 주소이기 때문에, 배열의 
		while (p != NULL)
		{
			save_artist(p, fp);
			p = p->next;
		}
	}
}

void remove(int index)
{
	SNode* q = NULL;	// previous to p
	SNode* p = index_directory[index % SIZE_INDEX_TABLE]; // 해당 index의 첫 번째 노래. head node
	while (p != NULL && p->song->index != index) {
		q = p;
		p = p->next;
	}

	if (p == NULL) {	// 처음부터 빈 list or 곡이 존재하지 않을 때
		printf("No such song exists.\n");
		return;
	}

	Song* ptr_song = p->song; // SNode와 Song 모두 삭제해야 함. Artist에서의 노래와 인덱스에서의 노래 모두를 삭제

	if (q == NULL) { // remove first
		index_directory[index % SIZE_INDEX_TABLE] = p->next; // p 다음 노래를 배열의 head로 저장
	}
	else {	// remove after q
		q->next = p->next;
	}
	free(p); // 삭제된 인덱스의 SNode를 삭제

	Artist* ptr_artist = ptr_song->artist;
	// find the snode in the double linked list of ptr_artist

	SNode* ptr_snode = find_snode(ptr_artist, ptr_song->title);
	if (ptr_snode == NULL) {
		printf("Not found snode - something wrong.\n");
		return;
	}
	// Artist의 SNode 찾음
	remove_snode(ptr_artist, ptr_snode);
	destroy_song(ptr_song);

}

void remove_snode(Artist* ptr_artist, SNode* ptr_snode)
{
	SNode* first = ptr_artist->head;
	SNode* last = ptr_artist->tail;
	if (first == ptr_snode && last == ptr_snode) { // SNode가 유일한 노드일 때
		first = NULL;
		last = NULL;
	}
	else if (first == ptr_snode) { // remove first
		ptr_snode->next->prev = NULL;
		first = ptr_snode->next;
	}
	else if (last == ptr_snode) { // remove last
		ptr_snode->prev->next = NULL;
		last = ptr_snode->prev;
	}
	else { // in the middle
		ptr_snode->next->prev = ptr_snode->prev;
		ptr_snode->prev->next = ptr_snode->next;
	}
	free(ptr_snode);
}

void destroy_song(Song* ptr_song)
{
	if (ptr_song->title != NULL)
		free(ptr_song->title);
	if (ptr_song->path != NULL)
		free(ptr_song->path);
	free(ptr_song);
}