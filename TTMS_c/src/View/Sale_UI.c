#include "Play_UI.h"
#include "Schedule_UI.h"
#include "Sale_UI.h"
#include "Ticket_UI.c"

#include "../Service/Schedule.h"
#include "../Service/play.h"
#include "../Service/seat.h"
#include "../Service/studio.h"
#include "../Service/Sale.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//���õ�½�û���ȫ�����ݽṹ
extern account_t gl_CurUser;

//���ݼƻ�ID����ʾ�ݳ�Ʊ
void Sale_UI_ShowTicket(int schID){
	schedule_t  mmp;
	FILE *fl;
	char choice;
	ticket_list_t  mlist;
	seat_list_t nlist;
	FILE *fp=fopen("Schedule.dat","rb");
	FILE *fs;
	ticket_list_t ticketList;
	seat_list_t   seatList;
	if (NULL==fp)
	    printf("Cannot open file Schedule.dat");
    while(!feof(fp))
	{
		fread(&mmp,sizeof(schedule_t),1,fp);
		if (mmp.id==schID)
		  {
	        if (Schedule_Srv_FetchByID(schID,&mmp)==1)
	         fs=fopen("Schedule.dat","rb");
			  if (fs == NULL)
		       {
		        	printf("Cannot open file Schedule.dat");
		       }
		    while(!feof(fs))
		    {
			    fread(nlist,sizeof(seat_list_t),1,fs);
			    if (nlist->data.roomID==mmp.studio_id)
			   	{
				    Seat_Srv_FetchByRoomID(nlist,mmp.studio_id);
			   	     fl=fopen("Ticket.dat","rb");
	     	         ticket_list_t  *list;
		             if (fl ==NULL)
		                printf("Cannot open file Ticket.dat");
		       }
		    }
		    while(!feof(fl))
		    {
			    fread(mlist,sizeof(ticket_list_t),1,fl);
			    if (mlist->data.schedule_id==mmp.id)
			   	{
					   Ticket_Srv_FetchBySchID(mlist,mmp.id);
					   printf("���������ѡ��");
					   scanf ("%c",&choice);
					   switch(choice)
					  {
					   case 'r':
					   case 'R':
					   		break;
					   case 'b':
					   case 'B':
//					    ticketList=Ticket_Srv_FetchAll(ticketList);
//					   	seatList=Seat_Srv_FetchAll(seatList);
//					   	Sale_UI_SellTicket(ticketList,seatList);
					   	break; 
					   default :break; 
					}
				}
		    }
		}
	}
}


