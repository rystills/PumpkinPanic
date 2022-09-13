#pragma once
enum ObstacleType {
	cube
};

typedef struct Obstacle {
	ObstacleType type;
	float zpos;
	int32_t lane;
	Obstacle(ObstacleType inType, float inZpos, int32_t inLane) : type(inType), zpos(inZpos), lane(inLane) {};
	Obstacle() {};
} Obstacle;

class Player {
public:
	int32_t rot[3];
	float pos[3] = { 0.f, -2.f, -3.f };
	int32_t lane = 1;
	int32_t elapsedFrames = 0;
	Obstacle obstacles[100];
	uint32_t obstacles_length = 0;

	Player();

	void update();
};