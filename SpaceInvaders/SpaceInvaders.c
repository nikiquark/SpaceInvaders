#include "objects.h"
#include "physics.h"
#include <malloc.h>
#include <stdio.h>

extern int HEIGTH;
extern int WIDTH;
extern int MAX_ID;

int main()
{
	srand(time(NULL));
	list_of_enemy a = (list_of_enemy*)malloc(sizeof(list_of_enemy));
	list_of_bullet b = (list_of_bullet*)malloc(sizeof(list_of_bullet));
	init_list_of_enemy(a);
	init_list_of_bullet(b);
	add_enemy(a, 0, (ship) { 100, 0, 0, 0, 0 });
	add_enemy(a, 1, (ship) { 2, 0, 0, 0, 0 });
	add_enemy(a, 2, (ship) { 100, 20, 0, 0, 0 });
	move_enemies(a, 1, 1);
	move_enemies(a, 1, 1);
	fire(b, a);
	while (1 == 1) {
		move_bullets(b, a, (ship) { 10, 10, 0, 0, 0 });
	}

	return 0;		 
}
