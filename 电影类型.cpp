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
	printf("电影名：%s  ",s->movie_name);	
	printf("语言：%s  ",s->language);											
	printf("导演：%s  ",s->director);									
	printf("年份：%d  ",s->year);										
	printf("id：%d",s->id);					
	printf("得分：%d",s->score);					
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
void create_Type(MovType* m,char* n){
	strcpy(m->type[m->len],n);
	(m->len)++;
}
void Movs_traval(MovType* m){
	int i = 0;
	Mov* tmpMovs; 
	for(i=0;i<m->len;i++){
		tmpMovs = m->Movs[i]->next;//相当于头指针
		printf("当前目录为	----------------------------------	%s\n",m->type[i]);
		while(tmpMovs){
			show_Move(tmpMovs);
			tmpMovs = tmpMovs->next;
		} 
			
		
		
	}
}
int bubble_sort(Mov* str, int n)
{
    int i,j; 
	Mov tmp;
    for(i=0; i<n; i++)
    {
        for(j=i+1; j<n; j++)
        {
            if(str[i].score > str[j].score) 
            {
                tmp = str[i]; 
                str[i] = str[j]; 
                str[j] = tmp;
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
		if(!strcmp(tmpMovs->movie_name,n)){
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
				return tmpMovs;
			}
			
			tmpMovs = tmpMovs->next;
		} 
	}
	
	printf("搜索了%d没有找到\n",sum);
	return NULL;
}
void mov_modify(MovType* m,char* n){
	Mov* modify_mov;
	modify_mov = mov_Search_name(m,n);
	if(modify_mov!=NULL){
		printf("下面进行修改\n"); 
		write_Move(modify_mov);
	}
} 
void insert_Mov(MovType* m,char* n,Mov* mov){
	int i = 0;
	for(i = 0;i<m->len;i++){
		if(!strcmp(n,m->type[i])){
			printf("匹配成功类目: %s",m->type[i]);
			insert_List(m,i,mov);//用链表插入 
			return;
		}
	}
	if(i==m->len){
		printf("!!!!请先创建类目!!!!");
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
	
	printf("*\tp.退出软件 			  					  *\n");

	printf("--------------------------------------------------------------------------------------\n");
}
void Menu_search()														
{

	printf("\n\n");
	
	printf("------------------------------请选择排序方式-------------------------------------------\n");

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
	Menu_Create1();
	scanf("%s",newuser.username);
	Menu_Create2();
	getchar(); 
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
	u.num=1;
	User tmpu1 = {"Admin","1234",1};
	User tmpu2 = {"CCC","1235",2};
	u.users[0] = tmpu1;
	u.users[1] = tmpu2;
}
int sign(Uarr &us,char* u,char* p){
	int i = 0;
	for(i=0;i<us.num;i++){
		if(!strcmp(us.users[i].username,u)&&!strcmp(us.users[i].password,p)){
			printf("登录成功");
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
	printf("%d",choice);
	if(choice == 1){

		while(true){
			Menu_Create1();
			scanf("%s",u);
			Menu_Create2();
			getchar(); 
			scanf("%s",p);
			
			if(key = sign(us,u,p)){
				
				return key;
			}else{
				printf("输入有误请重新输入");
			}
		}
		
	}else if(choice == 2){
		adduser(us);
		while(true){
			Menu_Create1();
			scanf("%s",u);
			Menu_Create2();
			getchar(); 
			scanf("%s",p);
			
			if(key = sign(us,u,p)){
				
				return key;
			}else{
				printf("输入有误请重新输入");
			}
		}
	}else{
		printf("输入错误 已退出");
	}
	return 0;
	
}
void pf(){
	printf("请输入你的选择");
}
void pn(){
	printf("请输入电影名");
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
			ans_type = search_type(m,type);
			if(ans_type != -1)
			mov_Search_asname(m,name,ans_type);
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


int main(){
	/**
	用户初始化 
	*/
	
	Uarr us;
	iniuser(us);
	movie_Type m;
	movie_Type* mp = &m;
	ini_movie_Type(mp);
	/**
	选项初始化 
	*/ 
	int jurisdiction = 0;
	
	
	
	//jurisdiction=joinapp(us); 
	jurisdiction = 1;
	//管理员界面 
	/**
	
	printf("*\t1.添加电影  								  *\n");printf("\n");

	printf("*\t2.修改电影   								  *\n");printf("\n");

	printf("*\t3.初始化库 			  					  *\n");printf("\n");
	
	printf("*\t4.删除电影 			  					  *\n");
	
	*/
	while(jurisdiction == 1){
		Menu_manage();
		char choice ;
		pf();
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
				write_Move(mov);
				insert_Mov(mp,name,mov);
				break;
			case '2':
				pn();
				scanf("%s",name);
				mov_modify(mp,name);
				
				break;
			case '3':
				printf("初始化库将会删除所有电影是否继续?");
				char c;
				scanf("%c",&c);
				if(c=='y'||c=='Y'){
					ini_movie_Type(mp);
				}
				break;
			case '4':
				pn();
				scanf("%s",name);
				mov_remove(mp,name);
				break;
			case '5':
				printf("请输入类名:");
				scanf("%s",name);
				create_Type(mp,name);
				break;
			case 'p': jurisdiction = 0; break;
			
			case 'c':  jurisdiction = 2; break;
			default: 
				printf("!!!输入错误!!!\n");
				
				break;
			
		}
		system("cls"); 
		
	}
	//用户界面 
	/**
	printf("*\t1.查找电影(类)  								  *\n");printf("\n");

	printf("*\t2.查找电影(全)  								  *\n");printf("\n");

	printf("*\t3.进行排序 			  					  *\n");printf("\n");
	
	printf("*\t4.查看全部电影 			  					  *\n");
	
	printf("*\t1.电影名称  								  *\n");printf("\n");

	printf("*\t2.电影评分   								  *\n");printf("\n");

	printf("*\t3.电影年份 			  					  *\n");printf("\n");
	
	printf("*\t4.电影导演 			  					  *\n");
	*/
	
	while(jurisdiction == 2){
		
		Menu_client();
		int choice ;
		int choice2;
		pf();
		
		scanf("%d",&choice);
		getchar();
		if(choice<=0||choice>=9){
			continue;
		}
		char name[10] = {'\0'};
		
		switch(choice){

			case 1:
				Menu_search();
				printf("请输入查找方式: ");
				scanf("%d",&choice2);
				switch_mov(mp,choice2);
				break;
			case 2:
				Menu_search();
				printf("请输入查找方式: ");
				scanf("%d",&choice2);
				switch_mov_all(mp,choice2);
				break;
			case 3:
				printf("请输入类型名称");
				scanf("%s",name);
				Movs_BubbleSort(mp,name);
				printf("已成功进行排序");
				break;
			case 4:
				
				Movs_traval(mp);
				break;
			default: printf("输入错误,重新输入\n");
		}
		
	}
	
	//主菜单 
	
	
	

	
//	
//	MovType m;
//	MovType* mp = &m;
//	ini_movie_Type(mp);
//	char name[10]="hello";
//	create_Type(mp,name);
//	Mov mov1 = {"a","aa","aaa",1949,11,111911};
//	Mov mov2 = {"a","aa","bbb",1949,22,2222222};
//	Mov mov3 = {"a","ee","eee",1949,33,333};
//	Mov mov4 = {"a","cc","bbb",1949,44,4222};
//	Mov mov5 = {"e","dd","eee",5,55,555};
//	Mov mov6 = {"e","aa","eee",5,55,11155};
//	write_Move(&mov1);
//	write_Move(&mov2);
//	write_Move(&mov3);
//	write_Move(&mov4);
//	write_Move(&mov5);
//	insert_Mov(mp,name,&mov1);
//	insert_Mov(mp,name,&mov2);
//	insert_Mov(mp,name,&mov3);
//	insert_Mov(mp,name,&mov4);
//	insert_Mov(mp,name,&mov5);
//	insert_Mov(mp,name,&mov6);
//	Movs_traval(mp);
//	BubbleSort(mp->Movs[0]);
//	Movs_traval(mp);
//	printf("\n");
//	search_movs_aslanguage(mp,"a");
} 
