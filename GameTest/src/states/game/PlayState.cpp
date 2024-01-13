#include "stdafx.h"
#include "PlayState.h"

PlayState::PlayState(): gameLevel(nullptr), player(nullptr), backgroundX(0), backgroundY(0), camX(0)
{
	background1 = App::CreateSprite(".\\graphics\\background\\background_0.png", 1, 1);
	background2 = App::CreateSprite(".\\graphics\\background\\background_1.png", 1, 1);
	background3 = App::CreateSprite(".\\graphics\\background\\background_2.png", 1, 1);
}

PlayState::~PlayState() {
	delete background1;
	delete background2;
	delete background3;
	delete player;
	delete gameLevel;
}

void PlayState::Enter() {
	printf("Entering PlayState\n");
	App::PlaySoundW(".\\sounds\\bgm.wav", true);

	// Generate new gamelevel and player
	gameLevel = levelMaker.Generate();

	player = new Player(TILE_SIZE / 2, WINDOW_WIDTH / 2, *gameLevel);
	background1->SetPosition(BACKGROUND_WIDTH / 2, WINDOW_HEIGHT / 2);
	background2->SetPosition(BACKGROUND_WIDTH / 2, WINDOW_HEIGHT / 2);
	background3->SetPosition(BACKGROUND_WIDTH / 2, WINDOW_HEIGHT / 2);
	background1->GetPosition(backgroundX, backgroundY);
	camX = 0;

	gameLevel->Init();
	SpawnEnemies();
}

void PlayState::Update(float deltaTime) {
	// Update camera based on player's x
	camX = player->GetX() - WINDOW_WIDTH / 2;

	if (player)
		player->Update(deltaTime);
	if (gameLevel)
		gameLevel->Update(deltaTime);
}

