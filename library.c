#include <stdio.h>
#include "library.h"
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <sys/types.h>
#include <sys/stat.h>


//---------------�˵���----------------
//���˵�
void menu_main()
{
	printf("\n\n");
	printf("\t\t\t *=======================================*\n");
	printf("\t\t\t|  * - * - * ��ӭ����ͼ�����ϵͳ * - * -*|\n");
	printf("\t\t\t| *                                     * |\n");
	printf("\t\t\t| |  [1]   �û���¼                     | |\n");
	printf("\t\t\t| *                                     * |\n");
	printf("\t\t\t| |  [2]   �û�ע��                     | |\n");
	printf("\t\t\t| *                                     * |\n");
	printf("\t\t\t| |  [3]   ����Ա��¼                   | |\n");
	printf("\t\t\t| *                                     * |\n");
	printf("\t\t\t| |  [4]   �˳�ϵͳ                     | |\n");
	printf("\t\t\t| *                                     * |\n");
	printf("\t\t\t|  * - * - * - * - * - * - * - * - * - *  |\n");
	printf("\t\t\t *=======================================*\n");
}
//�û��˵���
void menu_user()
{
	printf("\n\n");
	printf("\t\t\t *=====================================*\n");
	printf("\t\t\t| | * - * - * -��-Ա-��-��- * - * - * | |\n");
	printf("\t\t\t| *                                   * |\n");
	printf("\t\t\t| |  [1]   ����ͼ����Ϣ               | |\n");
	printf("\t\t\t| *  [2]   ����ͼ��                   * |\n");
	printf("\t\t\t| |  [3]   �黹ͼ��                   | |\n");
	printf("\t\t\t| |  [4]   �޸��˻���Ϣ               | |\n");
	printf("\t\t\t| *  [5]   �˳��û�����               * |\n");
	printf("\t\t\t| |                                   | |\n");
	printf("\t\t\t| * - * - * - * - * - * - * - * - * - * |\n");
	printf("\t\t\t *=====================================*\n");
}
//����Ա�˵���
void menu_manager()
{
	printf("\n\n");
	printf("\t\t\t *======================================*\n");
	printf("\t\t\t| | * - * - * ��-��-Ա-��-�� * - * - * | |\n");
	printf("\t\t\t| *                                    * |\n");
	printf("\t\t\t| |  [1]   ���ͼ��                    | |\n");
	printf("\t\t\t| *  [2]   ɾ��ͼ��                    * |\n");
	printf("\t\t\t| |  [3]   �޸�ͼ����Ϣ                | |\n");
	printf("\t\t\t| *  [4]   ����ͼ����Ϣ                * |\n");
	printf("\t\t\t| |  [5]   ��ʾȫ��ͼ����Ϣ            | |\n");
	printf("\t\t\t| *  [6]   ��ʾ���л�Ա��Ϣ            * |\n");
	printf("\t\t\t| |  [7]   ͳ�����н�����Ϣ            | |\n");
	printf("\t\t\t| |  [8]   ��ʾ������Ϣ����            | |\n");
	printf("\t\t\t| *  [9]   �˳�����Ա����              * |\n");
	printf("\t\t\t| |                                    | |\n");
	printf("\t\t\t| * - * - * - * - * -- * - * - * - * - * |\n");
	printf("\t\t\t *======================================*\n");
}


