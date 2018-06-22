/*
* File name:  Play_UI.c
* File ID:	  TTMS_SSF_Play_UI_Sour
* Author:     Huang Ru
* Version:    V1.0
* Date: 	  2015-04-25
*/


#include "Play_UI.h"

#include "../Common/list.h"
#include "../Service/play.c"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/*
 * Function:    Play_UI_MgtEntry
 * Function ID:	TTMS_SCU_Play_UI_MgtEnt
 * Description: ��Ŀ��Ϣ�������
 * Input:       flagΪ0���������ҳ�棬flagΪ1�����ѯ����
 * Output:      ��Ŀ�������
 * Return:      ��
*/

void Play_UI_MgtEntry(int flag) {
	system("cls"); 

    //����ʵ�ֲ���
    play_list_t     list;
    play_node_t     *p;
    int             i,u,pageSize=5;
    Pagination_t    paging;
	char filter[20],name[20];
    char choice;
    play_t *buf;
    
    List_Init(list,play_node_t);
    
    paging.totalRecords = Play_Srv_FetchAll(list);
    paging.pageSize = pageSize;
    Paging_Locate_FirstPage(list,paging);           //��λ����һҳ
    
    do {
    	system("cls");
		printf("\t=====================================================================================================\t\n");
 		printf("\t|                                      ******��Ŀ��Ϣ******                                         |\t\n");
 		printf("\t=====================================================================================================\n");
		printf("\t|%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s|\n", "ID", "Name", "��Ŀ����",
			"��Ʒ����", "�ȼ�","ʱ��","��ӳ����","��������","Ʊ��");
 		printf("\t|===================================================================================================|\t\n");
	  	for (i = 0, p = (play_node_t *) (paging.curPos);
			p != list && i < paging.pageSize; i++) {
			printf("\t%d\t%s\t%s\t\t%s\t\t%s\t%d\t%d/%d/%d\t%d/%d/%d\t\t%d\t\n", 
				p->data.id,
				p->data.name,
				(p->data.type == 1)?"Film":(p->data.type == 2?"Opear":"Concert"),
            	p->data.area,
			   (p->data.rating == 1)?"Child":(p->data.rating == 2?"Teenage":"Adult"),
                p->data.duration,
				p->data.start_date.year,p->data.start_date.month,p->data.start_date.day,
				p->data.end_date.year, p->data.end_date.month,p->data.end_date.day,
				p->data.price);
			p = p->next;
		}
	    printf("\n\t------------------Total Records:%2d ------------------------------------- Page %2d/%2d -------------------\n",
               paging.totalRecords, Pageing_CurPage(paging),
               Pageing_TotalPages(paging));
	    printf("\t|========================================================|\t\n");
	
	printf("\t[F]��һҳ|[P]��һҳ|[N]��һҳ|[L]���һҳ|[E]�˳�\n");
 	printf("\n\n");
 	
    printf("Your Choice:");
 	fflush(stdin);
    scanf("%c",&choice);
    
 	switch(choice){
 		case 'f':
 		case 'F':
 			Paging_Locate_FirstPage(list,paging);
 			break;
 		case 'p':
 		case 'P':
 			if (1 < Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(list, paging, -1, play_node_t);
			}
			break;
		case 'n':
		case 'N':
		if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(list, paging, 1, play_node_t);
			}
			break;
	    case 'l':
	    case 'L':
	   		Paging_Locate_LastPage(list,paging,play_node_t);
	   		break;
	   	case 'E':
	   	case 'e':break;
	    default:
	    	printf("��������\n");
	    }
	}while(choice!='E'&&choice!='e');
	switch(flag){
		case 0:
			printf("\n\n\n");
			printf("\t=================================\t\n");
			printf("\t|      ***��Ŀ�������***       |\t\n");
			printf("\t=================================\t\n");
			printf("\t|     A.��Ӿ�Ŀ                |\t\n");
			printf("\t|     U.�޸ľ�Ŀ                |\t\n"); 
			printf("\t|     D.ɾ����Ŀ                |\t\n");
			printf("\t|     M.�ݳ��ƻ�����            |\t\n");
			printf("\t=================================\t\n");
			printf("���������ѡ��(r/R��ʾ����):");
			fflush(stdin);
			scanf("%c",&choice);
			while(choice != 'r' && choice != 'R'){
				switch(choice) {
					case 'a':
					case 'A':
						if (Play_UI_Add()) //����ӳɹ����������һҳ��ʾ
							{
							paging.totalRecords = Play_Srv_FetchAll(list);
							Paging_Locate_LastPage(list, paging, play_node_t);  //��� 
							}
							break;
					case 'u':
					case 'U':
						printf("������Ҫ�޸ĵľ�Ŀ���:");
						scanf("%d",&u);
						Play_UI_Modify(u);
						if (Play_UI_Modify(u)) {	//������������
							paging.totalRecords = Play_Srv_FetchAll(list);
							List_Paging(list, paging, play_node_t);
						}
						break;
					case 'm':
					case 'M':
						printf("������Ҫ�����ݳ��ƻ��Ķ�Ӧ��ĿID:"); 
						scanf("%d",&u); 
						Schedule_UI_MgtEntry(u); 
			       		break;
				    case 'd':
				   	case 'D':
				   		printf("������Ҫɾ���ľ�Ŀid:");
						scanf("%d",&u);
						if(Play_UI_Delete(u)){
							paging.totalRecords = Play_Srv_FetchAll(list);
							List_Paging(list, paging, play_node_t);
						}
						break;     		
					default:		
						printf("�Բ������������Ϣ��������������\n");			
					}
					printf("���������ѡ��(r/R��ʾ����):");
					fflush(stdin);
			    	scanf("%c",&choice);
				}
				break;
		case 1:
				printf("\n\n\n");
				printf("\t=================================\t\n");
				printf("\t|      ***��Ŀ��ѯ����***       |\t\n");
				printf("\t|             1.ID��ѯ          |\t\n");
				printf("\t|             2.���Ʋ�ѯ        |\t\n");
				printf("\t|             3.ģ����ѯ        |\t\n");
				printf("\t=================================\t\n");
				printf("�����빦�����:");
				fflush(stdin);
				scanf("%c",&choice);
				switch(choice){ 
					case '1':
						printf("������Ҫ��ѯ�ľ�ĿID:");
						scanf("%d",&u);
						if(Play_UI_Query(u,buf)){
							play_print(*buf); 
						}
						break;
					case '2':
						printf("������Ҫ��ѯ������:");
						scanf("%s",name);
						if(Play_Srv_FetchByName(list,name)){
							paging.totalRecords = Play_Srv_FetchAll(list);
							List_Paging(list, paging, play_node_t);
						} 
						break;
					case '3':
						printf("������Ҫ��ѯ�Ĺؼ���:");
						scanf("%s",filter); 
						Play_Srv_FilterByName(list,filter);
					default:
						printf("��������\n");
						break;	
				}
		default:
			printf("��������\n");
			break;		
	}
}
 /* Function:    Play_UI_Add
 * Function ID:	TTMS_SCU_Play_UI_Add
 * Description: ���һ����Ŀ��Ϣ
 * Input:       ��
 * Output:      ������Ϣʱ�ĸ�����ʾ
 * Return:      ��ӵļ�¼��
 */
 
