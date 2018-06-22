#include <stdio.h>
#include <stdlib.h>

#include "Queries_Menu.h"
#include "Schedule_UI.h"
#include "Studio_UI.h"
#include "Play_UI.h"

void Queries_Menu(void){
	char choice;
	do {
		printf("\n==================================================================\n");
		printf("************************Information Queries*************************\n");
		printf("[S]�ݳ�����ѯ\n");
		printf("[P]��Ŀ��ѯ\n");
		printf("[T]Ʊ���ѯ(δ���)\n");
		printf("[C]�ݳ��ƻ���ѯ\n");
		printf("[R]�˳�.\n");
		printf("\n==================================================================\n");
		printf("Please input your choice:");
		fflush(stdin);
		choice = getchar();
		switch (choice) {
		case 'S':
		case 's':
	//		Studio_UI_query();
			break;
		case 'P':
		case 'p':
			Play_UI_MgtEntry(1);
			break;
		case 'T':
		case 't': 
		//Ticket_UI_query;
			break;
		case 'C':
		case 'c':
		//	Schedule_UI_ListAll();
			break;
		}
	} while ('R' != choice && 'r' != choice);
	}
