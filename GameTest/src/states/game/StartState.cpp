#include "stdafx.h"
#include "StartState.h"

StartState::StartState(): currentLevel(0) {
	background1 = App::CreateSprite(".\\graphics\\background\\background_layer_1.png", 1, 1);
	background2 = App::CreateSprite(".\\graphics\\background\\background_layer_2.png", 1, 1);
	background1->SetPosition(BACKGROUND_WIDTH / 2, WINDOW_HEIGHT / 2);
	background2->SetPosition(BACKGROUND_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void StartState::Enter() {
	currentLevel++;
}

StartState::~StartState() {
	delete background1;
	delete background2;
}

void StartState::Update(float deltaTime) {
	if (App::IsKeyPressed(VK_SPACE) || App::IsKeyPressed(VK_RETURN)) {
		StateMachineManager::GetInstance()->ChangeState(State::PLAY);
	}
}

void StartState::Render() {
	background1->Draw();
	background2->Draw();
	App::Print(20, WINDOW_HEIGHT - 20, "WASD / arrow keys to control directions", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
	App::Print(20, WINDOW_HEIGHT - 40, "Space key to jump", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
	App::Print(20, WINDOW_HEIGHT - 60, "Jump on an enemy to kill it", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
	App::Print(20, WINDOW_HEIGHT - 80, "Press Space or Return to start the game!", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
	App::Print(WINDOW_WIDTH - 200, WINDOW_HEIGHT - 20, "Current Level: ", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
	App::Print(WINDOW_WIDTH - 60, WINDOW_HEIGHT - 20, std::to_string(currentLevel).c_str(), 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
}