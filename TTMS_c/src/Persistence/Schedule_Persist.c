/*
* File name:  Schedule_Persist.c
* File ID:	  TTMS_SSF_Schedule_Perst_Sour
* Author:     Huang Ru
* Version:    V1.0
* Date: 	  2015-04-25
*/


#include "Schedule_Persist.h"
#include "../Service/schedule.h"
#include "../Common/list.h"
#include "../Service/ticket.h"
#include "../View/Ticket_UI.h"
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <assert.h>


/*
 * Function:    Schedule_Perst_Insert
 * Function ID:	TTMS_SCU_Schedule_Perst_Insert
 * Description: ���ݳ��ƻ���Ϣ�ļ�ĩβд��һ���ݳ��ƻ���Ϣ
 * Input:       �������ļ����ݳ��ƻ���Ϣ����
 * Output:      ���ļ�ʧ�ܵ���Ϣ
 * Return:      д���ļ��ļ�¼��
 */
int Schedule_Perst_Insert(const schedule_t *data)
{
	FILE *fp;
	int rtn=0;
	fp=fopen("Schedule.dat","ab");
	if(fp==NULL)
	{
		printf("\n���ļ�ʧ��\n");
		return 0;
	}
	rtn=fwrite(data,sizeof(schedule_t),1,fp);
	fclose(fp);
	return rtn;
}

/*
 * Function:    Schedule_Perst_Update
 * Function ID:	TTMS_SCU_Schedule_Perst_Mod
 * Description: �����ݳ��ƻ�ID�Ÿ����ļ��е��ݳ��ƻ���Ϣ
 * Input:       �����ļ��и��µ��ݳ��ƻ���Ϣ����
 * Output:      ���ļ�ʧ�ܵ���Ϣ
 * Return:      ���µ��ݳ��ƻ���Ϣ����0��ʾδ�ҵ���1��ʾ�ҵ�������
 */

int Schedule_Perst_Update(const schedule_t *data) {
	
	assert(data != NULL);
	int found = 0;
	schedule_t buf;
	
	FILE *fp = fopen("Schedule.dat","rb+");
	if(fp == NULL) {
		printf("�Բ��𣬴��ļ�ʧ��\n");
		return 0;
	}
	else {
		while(!(fp))                //�ж��Ƿ�����ļ�ĩβ 
		{
			if(fread(&data,sizeof(schedule_t),1,fp)) {
				if(buf.id == data->id) {
					fseek(fp, -sizeof(schedule_t), SEEK_CUR);
				    fwrite(data, sizeof(schedule_t), 1, fp);
				    found = 1;
				    break;
				}
			}
		}
	}	
   return found;
}
/*
 * Function:    Schedule_Perst_DeleteByID
 * Function ID:	TTMS_SCU_Schedule_Perst_DelByID
 * Description: �����ݳ��ƻ�ID��ɾ���ݳ��ƻ�����Ϣ
 * Input:       ��ɾ�����ݳ��ƻ�ID��
 * Output:      ���ļ�ʧ�ܵ���Ϣ
 * Return:      0��ʾɾ��ʧ�ܣ�1��ʾɾ���ɹ�
 */

