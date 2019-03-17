#pragma once
#include "objects.h"

void move_enemies(list_of_enemy list, int dir_x, int dir_y);

void fire(list_of_bullet bullets, list_of_enemy enemies);

void move_bullets(list_of_bullet bullets, list_of_enemy enemies, ship SHIP);