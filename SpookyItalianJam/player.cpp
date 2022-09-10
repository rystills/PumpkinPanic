#include <libdragon.h>
#include <math.h>

#include "player.hpp"

Player::Player() {
	obstacles[obstacles_length++] = 1;
}

void Player::update() {
	controller_scan();
	struct controller_data pressed = get_keys_pressed();
	struct controller_data down = get_keys_down();

	if (down.c[0].left && lane > 0) {
		--lane;
	}

	if (down.c[0].right && lane < 2) {
		++lane;
	}

	/*if (down.c[0].start) {
		debugf("%ld\n", animation);
	}*/

	/*if (down.c[0].C_right) {
		texture_index = (texture_index + 1) % 4;
	}*/

	++elapsedFrames;
	rot[0] = sinf(elapsedFrames*.1f)*10;
	pos[0] = (lane-1) * 2;
	if (elapsedFrames >= 150 && elapsedFrames < 190 && lane == 1) {
		elapsedFrames = 0;
	}
}