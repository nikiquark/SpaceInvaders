#include "objects.h"
#include "physics.h"
#include <malloc.h>
#include <stdio.h>

int main()
{
	srand(time(NULL));
	list enemies = (list)malloc(sizeof(list));
	list bullets = (list)malloc(sizeof(list));
	init_list(enemies);
	init_list(bullets);
	add_enemy(enemies, 100, 1, 1, 1, 1);
	add_enemy(enemies, 100, 7, 1, 1, 1);
	add_enemy(enemies, 100, 14, 1, 1, 1);
	move_enemies(enemies, 1, 1);
	move_enemies(enemies, 1, 1);
	move_enemies(enemies, 1, 1);
	fire(bullets, enemies);
	while (1 == 1) {
		move_bullets(bullets, enemies, (ship) { 1, 1, 1, 1, 1 });
		bullet* bullet1 = (bullet*)get_comp(bullets, 0);
		bullet* bullet2 = (bullet*)get_comp(bullets, 1);
		bullet* bullet3 = (bullet*)get_comp(bullets, 2);
		printf("%d %d\n%d %d\n%d %d\n\n", bullet1->x, bullet1->y, bullet2->x, bullet2->y, bullet3->x, bullet3->y);
	}
	return 0;
}
