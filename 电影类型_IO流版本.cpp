#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>
#define Max 100 
typedef struct movie 				//结构体名											//movie结构体名 
{
	
	char language[20];					
	char movie_name[20];			
	char director[20];			
	int year;			
	int  id;				
	int score;
	movie* next;
	
}Mov;					//类型名	
typedef struct movie_Type{
	char type[10][10];
	Mov *Movs[10];
	int len;
	int Size;
}MovType;

void write_Move(Mov* s){
	printf("请输入电影名：  ");						
	scanf("%s",&s->movie_name);		
	printf("请输入语言：  ");						
	scanf("%s",&s->language);						
	printf("请输导演：  ");					
	scanf("%s",&s->director);				
	printf("请输入年份：  ");						
	scanf("%d",&s->year);				
	printf("请输入id：");					
	scanf("%d",&s->id);
	printf("请输入得分：");					
	scanf("%d",&s->score);
}
void show_Move(Mov* s){
	printf("电影名：%s\t",s->movie_name);	
	printf("语言：%s\t",s->language);											
	printf("导演：%s\t",s->director);									
	printf("年份：%d\t",s->year);										
	printf("id：%d\t",s->id);					
	printf("得分：%d\t",s->score);					
	printf("\n");
}
void ini_movie(Mov* e){
	
	for(int i = 0;i<10;i++){

		e->language[i] = '\0'; 
		printf("%d",i);
		e->movie_name[i] = '\0';
		e->director[i] = '\0';
	}
		
	e->id = -1;
	e->year = -1;
	e->score = -1;
	e->next = NULL;
}
void ini_movie_Type(movie_Type* m){
	m->len = 0;
	m->Size = 10;
	int i = 0;
	for(i=0;i<10;i++){
		for(int j = 0;j<10;j++){
			m->type[i][j] = '\0';
		}
		for(int j = 0;j<10;j++){
			m->Movs[j] = (Mov*)malloc(sizeof(Mov));
			for(int n = 0;n<10;n++){
				m->Movs[j]->director[n] = '\0';
				m->Movs[j]->movie_name[n] = '\0';
				m->Movs[j]->language[n] = '\0';
				m->Movs[j]->id = -1;
				m->Movs[j]->score = -1;
				m->Movs[j]->year = -1;
			}
			
		}
	}
}
void insert_List(MovType* m,int i,Mov* mov){
	mov->next = m->Movs[i]->next;
	m->Movs[i]->next = mov;
	printf("电影类目为: %s \n",m->type[i]);
}
//新建电影leibie  
void create_Type(MovType* m,char* n){
	strcpy(m->type[m->len],n);
	(m->len)++;
}
//遍历所有的电影 
void Movs_traval(MovType* m){
	int i = 0;
	Mov* tmpMovs; 
	for(i=0;i<m->len;i++){
		tmpMovs = m->Movs[i]->next;//相当于头指针
		printf("当前目录为	-----------------------------------------  <<%s>>\n",m->type[i]);
		while(tmpMovs){
			show_Move(tmpMovs);
			tmpMovs = tmpMovs->next;
		} 
			
		
		
	}
}
//结果集进行冒泡排序 
int bubble_sort(Mov* str, int n)
{
    int i,j; 
	Mov tmp;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n-i-1; j++)
        {
            if(str[j].score > str[j+1].score) 
            {
                tmp = str[j]; 
                str[j] = str[j+1]; 
                str[j+1] = tmp;
            }
        }
    }

    return 0;
}
void mov_Search_asname(MovType* m,char* n,int i){
	int sum = 0;
	Mov tmparr[20];
	int index = 0;
	Mov* tmpMovs; 

	tmpMovs = m->Movs[i];//相当于头指针
	while(tmpMovs){
		//这里需要修改 
		//如果电影的名字和传入的名字一致就可以把结果放入tmparr结果集当中
		//方便进行排序显式 
		if(!strcmp(tmpMovs->movie_name,n)){
			sum++;
			tmparr[index++] = *tmpMovs;
		}
		tmpMovs = tmpMovs->next;
		
	}
	bubble_sort(tmparr,sum);//冒泡排序 
	int j = 0;
	// 遍历函数 
	for(j = 0;j<sum;j++){
		Mov* tmpp = &tmparr[j];
		show_Move(tmpp);
	}
	//如果结果集当中的sum为0 就是一个结果都没找到 
	if(sum==0){
		printf("没有找到\n");
	}
}
Mov* mov_Search_name(MovType* m,char* n){
	int i = 0;
	int sum = 0;
	Mov* tmpMovs; 
	Mov tmparr[20];
	for(i=0;i<m->len;i++){
		tmpMovs = m->Movs[i];//相当于头指针
		while(tmpMovs){
			
			if(!strcmp(tmpMovs->movie_name,n)){
				//mparr[sum++] = *tmpMovs;
				return tmpMovs;// 找到直接返回 这里不需要用到结果集 
			}
			
			tmpMovs = tmpMovs->next;
		} 
	}
	
	printf("搜索了%d没有找到\n",sum);//进行搜索个数统计 
	return NULL;
}
void mov_modify(MovType* m,char* n){
	Mov* modify_mov;
	modify_mov = mov_Search_name(m,n);// 函数返回一个指针 可以对指针所指向的内容进行修改 
	if(modify_mov!=NULL){
		printf("下面进行修改\n"); 
		write_Move(modify_mov);
	}
} 
void insert_Mov(MovType* m,char* n,Mov* mov){
	int i = 0;
	//进行Type类目匹配 
	for(i = 0;i<m->len;i++){
		if(!strcmp(n,m->type[i])){
			printf("匹配成功类目: %s",m->type[i]);
			//对匹配的类目所指向的链表进行头插法插入 
			insert_List(m,i,mov);//用链表插入 
			return;
		}
	}
	if(i==m->len){//没有找到的情况 
		printf("!!!! 请先创建类目 - %s !!!!",n);
	}
//	if(i==m->len){
//		printf("没有匹配的类目 是否创建类目? Y/N");
//		getchar();
//		char choice;
//		scanf("%c",&choice);
//		if(choice=='y'||choice=='Y'){
//			create_Type(m,n);
//			insert_List(m,i,mov);
//		}else{
//			printf("返回中...");
//			return;
//		} 
//	}
}

