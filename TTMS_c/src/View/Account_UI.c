/*
* Account_UI.c
*
*  Created on: 2015��5��8��
*      Author: Administrator
*/

#include "Account_UI.h"
#include "../Common/list.h" 
#include "../Service/Account.c"
#include<windows.h>
#include <stdio.h>
#include<assert.h>
#include<string.h>
#include <unistd.h>
#include <sys/time.h>

void Account_UI_ShowList(account_list_t list, Pagination_t paging);

//��¼��������ʾ�û������û��������룬��¼�ɹ�return 1��������ʾ���µ�¼������3�Σ���¼ʧ��
int SysLogin() {
	//ϵͳ��¼
	Account_Srv_InitSys();
	char ch;
	int i = 0, j,m,n=0;
	char usrName[30];
	char pwd[30];
	int londtime = 3;

	do {
		printf("\t\t\t�X = = = = = = = = = = = = = = = = = = = = = = = = = = = = =  �[\n\n\n");
		printf("\t\t\t�p�פפפפפפפפ�  X����ԺƱ�����ϵͳ  �פפפפפפפפ� �p\n\n\n");
		printf("\t\t\t�^ = = = = = = = = = = = = = = = = = = = = = = = = = = = = =  �a\n\n\n");
		printf("��ӭʹ�ã�");
		printf("������1.��ƱԱ��2.����9.����Ա\n");
		scanf("%d", &j);
		getchar(); 
		printf("�������û���:\n");
		scanf("%s", usrName);
		getchar(); 
		printf("����������:\n");
		scanf("%s",pwd); 
		/*while ((ch = getch()) != '\r')
		{
			if (ch != 8)
			{
				pwd[i] = ch;
				putchar('*');
				i++;
			}
			else
			{
				putchar('\b');//������ɾ��һ������ͨ������س��� /b�س�һ��
				putchar(' ');//����ʾ�ո���Ѹղŵ�*����ס��
				putchar('\b');//Ȼ���ٻس�һ��ȴ�¼�롣
				i--;
			}
		}
		pwd[i] = '\0';		*/
		m=(Account_Srv_Verify(usrName, pwd));
		if (m!=1)
		{
			if (n == londtime)
			{
				printf("���ѵ�½���Σ�������Ȩ��½��ϵͳ......\n");
				exit (0);
			}
			else
			{
				n++;
				printf("���������������˻�����������%d�ε�½���ᣡ\n", londtime - n);
			}
		}
		else
	{	printf("��½�ɹ�");
		getchar(); 
			return  1;} 
	} while (n <= 4);
	return 1;
}
//����ϵͳ�û�������ں�������ʾ�û��˺Ź���˵�
void Account_UI_MgtEntry() {
	char usrName[20];
	char i, j;
	int pagesize;
	account_node_t *p = NULL;
	Pagination_t paging;
	account_list_t head;
	p = head;
	account_node_t *pos;
	//CreateList_Head(head);
	List_Init(head, account_node_t);
//	List_Paging(head, paging, account_node_t);
	printf("������ҳ��\n");
	scanf("%d", &pagesize);
	if (pagesize <= 0)
		pagesize = 5;
	paging.pageSize = pagesize;
	paging.totalRecords = Account_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);
	do {
		printf("\n==================================================================\n");
		printf("********************** account  **********************\n");
		printf("%s\t%s\t%s\t%s\n", "ID", "type", "username", "password");
		printf("------------------------------------------------------------------\n");
		//��ʾ����
		for (i = 0, pos = (account_node_t *)(paging.curPos);
			pos != head && i < paging.pageSize; i++) {
			printf("%d\t%d\t%s\t\t%s\n", pos->data.id,
				pos->data.type, pos->data.username, pos->data.password);
			pos = pos->next;
		}
		printf("------- Total Records:%2d ----------------------- Page %2d/%2d ----\n",
			paging.totalRecords, Pageing_CurPage(paging),
			Pageing_TotalPages(paging));
		printf("�û��˺Ź���˵�\n");
		printf("1:�����û���Ϣ\n");
		printf("2:ɾ���û���Ϣ\n");
		printf("3:�޸��û���Ϣ\n");
		printf("4:��ѯ�û���Ϣ\n");
		printf("\t[R]��һҳ|[P]��һҳ|[N]��һҳ|[L]���һҳ\n");
		printf("\n\n");
		fflush(stdin);
		printf("9:��ֹ����\n");
		scanf("%c", &i);
		system("cls");
		switch (i)
		{
		case '1':
			if (head == NULL)
			{
				printf("�޷�����˺�");
			}
			else
			{	Account_UI_Add(head);
				paging.totalRecords = Account_Srv_FetchAll(head);
				List_Paging(head, paging, account_node_t);
			break;} 
		case '2':
			if (head == NULL)
			{
				printf("û�п�ɾ�����û�");
			}
			else
			{
				printf("������Ҫɾ���û����û���");
				scanf("%s", usrName);
				getchar();
				 
				if(Account_UI_Delete(head, usrName)){
				
				paging.totalRecords = Account_Srv_FetchAll(head);
				List_Paging(head, paging, account_node_t);
			}}
			break;
		case '3':if (head == NULL)
		{
			printf("û�п��޸ĵ��û�");
		}
				 else
				 {
					 printf("������Ҫ�޸��û����û���");
					 scanf("%s", usrName);
					 getchar();
					 Account_UI_Modify(head, usrName);
					paging.totalRecords = Account_Srv_FetchAll(head);
					List_Paging(head, paging, account_node_t);
				 }
				 break;
		case '4':if (head == NULL)
		{
			printf("û�пɲ�ѯ���û�");
		}
				 else
				 {
					 printf("������Ҫ��ѯ�û����û���");
					 scanf("%s", usrName);
					 getchar();
					 Account_UI_Query(head, usrName);
					 paging.totalRecords = Account_Srv_FetchAll(head);
					 List_Paging(head, paging, account_node_t);
				 }
				 break;
		case 'R':
		case 'r':
			Paging_Locate_FirstPage(head, paging);
			break;
		case 'p':
		case 'P':
			if (1 < Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, account_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, account_node_t);
			}
			break;
 		case 'l':
	   	case 'L':
	   		Paging_Locate_LastPage(head,paging,account_node_t);
	   		break;

			 
		case '9':printf("ллʹ��!\n");exit(0);//��ֹ����
		}
	} while (i != 'r' || i != 'R');
