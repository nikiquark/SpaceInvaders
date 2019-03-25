#pragma once
#include "objects.h"

void render_image(char image[30][150], list enemies, list bullets, ship SHIP);

void erase(char image[30][150]);

void copy(char image_from[30][150], char image_to[30][150]);

void out(char current_image[30][150], char next_image[30][150]);