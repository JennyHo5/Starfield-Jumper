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
}

void PlayState::Enter() {
	App::PlaySoundW(".\\sounds\\bgm.wav", true);

	// Generate new gamelevel using LevelMaker
	gameLevel = levelMaker.Generate();

	// Make a new Player object, pass in gameLevel as reference
	player = std::make_unique<Player>(TILE_SIZE / 2, WINDOW_WIDTH / 2, *gameLevel);

	// Reset background and camera positions
	background1->SetPosition(BACKGROUND_WIDTH / 2, WINDOW_HEIGHT / 2);
	background2->SetPosition(BACKGROUND_WIDTH / 2, WINDOW_HEIGHT / 2);
	background3->SetPosition(BACKGROUND_WIDTH / 2, WINDOW_HEIGHT / 2);
	background1->GetPosition(backgroundX, backgroundY);
	camX = 0;

	// Add enemy entities (slime, bat) to the gameLevel
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
	
	// Basic UI
	App::Print(WINDOW_WIDTH - 200, WINDOW_HEIGHT - 20, "Current Score: ", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
	App::Print(WINDOW_WIDTH - 60, WINDOW_HEIGHT - 20, std::to_string(player->GetScore()).c_str(), 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);

	// If player is dead, show dead UI
	if (player->IsDead())
	{
		App::Print(WINDOW_WIDTH / 2 - 60, WINDOW_HEIGHT/ 2 + 20, "You are dead!", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
		App::Print(WINDOW_WIDTH / 2 - 120, WINDOW_HEIGHT / 2, "Press R to restart a new level", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
	}

	// If player wins, show win UI
	if (player->GetIsWin())
	{
		App::Print(WINDOW_WIDTH / 2 - 60, WINDOW_HEIGHT / 2 + 20, "You win!", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
		App::Print(WINDOW_WIDTH / 2 - 120, WINDOW_HEIGHT / 2, "Press R to restart a new level", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
	}
}

void PlayState::SpawnEnemies() {
	// Get tiles as a const pointer as a reference to spawn enemies
	const std::vector<std::vector<Tile*>>* tiles = gameLevel->GetTileMap()->GetTiles();

	// Spawn slimes
	for (int x = 1; x < MAP_WIDTH - 8; x++) {
		for (int y = 0; y < MAP_HEIGHT; y++) {
			if ((*tiles)[x][y]->IsTop() || (*tiles)[x][y]->IsPlatform()) {
				if (GetRandom(5) == 1) {
					std::unique_ptr<Slime> slime = std::make_unique<Slime>((x + 1) * TILE_SIZE - SLIME_WIDTH / 2, (y + 1) * TILE_SIZE + SLIME_HEIGHT / 2, *gameLevel);
					slime->GetStateMachine()->AddState(State::SLIME_MOVING, std::make_unique<SlimeMovingState>(gameLevel->GetTileMap(), player.get(), slime.get()));
					slime->GetStateMachine()->AddState(State::SLIME_DEAD, std::make_unique<SlimeDeadState>(slime.get()));
					slime->GetStateMachine()->AddState(State::SLIME_CHASING, std::make_unique<SlimeChasingState>(gameLevel->GetTileMap(), player.get(), slime.get()));
					slime->GetStateMachine()->ChangeState(State::SLIME_MOVING);
					gameLevel->AddEntity(std::move(slime));
				}
			}
		}
	}

	// Spawn bats
	for (int x = 1; x < MAP_WIDTH; x++) {
		for (int y = MAP_HEIGHT * 2/3; y < MAP_HEIGHT - 1; y++) {
			if ((*tiles)[x][y]->GetID() == TILE_ID_EMPTY) {
				if (GetRandom(20) == 1) {
					// Add Bat at column x
					std::unique_ptr<Bat> bat = std::make_unique<Bat>((x + 1) * TILE_SIZE - BAT_WIDTH / 2, (y + 1) * TILE_SIZE + BAT_HEIGHT / 2, *gameLevel);
					bat->GetStateMachine()->AddState(State::BAT_FLYING, std::make_unique<BatFlyingState>(gameLevel->GetTileMap(), player.get(), bat.get()));
					bat->GetStateMachine()->AddState(State::BAT_DEAD, std::make_unique<BatDeadState>(bat.get()));
					bat->GetStateMachine()->ChangeState(State::BAT_FLYING);
					gameLevel->AddEntity(std::move(bat));
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

	background1->SetPosition(static_cast<float>(newX1), backgroundY); // Use floor to avoid blurry during movement
	background2->SetPosition(static_cast<float>(newX2), backgroundY);
	background3->SetPosition(static_cast<float>(newX3), backgroundY);

	// Player
	player->GetSprite()->SetPosition(player->GetX() - floor(camX), player->GetY());

	// TileMap
	const std::vector<std::vector<Tile*>>* tiles = gameLevel->GetTileMap()->GetTiles();
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			Tile* t = (*tiles)[x][y];
			t->GetSprite()->SetPosition(t->GetX() - floor(camX), t->GetY());
		}
	}

	// Entities
	for (const auto& eptr : gameLevel->GetEntities()) {
		Entity* e = eptr.get();
		e->GetSprite()->SetPosition(e->GetX() - floor(camX), e->GetY());
	}

	// Game Objects
	for (const auto& optr : gameLevel->GetGameObjects()) {
		GameObject* o = optr.get();
		o->GetSprite()->SetPosition(o->GetX() - floor(camX), o->GetY());
	}
}

void PlayState::Exit() {
	App::StopSound(".\\sounds\\bgm.wav");
	player.reset();
	gameLevel.reset();
}