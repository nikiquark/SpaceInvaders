#pragma once

typedef struct _bullet {
	int x, y, speed_x, speed_y, is_enemy;
} bullet;

typedef struct _ship {
	int x, y, size_x, size_y, type;
} ship;

typedef struct _list_of_bullet *list_of_bullet;
typedef struct _list_of_enemy *list_of_enemy;

void init_list_of_enemy(list_of_enemy list);
void init_list_of_bullet(list_of_bullet list);

void add_enemy(list_of_enemy list, int id, ship enemy);
void add_bullet(list_of_bullet list, int id, bullet bullet);

void remove_enemy(list_of_enemy list, int id);
void remove_bullet(list_of_bullet list, int id);

ship get_enemy(list_of_enemy list, int id);
bullet get_bullet(list_of_bullet list, int id);

int get_next_bullet_id(list_of_bullet list, int id);
int get_next_enemy_id(list_of_enemy list, int id);

void change_enemy(list_of_enemy list, int id, ship enemy);
void change_bullet(list_of_bullet list, int id, bullet bullet); 

int last_bullet_id(list_of_bullet list);
int last_enemy_id(list_of_enemy list);

int get_prev_bullet_id(list_of_bullet list, int id);
int get_prev_enemy_id(list_of_enemy list, int id);

//void delete_list_of_bullet(list_of_bullet list);
//void delete_list_of_enemy(list_of_enemy list);