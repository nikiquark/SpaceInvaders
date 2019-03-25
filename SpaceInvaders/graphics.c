#include "graphics.h"
#include "objects.h"
#include "console.h"

char ships[2][4][4] = {
	{
	"asd",
	"asd",
	"asd",
	"asd"
	},{
	"•√π",
	"¶∆^",
	"°✓",
	"™®©"
	}
};
//!@#$%^&*()-_=+\"№%:?[]{}\|/;:',<.>/~☺¶§
void render_image(char image[30][150],list enemies, list bullets, ship SHIP) {
	int current_bullet_id = get_next_id(bullets, -1);
	while (current_bullet_id != -1) {
		bullet* current_bullet = get_comp(bullets, current_bullet_id);
		image[current_bullet->y][current_bullet->x] = '*';
		current_bullet_id = get_next_id(bullets, current_bullet_id);
	}
	int current_enemy_id = get_next_id(enemies, -1);
	while (current_enemy_id != -1) {
		ship* current_enemy = get_comp(enemies, current_enemy_id);
		for (int i = 0; i <current_enemy->size_x; i++) {
			for (int j = 0; j < current_enemy->size_y; j++) {
				image[j + current_enemy->y][i + current_enemy->x] = ships[current_enemy->type][j][i];
			}
		}
		current_enemy_id = get_next_id(enemies, current_enemy_id);
	}

}

void erase(char image[30][150]) {
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 150; j++) {
			if (image[i][j] != ' ')
				image[i][j] = ' ';
		}
	}
}

void copy(char image_from[30][150], char image_to[30][150]) {
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 150; j++) {
			if (image_from[i][j] != image_to[i][j])
				image_to[i][j] = image_from[i][j];
		}
	}
}

void out(char current_image[30][150], char next_image[30][150]) {
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 150; j++) {
			if (current_image[i][j] != next_image[i][j]) {
				con_gotoXY(j, i);
				con_outTxt("%c", next_image[i][j]);

			}
		}
	}
}