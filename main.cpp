#include <stdio.h>
#include "Akinator.cpp"

#define MAXLEN 128

void RunAkinator(int mode, char* filename, char* png);

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("too few args\n");
        return 1;
    }

    printf("Какой режим хотите запустить?\n1 - режим отгадывания\n2 - режим биографии\n3 - режим сравнения\n");

    int mode = 1;
    
    if (scanf("%d", &mode) != 1 || mode > 3 || mode < 1) return printf("incorrect input\n");
    getchar();

    RunAkinator(mode, argv[1], argv[2]);

    return 0;
}

void RunAkinator(int mode, char* filename, char* png)
{
    switch (mode)
    {
        case 1: Akinator(filename, png); break;

        case 2:
        {
            printf("Какого персонажа разложить по Тейлору?\n");
            char name[MAXLEN] = {};
            scanf("%s", name);
            Path(filename, name);
            break;
        }
        case 3:
        {
            printf("Каких персонажей хотите сравнить? Введите через пробел\n");

            char name1[MAXLEN] = {};
            char name2[MAXLEN] = {};

            scanf("%s", name1);
            scanf("%s", name2);

            Compare(filename, name1, name2);

            break;
        }

        default: break;

    }

}
