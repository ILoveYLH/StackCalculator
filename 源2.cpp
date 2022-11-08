#include"��ͷ.h"
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
	printf("\n������ı��ʽ �� ");
	scanf("%s", str);
	while (1) {
		while (!isLegal(str)) {
			printf("���벻�Ϸ����������룺");
			scanf("%s", str);
		}
		calculate(str);//��ʼ�����ַ���
		display();
		ClearStack1(&optr);
		ClearStack2(&opnd);
		printf("\n������ı��ʽ: ");
		scanf("%s", str);
	}
}
bool isLegal(char* str)
{
	int num1 = 0;
	int num2 = 0;//num1��num2�ֱ����������ŵ���Ŀ 
	while (*str != '=') {//�ж��Ƿ�Ϸ�ѭ����ֱ����\0����ֹͣ 
		if (!isdigit(*str) && !IsOperator(*str)) {//����ַ���������Ҳ���ǲ��������Ż�false 
			return false;
		}
		else if (isdigit(*str)) {
			*str++; //����ַ������֣���ָ��������һ���ַ� 
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
			//����ǲ����������ȶ����ŵ����������жϡ��κ�ʱ�̣������ŵ��������ڵ��������š����򷵻�false 
		}
	}
	if (num1 != num2) return false;//�������ŵ�����Ҫ��� 
	return true;
}
void calculate(char* str) {
	bool LoopCount = false;
	while (*str != '\0') {
		if (isdigit(*str)) {
			convertNum(&str);
			LoopCount = true;
		}
		//ע���жϵ�һ���Ǹ������жϺ��漸���Ǹ������ֿܷ�д
		//�ֿ�д�Ļ��жϺ���ĸ���ʱ��*(--str)�������ţ�
		//����д��ʱ���߼��ܷ��ӣ������ر����׳����������Ѿ�����n����˻�û�иĺã�Ȼ��ͷ�����
		if (IsOperator(*str)) {//��ʼ���ж��Ƿ�Ϊ����
			if (*str == '-') {
				if (!LoopCount) {
					convertNum(&str);
					double negat = -Pop2(&opnd);
					Push2(&opnd, negat);
				}
				//�������ע�⣬if���ִ�в��ɹ�������ǰ���--str���ǻ�ִ��
				//���Ա������һ���������жϵ���ִ����û��
				//���û��ִ�еĻ������str++������ջ���������㲻������ȷ���
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
			if (StackEmpty1(&optr) == 1) {//ջΪ�յ�����·���1�����򷵻�0
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
		double sum2 = 0;//����С����ֵ
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
	case'&'://ע�⣬pow�����Ļ����ܿ������������ø���������ת������������Ȼ���ټ�һ������
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
//-----------------------------------��������Ǵ���ָ���ָ�룬һ��Ҫ�����ף�ȡ���ַ�Ҫ�õ�**str
//��Ҫ����**������ط��������׸㲻��
void convertNum(char** str) {
	if (isdigit(**str)) {
		int digit1 = 1;//��¼�������ֵ�λ��
		int digit2 = 0;//��¼С�����ֵ�λ��
		double num = **str - '0';
		Push2(&opnd, num);
		(*str)++;
		while (isdigit(**str)) {
			num = **str - '0';
			digit1++;
			Push2(&opnd, num);
			(*str)++;
		}
		convertDigit(&opnd, digit1);//push��ȥ�������кܶ࣬������һ������
		if (**str == '.') {
			(*str)++;//��С��������ȥ�����������С��
			while (isdigit(**str)) {
				num = **str - '0';
				Push2(&opnd, num);
				digit2++;
				(*str)++;
			}
		}
		convertFraction(&opnd, digit2);//������ȥС�������λ�ϳ�һ��double�����ӽ�ȥ
	}
}
void Menu() {
	printf("*********************** ��ӭʹ�� calculator **********************\n");
	printf("ʹ��˵��:\n");
	printf("���ʽ�ɰ���:\n");
	printf("1.��(+)����(-),��(*),��(/)����ģ(%),����(&)���˷�(^)�����\n");
	printf("2.����");
}
