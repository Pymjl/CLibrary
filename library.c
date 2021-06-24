#include <stdio.h>
#include "library.h"
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <sys/types.h>
#include <sys/stat.h>


//---------------菜单栏----------------
//主菜单
void menu_main()
{
	printf("\n\n");
	printf("\t\t\t *=======================================*\n");
	printf("\t\t\t|  * - * - * 欢迎来到图书管理系统 * - * -*|\n");
	printf("\t\t\t| *                                     * |\n");
	printf("\t\t\t| |  [1]   用户登录                     | |\n");
	printf("\t\t\t| *                                     * |\n");
	printf("\t\t\t| |  [2]   用户注册                     | |\n");
	printf("\t\t\t| *                                     * |\n");
	printf("\t\t\t| |  [3]   管理员登录                   | |\n");
	printf("\t\t\t| *                                     * |\n");
	printf("\t\t\t| |  [4]   退出系统                     | |\n");
	printf("\t\t\t| *                                     * |\n");
	printf("\t\t\t|  * - * - * - * - * - * - * - * - * - *  |\n");
	printf("\t\t\t *=======================================*\n");
}
//用户菜单栏
void menu_user()
{
	printf("\n\n");
	printf("\t\t\t *=====================================*\n");
	printf("\t\t\t| | * - * - * -会-员-界-面- * - * - * | |\n");
	printf("\t\t\t| *                                   * |\n");
	printf("\t\t\t| |  [1]   查找图书信息               | |\n");
	printf("\t\t\t| *  [2]   借阅图书                   * |\n");
	printf("\t\t\t| |  [3]   归还图书                   | |\n");
	printf("\t\t\t| |  [4]   修改账户信息               | |\n");
	printf("\t\t\t| *  [5]   退出用户界面               * |\n");
	printf("\t\t\t| |                                   | |\n");
	printf("\t\t\t| * - * - * - * - * - * - * - * - * - * |\n");
	printf("\t\t\t *=====================================*\n");
}
//管理员菜单栏
void menu_manager()
{
	printf("\n\n");
	printf("\t\t\t *======================================*\n");
	printf("\t\t\t| | * - * - * 管-理-员-界-面 * - * - * | |\n");
	printf("\t\t\t| *                                    * |\n");
	printf("\t\t\t| |  [1]   添加图书                    | |\n");
	printf("\t\t\t| *  [2]   删减图书                    * |\n");
	printf("\t\t\t| |  [3]   修改图书信息                | |\n");
	printf("\t\t\t| *  [4]   查找图书信息                * |\n");
	printf("\t\t\t| |  [5]   显示全部图书信息            | |\n");
	printf("\t\t\t| *  [6]   显示所有会员信息            * |\n");
	printf("\t\t\t| |  [7]   统计所有借阅信息            | |\n");
	printf("\t\t\t| |  [8]   显示罚款信息详情            | |\n");
	printf("\t\t\t| *  [9]   退出管理员界面              * |\n");
	printf("\t\t\t| |                                    | |\n");
	printf("\t\t\t| * - * - * - * - * -- * - * - * - * - * |\n");
	printf("\t\t\t *======================================*\n");
}


