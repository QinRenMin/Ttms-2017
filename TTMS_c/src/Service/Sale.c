#include "sale.h" 
#include "../Persistence/Sale_Persist.c"
#include "../Persistence/Query_Persist.h"
ticket_t   new;  
//����Ʊ����Ϣ���뵽��������Ϣ
inline int Sale_Srv_Add(const sale_t *data) {
	return Sale_Perst_Insert(data);
}

//ɾ����������Ϣj
inline int Sale_Srv_DeleteByID(int saleID) {
	return Sale_Perst_DeleteByID(saleID);
}

/*
//ͨ��uid��ѯ����
inline int Sale_Srv_SelectByUid(char *queryuid, Sale_list_t head) {
	return Sale_Infor_By_Uid(queryuid, head);
}

//����ʱ���ѯ����
inline int Sale_Srv_selectByTime(char querytime[][30], Sale_list_t head) {
	return Sale_Infor_By_Time(querytime, head);
}
*/
