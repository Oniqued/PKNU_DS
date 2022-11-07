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

void initialize() // Aritst �迭�� INDEX �迭�� �ʱ�ȭ
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
		name = strtok(buffer, "#");	// ���鹮�� ������ tokenize�Ͽ� ����
		if (strcmp(name, " ") == 0) // �̸��� �������� �ʴ´ٸ�
			name = NULL;
		else
			name = strdup(name); // �̸��� �����Ͽ� ����

		title = strtok(NULL, "#");	// ���鹮�� ������ tokenize�Ͽ� ����
		if (strcmp(title, " ") == 0) // �̸��� �������� �ʴ´ٸ�
			title = NULL;
		else
			title = strdup(title); // �̸��� �����Ͽ� ����

		path = strtok(NULL, "#");	// ���鹮�� ������ tokenize�Ͽ� ����
		if (strcmp(path, " ") == 0) // �̸��� �������� �ʴ´ٸ�
			path = NULL;
		else
			path = strdup(path); // �̸��� �����Ͽ� ����
		//printf("%s %s %s\n", name, title, path);
		add_song(name, title, path);
	}
}

Artist* create_artist_instance(char* name) // Artist ��ü�� �����ϴ� �Լ�
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
	// Artist ��ü�� ����� ���� �Լ����� �ñ�
	Artist* ptr_artist = create_artist_instance(name);
	Artist* p = artist_directory[(unsigned char)name[0]]; // ���Ӱ� ���� ���Ḯ��Ʈ�� ù ��°(�迭�� �̸�)
	Artist* q = NULL;	// ���� ����Ʈ���� p�� ���󰡸� ��ġ�� ����ϴ� �뵵

	while (p != NULL && strcmp(p->name, name) < 0)	// ordered list���� p���� ���� ���� ��Ÿ�� �� ����
	{
		q = p;
		p = p->next;
	}

	if (p == NULL && q == NULL) // ����Ʈ�� ������� ��. �� p�� ������ ��尡 ��
	{
		artist_directory[(unsigned char)name[0]] = ptr_artist;
	}
	else if (q == NULL)	// p�� �� �տ� ��ġ��
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

	// head�� ����� ������ ptr_snode�� ����� ������ Ŭ ������ while�� �ݺ�
	while (p != NULL && strcmp(p->song->title, ptr_snode->song->title) < 0)
		p = p->next;
	// p�� ptr_snode�� �� �ڸ����� �� �ڸ� �ڿ� �ֱ� ������ p�� �� ��ġ�� ���ο� snode�� ����
	// 1. ���Ḯ��Ʈ�� ������� �� 2. �� �տ� ������ �� 3. �� �ڿ� ������ �� 4. �뷡 ���̿� ����
	if (ptr_artist->head == NULL) { // 1�� ���̽�
		ptr_artist->head = ptr_snode;
		ptr_artist->tail = ptr_snode;	// ����Ʈ�� ������ ���̱� ������ ���߿��Ḯ��Ʈ�� head�� tail�� ��� ptr_snode
	}
	else if (p == ptr_artist->head) { // 2�� ���̽�.
		ptr_snode->next = ptr_artist->head;
		ptr_artist->head->prev = ptr_snode;
		ptr_artist->head = ptr_snode; // ���ο� ���� �� ����Ʈ�� ù ��° �� �ڸ��� ��ġ��
	}
	else if (p == NULL) { // 3�� ���̽�. 
		ptr_snode->prev = ptr_artist->tail;
		ptr_artist->tail->next = ptr_snode;
		ptr_artist->tail = ptr_snode;
	}
	else {	// 4�� ���̽�. p �տ� �뷡�� �߰�
		ptr_snode->next = p;
		ptr_snode->prev = p->prev;
		p->prev->next = ptr_snode;
		p->prev = ptr_snode;
	}
}

void insert_to_index_directory(Song* ptr_song)	// �ܹ��� ���Ḯ��Ʈ
{
	SNode* ptr_snode = (SNode*)malloc(sizeof(SNode));
	ptr_snode->song = ptr_song;
	ptr_snode->next = NULL;
	ptr_snode->prev = NULL;

	int index = ptr_song->index % SIZE_INDEX_TABLE; // �뷡�� �ε����� �迭�� ũ��� ���� ������
	// add the snode into the single linked list at index_table[index]
	SNode* p = index_directory[index];	// �ش� �ε����� ù ��° ���� �ּ�
	SNode* q = NULL; // �ܹ��� ���Ḯ��Ʈ�� ordered list�� ����� ���� ����
	while (p != NULL && strcmp(p->song->title, ptr_song->title) < 0) {	// ���ĺ��� ����
		q = p;	// p���� �� ���� �ڿ� �ִ� ���
		p = p->next;
	}
	if (q == NULL) { // ù ��° ��ġ�� ����
		ptr_snode->next = p;
		index_directory[index] = ptr_snode; // �ش� �ε����� ù ��° ���� ��
	}
	else {	// add after q
		ptr_snode->next = p;
		q->next = ptr_snode;
	}
}

