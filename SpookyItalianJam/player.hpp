#pragma once
class Player {
public:
	int32_t rot[3];
	int32_t pos[3];
	int32_t elapsedFrames = 0;
	uint32_t obstacles[100];
	uint32_t obstacles_length = 0;

	Player();

	void update();
};