//	Account_UI_ShowList(head, paging);




}


//���һ���û��˺���Ϣ������˺������ڣ���ʾ������Ϣ
int Account_UI_Add(account_list_t list)
{ 
	int i=0;
	account_node_t *m,p, *q = list;
	char num;
	system("cls");
	do
	{
		printf("������Ҫ����û����˺�:");
		scanf("%s", p.data.username);
		getchar();
		if (Account_Srv_FindByUsrName(list, p.data.username) != NULL)
		{
			printf("�˺��Ѿ�����");
			return 0;
		}
		else {
			printf("������Ҫ����û�������");
			scanf("%s", p.data.password);
			getchar();
			printf("������Ҫ����û������id(1:��ƱԱ||2:����||9:ϵͳ����Ա)");
			while (scanf("%d", &p.data.type) != 1)
			{
				printf("����Ĳ�������,����������!");
				continue;
			}
			p.data.id = EntKey_Srv_CompNewKey("account");
			if (Account_Srv_Add(&(p.data)) == 1)
			{
				m=&p;
				m = (account_node_t*)malloc(sizeof(account_node_t));
				List_AddHead(list,m);
				printf("��ӳɹ�"); 
				return 1;} 
		/*		while (q->next)
					q = q->next;
				q->next = p;
				p->prev = q;
				p->next = NULL;
				printf("��ӳɹ�");
			}
			printf("�Ƿ��������?1:��������:�˳�");
			while (scanf("%d", &i) != 1)
			{
				printf("����Ĳ�������,����������!");
				continue;
			}*/
		}
	} while (i == 1);
	return 1;
}
/*data
Account_Srv_Add()*/


