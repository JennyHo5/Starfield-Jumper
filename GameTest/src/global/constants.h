#pragma once

const float WINDOW_WIDTH = APP_INIT_WINDOW_WIDTH;
const float WINDOW_HEIGHT = APP_INIT_WINDOW_HEIGHT;

const float BACKGROUND_WIDTH = 2476.0f;
const float BACKGROUND_HEIGHT = 774.0f;

// Camera
const float CAMERA_SCROLL_SPEED = 0.2f;
const float BACKGROUND_LOOPING_POINT = BACKGROUND_WIDTH / 2;

// Tile map
const float TILE_SIZE = 64.0f;
const int TILE_ID_EMPTY = 22;
const int TILE_ID_GROUND[] = { 162, 179 };
const int GROUND_NUMBER = 2;
const int TILE_ID_TOP[] = {166, 167};
const int TOPS_NUMBER = 2;
const int TILE_ID_DECOR[] = {72, 73, 94};
const int DECOR_NUMBER = 3;

const int TILE_ID_PLATFORM_LEFT = 77;
const int TILE_ID_PLATFORM_MIDDLE = 79;
const int TILE_ID_PLATFORM_RIGHT = 81;
const int PLATFORMS[] = { 77, 79, 81 };
const int PLATFORMS_SIZE = 3;

const int COLLIDABLE[] = { 166, 167 };
const int COLLIDABLE_SIZE = 5;

const int MAP_WIDTH = 100;
const int MAP_HEIGHT = 12;
const int GROUND_HEIGHT = MAP_HEIGHT * 1 / 5;
const int PILLAR_HEIGHT = MAP_HEIGHT * 1 / 5;

// entities
const float PLAYER_WIDTH = 45.0f;
const float PLAYER_HEIGHT = 85.0f;
const float PlAYER_WALKING_SPEED = 0.2f;
const float PLAYER_JUMP_VELOCITY = 0.4f;

const float SLIME_WIDTH = 65.0f;
const float SLIME_HEIGHT = 40.0f;
const float SLIME_RUNNING_SPEED = 0.1f;
const int SLIME_MOVING_DURATION = 2000;

const float BAT_WIDTH = 64.0f;
const float BAT_HEIGHT = 32.0f;
const float BAT_FLYING_SPEED = 0.15f;
const int BAT_MOVING_DURATION = 4000;

// decors
const float ROCK_WIDTH = TILE_SIZE * 2;
const float ROCK_HEIGHT = 80.0f;
const float SMALL_TREE_WIDTH = 256.0f;
const float SMALL_TREE_HEIGHT = 256.0f;
const float BIG_TREE_WIDTH = 512.0f;
const float BIG_TREE_HEIGHT = 512.0f - 4*16.0f;
const float SIGN_WIDTH = TILE_SIZE;
const float SIGN_HEIGHT = 124.0f;

// Animation
const float ANIMATION_SPEED = 0.1f;
const int UPDATE_CALLS_PER_FRAME = 3;

// Physics
const float GRAVITY = -0.016f;

// States
enum class State {
	// Game States
	START,
	PLAY,
	// Player States
	IDLE,
	WALKING,
	JUMP,
	FALLING,
	DEAD,
	WIN,
	// SLIME States
	SLIME_MOVING,
	SLIME_DEAD,
	SLIME_CHASING,
	// Eagle states
	EAGLE_FLYING
};