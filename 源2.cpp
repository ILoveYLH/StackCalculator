#include"标头.h"
#include<math.h>
char str[100];
bool isLegal(char* str);
int isp(char ch);
int osp(char ch);
void cal(char op, double x, double y, SqStack2* s);
bool isdigit(char ch);
bool IsOperator(char ch);
void calculate(char* str);
void convertDigit(SqStack2* s, int digit1);
void convertFraction(SqStack2* s, int digit2);
SqStack1 optr = InitStack1();
SqStack2 opnd = InitStack2();
void display();
void convertNum(char** ch);
void Menu();
int main() {
	Menu();
	printf("\n输入你的表达式 ： ");
	scanf("%s", str);
	while (1) {
		while (!isLegal(str)) {
			printf("输入不合法请重新输入：");
			scanf("%s", str);
		}
		calculate(str);//开始计算字符串
		display();
		ClearStack1(&optr);
		ClearStack2(&opnd);
		printf("\n输入你的表达式: ");
		scanf("%s", str);
	}
}
bool isLegal(char* str)
{
	int num1 = 0;
	int num2 = 0;//num1和num2分别是左右括号的数目 
	while (*str != '=') {//判断是否合法循环，直到“\0”处停止 
		if (!isdigit(*str) && !IsOperator(*str)) {//如果字符不是数字也不是操作符，放回false 
			return false;
		}
		else if (isdigit(*str)) {
			*str++; //如果字符是数字，则指针移向下一个字符 
		}
		else if (IsOperator(*str)) {
			if (*str == '(') {
				num1++;
				*str++;
			}
			else if (*str == ')') {
				num2++;
				*str++;
			}
			else if (IsOperator(*(++str))) {
				if (*str != '(') {
					return false;
				}
			}
			if (num1 < num2) {
				return false;
			}
			//如果是操作符，首先对括号的数量进行判断。任何时刻，左括号的数量大于等于右括号。否则返回false 
		}
	}
	if (num1 != num2) return false;//左右括号的数量要相等 
	return true;
}
void calculate(char* str) {
	bool LoopCount = false;
	while (*str != '\0') {
		if (isdigit(*str)) {
			convertNum(&str);
			LoopCount = true;
		}
		//注意判断第一个是负数和判断后面几个是负数不能分开写
		//分开写的话判断后面的负数时用*(--str)来看负号，
		//这样写的时候逻辑很繁杂，而且特别容易出错，至少我已经改了n多回了还没有改好，然后就放弃了
		if (IsOperator(*str)) {//开始先判断是否为负数
			if (*str == '-') {
				if (!LoopCount) {
					convertNum(&str);
					double negat = -Pop2(&opnd);
					Push2(&opnd, negat);
				}
				//这个必须注意，if如果执行不成功，但是前面的--str还是会执行
				//所以必须外加一个条件来判断到底执行了没有
				//如果没有执行的话必须把str++，否则栈会错误或者算不出来正确结果
				bool flag = false;
				if (*(--str)=='(') {
					flag = true;
					str += 2;
					convertNum(&str);
					double negat = -Pop2(&opnd);
					Push2(&opnd, negat);
				}
				if (!flag)str++;
			}
			if (StackEmpty1(&optr) == 1) {//栈为空的情况下返回1，否则返回0
				Push1(&optr, *str);
				str++;
			}
			else {
				char ch = GetTop1(&optr);
				int inPriority = isp(ch);
				int otPriority = osp(*str);
				if (inPriority < otPriority) {
					Push1(&optr, *str);
					str++;
				}
				if (inPriority == otPriority) {
					char waste = Pop1(&optr);
					str++;
				}
				if (inPriority > otPriority) {
					double num1 = Pop2(&opnd);
					double num2 = Pop2(&opnd);
					char op = Pop1(&optr);
					cal(op, num1, num2, &opnd);
				}
			}
		}
	}
}
void convertDigit(SqStack2* s, int digit1) {
	if (digit1 == 1)return;
	else {
		double sum1 = 0;
		for (int i = 0; i < digit1; i++) {
			sum1 += Pop2(s) * pow(10.0, i);
		}
		Push2(s, sum1);
	}
}
void convertFraction(SqStack2* s, int digit2) {
	if (digit2 == 0)return;
	else {
		double sum2 = 0;//储存小数的值
		for (int i = digit2; i > 0; i--) {
			sum2 += Pop2(s) * pow(10.0, -i);
		}
		double result = Pop2(s) + sum2;
		Push2(s, result);
	}
}
int isp(char ch) {
	switch (ch) {
	case'=':
		return 0;
	case'+':
		return 3;
	case'-':
		return 3;
	case'*':
		return 5;
	case'/':
		return 5;
	case'%':
		return 5;
	case'(':
		return 1;
	case')':
		return 8;
	case'^':
		return 7;
	case'&':
		return 7;
	}
}
int osp(char ch) {
	switch (ch) {
	case'=':
		return 0;
	case'+':
		return 2;
	case'-':
		return 2;
	case'*':
		return 4;
	case'/':
		return 4;
	case'%':
		return 4;
	case'(':
		return 8;
	case')':
		return 1;
	case'^':
		return 6;
	case'&':
		return 6;
	}
}
void cal(char op, double x, double y, SqStack2* s)
{
	switch (op) {
	case'+':
		Push2(s, x + y);
		break;
	case'-':
		Push2(s, y - x);
		break;
	case'*':
		Push2(s, x * y);
		break;
	case'/':
		Push2(s, y / x);
		break;
	case'^':
		Push2(s, pow(y, x));
		break;
	case'&'://注意，pow函数的话不能开负数的奇数访根，必须先转化成整数开，然后再加一个负号
		if (y >= 0)Push2(s, pow(y, 1 / x));
		else {
			double result = 0;
			result = -pow(-y, 1 / x);
			Push2(s, result);
		}
		break;
	case'%':
		Push2(s, (int)y % (int)x);
		break;
	}
}
bool isdigit(char ch) {
	char number[15] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	for (int i = 0; i <= 9; i++) {
		if (number[i] == ch)
			return true;
	}
	return false;
}
bool IsOperator(char ch) {
	char calculate[15] = { '+', '-', '*', '/', '^', '&','(',')','=','.','%' };
	for (int i = 0; i <= 10; i++) {
		if (calculate[i] == ch)
			return true;
	}
	return false;
}
void display() {
	printf(" %f\n", Pop2(&opnd));
}
//-----------------------------------这个函数是传的指针的指针，一定要搞明白，取出字符要用到**str
//需要两个**，这个地方可能容易搞不懂
void convertNum(char** str) {
	if (isdigit(**str)) {
		int digit1 = 1;//记录整数部分的位数
		int digit2 = 0;//记录小数部分的位数
		double num = **str - '0';
		Push2(&opnd, num);
		(*str)++;
		while (isdigit(**str)) {
			num = **str - '0';
			digit1++;
			Push2(&opnd, num);
			(*str)++;
		}
		convertDigit(&opnd, digit1);//push进去的整数有很多，将其变成一个数。
		if (**str == '.') {
			(*str)++;//将小数点跳过去继续读后面的小数
			while (isdigit(**str)) {
				num = **str - '0';
				Push2(&opnd, num);
				digit2++;
				(*str)++;
			}
		}
		convertFraction(&opnd, digit2);//将读进去小数的许多位合成一个double变量加进去
	}
}
void Menu() {
	printf("*********************** 欢迎使用 calculator **********************\n");
	printf("使用说明:\n");
	printf("表达式可包括:\n");
	printf("1.加(+)，减(-),乘(*),除(/)，求模(%),开方(&)，乘方(^)运算符\n");
	printf("2.括号");
}