inline int Sale_UI_SellTicket(ticket_list_t tickList, seat_list_t seatList){
	int row;
	int column;
	seat_node_t *pos;
	ticket_node_t *p;
	printf("��������λ�����У�");
	scanf ("%d%d",&row,&column);
    if (pos=Seat_Srv_FindByRowCol(seatList,row,column)!=NULL)
      { 
	     if  (p=Ticket_Srv_FindBySeatID(tickList,pos->data.id))
		  {
		  	     if(Ticket_Srv_Modify(&(p->data))==1) 
                     printf("��Ʊ�ɹ���");
	return 0;
          }
      }
}
//���ݾ�ĿID��ʾ�ݳ��ƻ�
void Sale_UI_ShowScheduler(int play_id) {
	
	play_t rec;
	int id;
	int i;
	int listSize = 0; 
	int pageSize=5;
	schedule_list_t head;
    schedule_node_t *p;
    
	
	
	schedule_t  schedule;
	Pagination_t paging;

    List_Init(head, schedule_node_t);

    paging.pageSize=pageSize;

   
	paging.offset = 0;
	 //��������
	paging.totalRecords = Schedule_Srv_FetchByPlay(head,play_id);
	Paging_Locate_FirstPage(head, paging);
	
	FILE *fp=fopen("schedule.dat","rb");
	if (NULL==fp)
	     printf("Cannot open file :schedule.dat");
    while(!feof(fp))
	{
		fread(&rec,sizeof(play_t),1,fp);
		if (rec.id==play_id)
		  {
		  	if(Play_Srv_FetchByID(play_id,&rec)==1)
		  	 {
			   char choice;
				printf("\n==================================================================\n");
				printf("********************** Projection Room List **********************\n");
				printf("%5s %5s %5s  %4s  %4s  %4s  \n","id", "play_ID", "studio_id","date","time","seat_count");
				//��ʾ���� 
			for (i = 0, p = (schedule_node_t *) (paging.curPos);
				p != head && i < paging.pageSize; i++) {
			printf("%4d\t  %4d\t  %4d\t  %4d%2d%2d\t  %2d%2d%2d\t %4d\t\n", p->data.id,p->data.play_id,
					p->data.studio_id, p->data.date.year,p->data.date.month,p->data.date.day, p->data.time.hour,p->data.time.minute,p->data.time.second,
			p->data.seat_count);
			p = p->next;
		}
				printf("------- Total Records:%2d ----------------------- Page %2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
				printf("------------------------------------------------------------------\n");
		  	  	printf("���������ѡ��p|P:ǰһҳ��t|T:��ʾ���е�Ʊ��n|N:��һҳ��\n");
		    	scanf("%c",&choice);
			   switch(choice)
			     {
				  case 'p':
			      case 'P':
				          if (1 < Pageing_CurPage(paging)) {
				                Paging_Locate_OffsetPage(head, paging, -1, play_node_t);
		          	        }
		                	break;
			      case 't':
			      case 'T':
				           printf("��������Ҫ��ѯ�ľ�Ŀ�ݳ��ƻ���ID!");
			               scanf ("%d",&id);
			               schedule.id=id;
				           Sale_UI_ShowTicket(schedule.id);
				           break;
				  case 'n':
				  case 'N':
				            if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
				                 Paging_Locate_OffsetPage(head, paging, 1, play_node_t);
	                        		}
			                   break;
			    }
			}
		}             
}
}
void Sale_UI_MgtEntry() {
static const int PLAY_PAGE_SIZE = 3;
	char logo;
	char name[30];
	int i;
	int ID;
	
	play_list_t head;
	play_list_t pos;
	Pagination_t paging; 
	play_node_t  *p;
	
	List_Init(head,play_node_t);
	paging.offset = 0;
	paging.pageSize = PLAY_PAGE_SIZE;
	paging.totalRecords = Play_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head,paging);
	do{
		system("cls");
  		printf("\t=====================================================================================================\t\n");
 		printf("\t|                                      ******��Ŀ��Ϣ******                                         |\t\n");
 		printf("\t=====================================================================================================\n");
		printf("\t|%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s|\n", "ID", "Name", "��Ŀ����",
							"��Ʒ����", "�ȼ�","ʱ��","��ӳ����","��������","Ʊ��");
 		printf("\t|===================================================================================================|\t\n");
	  	for (i = 0, p = (play_node_t *) (paging.curPos);
			p != head && i < paging.pageSize; i++) {
			printf("\t%d\t%s\t%s\t\t%s\t\t%s\t%d\t%d/%d/%d\t\t%d/%d/%d\t\t%d\t\n", 
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
	    printf("\t|========================================================================|\t\n");

		printf("c|C:�ݳ��ƻ���s|S:��ѯ��Ŀ��f|F:ģ������, p|P:ǰһҳ��n|N:��һҳ, r|R:���أ�\n");
   		printf("\n============================================================================\n");
	printf("���������ѡ��:(r/R�˳���Ŀ��ʾ)");
	fflush(stdin);
	scanf ("%c",&logo);
	getchar(); 
	switch(logo)
	{
		case 'c':
		case 'C':
			printf("�������ѯ�ľ�ĿID��");
			scanf ("%d",&ID);
			Sale_UI_ShowScheduler(ID);
			break; 
		case 's':
		case 'S':
			printf("��������Ҫ��ѯ�ľ�Ŀ���֣�\n");
			scanf ("%s",name);
			Play_Srv_FetchByName(head,name);
			break;
		case 'f':
		case 'F':	
		printf("��������Ҫ���ҵľ�Ŀ���ƣ�\n");
		scanf ("%s",name);
		Play_Srv_FilterByName(head,name);break;
		case 'p':
		case 'P':if (1 < Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, play_node_t);
			}
			break;
		case 'n':
		case 'N':	if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, play_node_t);
			}
			break;
		}	
}while(logo!='R'||logo!='r');
}
//��Ʊ
void Sale_UI_ReturnTicket(){
	int  ID;
	ticket_t  *buf; 
	printf("������Ʊ��ID��\n");
	scanf("%d",&ID); 
	sale_t al;  
	if (Ticket_Srv_FetchByID(ID,buf)==1)
	{
	//1��ʾ�������۳�
	if (buf->status==1)
	  {
	    if (Ticket_Srv_Modify(buf)==1)
		      al.date= DateNow();
		      al.time= TimeNow();
		      al.id=EntKey_Srv_CompNewKey("Sale");
		      al.type=-1;
		      printf("���������ID!\n");
		      scanf ("%d",&al.user_id);
		      al.ticket_id=ID;
		      al.value=buf->price;
		      Sale_Srv_Add(&al);
	          printf("�����ɹ���\n");
      }
  	else  
		printf("��Ʊʧ��!Ʊ�Ѿ��۳�����Ԥ����\n");
	}
}
	