void mov_remove(MovType* m,char* n){
	int i = 0;
	int sum = 0;
	Mov* tmpMovs; 
	for(i=0;i<m->len;i++){
		tmpMovs = m->Movs[i];//相当于头指针
		printf("2");
		while(tmpMovs->next){
			printf("1");
			sum++;
			if(!strcmp(tmpMovs->next->movie_name,n)){
				
				Mov* M = tmpMovs->next;
				show_Move(M);
				printf("3");
				tmpMovs->next = M->next;
				printf("5");
				free(M);
				printf("4");
				M= NULL;
				return;
			}
			
			tmpMovs = tmpMovs->next;
		} 
	}
	printf("搜索了%d没有找到\n",sum);

}
void temp(Mov* m1,Mov* m2){
	char tmp[10] = {'0'};
	strcpy(tmp,m1->director);
	strcpy(m1->director,m2->director);
	strcpy(m2->director,tmp);
	strcpy(tmp,m1->language);
	strcpy(m1->language,m2->language);
	strcpy(m2->language,tmp);
	strcpy(tmp,m1->movie_name);
	strcpy(m1->movie_name,m2->movie_name);
	strcpy(m2->movie_name,tmp);
	
	int tmpInt;
	tmpInt = m1->id;
	m1->id = m2->id;
	m2->id = tmpInt;
	tmpInt = m1->score;
	m1->score = m2->score;
	m2->score = tmpInt;
	tmpInt = m1->year;
	m1->year = m2->year;
	m2->year = tmpInt;
	
}
void  BubbleSort(Mov* list){
    for (Mov* first = list->next; first != NULL; first = first->next)
    {
        for (Mov* second = list->next; second != NULL; second = second->next)
        {
            if (second->next != NULL)
            {
                if (second->score > second->next->score) // >增序  <降序 
                {
                	Mov* m1 = second;
                	Mov* m2 = second->next;
                	temp(m1,m2);
                	
                }
            }
        }
    }
}
void Movs_BubbleSort(MovType* m,char* n){
	int i = 0;
	for(i = 0;i<m->len;i++){
		if(!strcmp(m->type[i],n)){
			BubbleSort(m->Movs[i]);
		}
	}
}

