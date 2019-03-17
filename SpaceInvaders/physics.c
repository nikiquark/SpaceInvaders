#include "objects.h"
#include "physics.h"
#include <Windows.h>

int MAX_ID = 10000;
int WIDTH = 150;
int HEIGHT = 30;

void move_enemies(list_of_enemy list, int dir_x, int dir_y) {
	int current_id = get_next_enemy_id(list, -1);
	while (current_id != -1) {
		ship current_enemy = get_enemy(list, current_id);
		current_enemy.x += dir_x;
		current_enemy.y += dir_y;
		change_enemy(list, current_id, current_enemy);
		current_id = get_next_enemy_id(list, current_id);
	}
}

void move_bullets(list_of_bullet bullets, list_of_enemy enemies, ship SHIP) {
	int current_bullet_id = get_next_bullet_id(bullets, -1);
	while (current_bullet_id != -1) {
		bullet current_bullet = get_bullet(bullets, current_bullet_id);
		current_bullet.x += current_bullet.speed_x;
		current_bullet.y += current_bullet.speed_y;
		change_bullet(bullets, current_bullet_id, 
			(bullet) 
				{ current_bullet.x,
				current_bullet.y,
				current_bullet.speed_x,
				current_bullet.speed_y,
				current_bullet.is_enemy });
		if (current_bullet.x < 0 || current_bullet.x > WIDTH - 1) {
			current_bullet_id = get_prev_bullet_id(bullets, current_bullet_id);
			remove_bullet(bullets, get_next_bullet_id(bullets, current_bullet_id));
		}
		else {
			if (current_bullet.y < 0 || current_bullet.y > HEIGHT - 1) {
				current_bullet.speed_y *= -1;
				current_bullet.y += 2 * current_bullet.speed_y;
				change_bullet(bullets, current_bullet_id,
					(bullet)
						{
							current_bullet.x,
							current_bullet.y,
							current_bullet.speed_x,
							current_bullet.speed_y,
							current_bullet.is_enemy
						});
			}
			if (current_bullet.is_enemy) {
				if (current_bullet.x > SHIP.x && current_bullet.x < SHIP.x + SHIP.size_x &&
					current_bullet.y > SHIP.y && current_bullet.y < SHIP.y + SHIP.size_y) {
					//game_over();
					system("cls");
					Sleep(100000);
					//GAME OVER ÍÀÏÈÑÀÒÜ
				}
			}
			else {
				int current_enemy_id = get_next_enemy_id(enemies, -1);
				while (current_enemy_id != -1) {
					ship current_enemy = get_enemy(enemies, current_enemy_id);
					if (current_bullet.x > current_enemy.x && current_bullet.x < current_enemy.x + current_enemy.size_x &&
						current_bullet.y > current_enemy.y && current_bullet.y < current_enemy.y + current_enemy.size_y) {
						current_enemy_id = get_prev_bullet_id(bullets, current_enemy_id);
						current_bullet_id = get_prev_enemy_id(enemies, current_enemy_id);
						remove_bullet(bullets, get_next_bullet_id(bullets, current_bullet_id));
						remove_enemy(enemies, get_next_enemy_id(enemies, current_enemy_id));
						break;
					}
					current_enemy_id = get_next_enemy_id(enemies, current_enemy_id);
				}
			}
		}
		current_bullet_id = get_next_bullet_id(bullets, current_bullet_id);
	}
}

void fire(list_of_bullet bullets, list_of_enemy enemies) {
	int current_enemy_id = get_next_enemy_id(enemies, -1);
	while (current_enemy_id != -1) {
		ship current_enemy = get_enemy(enemies, current_enemy_id);
		add_bullet(bullets, (last_bullet_id(bullets) + 1) % MAX_ID, (bullet){current_enemy.x, current_enemy.y, -1, rand() % 3 - 1, 1});
		current_enemy_id = get_next_enemy_id(enemies, current_enemy_id);
	}
}