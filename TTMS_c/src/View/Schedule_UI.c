/*
* File name:  Schedule_UI.c
* File ID:	  TTMS_SSF_Schedule_UI_Sour
* Author:     Huang Ru
* Version:    V1.0
* Date: 	  2015-04-25
*/


#include "Schedule_UI.h"
#include "Play_UI.h"

#include "../Service/Play.h"
#include "../Service/Studio.h"
#include "../Service/EntityKey.h"

#include <stdio.h>
#include <stdlib.h>

	/*
	 * Function:    Schedule_UI_ListAll
	 * Function ID:	TTMS_SCU_Schedule_UI_List
	 * Description: ��ʾ���е��ݳ��ƻ���Ϣ,���в�ѯ��
	 * Input:       ��
	 * Output:      ���о�Ŀ����Ϣ
	 * Return:      ��
	 */
void Schedule_UI_ListAll(void) {
	
}

/*
 * Function:    Schedule_UI_Add
 * Function ID:	TTMS_SCU_Schedule_UI_Add
 * Description: ���һ���ݳ��ƻ���Ϣ
 * Input:       ��ؾ�Ŀ��ID��
 * Output:      ������Ϣʱ�ĸ�����ʾ
 * Return:      ��ӵļ�¼��
 */
int Schedule_UI_Add(int play_id) {
	schedule_t rec;
	int newRecCount = 0;//��¼������Ŀ�� 
	char choice;

	printf("\n=================================================\n");
	printf("*****************  ����ݳ��ƻ�   *****************\n");
	printf("---------------------------------------------------\n");

	rec.play_id=play_id ;
	printf("����ݳ���ID"); 
	scanf("%d",&rec.studio_id);
	printf("��ӷ�ӳ���� ");
	scanf("%d%d%d",&rec.date.year,&rec.date.month,&rec.date.day);
	printf("��ӷ�ӳʱ��"); 
	scanf("%d%d%d",&rec.time.hour,&rec.time.minute,&rec.time.second);
	printf("�����λ��");
	scanf("%d",&rec.seat_count);
	
	rec.id = EntKey_Srv_CompNewKey("Schedule");
	
	if(Schedule_Srv_Add(&rec))
	{
		newRecCount += 1;
			printf("����ݳ��ƻ��ɹ�\n");
	}
	else
		printf("����ݳ��ƻ�ʧ��\n");
		printf("------------------------------------------------\n");
	
	return newRecCount;
}
/*
 * Function:    Schedule_UI_Modify
 * Function ID:	TTMS_SCU_Schedule_UI_Mod
 * Description: ����ID�Ÿ����ݳ��ƻ���Ϣ
 * Input:       �����µľ�ĿID��
 * Output:      ������Ϣʱ�ĸ�����ʾ
 * Return:      ���µľ�Ŀ��Ϣ����0��ʾδ�ҵ���1��ʾ�ҵ�������
 */
int Schedule_UI_Modify(int id){

	int rtn=0;
	schedule_t rec;
	int choice;
	
	if(Schedule_Srv_FetchByID(id,&rec)==1){ 
		printf("δ�ҵ��þ�Ŀ���ݳ��ƻ�");
		return 0; 
	}
	 
	printf("\n=================================\n");
	printf("***********  �޸��ݳ��ƻ�  ********\n");
	printf("------------------------------------");
	printf("\n=================================\n");
	printf("\n|*******  1.�ݳ���ID    ******* |\n");
	printf("\n|*******  2.��ӳ����    ******* |\n");
	printf("\n|*******  3.��ӳʱ��    ******* |\n");
	printf("\n|*******  4.��λ��      ******* |\n");
	printf("\n=================================\n");
	printf("\n\n");
	do{
		printf("���������޸����ݵ�ѡ��(0�˳��ݳ��ƻ��޸�):");
		scanf("%d",&choice);
		switch(choice){
		
			case 1:
				printf("�ݳ���ID:");
				scanf("%d",&rec.studio_id);
				break;
			case 2:
				printf("��ӳ����");
				scanf("%d%d%d",&rec.date.year,&rec.date.month,&rec.date.day);
				break;
			case 3:
				printf("��ӷ�ӳʱ��"); 
				scanf("%d%d%d",&rec.time.hour,&rec.time.minute,&rec.time.second);
				break;
			case 4:
				printf("�����λ��");
				scanf("%d",&rec.seat_count);
				break; 
			case 0:break;
			
			default:
				printf("�Բ����������Ϣ����\n");
				break;
		}
	}while(choice!=0);
	
	rtn=Schedule_Srv_Modify(&rec);
	if(rtn==1)
		printf("�޸��ݳ��ƻ��ɹ�\n");
	else
		printf("�޸��ݳ��ƻ�ʧ��\n");
		
}

/*
 * Function:    Schedule_UI_Delete
 * Function ID:	TTMS_SCU_Schedule_UI_Del
 * Description: ����ID��ɾ���ݳ��ƻ���Ϣ
 * Input:       ��ɾ���ľ�ĿID��
 * Output:      ��ʾɾ���Ƿ�ɹ�
 * Return:      0��ʾɾ��ʧ�ܣ�1��ʾɾ���ɹ�
 */
