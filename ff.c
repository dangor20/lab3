#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include "header.h"
#include <locale.h>


Elem *BegQ, *EndQ;
FILE * file = NULL;


void queue_create(long long num)
{
    setlocale(LC_ALL, "Rus");
    BegQ = NULL;
    EndQ = NULL;
    Elem *p = (Elem *)malloc(sizeof(Elem));
    p -> inf = num;
    p -> link = NULL;
    BegQ = p;
    EndQ = p;
}


void queue_push(long long num)
{
    Elem *p = (Elem *)malloc(sizeof(Elem));
    p -> inf = num;
    p -> link = NULL;

    EndQ -> link = p;
    EndQ = p;
}


void queue_pop()
{
    Elem *p = BegQ;
    BegQ = p -> link;
    free(p);
}


void queue_clear()
{
    while (BegQ != EndQ) queue_pop();

    free(BegQ);
    BegQ = NULL;
    EndQ = NULL;
}


void get_queue(char * filename)
{
    int is_new_num = 1, num_count = 0;
    int sign = 1; // 1 ~ "+", -1 ~ "-"
    char symbol[2] = " ";
    long long digit, num = 0;

    if (file != NULL) fclose(file);

    file = fopen(filename, "r");
    if(file == NULL)
    {
        printf("Ошибка открытия %s. Файла не существует.\n", filename);
        return;
    }

    while (((symbol[0] = getc(file)) != EOF) || (is_new_num == 0))
    {
        digit = atof(symbol);
        if ((strcmp(symbol, " ") == 0) || (strcmp(symbol, "\n") == 0) || (symbol[0] == EOF))
        {
            if (is_new_num == 0)
            {
                num = sign * num;
                // printf("%lld\n", num);
                if (BegQ == NULL) queue_create(num);

                else queue_push(num);

                num_count++;
                num = 0;
                sign = 1;
            }
            is_new_num = 1;
        }
        else if ((is_new_num == 1) && ((digit > 0) || (strcmp(symbol, "-") == 0)) || ((strcmp(symbol, "0") == 0)))
        {
            if (strcmp(symbol, "-") == 0) sign = -1;

            num = num * 10 + digit;
            is_new_num = 0;
        }
        else if ((is_new_num == 0) && ((digit > 0) || (strcmp(symbol, "0") == 0)))
        {
            if (((LLONG_MAX - digit) / 10) <= num)
            {
                printf("Переполнение %s\n", filename); 
                return;
            }

            else num = num * 10 + digit;
        }
        else
        {
            printf("Невозможно прочитать %s.\n", filename);
            return;
        }
    }
    fclose(file);
    file = NULL;
    write_row(filename, 0);
}


void write_row(char * filename, int is_sorted)
{
    char num_s[21];
    int len;
    Elem *p = BegQ;

    if (is_sorted == 1) fputs("\n\n", file);

    if (file == NULL) file = fopen(filename, "w");
    while (p != NULL)
    {
        snprintf(num_s, sizeof(num_s), "%lld", p -> inf);
        len = strlen(num_s);
        fputs(num_s, file);
        putc(' ', file);
        p = p -> link;
    }
    free(p);
    p = NULL;
    
    if (is_sorted == 1) 
    {
        fclose(file);
        file = NULL;
    }
}


void selection_sort()
{
    Elem *p = BegQ, *i, *min_elem = NULL;
    

    while (p != EndQ)
    {
        i = p;
        min_elem = i;
        while (i != NULL)
        {
            if ((i -> inf) < (min_elem -> inf))
            {
                min_elem = i;
            }
            i = i -> link;
        }
        long long temp = p -> inf;
        p -> inf = min_elem -> inf;
        min_elem -> inf = temp;

        p = p -> link;
    }
    return;
}