#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>
#define Max 100 
typedef struct movie 				//�ṹ����											//movie�ṹ���� 
{
	
	char language[20];					
	char movie_name[20];			
	char director[20];			
	int year;			
	int  id;				
	int score;
	movie* next;
	
}Mov;					//������	
typedef struct movie_Type{
	char type[10][10];
	Mov *Movs[10];
	int len;
	int Size;
}MovType;

void write_Move(Mov* s){
	printf("�������Ӱ����  ");						
	scanf("%s",&s->movie_name);		
	printf("���������ԣ�  ");						
	scanf("%s",&s->language);						
	printf("���䵼�ݣ�  ");					
	scanf("%s",&s->director);				
	printf("��������ݣ�  ");						
	scanf("%d",&s->year);				
	printf("������id��");					
	scanf("%d",&s->id);
	printf("������÷֣�");					
	scanf("%d",&s->score);
}
void show_Move(Mov* s){
	printf("��Ӱ����%s\t",s->movie_name);	
	printf("���ԣ�%s\t",s->language);											
	printf("���ݣ�%s\t",s->director);									
	printf("��ݣ�%d\t",s->year);										
	printf("id��%d\t",s->id);					
	printf("�÷֣�%d\t",s->score);					
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
	printf("��Ӱ��ĿΪ: %s \n",m->type[i]);
}
//�½���Ӱleibie  
void create_Type(MovType* m,char* n){
	strcpy(m->type[m->len],n);
	(m->len)++;
}
//�������еĵ�Ӱ 
void Movs_traval(MovType* m){
	int i = 0;
	Mov* tmpMovs; 
	for(i=0;i<m->len;i++){
		tmpMovs = m->Movs[i]->next;//�൱��ͷָ��
		printf("��ǰĿ¼Ϊ	-----------------------------------------  <<%s>>\n",m->type[i]);
		while(tmpMovs){
			show_Move(tmpMovs);
			tmpMovs = tmpMovs->next;
		} 
			
		
		
	}
}
//���������ð������ 
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

	tmpMovs = m->Movs[i];//�൱��ͷָ��
	while(tmpMovs){
		//������Ҫ�޸� 
		//�����Ӱ�����ֺʹ��������һ�¾Ϳ��԰ѽ������tmparr���������
		//�������������ʽ 
		if(!strcmp(tmpMovs->movie_name,n)){
			sum++;
			tmparr[index++] = *tmpMovs;
		}
		tmpMovs = tmpMovs->next;
		
	}
	bubble_sort(tmparr,sum);//ð������ 
	int j = 0;
	// �������� 
	for(j = 0;j<sum;j++){
		Mov* tmpp = &tmparr[j];
		show_Move(tmpp);
	}
	//�����������е�sumΪ0 ����һ�������û�ҵ� 
	if(sum==0){
		printf("û���ҵ�\n");
	}
}
Mov* mov_Search_name(MovType* m,char* n){
	int i = 0;
	int sum = 0;
	Mov* tmpMovs; 
	Mov tmparr[20];
	for(i=0;i<m->len;i++){
		tmpMovs = m->Movs[i];//�൱��ͷָ��
		while(tmpMovs){
			
			if(!strcmp(tmpMovs->movie_name,n)){
				//mparr[sum++] = *tmpMovs;
				return tmpMovs;// �ҵ�ֱ�ӷ��� ���ﲻ��Ҫ�õ������ 
			}
			
			tmpMovs = tmpMovs->next;
		} 
	}
	
	printf("������%dû���ҵ�\n",sum);//������������ͳ�� 
	return NULL;
}
void mov_modify(MovType* m,char* n){
	Mov* modify_mov;
	modify_mov = mov_Search_name(m,n);// ��������һ��ָ�� ���Զ�ָ����ָ������ݽ����޸� 
	if(modify_mov!=NULL){
		printf("��������޸�\n"); 
		write_Move(modify_mov);
	}
} 
void insert_Mov(MovType* m,char* n,Mov* mov){
	int i = 0;
	//����Type��Ŀƥ�� 
	for(i = 0;i<m->len;i++){
		if(!strcmp(n,m->type[i])){
			printf("ƥ��ɹ���Ŀ: %s",m->type[i]);
			//��ƥ�����Ŀ��ָ����������ͷ�巨���� 
			insert_List(m,i,mov);//��������� 
			return;
		}
	}
	if(i==m->len){//û���ҵ������ 
		printf("!!!! ���ȴ�����Ŀ - %s !!!!",n);
	}
//	if(i==m->len){
//		printf("û��ƥ�����Ŀ �Ƿ񴴽���Ŀ? Y/N");
//		getchar();
//		char choice;
//		scanf("%c",&choice);
//		if(choice=='y'||choice=='Y'){
//			create_Type(m,n);
//			insert_List(m,i,mov);
//		}else{
//			printf("������...");
//			return;
//		} 
//	}
}

