﻿#include "graphics.h"
#include "objects.h"
#include "console.h"
#define CHAR_BORDER '#'
#define CHAR_FIELD  ' '
#define CHAR_BULLET '*'
#define COLOR_BORDER 1
#define COLOR_FIELD  2
#define COLOR_BULLET  3
#define COLOR_SHIP 4
char ships[2][4][4] = {
	{
	"==+",
	"OO ",
	"OO ",
	"==+"
	},{
	"}=\\",
	" []",
	" []",
	"}=/"
	}
};
//!@#$%^&*()-_=+\"№%:?[]{}\|/;:',<.>/~☺¶§

void init_colors() {
	con_initPair(COLOR_BORDER, CON_COLOR_BLACK, CON_COLOR_BLUE);
	con_initPair(COLOR_FIELD, CON_COLOR_BLACK, CON_COLOR_BLACK);
	con_initPair(COLOR_BULLET, CON_COLOR_BLUE, CON_COLOR_BLACK);
	con_initPair(COLOR_SHIP, CON_COLOR_RED, CON_COLOR_BLACK);
}

void con_charAt(int ch, int color, int x, int y) {
	con_gotoXY(x, y);
	con_setColor(color);
	con_outTxt("%c", ch);
}

void render_image(char image[30][150], list enemies, list bullets, ship SHIP) {
	int current_bullet_id = get_next_id(bullets, -1);
	while (current_bullet_id != -1) {
		bullet* current_bullet = get_comp(bullets, current_bullet_id);
		image[current_bullet->y][current_bullet->x] = '*';
		current_bullet_id = get_next_id(bullets, current_bullet_id);
	}
	int current_enemy_id = get_next_id(enemies, -1);
	while (current_enemy_id != -1) {
		ship* current_enemy = get_comp(enemies, current_enemy_id);
		for (int i = 0; i < current_enemy->size_x; i++) {
			for (int j = 0; j < current_enemy->size_y; j++) {
				image[j + current_enemy->y][i + current_enemy->x] = ships[current_enemy->type][j][i];
			}
		}
		current_enemy_id = get_next_id(enemies, current_enemy_id);
	}
	for (int i = 0; i < SHIP.size_x; i++) {
		for (int j = 0; j < SHIP.size_y; j++) {
			image[j + SHIP.y][i + SHIP.x] = ships[SHIP.type][j][i];
		}
	}
	for (int i = 0; i < 30; i++)
		for (int j = 0; j < 120; j++)
			if (i == 0 || i == 29 || j == 0 || j == 119)
				if (image[i][j] != '#')
					image[i][j] = '#';
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
	int color;
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 150; j++) {
			if (current_image[i][j] != next_image[i][j]) {
				//con_gotoXY(j + FIELD_Y, i + FIELD_X);
				//con_outTxt("%c", next_image[i][j]);
				switch (next_image[i][j])
				{
				case '#':
					color = COLOR_BORDER;
					break;
				case ' ':
					color = COLOR_FIELD;
					break;
				case '*':
					color = COLOR_BULLET;
					break;
				default:
					color = COLOR_SHIP;
					break;
				}
				con_charAt(next_image[i][j], color, j + FIELD_Y, i + FIELD_X);

			}
		}
	}
}

void init() {
	con_clearScr();
	con_gotoXY(20, 2);
	con_outTxt("Use arrows to move, use C to exit.");

	for (int i = 0; i < 120; ++i) {
		for (int j = 0; j < 30; ++j) {
			int ch;
			int color;
			if (i == 0 || i == 120 - 1 || j == 0 || j == 30 - 1) {
				ch = CHAR_BORDER;
				color = COLOR_BORDER;
			}
			else {
				ch = CHAR_FIELD;
				color = COLOR_FIELD;
			}
			con_charAt(ch, color, FIELD_Y + i, FIELD_X + j);
		}
	}
}