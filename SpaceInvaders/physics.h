#pragma once
#include "objects.h"

void move_enemies(list list, int dir_x, int dir_y);

void fire(list bullets, list enemies);

void move_bullets(list bullets, list enemies, ship SHIP);