//---------------��¼����----------------
//�û���¼
int login(pUser* user)
{
	char account[ACCOUNT]="";
	char password[PASSWORD]="";
	FILE* fp;
	pUser users = NULL;
	//�����˺�����
	input(account, password);
	//���ļ������ļ����������û���Ϣ
	errno_t message = fopen_s(&fp, "users.txt", "r");
	findAll_user(fp, &users);
	if (fp)
	{
		fclose(fp);
	}
	//У������
	if (!login_compare(account, password, users, user))
	{
		return False;
	}
	return True;
}
//�û�/����Ա�����˺���Ϣ
int input(char* account, char* password) {
	printf("����������˺�:\n");
	gets_s(account, ACCOUNT);
	printf("\n�������������:\n");
	for (int i = 0; i < PASSWORD; i++)
	{
		char ch = _getch();
		if (ch == '\r')
		{
			break;
		}
		printf("*");
		password[i] = ch;
	}
	return True;
}
//���������û��ĺ���
int findAll_user(FILE* fp,pUser* users) 
{
	pUser user = (pUser)malloc(sizeof(User));
	if (user==NULL)
	{
		printf("��̬�ڴ����ʧ��\n");
		exit(1);
	}
	int result = 0,flag = 0;
	if (fp)
	{
		result = fscanf_s(fp, "%s %s %s %s %d %d", user->user_name, MAX, user->account, ACCOUNT, user->password, PASSWORD,
			user->gender, GENDER,&user->identity,&user->fine);
		user->next = NULL;
	}
	*users = user;
	while (result!=-1)
	{
		pUser current = (pUser)malloc(sizeof(User));
		if (current == NULL)
		{
			printf("��̬�ڴ����ʧ��\n");
			exit(1);
		}
		if (fp)
		{
			result = fscanf_s(fp, "%s %s %s %s %d %d", current->user_name, MAX, current->account, ACCOUNT, current->password, PASSWORD,
				current->gender, GENDER, &current->identity, &current->fine);
			/*���������һ�����⣬���ļ�����һ�У���֪��Ϊʲô�������ļ���ֻ���������ݽ�������������ṹ�壬
			�������ṹ�廹�����룬�²�����ǻ��з�����ģ���������Ӹ��жϹ���һ��*/
			if (current->identity==0||current->identity==1)
			{
				current->next = NULL;
				user->next = current;
				user = current;
			}
		}
	}
	return True;
}
//У�麯��
int login_compare(char* account, char* password,pUser users,pUser* user)
{
	pUser head = users;
	int identity = 0;
	while (head)
	{
		if ((strcmp(account,head->account)==0)&& (strcmp(password, head->password) == 0))
		{
			*user = head;
			return True;
		}
		head = head->next;
	}
	return False;
}
//���ắ��
int freeze_account(int number)
{
	if (number >= 3)
	{
		printf("�˺���������������3�Σ���һ���Ӻ�����\n");
		printf("...\n");
		Sleep(60000);
		number = -1;
	}
	return ++number;
}


//---------------�û�ע��----------------
//�û�ע���˺�
int register_user()
{
	FILE* fp;
	pUser user = NULL;
	if (register_input(&user))
	{
		//���ļ�
		errno_t message = fopen_s(&fp, "users.txt", "ab+");
		//���û���Ϣ�־û���Ӳ��(д���ļ�)
		if (fp)
		{
			register_fwrite(fp, user);
			fclose(fp);
		}
		//���������ɵ��˺�
		printf("�����˺���: %s, ���ס�����˺ţ�\n",user->account);
		return True;
	}
	return False;
}
//��������˻��ĺ���
void register_rand_account(char* account,int number)
{
	int i;
	srand((unsigned)time(NULL));
	for (i = 0; i < number; i++)
	{
		/* int A = rand() % x+y:����һ��y��x+y������� */
		int num = rand() % 9;
		account[i] = num + '0';
	}
	account[i] = '\0';
}
//�û�ע��¼����Ϣ�ĺ���
int  register_input(pUser* student)
{
	char password[PASSWORD] = "";/*�����������ı���*/

	pUser stu = (pUser)malloc(sizeof(User));/*Ϊѧ����������ڴ�*/
	if (stu==NULL)
	{
		printf("�ڴ����ʧ��\n");
		exit(1);
	}
	
	//¼����Ϣ
	register_rand_account(stu->account,10);//��������˺�
	stu->identity = USER;//¼�����
	stu->fine = 0;
	printf("�������������:\n");
	gets_s(stu->user_name, MAX);//¼���û���
	if (strcmp(stu->user_name,"")==0)
	{
		printf("��������Ϊ��,����������\n");
		return False;
	}
	printf("�������������(���볤��ӦΪ8-16):\n");
	gets_s(stu->password, PASSWORD);
	//У�鳤��
	if (strlen(stu->password) < 8)
	{
		printf("������볤�Ȳ����Ϲ淶������������\n");
		return False;
	}
	printf("���ظ��������(���볤��ӦΪ8-16):\n");
	gets_s(password, PASSWORD);
	//У�������Ƿ�һ��
	if (strcmp(password, stu->password) != 0)
	{
		printf("�����������������������������\n");
		return False;
	}
	
	printf("����������Ա�:\n");
	gets_s(stu->gender, GENDER);//¼���Ա�
	stu->next = NULL;
	*student = stu;//���û���Ϣ����
	return True;
}
//д���ļ�
int register_fwrite(FILE* fp, pUser user)
{
	fprintf(fp, "%s\t%s\t%s\t%s\t%d\t%d\n", user->user_name, user->account, user->password,
		user->gender, user->identity, user->fine);
	return True;
}


