#include "objects.h"

int main()
{
	list_of_bullet a = (list_of_bullet*)malloc(sizeof(list_of_bullet));
	init_list_of_bullet(a);
	add_bullet(a, 0, (bullet){ 1,2,3,4,5 });
	return 0;
}
