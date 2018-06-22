#include <stdio.h>

#include "Main_Menu.h"
#include "../Service/ticket.c"
#include "../Service/EntityKey.c"

#include "..\Common\common.c"
#include "../Common/play_print.c" 

#include "Studio_UI.c" 

#include "Play_UI.c"
#include "../Persistence/Play_Persist.c"
#include "Schedule_UI.c"
#include "../Service/Schedule.c"


#include "Queries_Menu.c"
#include "Account_UI.c"

#include "Sale_UI.c"
#include "SalesAnalysis_UI.c"

void Main_Menu(void) {
	char choice;
	do {
		system("cls");
		printf("\n==================================================================\n");
		printf("******************** ��ԺƱ�����ϵͳ ********************\n");
		printf("[S]�ݳ�������\n");
		printf("[P]��Ŀ����\n");
		printf("[T]��Ʊ����\n");
		printf("[R]��Ʊ\n");
		printf("[Q]��ѯ\n");
		printf("[n]���ݷ���\n");
		printf("[A]����ϵͳ�û�\n");
		printf("[E]�˳�ϵͳ.\n");
		printf("\n==================================================================\n");
		printf("Please input your choice:");
		fflush(stdin);
		choice = getchar();
		switch (choice) {
		case 'S':
		case 's':
			Studio_UI_MgtEntry();
			break;
		case 'P':
		case 'p':
			Play_UI_MgtEntry(0);
			break;
		case 'Q':
		case 'q':
			Queries_Menu();
			break;
		case 'T':
		case 't':
			Sale_UI_MgtEntry();
			break;
		case 'R':
		case 'r':
	//		Sale_UI_ReturnTicket();
			break;
		case 'N':
		case 'n':
			SalesAanalysis_UI_MgtEntry();
			break;
		case 'A':
		case 'a':
			Account_UI_MgtEntry();
			break;
		case 'E':
		case 'e':
			printf("ллʹ��!"); 
		}
	} while ('E' != choice && 'e' != choice);
}

