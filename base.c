#include <stdio.h>

#include "Header.h"

int main()
{
	key();
	int operation;
	for (;;)
	{
		printf("Enter:\n\"1\" for adding new record\n"
			"\"2\" for deleting record\n"
			"\"3\" for viewing records\n"
			"\"4\" for updating record\n"
			"\"5\" for viewing all employees accepted after the entered date\n"
			"\"6\" for viewing all employees whoose full salary is in the given range\n"
			"\"0\" for ending session (data will be saved)\n");

		scanf_s("%d", &operation);
		switch (operation)
		{
		case 1:new_rec(); break;
		case 2:delete_rec(); break;
		case 3:all_recs(); break;
		case 4:update(); break;
		case 5:after_date(); break;
		case 6:salary(); break;
		case 0: return 0;
		default: printf("Wrong operation, try again\n"); break;
		}
	}
}