//---------------登录操作----------------
//用户登录
int login(pUser* user)
{
	char account[ACCOUNT]="";
	char password[PASSWORD]="";
	FILE* fp;
	pUser users = NULL;
	//输入账号密码
	input(account, password);
	//打开文件并从文件读入所有用户信息
	errno_t message = fopen_s(&fp, "users.txt", "r");
	findAll_user(fp, &users);
	if (fp)
	{
		fclose(fp);
	}
	//校验密码
	if (!login_compare(account, password, users, user))
	{
		return False;
	}
	return True;
}
//用户/管理员输入账号信息
int input(char* account, char* password) {
	printf("请输入你的账号:\n");
	gets_s(account, ACCOUNT);
	printf("\n请输入你的密码:\n");
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
//查找所有用户的函数
int findAll_user(FILE* fp,pUser* users) 
{
	pUser user = (pUser)malloc(sizeof(User));
	if (user==NULL)
	{
		printf("动态内存分配失败\n");
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
			printf("动态内存分配失败\n");
			exit(1);
		}
		if (fp)
		{
			result = fscanf_s(fp, "%s %s %s %s %d %d", current->user_name, MAX, current->account, ACCOUNT, current->password, PASSWORD,
				current->gender, GENDER, &current->identity, &current->fine);
			/*这里会遇到一个问题，读文件会多读一行，不知道为什么，明明文件里只有两个数据结果读出了三个结构体，
			第三个结构体还是乱码，猜测可能是换行符引起的，所以这里加个判断过滤一下*/
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
//校验函数
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
//冻结函数
int freeze_account(int number)
{
	if (number >= 3)
	{
		printf("账号密码错误次数超过3次，请一分钟后再试\n");
		printf("...\n");
		Sleep(60000);
		number = -1;
	}
	return ++number;
}


//---------------用户注册----------------
//用户注册账号
int register_user()
{
	FILE* fp;
	pUser user = NULL;
	if (register_input(&user))
	{
		//打开文件
		errno_t message = fopen_s(&fp, "users.txt", "ab+");
		//将用户信息持久化到硬盘(写入文件)
		if (fp)
		{
			register_fwrite(fp, user);
			fclose(fp);
		}
		//输出随机生成的账号
		printf("您的账号是: %s, 请记住您的账号！\n",user->account);
		return True;
	}
	return False;
}
//随机生成账户的函数
void register_rand_account(char* account,int number)
{
	int i;
	srand((unsigned)time(NULL));
	for (i = 0; i < number; i++)
	{
		/* int A = rand() % x+y:生成一个y到x+y的随机数 */
		int num = rand() % 9;
		account[i] = num + '0';
	}
	account[i] = '\0';
}
//用户注册录入信息的函数
int  register_input(pUser* student)
{
	char password[PASSWORD] = "";/*定义检验密码的变量*/

	pUser stu = (pUser)malloc(sizeof(User));/*为学生对象分配内存*/
	if (stu==NULL)
	{
		printf("内存分配失败\n");
		exit(1);
	}
	
	//录入信息
	register_rand_account(stu->account,10);//生成随机账号
	stu->identity = USER;//录入身份
	stu->fine = 0;
	printf("请输入你的姓名:\n");
	gets_s(stu->user_name, MAX);//录入用户名
	if (strcmp(stu->user_name,"")==0)
	{
		printf("姓名不能为空,请重新输入\n");
		return False;
	}
	printf("请输入你的密码(密码长度应为8-16):\n");
	gets_s(stu->password, PASSWORD);
	//校验长度
	if (strlen(stu->password) < 8)
	{
		printf("你的密码长度不符合规范，请重新输入\n");
		return False;
	}
	printf("请重复你的密码(密码长度应为8-16):\n");
	gets_s(password, PASSWORD);
	//校验密码是否一致
	if (strcmp(password, stu->password) != 0)
	{
		printf("你两次输入的密码有误，请重新输入\n");
		return False;
	}
	
	printf("请输入你的性别:\n");
	gets_s(stu->gender, GENDER);//录入性别
	stu->next = NULL;
	*student = stu;//将用户信息返回
	return True;
}
//写入文件
int register_fwrite(FILE* fp, pUser user)
{
	fprintf(fp, "%s\t%s\t%s\t%s\t%d\t%d\n", user->user_name, user->account, user->password,
		user->gender, user->identity, user->fine);
	return True;
}


//---------------功能模块----------------
// --------------管理员----------
//查找所有书籍
int findAll_book(pBook* book_list)
{
	FILE* fe;
	fe = fopen("library.txt", "r");
	if (!fe)
	{
		printf("打开文件失败");
	}
	pBook head = (pBook)malloc(sizeof(Book));
	if (head==NULL)
	{
		printf("内存分配失败");
		exit(1);
	}
	//从文件中拿取数据
	if (fe)
	{
		int result=fscanf_s(fe, "%s %s %s %s %s %d %d %d", head->book_name, MAX, head->author, MAX, head->describe, DESCRIBE,
			head->type, MAX, head->ID,MAX, &head->digits, &head->times, &head->isBorrowed);
		if (head->ID<=0||result==-1)
		{
			//文件为空
			return False;
		}
		else
		{
			//让图书列表指针指向头指针
			*book_list = head;
			head->next = NULL;
		}
		while (result!=-1)
		{
			//分配内存
			pBook current = (pBook)malloc(sizeof(Book));
			if (current==NULL)
			{
				printf("分配内存失败");
				exit(1);
			}

			 result = fscanf_s(fe, "%s %s %s %s %s %d %d %d", current->book_name, MAX, current->author, MAX, current->describe, DESCRIBE,
				current->type, MAX, &current->ID, MAX, &current->digits, &current->times, &current->isBorrowed);
			 //连接链表
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
//打印所有书籍
void println(pBook head)
{
	printf("书籍\t\t作者\t描述\t\t分类\t图书编号\t馆藏数量\t被借阅次数\t借出数量(0表示未借出)\n");
	while (head)
	{
		printf("《%s》\t%s\t%s\t%s\t%s\t\t%d\t\t%d\t\t%d\n", head->book_name, head->author, head->describe,
			head->type, head->ID, head->digits, head->times, head->isBorrowed);
		head = head->next;
	}
}
//模糊查询书籍
int keywors_find(pBook* book_list)
{
	int flag = False;
	int cnt = 0;
	pBook head = *book_list;
	printf("\n请输入关键字：\n");
	char keywords[MAX]="";
	gets_s(keywords, MAX);
	while (head)
	{
		if (strstr(head->book_name, keywords)|| strstr(head->author, keywords) ||
			strstr(head->describe, keywords)|| strstr(head->type, keywords))
		{
			if (cnt==0)
			{
				printf("\n书籍\t\t作者\t描述\t\t分类\t图书编号\t馆藏数量\t被借阅次数\t借出数量(0表示未借出)\n");
				cnt = 1;
			}
			printf("《%s》\t%s\t%s\t%s\t%s\t\t%d\t\t%d\t\t%d\n", head->book_name, head->author, head->describe,
				head->type, head->ID, head->digits, head->times,head->isBorrowed);
			flag = True;
		}
		head = head->next;
	}
	return flag;
}
//添加书籍
int add_book(pBook* book_list)
{
	FILE* fp;
	fp = fopen("library.txt", "w");
	if (!fp)
	{
		printf("打开文件失败\n");
		exit(1);
	}
	pBook book = (pBook)malloc(sizeof(Book));
	if (book==NULL)
	{
		printf("分配内存失败");
		exit(1);
	}
	printf("\n请输入书的名字:\n");
	gets_s(book->book_name, MAX);
	printf("请输入作者:\n");
	gets_s(book->author, MAX);
	if (book_compare(book,book_list))
	{
		goto write;
	}
	else
	{
		printf("请输入书籍的分类:\n");
		gets_s(book->type, MAX);
		printf("请输入书籍的简单描述:\n");
		gets_s(book->describe, DESCRIBE);
		//随机生成书籍唯一ID
		register_rand_account(book->ID, 6);
		//生成借阅次数和馆藏
		book->times = 0;
		book->digits = 1;
		book->isBorrowed = False;
		book->next = NULL;

		//头插
		pBook head = *book_list;
		book->next = head;
		*book_list = book;

	write://写数据
		write_book(fp, book_list);
		fclose(fp);
		return True;
	}
	
}
//验证图书馆是否存在录入书籍的函数
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
//将书籍持久化到硬盘的函数
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
//删除图书
int delete_book(pBook* book_list)
{
	char name[MAX] = "";
	char author[MAX] = "";
	printf("\n请输入你要删除的图书名:\n");
	gets_s(name, MAX);
	printf("请输入你要删除图书的作者:\n");
	gets_s(author, MAX);
	if (delete_compare(name,author,book_list))
	{
		//如果删除成功，持久化到硬盘
		FILE* fp;
		fp = fopen("library.txt", "w");
		if (!fp)
		{
			printf("打开文件失败\n");
			exit(1);
		}
		write_book(fp, book_list);
		fclose(fp);
		return True;
	}
	return False;
}
//删除图书时链表处理比较的函数
int delete_compare(char* book_name, char* author, pBook* book_list)
{
	pBook head = *book_list, previous = NULL;
	while (head)
	{
		if ((strcmp(book_name,head->book_name)==0)&&(strcmp(author,head->author)==0))
		{
			if (head->digits==0&&previous==NULL)
			{
				*book_list = head->next;/*要删除的书籍在头节点*/
				return True;
			}
			else if (head->digits==0&&previous!=NULL)
			{
				previous->next = head->next;/*要删除的节点不在头节点*/
				return True;
			}
			else/*要删除的书籍馆藏量不为0*/
			{
				printf("\n你要删除的书籍图书馆还有馆藏，确定删除信息吗？(y/n)\n");
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
//更新书籍信息
int update_book(pBook* book_list)
{
	pBook head = *book_list;
	printf("请输入你要更改书籍的ID(如不清楚书籍ID请先使用查询功能)：\n");
	char ID[MAX] = "";
	gets_s(ID, MAX);
	while (head)
	{
		if (strcmp(head->ID,ID)==0)
		{
			//录入信息
			printf("请输入新的书籍名称:\n");
			gets_s(head->book_name, MAX);
			printf("请输入新的书籍作者:\n");
			gets_s(head->author, MAX);
			printf("请输入新的书籍描述:\n");
			gets_s(head->describe, DESCRIBE);
			//持久化
			FILE* fp;
			fp = fopen("library.txt", "w");
			if (!fp)
			{
				printf("打开文件失败\n");
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
//打印所有用户
int printlnAll_users()
{
	FILE* fp;
	fp = fopen("users.txt", "r");
	if (!fp)
	{
		printf("打开文件失败");
		exit(1);
	}
	pUser users = NULL;
	findAll_user(fp, &users);
	fclose(fp);
	printf("姓名\t账号\t\t密码\t\t性别\t身份(1:管理员/0:用户)\t逾期罚款\n");
	while (users)
	{
		printf("%s\t%s\t%s\t%s\t%d\t\t\t%d\n", users->user_name, users->account, users->password
			, users->gender, users->identity, users->fine);
		users = users->next;
	}
	return True;
}
//定义统计信息的函数
int count_books(pBook book_list)
{
	//统计在馆书籍数量
	int sum_books = 0, lent_books = 0, return_books = 0;
	while (book_list)
	{
		lent_books += book_list->isBorrowed;
		return_books += book_list->digits;
		book_list = book_list->next;
	}
	sum_books = lent_books + return_books;
	printf("在馆书籍：%d\t借出书籍：%d\t总数：%d\n", return_books, lent_books, sum_books);
	//打印借阅记录
	pRecord records = NULL;
	findAll_records(&records);
	printlnAll_records(&records);
	destory_records(records);
	return True;

}
//打印所有借阅记录
int printlnAll_records(pRecord* records)
{
	pRecord head = *records;
	printf("\n借出书籍\t借出用户\t\t借出时间\t\t\t归还时间\t\t\t\t规定归还时间\n");
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
//去掉字符串末尾的换行符(ctime_s返回的时间字符串末尾有换行符，需要手动去除)
void delete_enter(char* str)
{
	char* tmp = NULL;
	if (tmp=strstr(str,"\n"))
	{
		*tmp = '\0';
	}
}
//显示罚款信息
void pritlnAll_fines()
{
	FILE* fp;
	fp = fopen("users.txt", "r");
	if (!fp)
	{
		printf("内存分配失败\n");
		exit(1);
	}
	pUser users = NULL;
	findAll_user(fp, &users);
	
}
//根据罚款多少排序
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
//获取链表长度
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


//----------用户----------
//用户借阅图书
int borrow_book(pUser user, pBook* book_list)
{
	printf("\n请输入你要借阅的图书ID(如果不清楚ID，请先使用查询功能)\n");
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
				printf("内存分配失败");
				exit(1);
			}
			record->borrow_time = time(NULL);
			record->return_time = 0;
			//生成当前时间
			time_t current_time = time(NULL);
			//规定一周后还书
			record->limted_time = current_time + WEEK;
			strcpy(record->bookID, head->ID);
			strcpy(record->book_name, head->book_name);
			strcpy(record->user_name, user->user_name);
			//将数据持久化到硬盘
			write_record(record);
			//写进文件后record就用不到了，所以这里要释放内存
			free(record);
			//把更改后的书籍信息写回文件
			FILE* fp;
			fp = fopen("library.txt", "w");
			if (!fp)
			{
				printf("内存分配失败\n");
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
//将借书记录持久化到硬盘
int write_record(pRecord record)
{
	FILE* fp;
	fp = fopen("record.txt", "a+");
	if (!fp)
	{
		printf("内存分配失败");
		exit(1);
	}
	fprintf(fp, "%s\t%s\t%s\t%lld\t%lld\t%lld\n", record->book_name, record->bookID,record->user_name,
		record->borrow_time, record->return_time, record->limted_time);
	fclose(fp);
	return True;
}
//用户归还图书
int return_book(pUser user,pBook* book_list)
{
	int flag = False;
	pBook head = *book_list;
	printf("请输入待归还书籍书名\n");
	char name[MAX] = "";
	gets_s(name, MAX);
	printf("请输入待归还书籍的作者\n");
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
	//把改动后的书籍信息写入文件
	FILE* fp;
	fp = fopen("library.txt", "w");
	if (fp==NULL)
	{
		printf("文件打开失败");
		exit(1);
	}
	write_book(fp, book_list);
	fclose(fp);
	destory_records(records);
	return flag;
}
//读出所有借书记录的函数
int findAll_records(pRecord* records)
{
	pRecord record = (pRecord)malloc(sizeof(Record));
	if (record == NULL)
	{
		printf("内存分配失败\n");
		exit(1);
	}
	FILE* fp;
	fp = fopen("record.txt", "r");
	int result = fscanf_s(fp, "%s\t%s\t%s\t%lld\t%lld\t%lld", record->book_name, MAX, record->bookID, MAX, record->user_name, MAX,
		&record->borrow_time, &record->return_time, &record->limted_time);
	record->next = NULL;
	//将头节点连接在读出的数据中
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
//用户是否逾期的函数
int is_overdue(pUser user, pRecord* records)
{
	pRecord record = *records;
	//打开存放记录的文件
	FILE* fe = NULL;
	fe = fopen("record.txt", "w");
	if (!fe)
	{
		printf("文件打开失败");
		exit(1);
	}
	int flag = False;
	//对查到的记录遍历
	while (record)
	{
		if ((strcmp(user->user_name,record->user_name)==0)&&(record->return_time==0))
		{
			flag = True;
			time_t current_time = time(NULL);
			record->return_time = current_time;
			if (current_time>record->limted_time)
			{	
				printf("超过还书日期了呢，请根据规定尽快交齐罚款\n");
				pUser users = NULL;
				FILE* fp;
				//读数据
				fp = fopen("users.txt", "r");
				if (!fp)
				{
					printf("打开文件失败");
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
				//将罚款写进文件
				fp = fopen("users.txt", "w");
				write_users(fp, &users);
				fclose(fp);
				//释放内存
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
//写入所有用户的函数
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
//释放用户的函数
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
//释放记录链表的函数
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
//用户修改信息的函数
int update_user(pUser user)
{
	int flag = False;
	FILE* fp;
	fp = fopen("users.txt", "r");
	if (!fp)
	{
		printf("文件打开失败\n");
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
			printf("请输入你的新姓名:\n");
			gets_s(head->user_name, MAX);
password:	printf("请输入你的新密码:\n");
			char password1[MAX]="", password2[MAX]="";
			gets_s(password1, MAX);
			printf("请再次确认你的密码：\n");
			gets_s(password2, MAX);
			if (strcmp(password1,password2)==0)
			{
				strcpy(head->password,password1);
			}
			else
			{
				printf("你两次输入的密码不一致，请重新输入\n");
				goto password;
			}
			flag = True;
			break;
		}
		head = head->next;
	}
	//将更新的信息持久化到硬盘
	fp = fopen("users.txt", "w");
	if (!fp)
	{
		printf("文件打开失败\n");
		exit(1);
	}
	write_users(fp, &users);
	fclose(fp);
	//释放内存
	destory_users(users);
	return flag;
}