void mov_remove(MovType* m,char* n){
	int i = 0;
	int sum = 0;
	Mov* tmpMovs; 
	for(i=0;i<m->len;i++){
		tmpMovs = m->Movs[i];//�൱��ͷָ��
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
	printf("������%dû���ҵ�\n",sum);

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
                if (second->score > second->next->score) // >����  <���� 
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


//������������������ 
void mov_Search_location(MovType* m,char* n,int i){
	int sum = 0;
	Mov tmparr[20];
	int index = 0;
	Mov* tmpMovs; 

	tmpMovs = m->Movs[i];//�൱��ͷָ��
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
		printf("û���ҵ�\n");
	}
}
void mov_Search_year(MovType* m,int y,int i){
	int sum = 0;
	Mov tmparr[20];
	int index = 0;
	Mov* tmpMovs; 

	tmpMovs = m->Movs[i];//�൱��ͷָ��
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
		printf("û���ҵ�\n");
	}
}
void mov_Search_score(MovType* m,int y,int i){
	int sum = 0;
	Mov tmparr[20];
	int index = 0;
	Mov* tmpMovs; 

	tmpMovs = m->Movs[i];//�൱��ͷָ��
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
		printf("û���ҵ�\n");
	}
}
void mov_Search_language(MovType* m,char* n,int i){
	int sum = 0;
	Mov tmparr[20];
	int index = 0;
	Mov* tmpMovs; 

	tmpMovs = m->Movs[i];//�൱��ͷָ��
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
		printf("û���ҵ�\n");
	}
}
void mov_Search_director(MovType* m,char* n,int i){
	int sum = 0;
	Mov tmparr[20];
	int index = 0;
	Mov* tmpMovs; 

	tmpMovs = m->Movs[i];//�൱��ͷָ��
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
		printf("û���ҵ�\n");
	}
}
//������ѯ��Ӱ ������ 
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
		tmpMovs = m->Movs[i];//�൱��ͷָ��
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
		printf("������%dû���ҵ�\n",sum);
	}
	
}
void search_movs_asscore(MovType* m,int n){
	int i = 0;
	int sum = 0;
	Mov tmparr[20];
	Mov* tmpMovs; 
	for(i=0;i<m->len;i++){
		tmpMovs = m->Movs[i];//�൱��ͷָ��
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
		printf("������%dû���ҵ�\n",sum);
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
		tmpMovs = m->Movs[i];//�൱��ͷָ��
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
		printf("������%dû���ҵ�\n",sum);
	}
	
}
void search_movs_asdirector(MovType* m,char* n){
	int i = 0;
	int sum = 0;
	Mov tmparr[20];
	Mov* tmpMovs; 
	for(i=0;i<m->len;i++){
		tmpMovs = m->Movs[i];//�൱��ͷָ��
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
		printf("������%dû���ҵ�\n",sum);
	}
}
void search_movs_asyear(MovType* m,int n){
	int i = 0;
	int sum = 0;
	Mov tmparr[20];
	Mov* tmpMovs; 
	for(i=0;i<m->len;i++){
		tmpMovs = m->Movs[i];//�൱��ͷָ��
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
		printf("������%dû���ҵ�\n",sum);
	}
	
}
void Menu_Login()														
{

	printf("\n\n");
	
	printf("------------------------------��¼ҳ��---------------------------------------------\n");

	printf("*\t1.��¼�˺�  								 *\n");
	
	printf("*\t2.�����˺�  								 *\n");

	
	printf("-----------------------------------------------------------------------------------\n");

  
}
void Menu_Create1()														
{

	printf("\n\n");
	
	printf("------------------------------ҳ���û�---------------------------------------------\n");

	printf("*\t1.�˺�  								 *\n");
	
	
	printf("�����룺");

  
}
void Menu_Create2()														
{

	printf("\n\n");
	
	printf("------------------------------ҳ���û�---------------------------------------------\n");

	printf("*\t1.����  								 *\n");
	
	
	printf("�����룺");

  
}
void Menu_client()														
{

	printf("\n\n");
	
	printf("------------------------------�û�ҳ��---------------------------------------------\n");

	printf("*\t1.���ҵ�Ӱ(��)							*\n");printf("\n");

	printf("*\t2.���ҵ�Ӱ(ȫ)							*\n");printf("\n");

	printf("*\t3.��������							*\n");printf("\n");
		
	printf("*\t4.�鿴ȫ����Ӱ							*\n");
		

	printf("-----------------------------------------------------------------------------------\n");
  
}
void Menu_manage()														
{

	printf("\n\n");
	
	printf("------------------------------������ҳ��--------------------------------------------\n");

	printf("*\t1.��ӵ�Ӱ  								  *\n");printf("\n");

	printf("*\t2.�޸ĵ�Ӱ   								  *\n");printf("\n");

	printf("*\t3.��ʼ���� 			  					  *\n");printf("\n");
	
	printf("*\t4.ɾ����Ӱ 			  					  *\n");printf("\n");
	
	printf("*\t5.������Ŀ 			  					  *\n");printf("\n");
	
	printf("*\tc.�л��û� 			  					  *\n");printf("\n");
	
	printf("*\tw.����ˢ�� 			  					  *\n");printf("\n");
	
	

	printf("--------------------------------------------------------------------------------------\n");
}
void Menu_search()														
{

	printf("\n\n");
	
	printf("------------------------------��ѡ����ҷ�ʽ-------------------------------------------\n");

	printf("*\t1.��Ӱ����  								  *\n");printf("\n");

	printf("*\t2.��Ӱ����   								  *\n");printf("\n");

	printf("*\t3.��Ӱ��� 			  					  *\n");printf("\n");
	
	printf("*\t4.��Ӱ���� 			  					  *\n");printf("\n");
	
	printf("*\t5.��Ӱ���� 			  					  *\n");

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
	printf("���ڴ����û�...");
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
	printf("��¼ʧ��");
	return 0;
}
int joinapp(Uarr &us){
	int choice;
	int key = 0;
	char u[10] = {'\0'};
	char p[10] = {'\0'};
	Menu_Login();

	//��¼ϵͳ 
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
				printf("������������������");
			}
		}
		
	}else if(choice == 2){
		
		adduser(us);
		printf("���������¼...");
		while(true){
			Menu_Create1();
			scanf("%s",u);
			Menu_Create2();
			getchar(); 
			scanf("%s",p);
			
			if(key = sign(us,u,p)){
				printf("������ȷ");
				return key;
			}else{
				printf("������������������");
			}
		}
	}else{
		printf("������� ���˳�");
	}
	system("cls");
	return 0;
	
}
void pf(){
	printf("���������ѡ��: ");
}
void pn(){
	printf("�������Ӱ��: ");
}
int search_type(MovType* m,char* name){
	int i = 0;
	for(i=0;i<m->len;i++){
		if(!strcmp(name,m->type[i])){
			return i;
		}
		
	}
	printf("δ�ҵ���Ŀ\n");
	return -1;
	
}
/**
	printf("*\t1.��Ӱ����  								  *\n");printf("\n");

	printf("*\t2.��Ӱ����   								  *\n");printf("\n");

	printf("*\t3.��Ӱ��� 			  					  *\n");printf("\n");
	
	printf("*\t4.��Ӱ���� 			  					  *\n");
	*/
