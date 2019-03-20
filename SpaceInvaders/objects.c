#include "objects.h"
#include <malloc.h>
#include <stdio.h>
#define MAX_ID 10000
typedef struct _comp_of_list {
	void* content;
	int id;
	struct _comp_of_list *next;
	struct _comp_of_list *prev;
} comp_of_list;

typedef struct _list {
	comp_of_list *tail;
} *list;

void init_list(list list) {
	comp_of_list *last = (comp_of_list*)malloc(sizeof(comp_of_list));
	if (last == NULL) {
		fprintf(stderr, "failed to allocate memory.\n");
		exit(-1);
	}
	last->id = -1;
	last->next = last;
	last->prev = last;
	list->tail = last;
}

void list_push(list list, int id, void* content) {
	comp_of_list *new_comp = (comp_of_list*)malloc(sizeof(comp_of_list));
	if (new_comp == NULL) {
		fprintf(stderr, "failed to allocate memory.\n");
		exit(-1);
	}
	new_comp->content = content;
	new_comp->id = id;
	new_comp->prev = list->tail->prev;
	new_comp->next = list->tail;
	list->tail->prev->next = new_comp;
	list->tail->prev = new_comp;
}

void list_pop(list list, int id) {
	comp_of_list* current_comp = list->tail->next;
	while (current_comp->id != id) {
		current_comp = current_comp->next;
	}
	current_comp->next->prev = current_comp->prev;
	current_comp->prev->next = current_comp->next;
	free(current_comp->content);
	free(current_comp);
}

void* get_comp(list list, int id) {
	comp_of_list* current_comp = list->tail->next;
	while (current_comp->id != id) {
		current_comp = current_comp->next;
	}
	return current_comp->content;
}

int get_next_id(list list, int id) {
	comp_of_list* current_comp = list->tail->next;
	while (current_comp->id != id) {
		current_comp = current_comp->next;
	}
	return current_comp->next->id;
}

int get_prev_id(list list, int id) {
	comp_of_list* current_comp = list->tail->next;
	while (current_comp->id != id) {
		current_comp = current_comp->next;
	}
	return current_comp->prev->id;
}

int last_id(list list) {
	return list->tail->prev->id;
}

void add_bullet(list list, int x, int y, int speed_x, int speed_y, int is_enemy) {
	bullet* bull = (bullet*)malloc(sizeof(bullet));
	bull->x = x;
	bull->y = y;
	bull->speed_x = speed_x;
	bull->speed_y = speed_y;
	bull->is_enemy = is_enemy;
	list_push(list, (last_id(list) + 1) % MAX_ID, bull);
}

void add_enemy_bullet(list list, ship* enemy) {
	add_bullet(list, enemy->x, enemy->y, -1, rand() % 3 - 1, 1);
}

void add_enemy(list list, int x, int y, int size_x, int size_y, int type) {
	ship* enemy = (ship*)malloc(sizeof(ship));
	enemy->x = x;
	enemy->y = y;
	enemy->size_x = size_x;
	enemy->size_y = size_y;
	enemy->type = type;
	list_push(list, (last_id(list) + 1) % MAX_ID, enemy);
}

