#include <libdragon.h>
#include <math.h>
#include <stdlib.h>

#include "player.hpp"

Player::Player() {
}

void Player::update() {
	controller_scan();
	struct controller_data pressed = get_keys_pressed();
	struct controller_data down = get_keys_down();

	lane -= (down.c[0].left && lane > 0);

	lane += (down.c[0].right && lane < 2);

	if (elapsedFrames % 50 == 0) {
		// spawn a new obstacle
		obstacles[obstacles_length++] = { ObstacleType::cube, -20.f - elapsedFrames*.1f, rand() % 3 };
		// remove obstacles in the foreground
		for (int i = 0; i < obstacles_length; ++i) {
			if  (!(obstacles[i].zpos + .1f * elapsedFrames > 0)) {
				// shift back from here
				if (i > 0) {
					for (int j = i; j < obstacles_length; ++j) {
						obstacles[j - i] = obstacles[j];
					}
					obstacles_length -= i;
				}
				break;
			}
		}
	}

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