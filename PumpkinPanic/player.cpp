#include <libdragon.h>
#include <math.h>
#include <stdlib.h>

#include "player.hpp"

Player::Player() {
}

void Player::checkSpawnEntity(Entity* arr, uint32_t &arrlen, uint32_t tickFrames) {
	if (elapsedFrames % tickFrames == 0) {
		// spawn a new obstacle
		arr[arrlen++] = { EntityType::cube, -20.f - elapsedFrames * .1f, rand() % 3 };
		// remove obstacles in the foreground
		for (int i = 0; i < arrlen; ++i) {
			if (!(arr[i].zpos + .1f * elapsedFrames > 0)) {
				// shift back from here
				if (i > 0) {
					for (int j = i; j < arrlen; ++j) {
						arr[j - i] = arr[j];
					}
					arrlen -= i;
				}
				break;
			}
		}
	}
}

void Player::update() {
	controller_scan();
	struct controller_data pressed = get_keys_pressed();
	struct controller_data down = get_keys_down();

	lane -= (down.c[0].left && lane > 0);

	lane += (down.c[0].right && lane < 2);

	checkSpawnEntity(obstacles, obstacles_length, 50);

	++elapsedFrames;
	rot[0] = sinf(elapsedFrames*.1f)*10;
	pos[0] = (lane-1) * 2;
	for (int i = 0; i < obstacles_length; ++i) {
		if (lane == obstacles[i].lane && obstacles[i].zpos + .1f * elapsedFrames >= pos[2] - 2 && obstacles[i].zpos + .1f * elapsedFrames < pos[2] + 2) {
			elapsedFrames = 0;
			obstacles_length = 0;
		}
	}
}