void PlayState::Render() {
	// Move every sprite in the scene by -camX
	Translate();
	
	background1->Draw();
	background2->Draw();
	background3->Draw();

	gameLevel->Render();
	player->Render();
	
	App::Print(WINDOW_WIDTH - 200, WINDOW_HEIGHT - 20, "Current Score: ", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
	App::Print(WINDOW_WIDTH - 60, WINDOW_HEIGHT - 20, std::to_string(player->GetScore()).c_str(), 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);

	// If player is dead, show dead UI
	if (player->IsDead())
	{
		App::Print(20, WINDOW_HEIGHT - 20, "You are dead!", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
		App::Print(20, WINDOW_HEIGHT - 40, "Press R to restart a new level", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
	}

	// If player wins, show win UI
	if (player->GetIsWin())
	{
		App::Print(20, WINDOW_HEIGHT - 20, "You win!", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
		App::Print(20, WINDOW_HEIGHT - 40, "Press R to restart a new level", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
	}
}

void PlayState::SpawnEnemies() {
	std::vector<std::vector<Tile*>>* tiles = gameLevel->GetTileMap()->GetTiles();

	// Spawn slimes
	for (int x = 1; x < MAP_WIDTH; x++) {
		for (int y = 0; y < MAP_HEIGHT; y++) {
			if ((*tiles)[x][y]->Collidable()) {
				if (GetRandom(5) == 1) {
					printf("Added slime at column %d's ground\n", x);
					Slime* slime = new Slime((x + 1) * TILE_SIZE - SLIME_WIDTH / 2, (y + 1) * TILE_SIZE + SLIME_HEIGHT / 2, *gameLevel);
					slime->GetStateMachine()->AddState(State::SLIME_MOVING, new SlimeMovingState(gameLevel->GetTileMap(), player, slime));
					slime->GetStateMachine()->AddState(State::SLIME_DEAD, new SlimeDeadState(slime));
					slime->GetStateMachine()->AddState(State::SLIME_CHASING, new SlimeChasingState(gameLevel->GetTileMap(), player, slime));
					slime->GetStateMachine()->ChangeState(State::SLIME_MOVING);
					gameLevel->AddEntity(slime);
				}
			}

			if ((*tiles)[x][y]->IsPlatform()) {
				if (GetRandom(10) == 1) {
					printf("Added slime at column %d's platform\n", x);
					Slime* slime = new Slime((x + 1) * TILE_SIZE - SLIME_WIDTH / 2, (y + 1) * TILE_SIZE + SLIME_HEIGHT / 2, *gameLevel);
					slime->GetStateMachine()->AddState(State::SLIME_MOVING, new SlimeMovingState(gameLevel->GetTileMap(), player, slime));
					slime->GetStateMachine()->AddState(State::SLIME_DEAD, new SlimeDeadState(slime));
					slime->GetStateMachine()->AddState(State::SLIME_CHASING, new SlimeChasingState(gameLevel->GetTileMap(), player, slime));
					slime->GetStateMachine()->ChangeState(State::SLIME_MOVING);
					gameLevel->AddEntity(slime);
				}
			}
		}
	}

	// Spawn eagles
	for (int x = 1; x < MAP_WIDTH; x++) {
		for (int y = MAP_HEIGHT * 2/3; y < MAP_HEIGHT; y++) {
			if ((*tiles)[x][y]->GetID() == TILE_ID_EMPTY) {
				if (GetRandom(20) == 1) {
					printf("Added bat at column %d\n", x);
					Bat* bat = new Bat((x + 1) * TILE_SIZE - BAT_WIDTH / 2, (y + 1) * TILE_SIZE + BAT_HEIGHT / 2, *gameLevel);
					bat->GetStateMachine()->AddState(State::BAT_FLYING, new BatFlyingState(gameLevel->GetTileMap(), player, bat));
					bat->GetStateMachine()->ChangeState(State::BAT_FLYING);
					gameLevel->AddEntity(bat);
				}
			}
		}
	}

}

void PlayState::Translate() {
	// Background
	double newX1 = fmod((backgroundX - floor(camX)), BACKGROUND_LOOPING_POINT); // Scrolling background
	if (newX1 < 0)
		newX1 = BACKGROUND_WIDTH / 2 + newX1;

	double newX2 = fmod((backgroundX - floor(camX * 0.8)), BACKGROUND_LOOPING_POINT);
	if (newX2 < 0)
		newX2 = BACKGROUND_WIDTH / 2 + newX2;

	double newX3 = fmod((backgroundX - floor(camX * 0.6)), BACKGROUND_LOOPING_POINT);
	if (newX3 < 0)
		newX3 = BACKGROUND_WIDTH / 2 + newX3;

	background1->SetPosition(newX1, backgroundY); // Use floor to avoid blurry during movement
	background2->SetPosition(newX2, backgroundY);
	background3->SetPosition(newX3, backgroundY);

	// Player
	player->GetSprite()->SetPosition(player->GetX() - floor(camX), player->GetY());

	// TileMap
	std::vector<std::vector<Tile*>>* tiles = gameLevel->GetTileMap()->GetTiles();
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			Tile* t = (*tiles)[x][y];
			t->GetSprite()->SetPosition(t->GetX() - floor(camX), t->GetY());
		}
	}

	// Entities
	std::vector<Entity*>* entities = gameLevel->GetEntities();
	for (Entity* e : *entities) {
		e->GetSprite()->SetPosition(e->GetX() - floor(camX), e->GetY());
	}

	// Game Objects
	std::vector<GameObject*>* gameObjects = gameLevel->GetGameObjects();
	for (GameObject* o : *gameObjects) {
		o->GetSprite()->SetPosition(o->GetX() - floor(camX), o->GetY());
	}
}

void PlayState::Exit() {
	printf("Exiting Play State\n");
	App::StopSound(".\\sounds\\bgm.wav");
	delete player;
	player = nullptr;
	delete gameLevel;
	gameLevel = nullptr;
}