#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef char Elemtype1;
typedef double Elemtype2;
typedef struct {
	Elemtype1* data;
	int top;
	int stacksize;
} SqStack1;
Elemtype1 Pop1(SqStack1* s);

typedef struct {
	Elemtype2* data;
	int top;
	int stacksize;
} SqStack2;
Elemtype2 Pop2(SqStack2* s);


SqStack1 InitStack1() {
	SqStack1 s;
	s.data = (Elemtype1*)malloc(STACK_INIT_SIZE * sizeof(Elemtype1));
	s.top = -1; 
	s.stacksize = STACK_INIT_SIZE;
	if (s.data != NULL)
	{
	}
	else
		printf("Init error!\n");
	return s;
}


void DestroyStack1(SqStack1* s) {
	free(s->data);
}

int StackEmpty1(SqStack1* s) {
	if (s->top == -1)
		return 1;
	else
		return 0;
}

void ClearStack1(SqStack1* s) {
	while (StackEmpty1(s) != 1) {
		Pop1(s);
	}
}

void Push1(SqStack1* s, Elemtype1 e) {
	if (s->top >= s->stacksize) {
		s->data = (Elemtype1*)malloc((STACK_INIT_SIZE + STACKINCREMENT) * sizeof(Elemtype1));
		s->stacksize += STACKINCREMENT;
		if (s->data != NULL) {}
		else
			printf("Push error!\n");
	}
	else {
		s->top++;
		s->data[s->top] = e;
	}
}

Elemtype1 Pop1(SqStack1* s) {
	if (StackEmpty1(s) != 1 && s->top >= 0) {
		Elemtype1 e = s->data[s->top];
		s->top--;
		return e;
	}
	//printf("Pop error!\n");
}

int StackLength1(SqStack1* s) {
	int len = 0, temp = s->top;
	while (temp >= 0) {
		len++;
		temp--;
	}
	return len;
}

Elemtype1 GetTop1(SqStack1* s) {
	if (StackEmpty1(s) != 1) {
		return s->data[s->top];
	}
	else
		printf("GetTop error!\n");
}

int StackTraverse1(SqStack1* s) {
	if (StackEmpty1(s) == 1) {
		printf("栈为空！\n");
		return 0;
	}
	int temp = 0;
	while (temp <= s->top) {
		printf("%c ", s->data[temp]);
		temp++;
	}
	return 1;
}


SqStack2 InitStack2() {
	SqStack2 s;
	s.data = (Elemtype2*)malloc(STACK_INIT_SIZE * sizeof(Elemtype2));
	s.top = -1; //表示栈空
	s.stacksize = STACK_INIT_SIZE;
	if (s.data != NULL)
	{
	}
	else
		printf("Init error!\n");
	return s;
}

void DestroyStack2(SqStack2* s) {
	free(s->data);
}

int StackEmpty2(SqStack2* s) {
	if (s->top == -1)
		return 1;
	else
		return 0;
}

void ClearStack2(SqStack2* s) {
	while (StackEmpty2(s) != 1) {
		Pop2(s);
	}
}

void Push2(SqStack2* s, Elemtype2 e) {
	if (s->top >= s->stacksize) {
		s->data = (Elemtype2*)malloc((STACK_INIT_SIZE + STACKINCREMENT) * sizeof(Elemtype2));
		s->stacksize += STACKINCREMENT;
		if (s->data != NULL) {}
		else
			printf("Push error!\n");
	}
	else {
		s->top++;
		s->data[s->top] = e;
	}
}

Elemtype2 Pop2(SqStack2* s) {
	if (StackEmpty2(s) != 1 && s->top >= 0) {
		Elemtype2 e = s->data[s->top];
		s->top--;
		return e;
	}
	//printf("Pop error!\n");
}

int StackLength2(SqStack2* s) {
	int len = 0, temp = s->top;
	while (temp >= 0) {
		len++;
		temp--;
	}
	return len;
}

Elemtype2 GetTop2(SqStack2* s) {
	if (StackEmpty2(s) != 1) {
		return s->data[s->top];
	}
	else
		printf("GetTop error!\n");
}

int StackTraverse2(SqStack2* s) {
	if (StackEmpty2(s) == 1) {
		printf("栈为空！\n");
		return 0;
	}
	int temp = 0;
	while (temp <= s->top) {
		printf("%c ", s->data[temp]);
		temp++;
	}
	return 1;
}