//---------------����ģ��----------------
// --------------����Ա----------
//���������鼮
int findAll_book(pBook* book_list)
{
	FILE* fe;
	fe = fopen("library.txt", "r");
	if (!fe)
	{
		printf("���ļ�ʧ��");
	}
	pBook head = (pBook)malloc(sizeof(Book));
	if (head==NULL)
	{
		printf("�ڴ����ʧ��");
		exit(1);
	}
	//���ļ�����ȡ����
	if (fe)
	{
		int result=fscanf_s(fe, "%s %s %s %s %s %d %d %d", head->book_name, MAX, head->author, MAX, head->describe, DESCRIBE,
			head->type, MAX, head->ID,MAX, &head->digits, &head->times, &head->isBorrowed);
		if (head->ID<=0||result==-1)
		{
			//�ļ�Ϊ��
			return False;
		}
		else
		{
			//��ͼ���б�ָ��ָ��ͷָ��
			*book_list = head;
			head->next = NULL;
		}
		while (result!=-1)
		{
			//�����ڴ�
			pBook current = (pBook)malloc(sizeof(Book));
			if (current==NULL)
			{
				printf("�����ڴ�ʧ��");
				exit(1);
			}

			 result = fscanf_s(fe, "%s %s %s %s %s %d %d %d", current->book_name, MAX, current->author, MAX, current->describe, DESCRIBE,
				current->type, MAX, &current->ID, MAX, &current->digits, &current->times, &current->isBorrowed);
			 //��������
			if (result!=-1)
			{
				current->next = NULL;
				head->next = current;
				head = current;
			}
		}
		fclose(fe);
	}
	return True;
}
//��ӡ�����鼮
void println(pBook head)
{
	printf("�鼮\t\t����\t����\t\t����\tͼ����\t�ݲ�����\t�����Ĵ���\t�������(0��ʾδ���)\n");
	while (head)
	{
		printf("��%s��\t%s\t%s\t%s\t%s\t\t%d\t\t%d\t\t%d\n", head->book_name, head->author, head->describe,
			head->type, head->ID, head->digits, head->times, head->isBorrowed);
		head = head->next;
	}
}
//ģ����ѯ�鼮
int keywors_find(pBook* book_list)
{
	int flag = False;
	int cnt = 0;
	pBook head = *book_list;
	printf("\n������ؼ��֣�\n");
	char keywords[MAX]="";
	gets_s(keywords, MAX);
	while (head)
	{
		if (strstr(head->book_name, keywords)|| strstr(head->author, keywords) ||
			strstr(head->describe, keywords)|| strstr(head->type, keywords))
		{
			if (cnt==0)
			{
				printf("\n�鼮\t\t����\t����\t\t����\tͼ����\t�ݲ�����\t�����Ĵ���\t�������(0��ʾδ���)\n");
				cnt = 1;
			}
			printf("��%s��\t%s\t%s\t%s\t%s\t\t%d\t\t%d\t\t%d\n", head->book_name, head->author, head->describe,
				head->type, head->ID, head->digits, head->times,head->isBorrowed);
			flag = True;
		}
		head = head->next;
	}
	return flag;
}
//����鼮
int add_book(pBook* book_list)
{
	FILE* fp;
	fp = fopen("library.txt", "w");
	if (!fp)
	{
		printf("���ļ�ʧ��\n");
		exit(1);
	}
	pBook book = (pBook)malloc(sizeof(Book));
	if (book==NULL)
	{
		printf("�����ڴ�ʧ��");
		exit(1);
	}
	printf("\n�������������:\n");
	gets_s(book->book_name, MAX);
	printf("����������:\n");
	gets_s(book->author, MAX);
	if (book_compare(book,book_list))
	{
		goto write;
	}
	else
	{
		printf("�������鼮�ķ���:\n");
		gets_s(book->type, MAX);
		printf("�������鼮�ļ�����:\n");
		gets_s(book->describe, DESCRIBE);
		//��������鼮ΨһID
		register_rand_account(book->ID, 6);
		//���ɽ��Ĵ����͹ݲ�
		book->times = 0;
		book->digits = 1;
		book->isBorrowed = False;
		book->next = NULL;

		//ͷ��
		pBook head = *book_list;
		book->next = head;
		*book_list = book;

	write://д����
		write_book(fp, book_list);
		fclose(fp);
		return True;
	}
	
}
//��֤ͼ����Ƿ����¼���鼮�ĺ���
int book_compare(pBook book, pBook* book_list)
{
	pBook head = *book_list;
	while (head)
	{
		if ((strcmp(head->book_name,book->book_name)==0)&&(strcmp(head->author,book->author)==0))
		{
			head->digits += 1;
			return True;
		}
		head = head->next;
	}
	return False;
}
//���鼮�־û���Ӳ�̵ĺ���
int write_book(FILE* fp, pBook* book_list)
{
	pBook head = *book_list;
	while (head)
	{
		if (fp)
		{
			fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%d\t%d\t%d\n", head->book_name, head->author, head->describe,
				head->type, head->ID, head->digits, head->times, head->isBorrowed);
		}
		head = head->next;
	}
	return True;
}
//ɾ��ͼ��
int delete_book(pBook* book_list)
{
	char name[MAX] = "";
	char author[MAX] = "";
	printf("\n��������Ҫɾ����ͼ����:\n");
	gets_s(name, MAX);
	printf("��������Ҫɾ��ͼ�������:\n");
	gets_s(author, MAX);
	if (delete_compare(name,author,book_list))
	{
		//���ɾ���ɹ����־û���Ӳ��
		FILE* fp;
		fp = fopen("library.txt", "w");
		if (!fp)
		{
			printf("���ļ�ʧ��\n");
			exit(1);
		}
		write_book(fp, book_list);
		fclose(fp);
		return True;
	}
	return False;
}
//ɾ��ͼ��ʱ������Ƚϵĺ���
int delete_compare(char* book_name, char* author, pBook* book_list)
{
	pBook head = *book_list, previous = NULL;
	while (head)
	{
		if ((strcmp(book_name,head->book_name)==0)&&(strcmp(author,head->author)==0))
		{
			if (head->digits==0&&previous==NULL)
			{
				*book_list = head->next;/*Ҫɾ�����鼮��ͷ�ڵ�*/
				return True;
			}
			else if (head->digits==0&&previous!=NULL)
			{
				previous->next = head->next;/*Ҫɾ���Ľڵ㲻��ͷ�ڵ�*/
				return True;
			}
			else/*Ҫɾ�����鼮�ݲ�����Ϊ0*/
			{
				printf("\n��Ҫɾ�����鼮ͼ��ݻ��йݲأ�ȷ��ɾ����Ϣ��(y/n)\n");
				char ch = getchar();
				if (ch == 'y')
				{
					if (previous == NULL) *book_list = head->next;
					else previous->next = head->next;
					return True;
				}
				else if (ch == 'n') break;
			}
		}
		previous = head;
		head = head->next;
	}
	return False;
}
//�����鼮��Ϣ
int update_book(pBook* book_list)
{
	pBook head = *book_list;
	printf("��������Ҫ�����鼮��ID(�粻����鼮ID����ʹ�ò�ѯ����)��\n");
	char ID[MAX] = "";
	gets_s(ID, MAX);
	while (head)
	{
		if (strcmp(head->ID,ID)==0)
		{
			//¼����Ϣ
			printf("�������µ��鼮����:\n");
			gets_s(head->book_name, MAX);
			printf("�������µ��鼮����:\n");
			gets_s(head->author, MAX);
			printf("�������µ��鼮����:\n");
			gets_s(head->describe, DESCRIBE);
			//�־û�
			FILE* fp;
			fp = fopen("library.txt", "w");
			if (!fp)
			{
				printf("���ļ�ʧ��\n");
				exit(1);
			}
			write_book(fp, book_list);
			fclose(fp);

			return True;
		}
		head = head->next;
	}
	return False;
}
//��ӡ�����û�
int printlnAll_users()
{
	FILE* fp;
	fp = fopen("users.txt", "r");
	if (!fp)
	{
		printf("���ļ�ʧ��");
		exit(1);
	}
	pUser users = NULL;
	findAll_user(fp, &users);
	fclose(fp);
	printf("����\t�˺�\t\t����\t\t�Ա�\t���(1:����Ա/0:�û�)\t���ڷ���\n");
	while (users)
	{
		printf("%s\t%s\t%s\t%s\t%d\t\t\t%d\n", users->user_name, users->account, users->password
			, users->gender, users->identity, users->fine);
		users = users->next;
	}
	return True;
}
//����ͳ����Ϣ�ĺ���
int count_books(pBook book_list)
{
	//ͳ���ڹ��鼮����
	int sum_books = 0, lent_books = 0, return_books = 0;
	while (book_list)
	{
		lent_books += book_list->isBorrowed;
		return_books += book_list->digits;
		book_list = book_list->next;
	}
	sum_books = lent_books + return_books;
	printf("�ڹ��鼮��%d\t����鼮��%d\t������%d\n", return_books, lent_books, sum_books);
	//��ӡ���ļ�¼
	pRecord records = NULL;
	findAll_records(&records);
	printlnAll_records(&records);
	destory_records(records);
	return True;

}
//��ӡ���н��ļ�¼
int printlnAll_records(pRecord* records)
{
	pRecord head = *records;
	printf("\n����鼮\t����û�\t\t���ʱ��\t\t\t�黹ʱ��\t\t\t\t�涨�黹ʱ��\n");
	while (head)
	{
		char return_time[MAX] = "", borrow_time[MAX] = "", limited_time[MAX] = "";
		ctime_s(return_time, MAX, &head->return_time);
		ctime_s(borrow_time, MAX, &head->borrow_time);
		ctime_s(limited_time, MAX, &head->limted_time);
		delete_enter(return_time);
		delete_enter(borrow_time);
		delete_enter(limited_time);
		printf("%s\t\t%s\t\t%s\t\t%s\t\t%s\n", head->book_name, head->user_name, borrow_time, return_time, limited_time);
		head = head->next;
	}
	return True;
}
//ȥ���ַ���ĩβ�Ļ��з�(ctime_s���ص�ʱ���ַ���ĩβ�л��з�����Ҫ�ֶ�ȥ��)
void delete_enter(char* str)
{
	char* tmp = NULL;
	if (tmp=strstr(str,"\n"))
	{
		*tmp = '\0';
	}
}
//��ʾ������Ϣ
void pritlnAll_fines()
{
	FILE* fp;
	fp = fopen("users.txt", "r");
	if (!fp)
	{
		printf("�ڴ����ʧ��\n");
		exit(1);
	}
	pUser users = NULL;
	findAll_user(fp, &users);
	
}
//���ݷ����������
int sort_users(pUser* users)
{
	pUser head = *users;
	pUser current = NULL, previous = NULL;
	int len = len_linked(head);
	for (int i = 0; i < len-1; i++)
	{
		for (int j = 0; j < len-i-1; j++)
		{

		}
	}

}
//��ȡ������
int len_linked(pUser user)
{
	int len = 0;
	while (user)
	{
		len++;
		user = user->next;
	}
	return len;
}


