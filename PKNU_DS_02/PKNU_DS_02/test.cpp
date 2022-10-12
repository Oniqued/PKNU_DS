#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define buffer_size 100

void open_txt();
void add(char* words);

char* word[buffer_size];

int n = 0;

int main1() {
    printf("hi");
    open_txt();
    for (int i = 0; i < n; i++)
        printf("%s\n", word[i]);
    return 0;
    printf("hi");
}

void open_txt() {
    char buf[buffer_size];
    FILE* fp = fopen("harry.txt", "r");

    if (fp == NULL) {
        printf("파일을 불러올 수 없습니다\n");
        return;

    }
    printf("파일을 불러오겠습니다.");
    while (fscanf(fp, "%s", buf) != EOF) {
        add(buf);
    }
    fclose(fp);
}

void add(char* words) {
    int i = n - 1;
    for (int i = n - 1; i >= 0; i--) {
        if (strcmp(word[i], words) == 0)
            return;
    }
    while (i >= 0 && strcmp(word[i], words) > 0) {
        word[i + 1] = word[i];
        i--;
    }
    word[i + 1] = strdup(words);
    n++;
}