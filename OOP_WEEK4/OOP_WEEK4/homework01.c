#include <stdio.h>
#include <stdlib.h>

int main() {
	//char s[99];
	char* s = malloc(sizeof(char) * 100); //���� �޸� �Ҵ�
	printf("���ڸ� �Է��ϼ���(100�� �̳�).\n");
	scanf(" %s", s);
	printf("�Էµ� ���ڴ� %s�Դϴ�.\n", s);

	free(s); //���� �޸� ����
	system("pause");
	return 0;
}