int bubble_sort_desc(Mov* str, int n)
{
    int i,j; 
	Mov tmp;
    for(i=0; i<n; i++)
    {
        for(j=i+1; j<n; j++)
        {
            if(str[i].score < str[j].score) 
            {
                tmp = str[i]; 
                str[i] = str[j]; 
                str[j] = tmp;
            }
        }
    }

    return 0;
}


//下面是三个基本排序 
void mov_Search_location(MovType* m,char* n,int i){
	int sum = 0;
	Mov tmparr[20];
	int index = 0;
	Mov* tmpMovs; 

	tmpMovs = m->Movs[i];//相当于头指针
	while(tmpMovs){
		if(!strcmp(tmpMovs->language,n)){
			sum++;
			tmparr[index++] = *tmpMovs;
		}
		tmpMovs = tmpMovs->next;
		
	}
	bubble_sort(tmparr,sum);
	int j = 0;
	for(j = 0;j<sum;j++){
		Mov* tmpp = &tmparr[j];
		show_Move(tmpp);
	}
	if(sum==0){
		printf("没有找到\n");
	}
}
void mov_Search_year(MovType* m,int y,int i){
	int sum = 0;
	Mov tmparr[20];
	int index = 0;
	Mov* tmpMovs; 

	tmpMovs = m->Movs[i];//相当于头指针
	while(tmpMovs){
		if(tmpMovs->year == y){
			sum++;
			tmparr[index++] = *tmpMovs;
		}
		tmpMovs = tmpMovs->next;
		
	}
	bubble_sort(tmparr,sum);
	int j = 0;
	for(j = 0;j<sum;j++){
		Mov* tmpp = &tmparr[j];
		show_Move(tmpp);
	}
	if(sum==0){
		printf("没有找到\n");
	}
}
void mov_Search_score(MovType* m,int y,int i){
	int sum = 0;
	Mov tmparr[20];
	int index = 0;
	Mov* tmpMovs; 

	tmpMovs = m->Movs[i];//相当于头指针
	while(tmpMovs){
		if(tmpMovs->year >= y){
			sum++;
			tmparr[index++] = *tmpMovs;
		}
		tmpMovs = tmpMovs->next;
		
	}
	bubble_sort(tmparr,sum);
	int j = 0;
	for(j = 0;j<sum;j++){
		Mov* tmpp = &tmparr[j];
		show_Move(tmpp);
	}
	if(sum==0){
		printf("没有找到\n");
	}
}
void mov_Search_language(MovType* m,char* n,int i){
	int sum = 0;
	Mov tmparr[20];
	int index = 0;
	Mov* tmpMovs; 

	tmpMovs = m->Movs[i];//相当于头指针
	while(tmpMovs){
		if(!strcmp(tmpMovs->language,n)){
			sum++;
			tmparr[index++] = *tmpMovs;
		}
		tmpMovs = tmpMovs->next;
		
	}
	bubble_sort(tmparr,sum);
	int j = 0;
	for(j = 0;j<sum;j++){
		Mov* tmpp = &tmparr[j];
		show_Move(tmpp);
	}
	if(sum==0){
		printf("没有找到\n");
	}
}
void mov_Search_director(MovType* m,char* n,int i){
	int sum = 0;
	Mov tmparr[20];
	int index = 0;
	Mov* tmpMovs; 

	tmpMovs = m->Movs[i];//相当于头指针
	while(tmpMovs){
		if(!strcmp(tmpMovs->director,n)){
			sum++;
			tmparr[index++] = *tmpMovs;
		}
		tmpMovs = tmpMovs->next;
		
	}
	bubble_sort(tmparr,sum);
	int j = 0;
	for(j = 0;j<sum;j++){
		Mov* tmpp = &tmparr[j];
		show_Move(tmpp);
	}
	if(sum==0){
		printf("没有找到\n");
	}
}
//跨分类查询电影 并排序 
void show_tmparr(Mov* tmparr,int sum){
		int j = 0;
	for(j=0;j<sum;j++){
		show_Move(&tmparr[j]);
	}
	
} 
void search_movs_asname(MovType* m,char* n){
	int i = 0;
	int sum = 0;
	Mov tmparr[20];
	Mov* tmpMovs; 
	for(i=0;i<m->len;i++){
		tmpMovs = m->Movs[i];//相当于头指针
		while(tmpMovs){
			
			if(!strcmp(tmpMovs->movie_name,n)){
				tmparr[sum++] = *tmpMovs;
			}
			
			tmpMovs = tmpMovs->next;
		} 
	}
	bubble_sort_desc(tmparr,sum);
	show_tmparr(tmparr,sum);
	if(sum==0){
		printf("搜索了%d没有找到\n",sum);
	}
	
}
void search_movs_asscore(MovType* m,int n){
	int i = 0;
	int sum = 0;
	Mov tmparr[20];
	Mov* tmpMovs; 
	for(i=0;i<m->len;i++){
		tmpMovs = m->Movs[i];//相当于头指针
		while(tmpMovs){
			
			if(tmpMovs->score == n){
				tmparr[sum++] = *tmpMovs;
			}
			
			tmpMovs = tmpMovs->next;
		} 
	}
	bubble_sort_desc(tmparr,sum);
	show_tmparr(tmparr,sum);
	if(sum==0){
		printf("搜索了%d没有找到\n",sum);
	}
	
}
//	char language[20];					
//	char movie_name[20];			
//	char director[20];		
void search_movs_aslanguage(MovType* m,char* n){
	int i = 0;
	int sum = 0;
	Mov tmparr[20];
	Mov* tmpMovs; 
	for(i=0;i<m->len;i++){
		tmpMovs = m->Movs[i];//相当于头指针
		while(tmpMovs){
			if(!strcmp(tmpMovs->language,n)){
				tmparr[sum++] = *tmpMovs;
			}
			
			tmpMovs = tmpMovs->next;
		} 
	}
	bubble_sort_desc(tmparr,sum);
	show_tmparr(tmparr,sum);
	if(sum==0){
		printf("搜索了%d没有找到\n",sum);
	}
	
}
void search_movs_asdirector(MovType* m,char* n){
	int i = 0;
	int sum = 0;
	Mov tmparr[20];
	Mov* tmpMovs; 
	for(i=0;i<m->len;i++){
		tmpMovs = m->Movs[i];//相当于头指针
		while(tmpMovs){
			if(!strcmp(tmpMovs->director,n)){
				tmparr[sum++] = *tmpMovs;
			}
			
			tmpMovs = tmpMovs->next;
		} 
	}
	bubble_sort_desc(tmparr,sum);
	show_tmparr(tmparr,sum);
	if(sum==0){
		printf("搜索了%d没有找到\n",sum);
	}
}
void search_movs_asyear(MovType* m,int n){
	int i = 0;
	int sum = 0;
	Mov tmparr[20];
	Mov* tmpMovs; 
	for(i=0;i<m->len;i++){
		tmpMovs = m->Movs[i];//相当于头指针
		while(tmpMovs){
			
			if(tmpMovs->year == n){
				tmparr[sum++] = *tmpMovs;
			}
			
			tmpMovs = tmpMovs->next;
		} 
	}
	bubble_sort_desc(tmparr,sum);
	show_tmparr(tmparr,sum);
	if(sum==0){
		printf("搜索了%d没有找到\n",sum);
	}
	
}
void Menu_Login()														
{

	printf("\n\n");
	
	printf("------------------------------登录页面---------------------------------------------\n");

	printf("*\t1.登录账号  								 *\n");
	
	printf("*\t2.创建账号  								 *\n");

	
	printf("-----------------------------------------------------------------------------------\n");

  
}
void Menu_Create1()														
{

	printf("\n\n");
	
	printf("------------------------------页面用户---------------------------------------------\n");

	printf("*\t1.账号  								 *\n");
	
	
	printf("请输入：");

  
}
void Menu_Create2()														
{

	printf("\n\n");
	
	printf("------------------------------页面用户---------------------------------------------\n");

	printf("*\t1.密码  								 *\n");
	
	
	printf("请输入：");

  
}
void Menu_client()														
{

	printf("\n\n");
	
	printf("------------------------------用户页面---------------------------------------------\n");

	printf("*\t1.查找电影(类)							*\n");printf("\n");

	printf("*\t2.查找电影(全)							*\n");printf("\n");

	printf("*\t3.进行排序							*\n");printf("\n");
		
	printf("*\t4.查看全部电影							*\n");
		

	printf("-----------------------------------------------------------------------------------\n");
  
}
void Menu_manage()														
{

	printf("\n\n");
	
	printf("------------------------------管理者页面--------------------------------------------\n");

	printf("*\t1.添加电影  								  *\n");printf("\n");

	printf("*\t2.修改电影   								  *\n");printf("\n");

	printf("*\t3.初始化库 			  					  *\n");printf("\n");
	
	printf("*\t4.删除电影 			  					  *\n");printf("\n");
	
	printf("*\t5.创建类目 			  					  *\n");printf("\n");
	
	printf("*\tc.切换用户 			  					  *\n");printf("\n");
	
	printf("*\tw.进行刷盘 			  					  *\n");printf("\n");
	
	

	printf("--------------------------------------------------------------------------------------\n");
}
void Menu_search()														
{

	printf("\n\n");
	
	printf("------------------------------请选择查找方式-------------------------------------------\n");

	printf("*\t1.电影名称  								  *\n");printf("\n");

	printf("*\t2.电影评分   								  *\n");printf("\n");

	printf("*\t3.电影年份 			  					  *\n");printf("\n");
	
	printf("*\t4.电影导演 			  					  *\n");printf("\n");
	
	printf("*\t5.电影语言 			  					  *\n");

	printf("----------------------------------------------------------------------------------------\n");
  
}
typedef struct user{
	char username[10];
	char password[10];
	int is_manage;
}User;
typedef struct uarr{
	user users[10];
	int num;
}Uarr;
void adduser(Uarr &u){
	User newuser ;
	newuser.is_manage = 2;
	printf("正在创建用户...");
	Menu_Create1();
	scanf("%s",newuser.username);
	Menu_Create2();
	scanf("%s",newuser.password);
	u.users[(u.num)++] = newuser;
}
void iniuser(Uarr &u){
	int i = 1;
	for(i = 0;i<10;i++){
		for(int j = 0;j<10;j++){
			u.users[i].username[j] = '\0';
			u.users[i].password[j] = '\0';
		}
		u.users[i].is_manage = 1;
	}
	
	User tmpu1 = {"Admin","1234",1};
	User tmpu2 = {"CCC","1235",2};
	u.users[0] = tmpu1;
	u.users[1] = tmpu2;
	u.num=2;
}
int sign(Uarr &us,char* u,char* p){
	int i = 0;
	for(i=0;i<us.num;i++){
		if(!strcmp(us.users[i].username,u)&&!strcmp(us.users[i].password,p)){
			return us.users[i].is_manage;
		}
	}
	printf("登录失败");
	return 0;
}
int joinapp(Uarr &us){
	int choice;
	int key = 0;
	char u[10] = {'\0'};
	char p[10] = {'\0'};
	Menu_Login();

	//登录系统 
	scanf("%d",&choice); 
	if(choice == 1){

		while(true){
			Menu_Create1();
			scanf("%s",u);
			Menu_Create2();
			scanf("%s",p);
			
			if(key = sign(us,u,p)){
				
				return key;
			}else{
				printf("输入有误请重新输入");
			}
		}
		
	}else if(choice == 2){
		
		adduser(us);
		printf("接下来请登录...");
		while(true){
			Menu_Create1();
			scanf("%s",u);
			Menu_Create2();
			getchar(); 
			scanf("%s",p);
			
			if(key = sign(us,u,p)){
				printf("密码正确");
				return key;
			}else{
				printf("输入有误请重新输入");
			}
		}
	}else{
		printf("输入错误 已退出");
	}
	system("cls");
	return 0;
	
}
void pf(){
	printf("请输入你的选择: ");
}
void pn(){
	printf("请输入电影名: ");
}
int search_type(MovType* m,char* name){
	int i = 0;
	for(i=0;i<m->len;i++){
		if(!strcmp(name,m->type[i])){
			return i;
		}
		
	}
	printf("未找到类目\n");
	return -1;
	
}
/**
	printf("*\t1.电影名称  								  *\n");printf("\n");

	printf("*\t2.电影评分   								  *\n");printf("\n");

	printf("*\t3.电影年份 			  					  *\n");printf("\n");
	
	printf("*\t4.电影导演 			  					  *\n");
	*/
