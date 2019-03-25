#include "objects.h"
#include "physics.h"
#include <Windows.h>

int WIDTH = 150;
int HEIGHT = 30;

void move_enemies(list list, int dir_x, int dir_y) {
	int current_id = get_next_id(list, -1);
	while (current_id != -1) {
		ship* current_enemy = get_comp(list, current_id);
		current_enemy->x += dir_x;
		current_enemy->y += dir_y;
		current_id = get_next_id(list, current_id);
	}
}

void move_bullets(list bullets, list enemies, ship SHIP) {
	int current_bullet_id = get_next_id(bullets, -1);
	while (current_bullet_id != -1) {
		bullet *current_bullet = (bullet*)get_comp(bullets, current_bullet_id);
		current_bullet->x += current_bullet->speed_x;
		current_bullet->y += current_bullet->speed_y;
		if (current_bullet->x < 0 || current_bullet->x > WIDTH - 1) {
			int id_for_pop = current_bullet_id;
			current_bullet_id = get_prev_id(bullets, current_bullet_id);
			list_pop(bullets, id_for_pop);
		}
		else {
			if (current_bullet->y < 0 || current_bullet->y > HEIGHT - 1) {
				current_bullet->speed_y *= -1;
				current_bullet->y += 2 * current_bullet->speed_y;
			}
			if (current_bullet->is_enemy) {
				if (current_bullet->x > SHIP.x && current_bullet->x < SHIP.x + SHIP.size_x &&
					current_bullet->y > SHIP.y && current_bullet->y < SHIP.y + SHIP.size_y) {
					//game_over();
					system("cls");
					Sleep(100000);
					//GAME OVER ÍÀÏÈÑÀÒÜ
				}
			}
			else {
				int current_enemy_id = get_next_id(enemies, -1);
				while (current_enemy_id != -1) {
					ship* current_enemy = (ship*)get_comp(enemies, current_enemy_id);
					if (current_bullet->x > current_enemy->x && current_bullet->x < current_enemy->x + current_enemy->size_x &&
						current_bullet->y > current_enemy->y && current_bullet->y < current_enemy->y + current_enemy->size_y) {
						int enemy_id_for_pop = current_enemy_id;
						int bullet_id_for_pop = current_bullet_id;
						current_enemy_id = get_prev_id(bullets, current_enemy_id);
						current_bullet_id = get_prev_id(enemies, current_enemy_id);
						list_pop(bullets, bullet_id_for_pop);
						list_pop(enemies, enemy_id_for_pop);
						break;
					}
					current_enemy_id = get_next_id(enemies, current_enemy_id);
				}
			}
		}
		current_bullet_id = get_next_id(bullets, current_bullet_id);
	}
}

void fire(list bullets, list enemies) {
	int current_enemy_id = get_next_id(enemies, -1);
	while (current_enemy_id != -1) {
		ship* current_enemy = (ship*)get_comp(enemies, current_enemy_id);
		//add_enemy_bullet(bullets, current_enemy);
		add_bullet(bullets, current_enemy->x-1, current_enemy->y, -1, rand() % 3 - 1, 1);
		add_bullet(bullets, current_enemy->x-1, current_enemy->y + current_enemy->size_y-1, -1, rand() % 3 - 1, 1);
		current_enemy_id = get_next_id(enemies, current_enemy_id);
	}
}