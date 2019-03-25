#pragma once


typedef struct _bullet {
	int x, y, speed_x, speed_y, is_enemy;
} bullet;

typedef struct _ship {
	int x, y, size_x, size_y, type;
} ship;

typedef struct _list *list;

void init_list(list list);

void list_pop(list list, int id);

void* get_comp(list list, int id);

int get_next_id(list list, int id);

int get_prev_id(list list, int id);

int last_id(list list);

void add_bullet(list list, int x, int y, int speed_x, int speed_y, int is_enemy);

void add_enemy_bullet(list list, ship* enemy);

void add_enemy(list list, int x, int y, int size_x, int size_y, int type);