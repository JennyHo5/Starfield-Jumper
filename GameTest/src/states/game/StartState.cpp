#include "stdafx.h"
#include "StartState.h"

StartState::StartState(): currentLevel(0) {
	background1 = App::CreateSprite(".\\graphics\\background\\background_0.png", 1, 1);
	background2 = App::CreateSprite(".\\graphics\\background\\background_1.png", 1, 1);
	background3 = App::CreateSprite(".\\graphics\\background\\background_2.png", 1, 1);
	background1->SetPosition(BACKGROUND_WIDTH / 2, WINDOW_HEIGHT / 2);
	background2->SetPosition(BACKGROUND_WIDTH / 2, WINDOW_HEIGHT / 2);
	background3->SetPosition(BACKGROUND_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void StartState::Enter() {
	currentLevel++;
}

StartState::~StartState() {
	delete background1;
	delete background2;
	delete background3;
}

void StartState::Update(float deltaTime) {
	if (App::IsKeyPressed(VK_SPACE) || App::IsKeyPressed(VK_RETURN)) {
		Game::GetInstance()->ChangeState(State::PLAY);
	}
}

void StartState::Render() {
	background1->Draw();
	background2->Draw();
	background3->Draw();
	App::Print(20, WINDOW_HEIGHT - 40, "Everytime you start a new level, you will be sent to a randomly generated world", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
	App::Print(20, WINDOW_HEIGHT - 60, "Watch out your steps below you, you might fall into a hole when the game starts!", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
	App::Print(20, WINDOW_HEIGHT - 80, "Jump on a slime to eliminate it, and avoid bats as you can", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
	App::Print(20, WINDOW_HEIGHT - 100, "WASD / arrow keys to control directions", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
	App::Print(20, WINDOW_HEIGHT - 120, "Space key to jump", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
	App::Print(20, WINDOW_HEIGHT - 140, "Esc to exit", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
	App::Print(20, WINDOW_HEIGHT - 160, "Press Space or Return to start the game!", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
	App::Print(WINDOW_WIDTH - 200, WINDOW_HEIGHT - 20, "Current Level: ", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
	App::Print(WINDOW_WIDTH - 60, WINDOW_HEIGHT - 20, std::to_string(currentLevel).c_str(), 1.0f, 1.0f, 1.0f, GLUT_BITMAP_9_BY_15);
}