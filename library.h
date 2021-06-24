#pragma once
#ifndef Library
#define Library

//----------------宏定义区---------------
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


//---------------结构体定义区---------------
/*书籍*/
typedef struct book{
	int isBorrowed;//是否借出
	int times;//被借用次数
	int digits;//图书馆馆藏量
	char ID[MAX];//书籍ID
	char book_name[MAX];//书名
	char author[MAX];//作者
	char type[MAX];//类别
	char describe[DESCRIBE];//书籍简单的描述
	struct book* next;//指针变量
}Book,*pBook;

/*用户*/
typedef struct user {
	int identity;//身份 MANAGER为管理员，USER为普通用户
	int fine;//逾期罚款
	char gender[GENDER];//性别
	char account[ACCOUNT];//账号
	char password[PASSWORD];//密码
	char user_name[MAX];//姓名
	struct user* next;
}User,*pUser;

/*借阅记录*/
typedef struct record {
	char bookID[MAX];//书籍ID
	char book_name[MAX];//书名
	char user_name[MAX];//借出用户
	time_t borrow_time;//借出时间
	time_t return_time;//归还时间
	time_t limted_time;//规定归还时间
	struct record* next;
}Record,*pRecord;



//---------------函数定义区---------------
//定义主菜单
void menu_main();
//定义用户菜单
void menu_user();
//定义管理员菜单
void menu_manager();
//定义冻结函数
int freeze_account(int number);
//定义释放用户链表的函数
int destory_users(pUser users);
//定义释放记录链表的含糊
int destory_records(pRecord records);

//登录----------------------------------------------------------
//定义 用户/管理 登录
int login(pUser* user);
//定义 用户/管理员 输入账号的函数
int input(char* account, char* password);
//定义校验函数
int login_compare(char* account, char* password,pUser users, pUser* user);//user用来存当前登录用户信息
//定义查找所有用户的函数
int findAll_user(FILE* fp,pUser* users);//users用来存查出的用户信息


//注册------------------------------------------------------------
//定义用户注册函数
int register_user();
//定义随机生成账号的函数
void register_rand_account(char *account,int number);
//定义用户注册时录入信息的函数
int register_input(pUser* student);
//定义用户注册时将信息写入文件的函数
int register_fwrite(FILE* fp, pUser user);


//查找书籍------------------------------------------------------------
/*查找书籍*/
//用户/管理员 查看所有书籍
int findAll_book(pBook* book_list);
//打印所有书籍
void println(pBook head);
//关键字查询(模糊查询)
int keywors_find(pBook* book_list);


//用户操作---------------------------------------------------------------
//用户借阅图书
int borrow_book(pUser user, pBook* book_list);
//将借书记录持久化到硬盘
int write_record(pRecord record);
//用户归还图书
int return_book(pUser user,pBook* book_list);
//读出所有借书记录的函数
int findAll_records(pRecord* records);
//定义用户是否逾期的函数
int is_overdue(pUser user,pRecord* records);//没有逾期返回false，逾期返回罚款金额，并写入文件
//定义写入所有用户的函数
int write_users(FILE* fp, pUser* users);
//定义用户查看借阅次数前十的书籍
int find_advanced_book();
//定义用户修改信息的函数
int update_user(pUser user);


//管理员操作-------------------------------------------------------------
//添加书籍
int add_book(pBook* book_list);
//定义验证图书馆是否存在指定书籍的函数
int book_compare(pBook book, pBook* book_list);
//定义将书籍持久化到硬盘的函数
int write_book(FILE* fp, pBook* book_list);
//定义删除图书
int delete_book(pBook* book_list);
//定义删除图书时链表处理比较的函数
int delete_compare(char* book_name, char* author, pBook* book_list);
//定义更新书籍信息
int update_book(pBook* book_list);
//定义查找所有会员
int printlnAll_users();
//定义统计信息的函数
int count_books(pBook book_list);
//打印所有借阅记录
int printlnAll_records(pRecord* records);
//去掉字符串末尾的换行符(ctime_s返回的时间字符串末尾有换行符，需要手动去除)
void delete_enter(char* str);
//显示罚款信息
void pritlnAll_fines();
//根据罚款多少排序
int sort_users(pUser* users);
//获取链表长度
int len_linked(pUser user);
#endif // !Library
