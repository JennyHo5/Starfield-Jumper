#pragma once

const float WINDOW_WIDTH = APP_INIT_WINDOW_WIDTH;
const float WINDOW_HEIGHT = APP_INIT_WINDOW_HEIGHT;

const float BACKGROUND_WIDTH = 2754.0f;
const float BACKGROUND_HEIGHT = 774.0f;

const float CAMERA_SCROLL_SPEED = 0.2f;
const float BACKGROUND_LOOPING_POINT = BACKGROUND_WIDTH / 2;

const float TILE_SIZE = 72.0f;
const int TILE_ID_EMPTY = 153;
const int TILE_ID_GROUND = 15;
const int TILE_ID_TOP = 1;
const int TILE_ID_GRASS[] = {70, 71, 72};
const int GRASSES_NUMBER = 3;
const int TILE_ID_LEFT = 14;
const int TILE_ID_TOPLEFT = 0;
const int TILE_ID_PILLAR_TOP = 34;
const int TILE_ID_PILLAR_GROUND = 62;

const int MAP_WIDTH = 100;
const int MAP_HEIGHT = 10;

const float PLAYER_WIDTH = 43.0f;
const float PLAYER_HEIGHT = 128.0f;
const float PlAYER_WALKING_SPEED = 0.2f;
const float PLAYER_JUMP_VELOCITY = 0.4f;

const float OPOSUM_WIDTH = 72.0f;
const float OPOSUM_HEIGHT = 56.0f;
const float OPOSUM_RUNNING_SPEED = 0.1f;
const int OPOSUM_MOVING_DURATION = 2000;

const float EAGLE_WIDTH = 64.0f;
const float EAGLE_HEIGHT = 64.0f;
const float EAGLE_FLYING_SPEED = 0.15f;
const int EAGLE_MOVING_DURATION = 4000;

const float ANIMATION_SPEED = 0.1f;

const float GRAVITY = -0.016f;

const int UPDATE_CALLS_PER_FRAME = 3;

enum class State {
	// Game States
	START,
	PLAY,
	// Player States
	IDLE,
	WALKING,
	JUMP,
	FALLING,
	ATTACK,
	DEAD,
	// Oposum States
	OPOSUM_RUNNING,
	OPOSUM_CHASING,
	// Eagle states
	EAGLE_FLYING
};