void switch_mov_all(MovType* m,int choice){
	char name[10] = {'\0'};
	int num;
	switch(choice){
		case 1:
			printf("请输入电影名称:");
			scanf("%s",&name);
			getchar();
			search_movs_asname(m,name);
			break; 
		case 2:
			printf("请输入电影得分:");
			scanf("%d",&num);
			getchar();
			search_movs_asscore(m,num);
			break;
		case 3:
			printf("请输入电影年份:");
			scanf("%d",&num);
			search_movs_asyear(m,num);
			break;
		case 4:
			printf("请输入电影导演:");
			scanf("%s",&name);
			search_movs_asdirector(m,name);
			break;
		case 5:
			printf("请输入电影地区/语言:");
			scanf("%s",&name);
			search_movs_aslanguage(m,name);
			break;
		default: 
			printf("输入错误，已退出");
			break;
	}
	
}
void switch_mov(MovType* m,int choice){
	char name[10] = {'\0'};
	char type[10] = {'\0'};
	int ans_type;
	int num;
	switch(choice){
		case 1:
			printf("请输入类目:");
			scanf("%s",&type);
			printf("请输入电影名称:");
			scanf("%s",&name);
			ans_type = search_type(m,type);// 查type 类目所在的数组下标  返回-1代表没有查找到 
			if(ans_type != -1)
			mov_Search_asname(m,name,ans_type);//返回的不是-1 就可以对数组下标为ans_type的数据结构下的 链表进行遍历 查找对应的name电影 
			break; 
		case 2:
			printf("请输入类目:");
			scanf("%s",&type);
			printf("请输入电影评分:");
			scanf("%d",&num);
			getchar();
			ans_type = search_type(m,type);
			if(ans_type != -1)
			mov_Search_score(m,num,ans_type);
			break;
		case 3:
			printf("请输入类目:");
			scanf("%s",&type);
			printf("请输入电影年份:");
			scanf("%d",&num);
			getchar();
			ans_type = search_type(m,type);
			if(ans_type != -1)
			mov_Search_year(m,num,ans_type);
			break;
		case 4:
			printf("请输入类目:");
			scanf("%s",&type);
			printf("请输入电影导演:");
			scanf("%s",&name);
			ans_type = search_type(m,type);
			if(ans_type != -1)
			mov_Search_director(m,name,ans_type);
			break;
		case 5:
			printf("请输入类目:");
			scanf("%s",&type);
			printf("请输入电影地区/语言:");
			scanf("%s",&name);
			ans_type = search_type(m,type);
			if(ans_type != -1)
			mov_Search_language(m,name,ans_type);
			break;
		default: 
			printf("输入错误，已退出");
			break;
	}
}
/**
r	以只读方式打开一个文本文件（不创建文件，若文件不存在则报错）
w	以写方式打开文件(如果文件存在则清空文件，文件不存在则创建一个文件)
a	以追加方式打开文件，在末尾添加内容，若文件不存在则创建文件
*/
int storage(MovType* m){
	//使用追加写的模式 
	FILE *fp = fopen("D:/Movies.txt","w+");
	int i = 0;
	int j = 0;
	Mov* tmp;
	for(i = 0;i<m->len;i++){
		tmp = m->Movs[i]->next;
		fputs("Type=",fp);
		fputs(m->type[i],fp);
		fputs("\n",fp);
		while(tmp!=NULL){
			fputs("name=",fp);
			fputs(tmp->movie_name,fp);
			fputs("\n",fp);
			fputs("director=",fp);
			fputs(tmp->director,fp);
			fputs("\n",fp);
			fputs("language=",fp);
			fputs(tmp->language,fp);
			fputs("\n",fp);
			//char* itoa(int value,char*string,int radix);//value: 要转换的整数，string: 转换后的字符串,radix: 转换进制数，如2,8,10,16 进制等。
			char tmpitoaid[10] = {'\0'};
			char tmpitoayear[10] = {'\0'};
			char tmpitoascore[10] = {'\0'};
			itoa(tmp->id,tmpitoaid,10);
			itoa(tmp->year,tmpitoayear,10);
			itoa(tmp->score,tmpitoascore,10);
			fputs("id=",fp);
			fputs(tmpitoaid,fp);
			fputs("\n",fp);
			fputs("year=",fp);
			fputs(tmpitoayear,fp);
			fputs("\n",fp);
			fputs("score=",fp);
			fputs(tmpitoascore,fp);
			fputs("\n",fp);
			tmp = tmp->next;
		}
	}
	fclose(fp);
}
/**
1） 函数原型： char* strtok (char* str,constchar* delimiters );
2） 函数功能： 切割字符串，将str切分成一个个子串
3） 函数参数：

str：在第一次被调用的时间str是传入需要被切割字符串的首地址；在后面调用的时间传入NULL。
delimiters：表示切割字符串（字符串中每个字符都会 当作分割符）。

*/