void switch_mov_all(MovType* m,int choice){
	char name[10] = {'\0'};
	int num;
	switch(choice){
		case 1:
			printf("�������Ӱ����:");
			scanf("%s",&name);
			getchar();
			search_movs_asname(m,name);
			break; 
		case 2:
			printf("�������Ӱ�÷�:");
			scanf("%d",&num);
			getchar();
			search_movs_asscore(m,num);
			break;
		case 3:
			printf("�������Ӱ���:");
			scanf("%d",&num);
			search_movs_asyear(m,num);
			break;
		case 4:
			printf("�������Ӱ����:");
			scanf("%s",&name);
			search_movs_asdirector(m,name);
			break;
		case 5:
			printf("�������Ӱ����/����:");
			scanf("%s",&name);
			search_movs_aslanguage(m,name);
			break;
		default: 
			printf("����������˳�");
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
			printf("��������Ŀ:");
			scanf("%s",&type);
			printf("�������Ӱ����:");
			scanf("%s",&name);
			ans_type = search_type(m,type);// ��type ��Ŀ���ڵ������±�  ����-1����û�в��ҵ� 
			if(ans_type != -1)
			mov_Search_asname(m,name,ans_type);//���صĲ���-1 �Ϳ��Զ������±�Ϊans_type�����ݽṹ�µ� ������б��� ���Ҷ�Ӧ��name��Ӱ 
			break; 
		case 2:
			printf("��������Ŀ:");
			scanf("%s",&type);
			printf("�������Ӱ����:");
			scanf("%d",&num);
			getchar();
			ans_type = search_type(m,type);
			if(ans_type != -1)
			mov_Search_score(m,num,ans_type);
			break;
		case 3:
			printf("��������Ŀ:");
			scanf("%s",&type);
			printf("�������Ӱ���:");
			scanf("%d",&num);
			getchar();
			ans_type = search_type(m,type);
			if(ans_type != -1)
			mov_Search_year(m,num,ans_type);
			break;
		case 4:
			printf("��������Ŀ:");
			scanf("%s",&type);
			printf("�������Ӱ����:");
			scanf("%s",&name);
			ans_type = search_type(m,type);
			if(ans_type != -1)
			mov_Search_director(m,name,ans_type);
			break;
		case 5:
			printf("��������Ŀ:");
			scanf("%s",&type);
			printf("�������Ӱ����/����:");
			scanf("%s",&name);
			ans_type = search_type(m,type);
			if(ans_type != -1)
			mov_Search_language(m,name,ans_type);
			break;
		default: 
			printf("����������˳�");
			break;
	}
}
/**
r	��ֻ����ʽ��һ���ı��ļ����������ļ������ļ��������򱨴�
w	��д��ʽ���ļ�(����ļ�����������ļ����ļ��������򴴽�һ���ļ�)
a	��׷�ӷ�ʽ���ļ�����ĩβ������ݣ����ļ��������򴴽��ļ�
*/
int storage(MovType* m){
	//ʹ��׷��д��ģʽ 
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
			//char* itoa(int value,char*string,int radix);//value: Ҫת����������string: ת������ַ���,radix: ת������������2,8,10,16 ���Ƶȡ�
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
1�� ����ԭ�ͣ� char* strtok (char* str,constchar* delimiters );
2�� �������ܣ� �и��ַ�������str�зֳ�һ�����Ӵ�
3�� ����������

str���ڵ�һ�α����õ�ʱ��str�Ǵ�����Ҫ���и��ַ������׵�ַ���ں�����õ�ʱ�䴫��NULL��
delimiters����ʾ�и��ַ������ַ�����ÿ���ַ����� �����ָ������

*/

#define MAX_MSG_LENGTH 512
 
// �滻�ַ����������ַ���Ϊָ���ַ���

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
	//ֻ��ģʽ 
	char buff[25] = {'\0'};
	/**
	�����ݴ�ŵ�buff���嵱��
	������� 
	һ�ζ�ȡ1024���ֽ�
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
		����ԭ��Ϊ: char *strreplace(char *src, char *sub, char *dst);
		���ַ���src��sub�ַ����滻��dst�ַ���, ����ֵΪ�滻����ַ�����
		����˵��:
		src --- Դ�ַ���
		sub --- ���滻���ַ���
		dst --- �滻���ַ���
		
		*/
		strcpy(tmpsign,strtok(buff,"="));
		
		// atoi �ǰ��ַ���ת����int�͵�һ��c���Ժ���
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
				�����Ǵ�����Ŀ 
				������m�в�����Ŀ����
			*/
			//printf("%s",tmpsign);
			tmpsign[strlen(tmpsign)-1] = '\0';
			strcpy(Typename,tmpsign);//�����ڽ��в����Ŀ¼����ˢ�� 
			
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
	printf("��Ӱ��ĿΪ: %s \n",m->type[i]);
	}
	*/
}

