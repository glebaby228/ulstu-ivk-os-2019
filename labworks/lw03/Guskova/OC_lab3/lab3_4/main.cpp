#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
//������������ ������ �3.4
//��������� ����� exec()
//��������� ��������� ��.�����-22 �������� �.�.
int main(int argc, char *argv[], char *envp[])
{
    printf("������������ ������ �3.4\n");
    printf("��������� ����� exec()\n");
    printf("��������� ��������� ��.�����-22 �������� �.�.\n");
    printf("�������: �������� ���������, ������� ������������� �� ������ �������� ���������� ���������.\n");
    //��������� ���������, ��������� �������� � ���� ������, ��� �� ���������� ����� ���������
    (void)execle("/bin/cat", "/bin/cat","/home/student/Desktop/lab3/lab3_4/lab3", 0, envp);
    return 0;
}
