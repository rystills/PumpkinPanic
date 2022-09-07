class Player {
public:
	uint32_t animation = 3283;
	bool near = false;
	uint32_t texture_index = 0;

	Player();

	void update();
};