int main(){
	/**
	�û���ʼ�� 
	*/
	
	Uarr us;
	iniuser(us);
	movie_Type m;
	movie_Type* mp = &m;
	ini_movie_Type(mp);
	read(mp);
	int jurisdiction = 0;
	/**
	ѡ���ʼ�� 
	*/ 
	
	
	
	jurisdiction=joinapp(us); //��õ�¼Ȩ�� 
	//jurisdiction = 2;
	//����joinapp�жϵ��ǽ����ĸ����� 
	while(jurisdiction == 1){
		Menu_manage();
		char choice ;
		pf();//
		/**
		void pf(){
		printf("���������ѡ��: ");
		}
		void pn(){
			printf("�������Ӱ��: ");
		}
		
		*/
		//����Ա������Ҫ�Ȱ��س� 
		getchar();
		scanf("%c",&choice);
		
		char name[10] = {'\0'};
		Mov* mov = NULL;
		switch(choice){
			case '1':
				printf("��������Ŀ����: ");
				scanf("%s",name);
				mov = (Mov*)malloc(sizeof(Mov));
				write_Move(mov);//¼���Ӱ��Ϣ 
				insert_Mov(mp,name,mov);//�����Ӱ 
				break;
			case '2':
				pn();
				scanf("%s",name);
				mov_modify(mp,name);// �ı��Ӱ��Ϣ 
				
				break;
			case '3':
				printf("��ʼ���⽫��ɾ�����е�Ӱ�Ƿ����?");
				char c;
				scanf("%c",&c);
				if(c=='y'||c=='Y'){
					ini_movie_Type(mp);//���ó�ʼ����������ɾ���� 
				}
				break;
			case '4':
				pn();
				scanf("%s",name);
				mov_remove(mp,name);//ɾ����Ӱ 
				break;
			case '5':
				printf("����������:");
				scanf("%s",name);
				create_Type(mp,name);//����һ���� 
				break;
			case '9': jurisdiction = 0; break;
			case 'c':  jurisdiction = 2; break;
			case 'w': storage(mp);break;//����ˢ�̺��� 
			default: 
				printf("!!!�������!!!\n");
				break;
		}
		
	}

	
	while(jurisdiction == 2){
		
		Menu_client();// �ͻ��˵� 
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
				printf("��������ҷ�ʽ: ");
				scanf("%d",&choice2);
				switch_mov(mp,choice2);//������Ŀ ���еĵ�Ӱ 
				break;
			case 2:
				Menu_search();
				printf("��������ҷ�ʽ: ");
				scanf("%d",&choice2);
				switch_mov_all(mp,choice2);//����������Ŀ ���еĵ�Ӱ 
				break;
			case 3:
				printf("��������������: ");
				scanf("%s",name);
				Movs_BubbleSort(mp,name);// �����������Ŀ���ƽ������� 
				printf("�ѳɹ���������");
				break;
			case 4:
				Movs_traval(mp);// �� �����ݽṹ���б��� 
				break;
			case 9:
				jurisdiction = 0;// ����Ȩ��Ϊ0 
				printf("���˳�");
				break; 
			default: printf("���������������\n");
			
		}
		
	}
	
	
} 