int Play_UI_Add(void)
{
	play_t rec;
	int newRecCount = 0;//��¼������Ŀ�� 
	char choice;

	do {
		/*system("cls");*/
		printf("\n=======================================================\n");
		printf("****************  Add New Play  ****************\n");
		printf("-------------------------------------------------------\n");
		printf("Play Name:");
		fflush(stdin);
		gets(rec.name);
		printf("��Ŀ����:(1��ʾ��Ӱ��2��ʾ��磬3��ʾ���ֻ�)");
		scanf("%d", &(rec.type));
		printf("��Ʒ����:");
		fflush(stdin);
		scanf("%s", &(rec.area));
		printf("��Ŀ����(1��ʾ��ͯ�ɹۿ���2��ʾ������ɹۿ���3��ʾ���˿ɹۿ�):");
		scanf("%d",&(rec.rating));
		printf("�ݳ�ʱ��:");
		scanf("%d",&(rec.duration));
		printf("��ӳ����(������,�ո����):");
		scanf("%d%d%d",&(rec.start_date.year),&(rec.start_date.month),&(rec.start_date.day));
		printf("��������(������,�ո����):");
		scanf("%d%d%d",&(rec.end_date.year),&(rec.end_date.month),&(rec.end_date.day));
		printf("Ʊ�ļ۸�:");
		scanf("%d",&(rec.price));
		printf("=======================================================\n");

		//��ȡ����
		rec.id = EntKey_Srv_CompNewKey("Play");

		if (Play_Srv_Add(&rec)) {
			newRecCount += 1;
			printf("The new room added successfully!\n");
	 	}
		else
			printf("The new room added failed!\n");
			printf("-------------------------------------------------------\n");
			printf("[A]dd more, [R]eturn:");
			fflush(stdin);
			scanf("%c", &choice);
	} while ('a' == choice && 'A' == choice);
	return newRecCount;
}
/*
 * Function:    Play_UI_Modify
 * Function ID:	TTMS_SCU_Play_UI_Mod
 * Description: ���¾�Ŀ��Ϣ
 * Input:       �����µľ�ĿID��
 * Output:      ������Ϣʱ�ĸ�����ʾ
 * Return:      ���µľ�Ŀ��Ϣ����0��ʾδ�ҵ���1��ʾ�ҵ�������
 */

