#pragma once
enum EntityType {
	cube
};

typedef struct Entity {
	EntityType type;
	float zpos;
	int32_t lane;
	Entity(EntityType inType, float inZpos, int32_t inLane) : type(inType), zpos(inZpos), lane(inLane) {};
	Entity() {};
} Entity;

class Player {
public:
	int32_t rot[3];
	float pos[3] = { 0.f, -2.f, -3.f };
	int32_t lane = 1;
	int32_t elapsedFrames = 0;
	Entity obstacles[100];
	uint32_t obstacles_length = 0;

	Player();

	void checkSpawnEntity(Entity* arr, uint32_t &arrlen, uint32_t tickFrames);
	void update();
};