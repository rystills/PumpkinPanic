#include <libdragon.h>

#include "player.hpp"

Player::Player() {

}

void Player::update() {
	controller_scan();
	struct controller_data pressed = get_keys_pressed();
	struct controller_data down = get_keys_down();

	if (pressed.c[0].A) {
		animation++;
	}

	if (pressed.c[0].B) {
		animation--;
	}

	if (down.c[0].start) {
		debugf("%ld\n", animation);
	}

	if (down.c[0].C_down) {
		near = !near;
	}

	if (down.c[0].C_right) {
		texture_index = (texture_index + 1) % 4;
	}
}