int Play_UI_Modify(int id){
	play_t rec; 
	int rtn = 0;
	int choice;
	if(!Play_Srv_FetchByID(id,&rec)) {
		printf("�����ڸþ�ĿID\n�밴�س���[enter]����\n");
		getchar();
		return 0;
	}
	printf("\t==============================================\t\n");
    printf("\t|**************  �޸ľ�Ŀ��Ϣ  **************|\t\n");
	printf("\t----------------------------------------------\t\n");
	printf("\t|   1.��Ŀ����                               |\t\n"); 
	printf("\t|   2.��Ŀ����                               |\t\n");
	printf("\t|   3.��Ŀ��Ʒ����                           |\t\n");
	printf("\t|   4.��Ŀ�ȼ�                               |\t\n");
	printf("\t|   5.��Ŀʱ��(����)                         |\t\n");
	printf("\t|   6.��ӳ����                               |\t\n");
	printf("\t|   7.��������                               |\t\n");
	printf("\t|   8.Ʊ��                                   |\t\n");
	printf("\t----------------------------------------------\t\n");
	printf("\n\n");
	
	printf("���������޸����ݵ�ѡ��(0��ʾ����):");
	scanf("%d",&choice);	
	while(choice != 0) {
	   switch(choice)
	  {
		case 1:
			printf("�������µľ�Ŀ����:");
			scanf("%s",rec.name);
			break;
		case 2:
			printf("�������µľ�Ŀ����(1��ʾ��ͯ�ɹۿ���2��ʾ������ɹۿ���3��ʾ���˿ɹۿ�):");
			scanf("%d",&rec.type);
			break;
		case 3:
			printf("�������µľ�Ŀ����:");
			scanf("%s",rec.area);
			break;
		case 4:
			printf("�������Ŀ�ȼ�(1��ʾ��Ӱ��2��ʾ��磬3��ʾ���ֻ�):");
			scanf("%d",&rec.rating);
		case 5:
			printf("�������¾�Ŀʱ��(����):");
			scanf("%d",&rec.duration);
			break;
		case 6:
			printf("�������¾�Ŀ��ӳ����(�ո��������2017 6 13):");
			scanf("%d%d%d",&rec.start_date.year,&rec.start_date.month,&rec.start_date.day);
			break;
		case 7:
			 printf("�������¾�Ŀ��������(�ո��������2017 6 13):");
			 scanf("%d%d%d",&rec.end_date.year,&rec.end_date.month,&rec.end_date.day);
			 break;
		case 8:
			printf("�������¾�ĿƱ��:");
			scanf("%d",&rec.price);
			break;
		default:
			printf("�Բ������������Ϣ����");
			break;
	    	}
	    	printf("���������޸����ݵ�ѡ��(0��ʾ����):");
			scanf("%d",&choice);
	}
	
	if(Play_Srv_Modify) {
		printf("�޸ĳɹ�");
		rtn = 1;
	}
	else
		printf("�Բ����޸���Ϣʧ��");
		
	return rtn;
}

/*
 * Function:    Play_UI_Delete
 * Function ID:	TTMS_SCU_Play_UI_Del
 * Description: ����ID��ɾ����Ŀ��Ϣ
 * Input:       ��ɾ���ľ�ĿID��
 * Output:      ��ʾɾ���Ƿ�ɹ�
 * Return:      0��ʾɾ��ʧ�ܣ�1��ʾɾ���ɹ�
 */
int Play_UI_Delete(int id){
	
	int rtn = 0;
	
	//�����ڸ�ID����ɾ���ò������� 
	if(Play_Srv_DeleteByID(id))
	{
		printf("ɾ���ɹ�\n����س���[enter]����\n");
		rtn = 1;
	}
	else
	    printf("ɾ��ʧ��\n����س���[enter]����\n");
	getchar();
	return rtn;
}
/*
 * Function:    Play_UI_Query
 * Function ID:	TTMS_SCU_Play_UI_Qry
 * Description: ����ID�Ų�ѯ��Ŀ��Ϣ
 * Input:       �����ҵľ�ĿID��
 * Output:      ���ҵ��ľ�Ŀ��Ϣ
 * Return:      0��ʾδ�ҵ���1��ʾ�ҵ���
 */
int Play_UI_Query(int id , play_t *rec){
	return Play_Perst_SelectByID(id,rec);
}
