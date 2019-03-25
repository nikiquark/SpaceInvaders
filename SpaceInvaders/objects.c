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