int Schedule_UI_Delete(int id){

	int rtn = 0;
	
	//�����ڸ�ID����ɾ���ò������� 
	if(Schedule_Srv_DeleteByID(id))
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
 * Function:    Schedule_UI_Query
 * Function ID:	TTMS_SCU_Schedule_UI_Qry
 * Description: ����ID�Ų�ѯ�ݳ��ƻ���Ϣ
 * Input:       �����ҵľ�ĿID��
 * Output:      ���ҵ��ľ�Ŀ��Ϣ
 * Return:      0��ʾδ�ҵ���1��ʾ�ҵ���
 */
int Schedule_UI_Query(int id){

	char chioce;
	schedule_t buf;
	int rtn;
	 if (Schedule_Srv_FetchByID( id, &buf)) {
		system("cls");
		printf("\n\n\n");
		printf("\t\t\t = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\t***********  IDΪ%2d���ݳ��ƻ�  **********\n",buf.id);
		printf("\t\t\t = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\n\n\n");
        rtn = 1;
        printf("�ƻ�ID: %d\n",&buf.id);
        printf("��ĿID: %d\n",&buf.play_id);
        printf("��ӳ��ID: %d\n",&buf.studio_id);
        printf("�ݳ�����:%d��%d��%d��\n", &buf.date.year, &buf.date.month, &buf.date.day);
        printf("�ݳ�ʱ��:%dʱ%d��%d��\n",&buf.time.hour, &buf.time.minute, &buf.time.second);
        printf("��λ����:%d\n",buf.seat_count);
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
        printf("����س�������");
        while(getchar() != '\n');
    }
	else    
    {
        printf("\n\t\t\t���Ҳ������ݳ��ƻ���");
		rtn = 0; 
    }
    return rtn;
	
}

/*
 * Function:    Schedule_UI_ListByPlay
 * Function ID:	TTMS_SCU_Schedule_UI_ListByPlay
 * Description: ���б�ģʽ��ʾ������Ŀ���ݳ��ƻ���Ϣ
 * Input:       listΪ���ҵ����ݳ��ƻ���Ϣ�����ͷָ�룬playΪ��Ŀ��Ϣ��pagingΪ��ʾ��ҳ���ò���
 * Output:      ��
 * Return:      ���ز��ҵ��ļ�¼��Ŀ
 */
void Schedule_UI_ListByPlay(const play_t *play, schedule_list_t list, Pagination_t paging){
}

/*
 * Function:    Schedule_UI_MgtEntry
 * Function ID:	TTMS_SCU_Schedule_UI_MgtEnt
 * Description: �ݳ��ƻ�������棬�ݳ��ƻ����վ�Ŀ���й����Ծ�ĿID��Ϊ����
 * Input:       ��ؾ�ĿID��
 * Output:      �ݳ��ƻ���Ϣ
 * Return:      ��
 */
void Schedule_UI_MgtEntry(int play_id){

	int id;//�ݳ��ƻ�ID 
	int i;
	char choice;
	char ch;
	schedule_list_t list;          
	schedule_node_t *p;  
	int flag;       
	Pagination_t paging; 
	        
	List_Init(list, schedule_node_t);        
//	paging.offset = 0;       
	paging.pageSize = 5;
	//��������
	paging.totalRecords = Schedule_Srv_FetchAll(list);
	Paging_Locate_FirstPage(list, paging);
	do{
    	system("cls");
		printf("\t|====================================================================================================|\n");
 		printf("\t|                                    ******�ݳ��ƻ���Ϣ******                                        |\t\n");
 		printf("\t|====================================================================================================|\n");
		printf("\t  %s\t%s\t%s\t%s\t%s\t%s\t\n","�ݳ��ƻ�ID","��ӳ��ĿID","�ݳ���ID","��ӳ����","��ӳʱ��","��λ��");
 		printf("\t|====================================================================================================|\t\n");
 		
	  	for (i = 0, p = (schedule_node_t *) (paging.curPos);
			p != list && i < paging.pageSize; i++) {
			printf("\t|%d\t%d\t%d\t%4d/%2d/%2d\t%4d/%2d/%2d\t%4d/%2d/%2d\t%d\t|\n",
			(p->data.id),
			(p->data.play_id),
			(p->data.studio_id),
			(p->data.date.year),(p->data.date.month),(p->data.date.day),
			(p->data.time.hour),(p->data.time.minute),(p->data.time.second));
			p = p->next;
		}
	    printf("\n\t------------------Total Records:%2d ------------------------------------- Page %2d/%2d -------------------\n",
               paging.totalRecords, Pageing_CurPage(paging),
               Pageing_TotalPages(paging));
	    printf("\t|========================================================|\t\n");
	    
		printf("\t[F]��һҳ|[P]��һҳ|[N]��һҳ|[L]���һҳ|[E]�˳�\n");
	 
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
	
	printf("\t===========================================================\n");
	printf("\t******************     �ݳ��ƻ�����    ********************\n");
//	printf("\t ID     Name     room     time    excess  ticket   quantity\n");
	printf("\t-----------------------------------------------------------\n");
	printf("\t***********************************************************\n");
	printf("\t[A]dd | [D]elete | [U]pdate | [Q]uery | [R]eturn\n");
	printf("\t===========================================================\n");
	do{
		printf("���������ѡ��(r/R�˳��ݳ��ƻ�����):");
		fflush(stdin);
		scanf("%c",&ch);
		switch(ch)
		{
			case'a':
			case'A':
					Schedule_UI_Add(play_id);break;
			case'd':
			case'D':
				printf("��������Ҫɾ�����ݳ��ƻ�id");
				scanf("%d",&id);
				Schedule_UI_Delete(id);break;
			case'u':
			case'U':
				printf("��������Ҫ�޸ĵ��ݳ��ƻ�id");
				scanf("%d",&id);
				Schedule_UI_Modify(id);break;
			case 'q':
			case 'Q':
				printf("������Ҫ��ѯ���ݳ��ƻ�ID");
				scanf("%d",&id); 
				Schedule_UI_Query(id);break;
			case 'r':
			case 'R':
				break; 
			default:
				printf("�Բ������������Ϣ����\n");
		}
	}while(ch!='r'&&ch!='R');
}

