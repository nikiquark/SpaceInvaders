#include "objects.h"
#include <malloc.h>
#include <stdio.h>

typedef struct _comp_of_bullets {
	bullet bullet;
	int id;
	struct _comp_of_bullets *next;
	struct _comp_of_bullets *prev;
} comp_of_bullets;

typedef struct _comp_of_enemies {
	ship enemy;
	int id;
	struct _comp_of_enemies *next;
	struct _comp_of_enemies *prev;
} comp_of_enemies;

typedef struct _list_of_bullet {
	comp_of_bullets *first;
	comp_of_bullets *tail;
} *list_of_bullet;

typedef struct _list_of_enemy {
	comp_of_enemies *first;
	comp_of_enemies *tail;
} *list_of_enemy;

void init_list_of_enemy(list_of_enemy list) {
	comp_of_enemies *last = (comp_of_enemies*)malloc(sizeof(comp_of_enemies));
	if (last == NULL) {
		fprintf(stderr, "failed to allocate memory.\n");
		exit(-1);
	}
	last->id = -1;
	last->next = last;
	last->prev = last;
	list->first = last;
	list->tail = last;
}

void init_list_of_bullet(list_of_bullet list) {
	comp_of_bullets *last = (comp_of_bullets*)malloc(sizeof(comp_of_bullets));
	last->id = -1;
	if (last == NULL) {
		fprintf(stderr, "failed to allocate memory.\n");
		exit(-1);
	}
	last->next = last;
	last->prev = last;
	list->first = last;
	list->tail = last;
}


void add_enemy(list_of_enemy list, int id, ship enemy) {
	comp_of_enemies *new_enemy = (comp_of_enemies*)malloc(sizeof(comp_of_enemies));
	if (new_enemy == NULL) {
		fprintf(stderr, "failed to allocate memory.\n");
		exit(-1);
	}
	new_enemy->enemy = enemy;
	new_enemy->id = id;
	new_enemy->prev = list->tail->prev;
	new_enemy->next = list->tail;
	list->tail->prev->next = new_enemy;
	list->tail->prev = new_enemy;
}

void add_bullet(list_of_bullet list, int id, bullet bullet) {
	comp_of_bullets *new_bullet = (comp_of_bullets*)malloc(sizeof(comp_of_bullets));
	if (new_bullet == NULL) {
		fprintf(stderr, "failed to allocate memory.\n");
		exit(-1);
	}
	new_bullet->bullet = bullet;
	new_bullet->id = id;
	new_bullet->prev = list->tail->prev;
	new_bullet->next = list->tail;
	list->tail->prev->next = new_bullet;
	list->tail->prev = new_bullet;
}

void remove_enemy(list_of_enemy list, int id) {
	comp_of_enemies* current_enemy = list->first->next;
	while (current_enemy->id != id) {
		current_enemy = current_enemy->next;
	}
	if (current_enemy != list->tail) {
		current_enemy->next->prev = current_enemy->prev;
		current_enemy->prev->next = current_enemy->next;
		free(current_enemy);
	}
}

void remove_bullet(list_of_bullet list, int id) {
	comp_of_bullets* current_bullet = list->first->next;
	while (current_bullet->id != id) {
		current_bullet = current_bullet->next;
	}
	if (current_bullet != list->tail) {
		current_bullet->next->prev = current_bullet->prev;
		current_bullet->prev->next = current_bullet->next;
		free(current_bullet);
	}
}

ship get_enemy(list_of_enemy list, int id) {
	comp_of_enemies* current_enemy = list->first->next;
	while (current_enemy->id != id) {
		current_enemy = current_enemy->next;
	}
	return current_enemy->enemy;
}

bullet get_bullet(list_of_bullet list, int id) {
	comp_of_bullets* current_bullet = list->first->next;
	while (current_bullet->id != id) {
		current_bullet = current_bullet->next;
	}
	return current_bullet->bullet;
}

int get_next_bullet_id(list_of_bullet list, int id) {
	comp_of_bullets* current_bullet = list->first->next;
	while (current_bullet->id != id) {
		current_bullet = current_bullet->next;
	}
	return current_bullet->next->id;
}

int get_next_enemy_id(list_of_enemy list, int id) {
	comp_of_enemies* current_enemy = list->first->next;
	while (current_enemy->id != id) {
		current_enemy = current_enemy->next;
	}
	return current_enemy->next->id;
}

int get_prev_bullet_id(list_of_bullet list, int id) {
	comp_of_bullets* current_bullet = list->first->next;
	while (current_bullet->id != id) {
		current_bullet = current_bullet->next;
	}
	return current_bullet->prev->id;
}

int get_prev_enemy_id(list_of_enemy list, int id) {
	comp_of_enemies* current_enemy = list->first->next;
	while (current_enemy->id != id) {
		current_enemy = current_enemy->next;
	}
	return current_enemy->prev->id;
}

void change_enemy(list_of_enemy list, int id, ship enemy) {
	comp_of_enemies* current_enemy = list->first->next;
	while (current_enemy->id != id) {
		current_enemy = current_enemy->next;
	}
	current_enemy->enemy = enemy;
}

void change_bullet(list_of_bullet list, int id, bullet bullet) {
	comp_of_bullets* current_bullet = list->first->next;
	while (current_bullet->id != id) {
		current_bullet = current_bullet->next;
	}
	current_bullet->bullet = bullet;
}

int last_bullet_id(list_of_bullet list) {
	return list->tail->prev->id;
}

int last_enemy_id(list_of_enemy list) {
	return list->tail->prev->id;
}

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