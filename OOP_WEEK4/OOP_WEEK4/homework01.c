#include <stdio.h>
#include <windows.h>

int main() {
	//char s[99];
	char* s = malloc(sizeof(char) * 100);
	printf("���ڸ� �Է��ϼ���(100�� �̳�).\n");
	scanf(" %s", s);
	printf("�Էµ� ���ڴ� %s�Դϴ�.\n", s);

	system("pause");
	return 0;
}