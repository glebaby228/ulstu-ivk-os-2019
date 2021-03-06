#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

/* Процессы могут получать данные о расположении FIFO в адресном пространстве ядра
и его состоянии не через родственные связи, а через файловую систему. */
int main(){
    printf ("Лабораторная работа №4 Часть 5, выполнил Мельников Г.Р., группа ИСТбд-21\n");// средство связи для организации потокового взаимодействия для любого взаимодействия (получение данных через файловую систему)
	int fd;
	char str[]= "Hello, how are you,man?";
    printf("Запись информации в FIFO...\n");
    /* создаём FIFO используется системный вызов mknod */
    printf("Начало создания FIFO...\n");
    mknod("/home/sergio/labrab/labrab4/fifo", S_IFIFO , 0666);//заводится файл-метка ,создание ФИФО
    printf("FIFO создан...\n");
    /* dev = 0 - является несущественным в этой ситуации
    S_IFIFO - указывает, что системный вызов должен создать FIFO
    0666 устанавливает атрибуты прав доступа различных категорий пользователей (rw- rw- r--) */
    printf("Открываем FIFO на запись...\n");
	fd = open("/home/sergio/labrab/labrab4/fifo", O_WRONLY);//-1 ошибка или дескриптор
	printf("Начало записи данных в FIFO...\n");
	write(fd, str, strlen(str));
	/* Если FIFO открывается только для записи, и флаг O_NDELAY не задан, то процесс,
	осуществивший системный вызов, блокируется до тех пор, пока
    какой-либо другой процесс не откроет FIFO на чтение. */
	printf("Данные записаны\n");
	close(fd);
    /* Когда все процессы, работающие с FIFO, закрывают все файловые дескрипторы,
    ассоциированные с ним, система освобождает ресурсы, выделенные под FIFO.
    Вся непрочитанная информация теряется. В то же время файл-метка остается
    на диске и может использоваться для новой реальной организации FIFO в дальнейшем. */
	return 0;
}