//�����û��˺����޸��û��˺����룬����������û��˺�������ʾ������Ϣ
int Account_UI_Modify(account_list_t list, char usrName[]) {
	account_node_t *x, *p = list;
	char q[30], q1[30], q2[30];
	int i=0;
	x = Account_Srv_FindByUsrName(p, usrName); 
	system("cls");
	do
	{
		if (x == NULL) {
			printf("û���ҵ����û�");
			return 0; 
		}
		else
		{
			printf("�û���Ϊ%s\n", x->data.username);
			printf("ԭ����Ϊ%s\n", x->data.password);
			printf("������������");
			scanf("%s", q1);
			getchar();
			printf("���ٴ�����������");
			scanf("%s", q2);
			getchar();
			if ((strcmp(q1, q2)) == 0)
			{
				strcpy(x->data.password, q1);
				if (Account_Srv_Modify(&(x->data)) == 1)
				{
					x->prev = p->prev;
					x->next = p->next;
					printf("�޸ĳɹ�");
					return 1;
				}
			}
			else {
				printf("�������벻һ��!�޸�ʧ��,����1�����޸�,���������˳�");
				scanf("%d", &i);
			}
		}
	} while (i == 1);
	return 1;
}

//�����û��˺���ɾ��һ���Ѿ����ڵ��û��˺���Ϣ���������������û��˺�������ʾ������Ϣ
int Account_UI_Delete(account_list_t list, char usrName[]) {
	account_node_t *q, *p = list;
	int usrID;
	char q2[30], q1[30];
	int i;
	char a;
	q = Account_Srv_FindByUsrName(p, usrName); 
	system("cls");
	if (q  == NULL)
	{
		printf("�˺Ų�����");
		return 0;
	}

	printf("Ҫɾ�����û���Ϊ%s\nȷ��ɾ����?(y/n)", q->data.username);
	scanf("%c", &a);
	getchar();
	usrID=(Account_Srv_FindByUsrName(list,usrName)->data.id);
	if (a == 'y' || a== 'Y') {
		Account_Srv_DeleteByID(q->data.id);
		printf("ɾ���ɹ�!");
		return 1;
	}
	else
		printf("ɾ��ʧ��");
	return 0;
}

//�����û��˺������Ҹ��û��˺��Ƿ���ڣ����ڷ���1�����򷵻�0������ʾ������Ϣ
int Account_UI_Query(account_list_t  list, char usrName[]) {
	account_node_t *q, *p = list;
	char q2[30], q1[30];
	int i;
	char a;
	q = Account_Srv_FindByUsrName(p, usrName); 
	system("cls");
	if (q== NULL)
	{
		printf("�˺Ų�����");
		return 0;
	}
	else {
		printf("���û�IDΪ%ld\n�û�����Ϊ%d\n�˺���Ϊ%s\n����Ϊ%s\n", q->data.id, q->data.type, q->data.username, q->data.password);
		getchar(); 
	}
	return 1;
}

//��ͷ�巨��������list.����ֵΪ���ݽڵ����
int CreateList_Head(account_list_t list) {
	int i;
	account_list_t p;

	for (i = 0; i < 100; i++) {
		p = (account_node_t*)malloc(sizeof(account_node_t));
		if (!p)
			break;
		List_AddHead(list, p);
	}
	return i;
}
//��������	
/*void Account_UI_ShowList(account_list_t list, Pagination_t paging) {

	int size = 0;
	ShowListByPage(list, size);
	List_Destroy(list, account_node_t);//��������	
}*/