#define MAX_MSG_LENGTH 512
 
// 替换字符串中特征字符串为指定字符串

int StrReplace(char strRes[],char from[], char to[])
 {
    int flag=0;
	char *Ptr = NULL;
    char *middle_flag = strstr(strRes, from);
	if(middle_flag == NULL)
	{
		return flag;
	}
    
    int len = strlen(middle_flag);
    Ptr = (char *)malloc(len * sizeof(char));
    if (NULL == Ptr)
    {
        return flag;
    }
    strcpy(Ptr, middle_flag + (strlen(from)));
    if (middle_flag != NULL)
    {
        /* code */
        *middle_flag = '\0';
        strcat(strRes, to);
        strcat(strRes, Ptr);
        free(Ptr);
        flag = 1;
    }
    return flag;
 }


int read(MovType* m){
	FILE *fp = fopen("D:/Movies.txt","r");
	//只读模式 
	char buff[25] = {'\0'};
	/**
	把内容存放到buff缓冲当中
	输出缓冲 
	一次读取1024个字节
	*/
	char id[25] = "id";
	char Type[25] = "Type";
	char language[25] = "language";
	char year[25] = "year";
	char name[25] = "name";
	char score[25] = "score";
	char director[25] = "director";
	char delimiters[2] = "=";
	int sum = 0;
	char tmpsign[25] = {'\0'};
	char Typename[25] = {'\0'};
	Mov* newMov = (Mov*)malloc(sizeof(Mov));
	while(fgets(buff,25,fp)!=NULL){
		
		/**
		函数原型为: char *strreplace(char *src, char *sub, char *dst);
		将字符串src中sub字符串替换成dst字符串, 返回值为替换后的字符串。
		参数说明:
		src --- 源字符串
		sub --- 被替换的字符串
		dst --- 替换的字符串
		
		*/
		strcpy(tmpsign,strtok(buff,"="));
		
		// atoi 是把字符串转换成int型的一个c语言函数
		if(!strcmp(tmpsign,id)){
			strcpy(tmpsign,strtok(NULL,"="));
			//printf("%d",atoi(tmpsign));
			newMov->id = atoi(tmpsign);
			sum++;
		}else if(!strcmp(tmpsign,name)){
			strcpy(tmpsign,strtok(NULL,"="));
			//printf("%s",tmpsign);
			tmpsign[strlen(tmpsign)-1] = '\0';
			strcpy(newMov->movie_name,tmpsign);
			sum++;
		}else if(!strcmp(tmpsign,language)){
			strcpy(tmpsign,strtok(NULL,"="));
			//printf("%s",tmpsign);
			tmpsign[strlen(tmpsign)-1] = '\0';
			strcpy(newMov->language,tmpsign);
			sum++;
		}else if(!strcmp(tmpsign,score)){
			strcpy(tmpsign,strtok(NULL,"="));
			//printf("%d",atoi(tmpsign));
			newMov->score = atoi(tmpsign);
			sum++;
		}else if(!strcmp(tmpsign,Type)){
			strcpy(tmpsign,strtok(NULL,"="));
			/**
				这里是创建类目 
				并且再m中插入类目名称
			*/
			//printf("%s",tmpsign);
			tmpsign[strlen(tmpsign)-1] = '\0';
			strcpy(Typename,tmpsign);//对现在进行插入的目录进行刷新 
			
			create_Type(m,Typename);
			//printf("%s|||||",Typename);
			//printf("[%d]",m->len);
			
		}else if(!strcmp(tmpsign,year)){
			strcpy(tmpsign,strtok(NULL,"="));
			//printf("%d",atoi(tmpsign));
			newMov->year = atoi(tmpsign);
			sum++;
		}else if(!strcmp(tmpsign,director)){
			strcpy(tmpsign,strtok(NULL,"="));
			//printf("%s",tmpsign);
			tmpsign[strlen(tmpsign)-1] = '\0';
			strcpy(newMov->director,tmpsign);
			sum++;
		}
		
		if(sum==6){
			insert_Mov(m,Typename,newMov);
			newMov = (Mov*)malloc(sizeof(Mov));
			//printf("[[[[]]]]%s",Typename);
			sum = 0;
		}
		
	}
	fclose(fp);
	/**
	void insert_List(MovType* m,int i,Mov* mov){
	mov->next = m->Movs[i]->next;
	m->Movs[i]->next = mov;
	printf("电影类目为: %s \n",m->type[i]);
	}
	*/
}

