/*
 * salesanalysisPersist.c
 *
 *  Created on: 2015年5月8日
 *      Author: Administrator
 */

#include "../Persistence/EntityKey_Persist.h"
#include "../Service/play.h"
#include "../Service/Sale.h"
#include "../Persistence/Sale_Persist.h"
#include "../Service/salesanalysis.h"
#include "../Common/list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

//static const char PLAY_DATA_FILE[] = "play.dat";
//static const char SALE_DATA_FILE[] = "sale.dat";
static const char SALESANALYSIS_DATA_FILE[] = "salesanalysis.dat";

//将一条salesanalysis记录（*data）写入salesanalysis.dat文件；成功return 1，否则return 0
int Salesanalysis_Perst_Insert(const salesanalysis_t *data) {
	assert(NULL!=data);
	FILE *fp = fopen(SALESANALYSIS_DATA_FILE, "ab");
	int rtn = 0;
	if (NULL == fp) {
		printf("Cannot open file %s!\n", SALESANALYSIS_DATA_FILE);
		return 0;
	}

	rtn = fwrite(data, sizeof(salesanalysis_t), 1, fp);

	fclose(fp);
	return rtn;

}

//遍历读salesanalysis.dat文件建立销售分析（salesanalysis）链表
int SalesAnalysis_Perst_SelectAll(salesanalysis_list_t list) {

    salesanalysis_node_t *newNode;
	salesanalysis_t data;
	int recCount = 0;

	assert(NULL!=list);

	List_Free(list, salesanalysis_node_t);

	FILE *fp = fopen(SALESANALYSIS_DATA_FILE, "rb");
	if (NULL == fp) { //文件不存在
		return 0;
	}

	while (!feof(fp)) {
		if (fread(&data, sizeof(salesanalysis_t), 1, fp)) {
			newNode = (salesanalysis_node_t*) malloc(sizeof(salesanalysis_node_t));
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

//遍历读Sale.dat文件建立list（sale_list_t） 链表，返回链表list长度
int Sale_Perst_SelectAll(sale_list_t list) {
	int count = 0;
	sale_t data;
	sale_node_t *newNode;
	FILE *fp = fopen("sale.dat","rb");
	if(fp == NULL) {
		printf("对不起，打开文件失败");
		return 0;
	}
	while(!feof(fp)) {
		if(fread(&data, sizeof(sale_t), 1, fp))
		{
			newNode = (sale_node_t*)malloc(sizeof(sale_node_t));
			if(!newNode) {
				printf("申请内存失败");
				return 0;
			}
			List_AddTail(list, newNode);
			count++;
		}			
	}
	return count;

}

