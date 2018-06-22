/*
* account.c
*
*  Created on: 2015��6��12��
*      Author: Administrator
*/
#include "Account.h"
#include "EntityKey.h"
#include "../Common/list.h"
#include "../Persistence/Account_Persist.c"
#include <string.h>
#include <stdlib.h>

extern account_t gl_CurUser;

//����ϵͳ��ʼ���˺�admin
void Account_Srv_InitSys() {
	int i, j;
if(Account_Perst_CheckAccFile()) return ;
	{
		account_t data_admin;
		printf("��ע���û�����[1]��ƱԱ[2]����[9]ϵͳ����Ա\n");
		scanf("%d", &data_admin.type); 
		printf("��ע���û��˺�\n");
		scanf("%s", data_admin.username); 
		printf("��ע���û�����\n");
		scanf("%s", data_admin.password); 
		data_admin.id = EntKey_Srv_CompNewKey("account");	
		Account_Srv_Add(&data_admin);
	}
}

//��֤��¼�˺��Ƿ��Ѵ��ڣ����ڣ������¼�û���Ϣ��ȫ�ֱ���gl_CurUser��return 1������return 0
inline int Account_Srv_Verify(char usrName[], char pwd[]) {
	account_t usr;
	if (Account_Perst_SelByName(usrName, &usr) != 0)
	{
		if (strcmp(pwd, usr.password) != 0)
		{
			return 0;
		}
		else
		{
			strcpy(gl_CurUser.username,usr.username);
			strcpy(gl_CurUser.password,usr.password);
			gl_CurUser.id=usr.id;
			gl_CurUser.type=usr.type;
			return 1;
		}
	}
	return 0;
}


//��֤�û����Ƿ���ڣ�����list�������ڣ����ض�Ӧ���ָ�룻���򣬷���null
account_node_t * Account_Srv_FindByUsrName(account_list_t list, char usrName[]) {
	account_list_t p;
	List_ForEach(list, p)
	{
		if(strcmp(p->data.username,usrName)==0)
		return p;
	}
	return NULL ;	
}

//���һ���û��˺ţ�ͨ������Account_Perst_Insert(data)����ʵ��
inline int Account_Srv_Add(const account_t *data) {
	if (Account_Perst_Insert(data) == 1)
		return 1;
	return 0;
}

//�޸�һ���û��˺ţ�ͨ������Account_Perst_Update(data)����ʵ��
inline int Account_Srv_Modify(const account_t *data) {
	if (Account_Perst_Update(data) == 1)
		return 1;
	return 0;
}

//ɾ��һ���û��˺ţ�ͨ������Account_Perst_DeleteByID(usrID)����ʵ��
inline int Account_Srv_DeleteByID(int usrID) {
	if (Account_Perst_DeleteByID(usrID) == 1)
		return 1;
	return 0;
}

//��ȡusrID��Ӧ���û��˺���Ϣ��ͨ������Account_Perst_SelectByID(usrID, buf)����ʵ��
inline int Account_Srv_FetchByID(int usrID, account_t *buf) {
	if(Account_Perst_SelectByID(usrID, buf))
	return 1;
	return 0;

}

//��ȡusrName��Ӧ���û��˺���Ϣ��ͨ������Account_Perst_SelByName(usrName, buf)����ʵ��
inline int Account_Srv_FetchByName(char usrName[], account_t *buf) {
	if(Account_Perst_SelByName(usrName, buf))
	return 1;
	return 0;
}

//��ȡ�����û��˺���Ϣ�����浽list�����У�ͨ������Account_Perst_SelectAll(list)����ʵ��
inline int Account_Srv_FetchAll(account_list_t list) {
	if(Account_Perst_SelectAll(list))
	return Account_Perst_SelectAll(list);
	else
	return 0;
	return 1;
}