//----------�û�----------
//�û�����ͼ��
int borrow_book(pUser user, pBook* book_list)
{
	printf("\n��������Ҫ���ĵ�ͼ��ID(��������ID������ʹ�ò�ѯ����)\n");
	char ID[MAX] = "";
	gets_s(ID, MAX);
	pBook head = *book_list;
	while (head)
	{
		if ((strcmp(head->ID,ID)==0)&&(head->digits>0))
		{
			head->digits -= 1;
			head->isBorrowed += 1;
			head->times += 1;

			pRecord record = (pRecord)malloc(sizeof(Record));
			if (!record)
			{
				printf("�ڴ����ʧ��");
				exit(1);
			}
			record->borrow_time = time(NULL);
			record->return_time = 0;
			//���ɵ�ǰʱ��
			time_t current_time = time(NULL);
			//�涨һ�ܺ���
			record->limted_time = current_time + WEEK;
			strcpy(record->bookID, head->ID);
			strcpy(record->book_name, head->book_name);
			strcpy(record->user_name, user->user_name);
			//�����ݳ־û���Ӳ��
			write_record(record);
			//д���ļ���record���ò����ˣ���������Ҫ�ͷ��ڴ�
			free(record);
			//�Ѹ��ĺ���鼮��Ϣд���ļ�
			FILE* fp;
			fp = fopen("library.txt", "w");
			if (!fp)
			{
				printf("�ڴ����ʧ��\n");
				exit(1);
			}
			write_book(fp, book_list);
			fclose(fp);
			return True;
		}
		head = head->next;
	}
	return False;
}
//�������¼�־û���Ӳ��
int write_record(pRecord record)
{
	FILE* fp;
	fp = fopen("record.txt", "a+");
	if (!fp)
	{
		printf("�ڴ����ʧ��");
		exit(1);
	}
	fprintf(fp, "%s\t%s\t%s\t%lld\t%lld\t%lld\n", record->book_name, record->bookID,record->user_name,
		record->borrow_time, record->return_time, record->limted_time);
	fclose(fp);
	return True;
}
//�û��黹ͼ��
int return_book(pUser user,pBook* book_list)
{
	int flag = False;
	pBook head = *book_list;
	printf("��������黹�鼮����\n");
	char name[MAX] = "";
	gets_s(name, MAX);
	printf("��������黹�鼮������\n");
	char author[MAX] = "";
	gets_s(author, MAX);

	pRecord records = NULL;
	findAll_records(&records);
	while (head)
	{
		if ((strcmp(head->author,author)==0)&&(strcmp(head->book_name,name)==0))
		{
			if (is_overdue(user, &records))
			{
				head->isBorrowed -= 1;
					head->digits += 1;
					flag = True;
					break;
			}
		}
		head = head->next;
	}
	//�ѸĶ�����鼮��Ϣд���ļ�
	FILE* fp;
	fp = fopen("library.txt", "w");
	if (fp==NULL)
	{
		printf("�ļ���ʧ��");
		exit(1);
	}
	write_book(fp, book_list);
	fclose(fp);
	destory_records(records);
	return flag;
}
//�������н����¼�ĺ���
int findAll_records(pRecord* records)
{
	pRecord record = (pRecord)malloc(sizeof(Record));
	if (record == NULL)
	{
		printf("�ڴ����ʧ��\n");
		exit(1);
	}
	FILE* fp;
	fp = fopen("record.txt", "r");
	int result = fscanf_s(fp, "%s\t%s\t%s\t%lld\t%lld\t%lld", record->book_name, MAX, record->bookID, MAX, record->user_name, MAX,
		&record->borrow_time, &record->return_time, &record->limted_time);
	record->next = NULL;
	//��ͷ�ڵ������ڶ�����������
	*records = record;
	while (result != -1)
	{
		pRecord current = (pRecord)malloc(sizeof(Record));
		result = fscanf_s(fp, "%s\t%s\t%s\t%lld\t%lld\t%lld", current->book_name, MAX, current->bookID, MAX, current->user_name, MAX,
			&current->borrow_time, &current->return_time, &current->limted_time);
		current->next = NULL;
		if (result != -1)
		{
			record->next = current;
			record = current;
		}
	}
	fclose(fp);
	return True;
}
//�û��Ƿ����ڵĺ���
int is_overdue(pUser user, pRecord* records)
{
	pRecord record = *records;
	//�򿪴�ż�¼���ļ�
	FILE* fe = NULL;
	fe = fopen("record.txt", "w");
	if (!fe)
	{
		printf("�ļ���ʧ��");
		exit(1);
	}
	int flag = False;
	//�Բ鵽�ļ�¼����
	while (record)
	{
		if ((strcmp(user->user_name,record->user_name)==0)&&(record->return_time==0))
		{
			flag = True;
			time_t current_time = time(NULL);
			record->return_time = current_time;
			if (current_time>record->limted_time)
			{	
				printf("���������������أ�����ݹ涨���콻�뷣��\n");
				pUser users = NULL;
				FILE* fp;
				//������
				fp = fopen("users.txt", "r");
				if (!fp)
				{
					printf("���ļ�ʧ��");
					exit(1);
						
				}
				findAll_user(fp, &users);

				pUser head = users;
				while (head)
				{
					if (strcmp(head->user_name,user->user_name)==0)
					{
						head->fine += 100;
						break;
					}
					head = head->next;
				}
				fclose(fp);
				//������д���ļ�
				fp = fopen("users.txt", "w");
				write_users(fp, &users);
				fclose(fp);
				//�ͷ��ڴ�
				destory_users(users);
			}
		}
		fprintf(fe, "%s\t%s\t%s\t%lld\t%lld\t%lld\n", record->book_name, record->bookID, record->user_name,
			record->borrow_time, record->return_time, record->limted_time);
		record = record->next;
	}
	fclose(fe);
	return flag;
}
//д�������û��ĺ���
int write_users(FILE* fp, pUser* users)
{
	pUser user = *users;
	while (user)
	{
		fprintf(fp, "%s\t%s\t%s\t%s\t%d\t%d\n", user->user_name, user->account, user->password,
			user->gender, user->identity, user->fine);
		user = user->next;
	}
	return True;
}
//�ͷ��û��ĺ���
int destory_users(pUser users)
{
	pUser previous = NULL;
	while (users)
	{
		previous = users->next;
		free(users);
		users = previous;
	}
}
//�ͷż�¼����ĺ���
int destory_records(pRecord records)
{
	pRecord previous = NULL;
	while (records)
	{
		previous = records->next;
		free(records);
		records = previous;
	}
	return True;
}
//�û��޸���Ϣ�ĺ���
int update_user(pUser user)
{
	int flag = False;
	FILE* fp;
	fp = fopen("users.txt", "r");
	if (!fp)
	{
		printf("�ļ���ʧ��\n");
		exit(1);
	}
	pUser users;
	findAll_user(fp, &users);
	fclose(fp);
	pUser head = users;
	while (head)
	{
		if (strcmp(user->account,head->account)==0)
		{
			printf("���������������:\n");
			gets_s(head->user_name, MAX);
password:	printf("���������������:\n");
			char password1[MAX]="", password2[MAX]="";
			gets_s(password1, MAX);
			printf("���ٴ�ȷ��������룺\n");
			gets_s(password2, MAX);
			if (strcmp(password1,password2)==0)
			{
				strcpy(head->password,password1);
			}
			else
			{
				printf("��������������벻һ�£�����������\n");
				goto password;
			}
			flag = True;
			break;
		}
		head = head->next;
	}
	//�����µ���Ϣ�־û���Ӳ��
	fp = fopen("users.txt", "w");
	if (!fp)
	{
		printf("�ļ���ʧ��\n");
		exit(1);
	}
	write_users(fp, &users);
	fclose(fp);
	//�ͷ��ڴ�
	destory_users(users);
	return flag;
}


