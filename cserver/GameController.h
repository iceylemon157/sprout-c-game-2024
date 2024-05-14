#ifndef CONTROL_H
#define CONTROL_H

#include <utility>
#include <string>
#include "wfrest/HttpServer.h"
#include "kitchen.h"

using namespace std;

namespace ctl {
    class GameController {
    public:

        // Singleton
        static GameController& getInstance(std::string _resp) {
            static GameController instance(_resp);
            return instance;
        }

        // Operation functions
        void MoveLeft();
        void MoveRight();
        void MoveUp();
        void MoveDown();
        void Interact();
        void InteractSpecial();

        void SetResponse(std::string _resp);
        std::string GetResponse();

        void SetPlayerPosition(std::pair<int, int> position);
        std::pair<int, int> GetPlayerPosition();

    private:
        // By chatGPT, I don't understand it, but it implements the singleton pattern
        GameController() {}
        GameController(std::string _resp) {
            resp = _resp;
        }
        ~GameController() {}

        // Private copy constructor and assignment operator to prevent copying
        GameController(const GameController&) = delete;
        GameController& operator=(const GameController&) = delete;

        static string resp;

        static int Round;
        static int TotalScore;
        static int TimeLeft; // Deprecated

        static pair<int, int> PlayerPosition;
        static vector<enum Ingredient> PlayerHoldItems;

        static int RecipeTimeOut; // Deprecated
        static pair<int, int> RecipeDelivered;

        static Recipe NewRecipe;
        static vector<Recipe> RecipeList;

        static int FryingTimer;
        static enum FryingState FryingState;

    };
}

#endif /* CONTROL_H */
