#include <stdio.h>
#include <windows.h>

int main() {
	//char s[99];
	char* s = malloc(sizeof(char) * 100);
	printf("문자를 입력하세요(100자 이내).\n");
	scanf(" %s", s);
	printf("입력된 문자는 %s입니다.\n", s);

	system("pause");
	return 0;
}