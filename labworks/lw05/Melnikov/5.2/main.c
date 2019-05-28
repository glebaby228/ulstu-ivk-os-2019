#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL,"Rus");
    printf ("абораторная работа №5 Часть 2, выполнил Мельников Г.Р., группа ИСТбд-21\n");
    printf ("Программа 2 для иллюстрации работы с разделяемой памятью\n");
    int *array; /* Указатель на разделяемую память */
    int shmid; /* IPC дескриптор для области разделяемой памяти */
    int ini = 1; /* Флаг необходимости инициализации элементов массива */
    char pname[] = "../5.1/Klych.c";
    key_t key; /* IPC ключ */
    /* Генерируем IPC */
    if((key = ftok(pname,0)) < 0)
    {
        printf("Не удаётся сгенерировать ключ\n");
        exit(-1);
    }
    /* Создание разделяемой памяти */
    if((shmid = shmget(key, 3*sizeof(int),0666|IPC_CREAT|IPC_EXCL)) < 0)
    {
        /* Анализ ошибки создания*/
        if(errno != EEXIST)
        { /*прочие ошибки*/
            printf("Не удаётся создать общую память\n");
            exit(-1);
        }
        else
        { /* Память уже существует */
            if((shmid = shmget(key, 3*sizeof(int), 0)) < 0)
            {
            printf("Не удаётся найти общую память\n");
            exit(-1);
            }
            ini = 0;
        }
    }
    /*Отображение разделяемой памяти в адресное пространство текущего
    процесса. Обратите внимание на то, что для правильного сравнения мы
    явно преобразовываем значение -1 к указателю на целое.*/
    if((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1))
    {
        printf("Не удаётся присоединить общую память\n");
        exit(-1);
    }
    /* В зависимости от значения флага new либо инициализируем массив,
    либо увеличиваем соответствующие счетчики */
    if(ini)
    {
        array[0] = 0;
        array[1] = 1;
        array[2] = 1;
    }
    else
    {
        array[1] += 1;
        array[2] += 1;
    }
    /* Печатаем новые значения счетчиков, удаляем разделяемую память из
    адресного пространства текущего процесса и завершаем работу */
    printf("Программа 1 была создана %d раз, программа 2 - %d раза, всего - %d раз\n",array[0], array[1], array[2]);
    if(shmdt(array) < 0)
    {
        printf("Не удаётся отсоединить общую память\n");
        exit(-1);
    }
    return 0;
}