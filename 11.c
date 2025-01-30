#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <locale.h>
#include "header.h"





int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Rus");
    FILE *file;
    char* line[1000];
    char ch;
    if (argc == 3 && strcmp(argv[1], "--file") == 0) {
        file = fopen(argv[argc - 1], "r");
        if (file == NULL) {
            perror("������ �������� �����");
            return 1;
        }
        printf("���������� ����� '%s':\n", argv[argc - 1]);
        while ((ch = fgetc(file)) != EOF) {
            putchar(ch); // ������� ������ �� �����
        }

        // ��������� ����
        fclose(file);

    return 0;
    } 
    else {
        // ���� ����� � ����������
        char numbers[1000];
        int n = 0;
        printf("������� ������������������ ����� ����� ������ (��� ��������� ����� ������� 'enter'): ");
        gets(numbers);

        file = fopen(argv[argc - 1], "w");
        if (file == NULL) {
        printf("������ �������� �����");
        return 1;
        }
        fputs(numbers, file);
        fclose(file);
        get_queue(argv[argc - 1]);
        selection_sort();

        write_row(argv[argc - 1], 1);
        queue_clear();
        printf("��������� �������� � %s.\n", argv[argc - 1]);
    }

    return 0;
}

