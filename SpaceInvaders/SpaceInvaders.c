#include "objects.h"
#include "physics.h"
#include "graphics.h"
#include <malloc.h>
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <sys/timeb.h>
#define RELOAD_TIME 1500
char current_image[30][150], next_image[30][150];

unsigned long long ft(struct timeb *a) {
	return (*a).time * 1000 + (*a).millitm;
}

int main()
{
	struct timeb t;
	ftime(&t);
	struct timeb last_update = t, last_fire = t, last_bot_fire = t;
	system("mode con cols=160 lines=35");
	con_init();
	con_hideCursor();
	srand(time(NULL));
	list enemies = (list)malloc(sizeof(list));
	list bullets = (list)malloc(sizeof(list));
	ship SHIP = {0,0,0,0,0};
	init_list(enemies);
	init_list(bullets);
	add_enemy(enemies, 100, 1, 3, 4, 1);
	add_enemy(enemies, 100, 7, 3, 4, 1);
	add_enemy(enemies, 100, 14, 3, 4, 1);
	move_enemies(enemies, 1, 1);
	move_enemies(enemies, 1, 1);
	move_enemies(enemies, 1, 1);
	fire(bullets, enemies);
	erase(current_image);
	erase(next_image);
	render_image(next_image, enemies, bullets, SHIP);
	while (1 == 1) {
		ftime(&t);
		move_bullets(bullets, enemies, (ship) { 1, 1, 1, 1, 1 });
		if (ft(&t) - ft(&last_bot_fire) > RELOAD_TIME) {
			last_bot_fire = t;
			fire(bullets, enemies);
		}
		
		out(current_image, next_image);
		copy(next_image, current_image);
		erase(next_image);
		render_image(next_image, enemies, bullets, SHIP);
		Sleep(100);
	}
	return 0;
}
