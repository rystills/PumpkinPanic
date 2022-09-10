#pragma once
class Player {
public:
	int32_t rot[3];
	float pos[3] = { 0.f, -2.f, -3.f };
	int32_t lane = 1;
	int32_t elapsedFrames = 0;
	uint32_t obstacles[100];
	uint32_t obstacles_length = 0;

	Player();

	void update();
};