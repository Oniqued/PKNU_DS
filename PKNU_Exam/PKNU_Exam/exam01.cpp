#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

//2
//void main() {
//	return 0;
//}
//void sort_three(int*a, int*b, int*c)
//{
//	int arr[3] = { *a, *b, *c };
//	for(int i = 2; i>0; i--)
//		for(int j = 0; j<i;j++)
//			if (arr[j] > arr[j + 1]) {
//				int tmp = arr[j];
//				arr[j] = arr[j + 1];
//				arr[j + 1] = tmp;
//			}
//	*a = arr[0];
//	*b = arr[1];
//	*c = arr[2];
//}


//3 
//주어진 단어를 반대로 출력하라 Enjoy Exam >> maxE yojnE
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//char* revert(char* a)
//{
//	char reversed[20];
//	int i, j;
//	for (i = 0, j = strlen(a) - 1; j >= 0; i++, j--)
//		reversed[i] = a[j];
//	reversed[strlen(a)] = '\0';	// 이유 1번
//	return strdup(reversed);	// 이유 2번
//}
//
//int main()
//{
//	char str[] = "Enjoy Exam";
//	char* reversed = revert(str);
//	printf("%s\n", reversed);
//	return 0;
//}

//4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	int data;
	struct node* next;
} Node;

Node* del_even(Node*head)
{
	int cnt = 0;
	Node*p = head;
	Node*q = NULL;
	while (p != NULL) {
		cnt++;
		if (cnt % 2 == 0)
		{
			q->next = p->next;
			p = p->next;
			continue;
		}
		q = p;
		p = p->next;
		
	}
	return head;
}

Node* createNode(int num);
Node *makeListFromArray(int n, int data[], Node* head);
void printList(Node*h);
int main()
{
	int node1[] = { 1, 2, 3, 4, 5, 6 };
	Node* head = NULL;
	head = makeListFromArray(sizeof(node1) / sizeof(node1[0]), node1, head);
	head = del_even(head);
	printList(head);
}

Node* createNode(int num)
{
	Node*p = (Node*)malloc(sizeof(Node));
	p->data = num;
	p->next = NULL;
	return p;
}

Node* head = NULL;

Node *makeListFromArray(int n, int data[], Node*head)
{
	Node *read = NULL;
	for (int i = n - 1; i >= 0; i--)
	{
		Node*p = createNode(data[i]);
		p->next = head;
		head = p;
	}
	return head;
}

void printList(Node*h)
{
	while (h != NULL)
	{
		printf("%d ", h->data);
		h = h->next;
	}
	printf("\n");
}