int main(){
	/**
	用户初始化 
	*/
	
	Uarr us;
	iniuser(us);
	movie_Type m;
	movie_Type* mp = &m;
	ini_movie_Type(mp);
	read(mp);
	int jurisdiction = 0;
	/**
	选项初始化 
	*/ 
	
	
	
	jurisdiction=joinapp(us); //获得登录权限 
	//jurisdiction = 2;
	//根据joinapp判断的是进入哪个界面 
	while(jurisdiction == 1){
		Menu_manage();
		char choice ;
		pf();//
		/**
		void pf(){
		printf("请输入你的选择: ");
		}
		void pn(){
			printf("请输入电影名: ");
		}
		
		*/
		//管理员界面需要先按回车 
		getchar();
		scanf("%c",&choice);
		
		char name[10] = {'\0'};
		Mov* mov = NULL;
		switch(choice){
			case '1':
				printf("请输入类目名称: ");
				scanf("%s",name);
				mov = (Mov*)malloc(sizeof(Mov));
				write_Move(mov);//录入电影信息 
				insert_Mov(mp,name,mov);//插入电影 
				break;
			case '2':
				pn();
				scanf("%s",name);
				mov_modify(mp,name);// 改变电影信息 
				
				break;
			case '3':
				printf("初始化库将会删除所有电影是否继续?");
				char c;
				scanf("%c",&c);
				if(c=='y'||c=='Y'){
					ini_movie_Type(mp);//调用初始化函数进行删除库 
				}
				break;
			case '4':
				pn();
				scanf("%s",name);
				mov_remove(mp,name);//删除电影 
				break;
			case '5':
				printf("请输入类名:");
				scanf("%s",name);
				create_Type(mp,name);//创建一个类 
				break;
			case '9': jurisdiction = 0; break;
			case 'c':  jurisdiction = 2; break;
			case 'w': storage(mp);break;//调用刷盘函数 
			default: 
				printf("!!!输入错误!!!\n");
				break;
		}
		
	}

	
	while(jurisdiction == 2){
		
		Menu_client();// 客户菜单 
		int choice ;
		int choice2;
		pf();
		
		scanf("%d",&choice);
		getchar();
		if(choice<=0||choice>9){
			continue;
		}
		char name[10] = {'\0'};
		
		switch(choice){

			case 1:
				Menu_search();
				printf("请输入查找方式: ");
				scanf("%d",&choice2);
				switch_mov(mp,choice2);//查找类目 当中的电影 
				break;
			case 2:
				Menu_search();
				printf("请输入查找方式: ");
				scanf("%d",&choice2);
				switch_mov_all(mp,choice2);//查找所有类目 当中的电影 
				break;
			case 3:
				printf("请输入类型名称: ");
				scanf("%s",name);
				Movs_BubbleSort(mp,name);// 根据输入的类目名称进行排序 
				printf("已成功进行排序");
				break;
			case 4:
				Movs_traval(mp);// 对 主数据结构进行遍历 
				break;
			case 9:
				jurisdiction = 0;// 设置权限为0 
				printf("已退出");
				break; 
			default: printf("输入错误！重新输入\n");
			
		}
		
	}
	
	
} 
