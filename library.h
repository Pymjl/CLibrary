#pragma once
#ifndef Library
#define Library

//----------------�궨����---------------
#define True 1
#define False 0
#define MAX 26
#define DESCRIBE 100
#define ACCOUNT 11
#define PASSWORD 17
#define GENDER 3
#define MANAGER 1
#define USER 0
#define WEEK 604800


//---------------�ṹ�嶨����---------------
/*�鼮*/
typedef struct book{
	int isBorrowed;//�Ƿ���
	int times;//�����ô���
	int digits;//ͼ��ݹݲ���
	char ID[MAX];//�鼮ID
	char book_name[MAX];//����
	char author[MAX];//����
	char type[MAX];//���
	char describe[DESCRIBE];//�鼮�򵥵�����
	struct book* next;//ָ�����
}Book,*pBook;

/*�û�*/
typedef struct user {
	int identity;//��� MANAGERΪ����Ա��USERΪ��ͨ�û�
	int fine;//���ڷ���
	char gender[GENDER];//�Ա�
	char account[ACCOUNT];//�˺�
	char password[PASSWORD];//����
	char user_name[MAX];//����
	struct user* next;
}User,*pUser;

/*���ļ�¼*/
typedef struct record {
	char bookID[MAX];//�鼮ID
	char book_name[MAX];//����
	char user_name[MAX];//����û�
	time_t borrow_time;//���ʱ��
	time_t return_time;//�黹ʱ��
	time_t limted_time;//�涨�黹ʱ��
	struct record* next;
}Record,*pRecord;



//---------------����������---------------
//�������˵�
void menu_main();
//�����û��˵�
void menu_user();
//�������Ա�˵�
void menu_manager();
//���嶳�ắ��
int freeze_account(int number);
//�����ͷ��û�����ĺ���
int destory_users(pUser users);
//�����ͷż�¼����ĺ���
int destory_records(pRecord records);

//��¼----------------------------------------------------------
//���� �û�/���� ��¼
int login(pUser* user);
//���� �û�/����Ա �����˺ŵĺ���
int input(char* account, char* password);
//����У�麯��
int login_compare(char* account, char* password,pUser users, pUser* user);//user�����浱ǰ��¼�û���Ϣ
//������������û��ĺ���
int findAll_user(FILE* fp,pUser* users);//users�����������û���Ϣ


//ע��------------------------------------------------------------
//�����û�ע�ắ��
int register_user();
//������������˺ŵĺ���
void register_rand_account(char *account,int number);
//�����û�ע��ʱ¼����Ϣ�ĺ���
int register_input(pUser* student);
//�����û�ע��ʱ����Ϣд���ļ��ĺ���
int register_fwrite(FILE* fp, pUser user);


//�����鼮------------------------------------------------------------
/*�����鼮*/
//�û�/����Ա �鿴�����鼮
int findAll_book(pBook* book_list);
//��ӡ�����鼮
void println(pBook head);
//�ؼ��ֲ�ѯ(ģ����ѯ)
int keywors_find(pBook* book_list);


//�û�����---------------------------------------------------------------
//�û�����ͼ��
int borrow_book(pUser user, pBook* book_list);
//�������¼�־û���Ӳ��
int write_record(pRecord record);
//�û��黹ͼ��
int return_book(pUser user,pBook* book_list);
//�������н����¼�ĺ���
int findAll_records(pRecord* records);
//�����û��Ƿ����ڵĺ���
int is_overdue(pUser user,pRecord* records);//û�����ڷ���false�����ڷ��ط������д���ļ�
//����д�������û��ĺ���
int write_users(FILE* fp, pUser* users);
//�����û��鿴���Ĵ���ǰʮ���鼮
int find_advanced_book();
//�����û��޸���Ϣ�ĺ���
int update_user(pUser user);


//����Ա����-------------------------------------------------------------
//����鼮
int add_book(pBook* book_list);
//������֤ͼ����Ƿ����ָ���鼮�ĺ���
int book_compare(pBook book, pBook* book_list);
//���彫�鼮�־û���Ӳ�̵ĺ���
int write_book(FILE* fp, pBook* book_list);
//����ɾ��ͼ��
int delete_book(pBook* book_list);
//����ɾ��ͼ��ʱ������Ƚϵĺ���
int delete_compare(char* book_name, char* author, pBook* book_list);
//��������鼮��Ϣ
int update_book(pBook* book_list);
//����������л�Ա
int printlnAll_users();
//����ͳ����Ϣ�ĺ���
int count_books(pBook book_list);
//��ӡ���н��ļ�¼
int printlnAll_records(pRecord* records);
//ȥ���ַ���ĩβ�Ļ��з�(ctime_s���ص�ʱ���ַ���ĩβ�л��з�����Ҫ�ֶ�ȥ��)
void delete_enter(char* str);
//��ʾ������Ϣ
void pritlnAll_fines();
//���ݷ����������
int sort_users(pUser* users);
//��ȡ������
int len_linked(pUser user);
#endif // !Library
