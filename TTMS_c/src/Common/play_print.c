int play_print(play_t p) {
	printf("\t==========================================================\t\n");
 	printf("\t|                 ******��Ŀ��Ϣ******                   |\t\n");
 	printf("\t==========================================================\n");
	printf("\t|   1.��ĿID:        %20d                |\t\n",p.id);
	printf("\t|   2.��Ŀ����:      %20s                |\t\n",p.name); 
	printf("\t|   3.��Ŀ����:      %20d                |\t\n",p.type);
	printf("\t|   4.��Ŀ��Ʒ����:  %20s                |\t\n",p.area);
	printf("\t|   5.��Ŀ�ȼ�:      %20d                |\t\n",p.rating);
	printf("\t|   6.��Ŀʱ��(����):%20d                |\t\n",p.duration);
	printf("\t|   7.��ӳ����:      %10d%4d%4d                |\t\n",p.start_date.year,p.start_date.month,p.start_date.day);
	printf("\t|   8.��������:      %10d%4d%4d                |\t\n",p.end_date.year,p.end_date.month,p.end_date.day);
	printf("\t|   9.Ʊ��:          %20d                |\t\n",p.price);
	    	     	
 	printf("\t|========================================================|\t\n");
 }