int Schedule_Perst_DeleteByID(int ID) {
	int found = 0;
	//��ԭʼ�ļ���������Ȼ���ȡ��������д�뵽�����ļ��У�����Ҫɾ����ʵ����˵���
	schedule_t buf;
	FILE *fpSour, *fpTarg;//ԭ�ļ�����ʱ�ļ� 
	//��ԭʼ�����ļ�������
	if(rename("Schedule.dat", "ScheduleTmp.dat")<0){
		printf("�Բ��𣬲��ܴ� %s!\n", "Schedule.dat");
		return 0;
	}
	
	else
	{
		fpSour = fopen("ScheduleTmp.dat", "rb");
		if (NULL == fpSour ){
			printf("�Բ��𣬲��ܴ� %s!\n", "Schedule.dat");
			return 0;
		}
		fpTarg = fopen("Schedule.dat", "wb");
		if ( NULL == fpTarg ) {
			printf("�Բ��𣬲��ܴ� %s!\n", "ScheduleTmp.dat");
			return 0;
		}
		while (!feof(fpSour)) {
			if (fread(&buf, sizeof(schedule_t), 1, fpSour)) {
				if (ID == buf.id) {
					found = 1;
					continue;
				}
				fwrite(&buf, sizeof(schedule_t), 1, fpTarg);
			}
		}
		fclose(fpTarg);
		fclose(fpSour);
	}
   	//ɾ����ʱ�ļ�
	remove("ScheduleTmp.dat");
	return found;
}
/*
 * Function:    Schedule_Perst_SelectByID
 * Function ID:	TTMS_SCU_Schedule_Perst_SelByID
 * Description: �����ݳ��ƻ�ID��ɾ���ݳ��ƻ�����Ϣ
 * Input:       �����ҵ��ݳ��ƻ�ID�ţ�������ҽ�����ڴ�ĵ�ַ
 * Output:      ��
 * Return:      0��ʾδ�ҵ���1��ʾ�ҵ���
 */
int Schedule_Perst_SelectByID(int ID, schedule_t *buf){
	assert(NULL!=buf);

	FILE *fp = fopen("Schedule.dat", "rb");
	if (NULL == fp) {
		return 0;
	}
	schedule_t data;
	int found = 0;
	while (!feof(fp)) {
		if (fread(&data, sizeof(schedule_t), 1, fp)) {
			if (ID == data.id) {
				*buf = data;
				found = 1;
				break;
			};

		}
	}
	fclose(fp);
	return found;
}

/*
 * Function:    Schedule_Perst_SelectAll
 * Function ID:	TTMS_SCU_Schedule_Perst_SelAll
 * Description: �������ݳ��ƻ���Ϣ������һ������
 * Input:       listΪ�ݳ��ƻ���Ϣ�����ͷָ��
 * Output:      ��ʾ��������ʱ������ռ�ʧ��
 * Return:      ���ز��ҵ��ļ�¼��Ŀ
 */
int Schedule_Perst_SelectAll(schedule_list_t list){
	schedule_node_t *newNode;
	schedule_t data;
	int recCount = 0;

	List_Free(list, schedule_node_t);

	FILE *fp = fopen("Schedule.dat", "rb");
	if (NULL == fp) { //�ļ�������
		return 0;
	}

	while (!feof(fp)) {
		if (fread(&data, sizeof(schedule_t), 1, fp)) {
			newNode = (schedule_node_t*) malloc(sizeof(schedule_node_t));
			if (!newNode) {
				printf(
						"Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
				break;
			}
			newNode->data = data;
			List_AddTail(list, newNode);
			recCount++;
		}
	}
	fclose(fp);
	return recCount;
}

/*
 * Function:    Schedule_Perst_SelectByPlay
 * Function ID:	TTMS_SCU_Schedule_Perst_SelByPlay
 * Description: ��ͬ���Ŀ���ݳ��ƻ���Ϣ��������������һ������
 * Input:       listΪ�����������ݳ��ƻ���Ϣ�����ͷָ�룬��Ŀ��ID��
 * Output:      ��ʾ��������ʱ������ռ�ʧ��
 * Return:      ���ز��ҵ��ļ�¼��Ŀ
 */
int Schedule_Perst_SelectByPlay(schedule_list_t list, int play_id){
	FILE *fp;
	schedule_t data;
	schedule_list_t newNode;
	int recCount=0;
	fp=fopen("Schedule.dat","rb");
	
	List_Free(list,schedule_node_t);
	
	while(!feof(fp)){
		if (fread(&data, sizeof(schedule_t), 1, fp)) {
			newNode = (schedule_node_t*) malloc(sizeof(schedule_node_t));
			if (!newNode) {
				printf(
						"Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
				break;
			}
			newNode->data = data;
			List_AddTail(list, newNode);
			recCount++;
		}
	}
	fclose(fp);
	return recCount;
}
