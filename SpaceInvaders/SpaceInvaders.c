#include "objects.h"
#include "physics.h"
#include "graphics.h"
#include <malloc.h>
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <sys/timeb.h>
#define RELOAD_TIME 2500
#define UPDATE_TIME 600

char current_image[30][150], next_image[30][150];

unsigned long long ft(struct timeb *a) {
	return (*a).time * 1000 + (*a).millitm;
}

int main()
{
	int dx = 0, dy = 2, q = 1, w = 1;
	int quit = 0;
	struct timeb t;
	ftime(&t);
	struct timeb last_update = t, last_fire = t, last_bot_fire = t;
	system("mode con cols=160 lines=35");
	con_init();
	con_hideCursor();
	srand(time(NULL));
	list enemies = (list)malloc(sizeof(list));
	list bullets = (list)malloc(sizeof(list));
	ship SHIP = { 2, 10, 3, 4 ,0 };
	init_list(enemies);
	init_list(bullets);
	add_enemy(enemies, 100, 4, 3, 4, 1);
	add_enemy(enemies, 100, 13, 3, 4, 1);
	add_enemy(enemies, 100, 22, 3, 4, 1);
	fire(bullets, enemies);
	erase(current_image);
	erase(next_image);
	render_image(next_image, enemies, bullets, SHIP);
	Sleep(1000);
	while (!quit) {
		ftime(&t);
		move_bullets(bullets, enemies, SHIP);
		if (ft(&t) - ft(&last_bot_fire) > RELOAD_TIME) {
			last_bot_fire = t;
			fire(bullets, enemies);
		}
		if (ft(&t) - ft(&last_update) > UPDATE_TIME) {
			move_enemies(enemies, q, w);
			dx += q; dy += w;
			if (dx < 0 || dx > 5) q *= -1;
			if (dy < 0 || dy > 5) w *= -1;
		}
		if (con_keyPressed()) {
			if (process_key(&SHIP)) {
				quit = 1;
			}
		}
		out(current_image, next_image);
		copy(next_image, current_image);
		erase(next_image);
		render_image(next_image, enemies, bullets, SHIP);
		Sleep(100);
	}
	return 0;
}
