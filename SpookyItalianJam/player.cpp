#include <libdragon.h>

#include "player.hpp"

Player::Player() {
	obstacles[obstacles_length++] = 1;
}

void Player::update() {
	controller_scan();
	struct controller_data pressed = get_keys_pressed();
	struct controller_data down = get_keys_down();

	if (pressed.c[0].left) {
		rot[0]-=5;
	}

	if (pressed.c[0].right) {
		rot[0] += 5;
	}

	if (pressed.c[0].up) {
		rot[1] += 5;
	}

	if (pressed.c[0].down) {
		rot[1] -= 5;
	}

	/*if (down.c[0].start) {
		debugf("%ld\n", animation);
	}*/

	/*if (down.c[0].C_right) {
		texture_index = (texture_index + 1) % 4;
	}*/

	++elapsedFrames;

}