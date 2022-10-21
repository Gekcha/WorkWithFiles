#include <windows.h>
#include <stdio.h>
#include <locale.h>
#define BUF_SIZE 256
int main(int argc, LPTSTR argv[]) {
	HANDLE hIn, hOut;
	DWORD nIn, nOut;
	CHAR Buffer[BUF_SIZE];
	setlocale(LC_ALL, "Rus");
	if (argc != 4) {
		printf("Использование: cpw файл1 файл2\n");
		return 1;
	}
	hIn = CreateFile(argv[1], GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hIn == INVALID_HANDLE_VALUE) {
		printf("Невозможно открыть входной файл. Ошибка: %x\n", GetLastError());
		return 2;
	}
	hOut = CreateFile(argv[2], GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	if (hOut == INVALID_HANDLE_VALUE) {
		printf("Невозможно открыть выходной файл. Ошибка: %x\n", GetLastError());
		return 3;
	}

	int k = 0;
	for (int i = 0; i < BUF_SIZE; i++) Buffer[i] = 0;
	while (ReadFile(hIn, Buffer, BUF_SIZE, &nIn, NULL) && nIn > 0) {
		for (int i = 0; i < BUF_SIZE; i++) {
			if (Buffer[i] == argv[3][0]) {
				Buffer[i] = '\0';
				k++;
			}

		}
		WriteFile(hOut, Buffer, nIn, &nOut, NULL);
	}
	printf("Количество выполненных операций - %d", k);
	CloseHandle(hIn);
	CloseHandle(hOut);
	return 0;
}