void add_song(char* artist, char* title, char* path)
{
	// ������ �̹� �����ϴ� ���
	// �������� �ʴ´ٸ� NULL return
	Artist* ptr_artist = find_artist(artist);	// ������ ã�Ƽ� Artist �����͸� return
	if (ptr_artist == NULL)	// ���� ������ �÷��̸���Ʈ�� �������� �ʴ´ٸ�
	{
		ptr_artist = add_artist(artist); // artist��� �̸��� ���� Artist ��ü�� �ϳ� �߰��Ͽ� �� �ּҸ� ����
	}

	Song* ptr_song = create_song_instance(ptr_artist, title, path);
	SNode* ptr_snode = (SNode*)malloc(sizeof(SNode));
	ptr_snode->song = ptr_song;	// SNode�鳢�� ���߿��Ḯ��Ʈ�� ����Ǵ� ����.
	ptr_snode->next = NULL; // �ǵ�ġ ���� �Ǽ��� �����ϱ� ���� ����ü�� ������ ���� null�� �������ִ� �͵� ����

	// insert node
	insert_node(ptr_artist, ptr_snode);
	insert_to_index_directory(ptr_song);
}

Artist* find_artist(char* name)
{
	Artist* p = artist_directory[(unsigned char)name[0]]; // ã�� ������ ���� �ʼ� �׷��� ù ��° ����. �迭�� �̸��� �� �ּ��̱� ����!
	/* name[0] : 00000000 ~ 11111111 */
	// int���� ù ��Ʈ 1�� ������ ��Ÿ��
	// ������ unsigned char�� ����ȯ
	// char = 8bit, int = 32bit

	while (p != NULL && strcmp(p->name, name) < 0)	// ���ĺ� ������ �� ū �̸��� ���´ٸ� ���� ������ ���� �ʿ�x
		p = p->next; // �̸��� ã�� �� ���� p�� ���� ���� �̵�

	if (p != NULL && strcmp(p->name, name) == 0)
		return p;	// p�� NULL�̶�� NULL return, name�� ã���� p�� return
	else
		return NULL;
}

void status()
{
	for (int i = 0; i < NUM_CHARS; i++)
	{
		Artist* p = artist_directory[i];	// �迭�� �̸��� �� �ּ��̱� ������, �迭�� 
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
	if (ptr_artist == NULL) {	// ������ �������� ����
		printf("No such artist exists.\n");
		return;
	}
	print_artist(ptr_artist);
}

SNode* find_snode(Artist* ptr_artist, char* title)
{
	SNode* ptr_snode = ptr_artist->head;
	while (ptr_snode != NULL && strcmp(ptr_snode->song->title, title) < 0)	// ptr_snode�� �뷡 ������ title���� �� ũ���� �� �̻� �� ������ ����
		ptr_snode = ptr_snode->next;

	if (ptr_snode != NULL && strcmp(ptr_snode->song->title, title) == 0) // ���� ã���� ��
		return ptr_snode;
	else	// ���� ã�� �� ���� ��
		return NULL;
}

void search_song(char* artist, char* title) {
	Artist* ptr_artist = find_artist(artist);
	if (ptr_artist == NULL) {	// ������ �������� ����
		printf("No such artist exists.\n");
		return;
	}

	SNode* ptr_snode = find_snode(ptr_artist, title);	// ������ �Լ��� ���� �����
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
	SNode* ptr_snode = index_directory[index % SIZE_INDEX_TABLE]; // �ش� index�� ù ��° �뷡
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
		fprintf(fp, "%s#", ptr_song->artist->name); // ���Ͽ� ���
	else
		fprintf(fp, " #");

	if (ptr_song->title != NULL)
		fprintf(fp, "%s#", ptr_song->title);
	else
		fprintf(fp, " #");

	if (ptr_song->path != NULL)
		fprintf(fp, "%s\n", ptr_song->path);
	else
		fprintf(fp, " #\n"); // ���� ���� ��ΰ� ����Ǿ����� ���� ��
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
		Artist* p = artist_directory[i];	// �迭�� �̸��� �� �ּ��̱� ������, �迭�� 
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
	SNode* p = index_directory[index % SIZE_INDEX_TABLE]; // �ش� index�� ù ��° �뷡. head node
	while (p != NULL && p->song->index != index) {
		q = p;
		p = p->next;
	}

	if (p == NULL) {	// ó������ �� list or ���� �������� ���� ��
		printf("No such song exists.\n");
		return;
	}

	Song* ptr_song = p->song; // SNode�� Song ��� �����ؾ� ��. Artist������ �뷡�� �ε��������� �뷡 ��θ� ����

	if (q == NULL) { // remove first
		index_directory[index % SIZE_INDEX_TABLE] = p->next; // p ���� �뷡�� �迭�� head�� ����
	}
	else {	// remove after q
		q->next = p->next;
	}
	free(p); // ������ �ε����� SNode�� ����

	Artist* ptr_artist = ptr_song->artist;
	// find the snode in the double linked list of ptr_artist

	SNode* ptr_snode = find_snode(ptr_artist, ptr_song->title);
	if (ptr_snode == NULL) {
		printf("Not found snode - something wrong.\n");
		return;
	}
	// Artist�� SNode ã��
	remove_snode(ptr_artist, ptr_snode);
	destroy_song(ptr_song);

}

void remove_snode(Artist* ptr_artist, SNode* ptr_snode)
{
	SNode* first = ptr_artist->head;
	SNode* last = ptr_artist->tail;
	if (first == ptr_snode && last == ptr_snode) { // SNode�� ������ ����� ��
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