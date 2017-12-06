//实验二 词法分析器
#include <stdio.h>
#include <string.h>

void Print();
void Compiler();

int sign;  //存放分析的类型
int p, m;

char ch;
int sum;  //暂存数字数值
char input[2000], check[10];

bool isNumber(char ch) {
  if (ch <= '9' && ch >= '0')
    return true;
  else
    return false;
}

bool isWord(char ch) {
  if ((ch >= 'a' && ch <= 'z' )|| (ch >= 'A' && ch <= 'Z'))
    return true;
  else
    return false;
}

void Compiler() {
  int num = 0;
  for (m = 0; m < 10; m++) {
    check[m] = NULL;
  }
  m = 0;
  ch = input[p++];

  while (ch == ' ' || ch == '\n' || ch == '\t') {
    ch = input[p++];
  }

  if (isWord(ch)) {
    do {
      check[m++] = ch;
      ch = input[p++];
    } while (isWord(ch) || isNumber(ch));

    p--;
    sign = 5;
    check[m++] = '\0';

    if (strcmp(check, "Const") == 0) {
      sign = 2;
    }

    if (strcmp(check, "begin") == 0 || strcmp(check, "end") == 0) {
      sign = 20;
    }

    if (strcmp(check, "if") == 0 || strcmp(check, "then") == 0 ||
        strcmp(check, "else") == 0) {
      sign = 16;
    }

    if (strcmp(check, "while") == 0 || strcmp(check, "do") == 0) {
      sign = 19;
    }

    if (strcmp(check, "Var") == 0) {
      sign = 8;
    }

    if (strcmp(check, "read") == 0 || strcmp(check, "write") == 0) {
      sign = 22;
    }
    return;

  } else if (isNumber(ch)) {
    sum = 0;
    while (isNumber(ch)) {
      sum = sum * 10 + ch - '0';
      ch = input[p++];
    }
    p--;
    sign = 6;
    if (isWord(ch)) sign = -1;
    return;
  } else {
    check[0] = ch;

    switch (ch) {
      case '<':
        ch = input[p++];
        if (ch == '>') {
          sign = 18;
          check[1] = ch;
        } else if (ch == '=') {
          sign = 18;
          check[1] = ch;
        } else {
          sign = 18;
          p--;
        }
        break;
      case '>':
        ch = input[p++];
        if (ch == '=') {
          sign = 18;
          check[1] = ch;
        } else {
          sign = 18;
          p--;
        }
        break;
      case '=':
        ch = input[p++];
        if (ch == '=') {
          sign = 18;
          check[1] = ch;
        } else {
          sign = 10;
          p--;
        }
        break;
      case '+':
        sign = 14;
        break;
      case '-':
        sign = 14;
        break;
      case '*':
        sign = 15;
        break;
      case '/':
        sign = 15;
        break;
      case '(':
        sign = 13;
        break;
      case ')':
        sign = 13;
        break;
      case ',':
        sign = 21;
        break;
      case ';':
        sign = 23;
        break;
      case '#':
        sign = 0;
        break;
      default:
        sign = -1;
        break;
    }
    return;
  }
}

void Print() {
  if (sign == 6) {
    printf("sign=%.2d| Number: %d\n", sign, sum);
  } else if (sign == 2 || sign == 8 || sign == 16 || sign == 19 || sign == 20 ||
             sign == 22) {
    printf("sign=%.2d| Reserved words: %s\n", sign, check);
  } else if (sign == 5) {
    printf("sign=%.2d| Identifier: %s\n", sign, check);
  } else if (sign == 10 || sign == 14 || sign == 15 || sign == 18) {
    printf("sign=%.2d| Operator: %s\n", sign, check);
  } else if (sign == 13) {
    printf("sign=%.2d| Brackets: %s\n", sign, check);
  } else if (sign == 21 || sign == 23) {
    printf("%s\n", check);
  }
}

int main() {
  printf("请输入输入词法串\n");
  printf("输入#标记结束\n");
  do {
    ch = getchar();
    input[p++] = ch;
  } while (ch != '#');
  p = 0;

  do {
    Compiler();
    switch (sign) {
      case -1:
        printf("分析失败\n");
        break;
      default:
        Print();
        break;
    }
  } while (sign != 0 && sign != -1);
  if (sign == 0) printf("分析成功!\n");
  return 0;
}
