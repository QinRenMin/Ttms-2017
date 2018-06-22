/*
 * salesanalysis.c
 *
 *  Created on: 2015��6��12��
 *      Author: Administrator
 */
#include <string.h>
#include <stdio.h>
#include "SalesAnalysis.h"
#include "../Persistence/Sale_Persist.h" 
#include "../Persistence/SalesAnalysis_Persist.c"
#include "Ticket.h"
#include "Play.h"
#include "Sale.h" 
#include "Schedule.h"
#include "../Common/list.h"

//����Ա��usrID�ڸ���ʱ����������۶�������۶�
inline int Salesanalysis_Srv_CompSaleVal(int usrID, user_date_t stDate, user_date_t endDate){

	int amount = 0;
	sale_list_t saleList; //���� 
	sale_node_t *pSale; //����ָ�����
	List_Init(saleList,sale_node_t);//��ʼ�� 
	Sale_Perst_SelectByUsrID(saleList,usrID,stDate,endDate);//����ƥ��usrID��������Ϣ���������� 
	List_ForEach(saleList,pSale);//���� 
	amount += pSale->data.value;
	return amount;//����ĳ��ƱԱ�����۶� 
}

//��Ͼ�ĿPlay.dat,ͳ���������ݣ��������۷���salesanalysis_list_t list��������list������
int Salesanalysis_Srv_StaticSale(salesanalysis_list_t list) {
	play_list_t playList; //����ͷָ��
	play_node_t *pos; //ָ�����
	salesanalysis_node_t *newNode;
	int sold,total; //�洢����Ʊ������Ʊ��
	int count = 0; //��¼�ڵ���� 
	
	List_Free(list,salesanalysis_node_t);//�ͷ�list���������ݽڵ� 
	List_Init(playList,play_node_t);//��ʼ��playList����
	 
	total = Play_Srv_FetchAll(playList);//�������ļ�play.dat�����Ŀ��Ϣ����playlist����
	
	List_ForEach(playList,pos);//����playList����
	{
		newNode = (salesanalysis_node_t*)malloc(sizeof(salesanalysis_node_t));
		if(!newNode)
		{
			printf("�ڴ����ʧ��!!\n");
			
		}
		newNode->data.play_id = pos->data.id;
		strcpy(newNode->data.name,pos->data.name);
		strcpy(newNode->data.area,pos->data.area);
		newNode->data.duration = pos->data.duration;
		newNode->data.start_date = pos->data.start_date;
		newNode->data.end_date	= pos->data.end_date;
		newNode->data.price = pos->data.price;
		newNode->data.sales = Schedule_Srv_StatRevByPlay(pos->data.id,&sold,&total);
		newNode->data.totaltickets = sold;
		List_AddTail(list,newNode);
		count++;
	}
		
	List_Destroy(playList,play_node_t);//�������� 
	 
	return count;
}

//�Ծ�Ժ��ӰƱ������
void SalesAnalysis_Srv_SortBySale(salesanalysis_list_t list){
	salesanalysis_node_t *p;
	salesanalysis_node_t *listLeft;
	if(list = NULL) {
		printf("�Բ����޷�ִ��");
	}
	else {
		list->prev->next = NULL;
		listLeft = NULL;
		list->next = list->prev = list;
		{
			if(listLeft == NULL) {
				printf("�Բ����޷�ִ��");
			}
			else {
				while(!listLeft) {
					listLeft = (salesanalysis_node_t *)malloc(sizeof(salesanalysis_node_t));
					p = listLeft;
					listLeft = listLeft->next;
					}
				}
		}
	}
}


