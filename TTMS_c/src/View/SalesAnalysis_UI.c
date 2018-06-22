/*
 * SalesAnalysis_UI.c
 *
 *  Created on: 2015��5��8��
 *      Author: Administrator
 */
#include "SalesAnalysis_UI.h"
#include "../Common/list.h"
#include "../Common/common.h"
#include "../Service/SalesAnalysis.c"
//#include "../Service/Account.c"


#include <conio.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

//�ⲿ����gl_CurUser ���ڴ洢��¼�û���Ϣ
extern account_t gl_CurUser;

//�����ҳ������ҳ���СΪ5
static const int SALESANALYSIS_PAGE_SIZE = 5;



//�������� 
//GreateList_Head(list) {
//	int i;//���ƴ�������Ľڵ���� 
//	salesanalysis_node_t *new;
//	
//	for(i = 0; i < 100; i++) {
//		new = (salesanalysis_node_t *)malloc(sizeof(salesanalysis_node_t));  //�����µĽڵ�
//		if(!new)
//			break; 
//		List_AddHead(list,new);
//	} 
//	return i;
//}




//��ҳ��
static void ShowSalesanalysisListByPage(salesanalysis_list_t head,int listsize) {
	 
 	Pagination_t paging; // �����ҳ����
	paging.pageSize =  SALESANALYSIS_PAGE_SIZE; //���÷�ҳ��ʾҳ���С 
	Salesanalysis_Srv_StaticSale(head);//��ȡ��ĿƱ����Ϣ���� 
	
	paging.totalRecords = Salesanalysis_Srv_StaticSale(head);//���÷�ҳ���ܼ�¼��
	
   	SalesAnalysis_Srv_SortBySale(head);//���þ�ĿƱ�����з�����
    salesanalysis_node_t *pos; //ͷָ��
    int i;
   //��λ����ҳ���ĵ�һҳ
   Paging_Locate_FirstPage(head,paging); 
	char choice;
	printf("\n\n\n");
	printf("\t==================================================\t\n");
	printf("\t|              ***��ĿƱ�����а�***              |\t\n");
	printf("\t==================================================\t\n");
	
	for (i = 0, pos = (salesanalysis_node_t *) (paging.curPos);
		pos != head && i < paging.pageSize; i++) {
				printf("\tID%5d Name%5s price%5d totaltickets%5ld sales%5ld",
				pos->data.play_id,
				pos->data.name,
				pos->data.price,
				pos->data.totaltickets,
				pos->data.sales);
				pos = pos->next;
			}
	printf("\t------- Total Records:%2d ----------------------- Page %2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
	printf("\t|============================================|\t\n");
		printf("\t|       P.��һҳ  N.��һҳ  R.�˳�       |\t\n");
	printf("\t|============================================|\t\n");
	do{
	printf("���ѡ����");
	scanf("%c",&choice);
	fflush(stdin);
	switch(choice) {
		case 'p':
		case 'P':
			if(1 < Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head,paging,-1,salesanalysis_node_t);
			}
			break;
		case 'n':
		case 'N':
			if(Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head,paging,1,salesanalysis_node_t);
			}
			break;
		default:
			break;			
		}
	}while(choice != 'r'&& choice != 'R');
	
 } 

//��Ժ�������а���,������ʾ��ֹĿǰ��Ժ��ӰƱ�����а�
void SalesAnalysis_UI_BoxOffice() {
	
	setvbuf(stdout,NULL,_IONBF,0);
	salesanalysis_list_t head; //��������ͷָ�� 
	int size = 0;
	
	List_Init(head,salesanalysis_node_t); //��ʼ������ 
	//size = GreateList_Head(list); //�������� 
	
	//Salesanalysis_Srv_StaticSale(head);//��ȡ��ĿƱ����Ϣ���� 
	
	//SalesAnalysis_Srv_SortBySale(head);//���þ�ĿƱ�����з�����
	
	ShowSalesanalysisListByPage(head,size); //ͨ����ҳ��ʾ��������
	
	List_Destroy(head,salesanalysis_node_t);//�������� 
}

//��ʾ��ƱԱ�ڸ��������������Ʊ���
void SalesAnalysis_UI_StatSale(int usrID, user_date_t stDate, user_date_t endDate){
	int sale;
	account_t usr;
	usr.id = usrID;
	sale = Salesanalysis_Srv_CompSaleVal(usr.id,stDate,endDate);
	Account_Srv_FetchByID(usr.id,&usr);
	printf("��%d.%d.%d��%d.%d.%d�ڼ����۶�Ϊ:%d",stDate.year,stDate.month,stDate.day,endDate.year,endDate.month,endDate.day,sale);

}

//���۷�����ں�������ʾ�˵����˵�����"������ʾ��ֹĿǰ��Ժ��ӰƱ�����а�"������ʾ���ѯ������ƱԱ��Ʊ�������
//����ѯ������������ĳ��ƱԱ��Ʊ�����
void SalesAanalysis_UI_MgtEntry() {
	char choice;
	account_t user;//�ṹ�� 
	user_date_t stDate;
	user_date_t endDate;
	char UsrName[20];//��ƱԱ������
	account_t gl_CurUser_type;
	
	Pagination_t paging; 
	
	//���� 
	printf("\n\n\n");
	printf("\t\n|===================================================================|\t\n");
	printf("\t\n|               *************�������ݷ���**************             |\t\n");
	printf("\t\n|===================================================================|\t\n");
	printf("\t\n| B.��ĿƱ�����а�  D.��ƱԱ���۶����  S.�������۶����  R.�˳�����|\t\n");
	printf("\t\n|===================================================================|\t\n"); 
	
	do{
	
		printf("���������ѡ��:");
		fflush(stdin);
		scanf("%c",&choice);
		switch(choice)
		{
			case 'b':
				case 'B':
					
					SalesAnalysis_UI_BoxOffice();
					
					break;
			case 'd':
				case 'D':
					if(gl_CurUser.type == USR_CLERK){
						SalesAnalysis_UI_StatSale(user.id,stDate,endDate);
					}
					else
					{
						printf("������ƱԱ������:");
						fflush(stdin);
						scanf("%s",&UsrName);
						if(!Account_Srv_FetchByName(UsrName,&user)) {
							printf("��Ǹ����δ�ҵ�����Ϣ");
						}
						else
							SalesAnalysis_UI_StatSale(user.id,stDate,endDate);
					}
					
					break;
			case 's':
				case 'S':
					if(gl_CurUser.type != USR_MANG)
					{
						printf("������ƱԱ������:");
						fflush(stdin);
						scanf("%s",&UsrName);
						if(!Account_Srv_FetchByName(UsrName,&user))
						{
							printf("��Ǹ����δ�ҵ�����Ϣ");
						}
						else
						{
							printf("�������Ŀ��ӳʱ������ӳʱ��:(�Կո��������2017 6 14)");
							scanf("%d%d%d",&stDate.year,&stDate.month,&stDate.day);
							scanf("%d%d%d",&endDate.year,&endDate.month,&endDate.day);
							SalesAnalysis_UI_StatSale(user.id,stDate,endDate);
					    }
						}
					else
						printf("�Բ���������Ϣ����");
					break;
			case 'r':
				case 'R':
					break;
			default:
				break; 
		}
	}while(choice != 'R' && choice != 'r');

}