//typedef struct _comp_of_bullets {
//	bullet bullet;
//	int id;
//	struct _comp_of_bullets *next;
//	struct _comp_of_bullets *prev;
//} comp_of_bullets;
//
//typedef struct _comp_of_enemies {
//	ship enemy;
//	int id;
//	struct _comp_of_enemies *next;
//	struct _comp_of_enemies *prev;
//} comp_of_enemies;
//
//typedef struct _list_of_bullet {
//	comp_of_bullets *first;
//	comp_of_bullets *tail;
//} *list_of_bullet;
//
//typedef struct _list_of_enemy {
//	comp_of_enemies *first;
//	comp_of_enemies *tail;
//} *list_of_enemy;
//
//void init_list_of_enemy(list_of_enemy list) {
//	comp_of_enemies *last = (comp_of_enemies*)malloc(sizeof(comp_of_enemies));
//	if (last == NULL) {
//		fprintf(stderr, "failed to allocate memory.\n");
//		exit(-1);
//	}
//	last->id = -1;
//	last->next = last;
//	last->prev = last;
//	list->first = last;
//	list->tail = last;
//}
//
//void init_list_of_bullet(list_of_bullet list) {
//	comp_of_bullets *last = (comp_of_bullets*)malloc(sizeof(comp_of_bullets));
//	last->id = -1;
//	if (last == NULL) {
//		fprintf(stderr, "failed to allocate memory.\n");
//		exit(-1);
//	}
//	last->next = last;
//	last->prev = last;
//	list->first = last;
//	list->tail = last;
//}
//
//
//void add_enemy(list_of_enemy list, int id, ship enemy) {
//	comp_of_enemies *new_enemy = (comp_of_enemies*)malloc(sizeof(comp_of_enemies));
//	if (new_enemy == NULL) {
//		fprintf(stderr, "failed to allocate memory.\n");
//		exit(-1);
//	}
//	new_enemy->enemy = enemy;
//	new_enemy->id = id;
//	new_enemy->prev = list->tail->prev;
//	new_enemy->next = list->tail;
//	list->tail->prev->next = new_enemy;
//	list->tail->prev = new_enemy;
//}
//
//void add_bullet(list_of_bullet list, int id, bullet bullet) {
//	comp_of_bullets *new_bullet = (comp_of_bullets*)malloc(sizeof(comp_of_bullets));
//	if (new_bullet == NULL) {
//		fprintf(stderr, "failed to allocate memory.\n");
//		exit(-1);
//	}
//	new_bullet->bullet = bullet;
//	new_bullet->id = id;
//	new_bullet->prev = list->tail->prev;
//	new_bullet->next = list->tail;
//	list->tail->prev->next = new_bullet;
//	list->tail->prev = new_bullet;
//}
//
//void remove_enemy(list_of_enemy list, int id) {
//	comp_of_enemies* current_enemy = list->first->next;
//	while (current_enemy->id != id) {
//		current_enemy = current_enemy->next;
//	}
//	if (current_enemy != list->tail) {
//		current_enemy->next->prev = current_enemy->prev;
//		current_enemy->prev->next = current_enemy->next;
//		free(current_enemy);
//	}
//}
//
//void remove_bullet(list_of_bullet list, int id) {
//	comp_of_bullets* current_bullet = list->first->next;
//	while (current_bullet->id != id) {
//		current_bullet = current_bullet->next;
//	}
//	if (current_bullet != list->tail) {
//		current_bullet->next->prev = current_bullet->prev;
//		current_bullet->prev->next = current_bullet->next;
//		free(current_bullet);
//	}
//}
//
//ship get_enemy(list_of_enemy list, int id) {
//	comp_of_enemies* current_enemy = list->first->next;
//	while (current_enemy->id != id) {
//		current_enemy = current_enemy->next;
//	}
//	return current_enemy->enemy;
//}
//
//bullet get_bullet(list_of_bullet list, int id) {
//	comp_of_bullets* current_bullet = list->first->next;
//	while (current_bullet->id != id) {
//		current_bullet = current_bullet->next;
//	}
//	return current_bullet->bullet;
//}
//
//int get_next_bullet_id(list_of_bullet list, int id) {
//	comp_of_bullets* current_bullet = list->first->next;
//	while (current_bullet->id != id) {
//		current_bullet = current_bullet->next;
//	}
//	return current_bullet->next->id;
//}
//
//int get_next_enemy_id(list_of_enemy list, int id) {
//	comp_of_enemies* current_enemy = list->first->next;
//	while (current_enemy->id != id) {
//		current_enemy = current_enemy->next;
//	}
//	return current_enemy->next->id;
//}
//
//int get_prev_bullet_id(list_of_bullet list, int id) {
//	comp_of_bullets* current_bullet = list->first->next;
//	while (current_bullet->id != id) {
//		current_bullet = current_bullet->next;
//	}
//	return current_bullet->prev->id;
//}
//
//int get_prev_enemy_id(list_of_enemy list, int id) {
//	comp_of_enemies* current_enemy = list->first->next;
//	while (current_enemy->id != id) {
//		current_enemy = current_enemy->next;
//	}
//	return current_enemy->prev->id;
//}
//
//void change_enemy(list_of_enemy list, int id, ship enemy) {
//	comp_of_enemies* current_enemy = list->first->next;
//	while (current_enemy->id != id) {
//		current_enemy = current_enemy->next;
//	}
//	current_enemy->enemy = enemy;
//}
//
//void change_bullet(list_of_bullet list, int id, bullet bullet) {
//	comp_of_bullets* current_bullet = list->first->next;
//	while (current_bullet->id != id) {
//		current_bullet = current_bullet->next;
//	}
//	current_bullet->bullet = bullet;
//}
//
//int last_bullet_id(list_of_bullet list) {
//	return list->tail->prev->id;
//}
//
//int last_enemy_id(list_of_enemy list) {
//	return list->tail->prev->id;
//}

//void delete_list_of_bullet(list_of_bullet list) {
//	comp_of_bullets* current_bullet = list->first->next;
//	while (current_bullet != list->tail) {
//		comp_of_bullets* c = current_bullet;
//		current_bullet = c->next;
//		free(c);
//	}
//	free(list->first);
//}
//
//void delete_list_of_enemy(list_of_enemy list) {
//	comp_of_enemies* current_enemy = list->first->next;
//	while (current_enemy != list->tail) {
//		comp_of_enemies* c = current_enemy;
//		current_enemy = c->next;
//		free(c);
//	}
//	free(list->first);
//}