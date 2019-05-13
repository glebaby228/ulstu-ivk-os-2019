#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

/* Процессы могут получать данные о расположении FIFO в адресном пространстве ядра
и его состоянии не через родственные связи, а через файловую систему. */
int main(){
    printf ("Лабораторная работа №4 Часть 5, выполнили Клементьев С.В., группа ИСТбд-21\n");
	int fd;
	char str[]= "Hi, my name is Sergio!";
    printf("Запись информации в FIFO...\n");
    /* создаём FIFO используется системный вызов mknod */
    printf("Начало создания FIFO...\n");
    mknod("/sergio/lab/fifo", S_IFIFO | 0666, 0);//заводится файл-метка
    printf("FIFO создан...\n");
    /* dev = 0 - является несущественным в этой ситуации
    S_IFIFO - указывает, что системный вызов должен создать FIFO
    0666 устанавливает атрибуты прав доступа различных категорий пользователей (rw- rw- r--) */
    printf("Открываем FIFO на запись...\n");
	fd = open("/sergio/lab/fifo", O_WRONLY);//-1 ошибка или дескриптор
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