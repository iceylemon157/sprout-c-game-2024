#include "GameController.h"
#include <utility>

using namespace std;
using namespace ctl;

string GameController::resp;
pair<int, int> GameController::PlayerPosition;

void GameController::MoveRight() {
    resp = "d";
}

void GameController::MoveLeft() {
    resp = "a";
}

void GameController::MoveUp() {
    resp = "w";
}

void GameController::MoveDown() {
    resp = "s";
}

void GameController::Interact() {
    resp = "e";
}

void GameController::InteractSpecial() {
    resp = "f";
}

string GameController::GetResponse() { return resp; }
void GameController::SetResponse(string _resp) { resp = _resp; }

void GameController::SetPlayerPosition(pair<int, int> position) {
    PlayerPosition = position;
}

pair<int, int> ctl::GameController::GetPlayerPosition() {
    return PlayerPosition;
}
