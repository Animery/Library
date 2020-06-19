
#include "Library.h"
#include "Interface.h"


int main()
{
	Library obj;
	obj.openData();
	bool check_select = true;

	do
	{
		unsigned int menu_count = menu();
		check_select = select(obj, menu_count);

	} while (check_select);
	
}