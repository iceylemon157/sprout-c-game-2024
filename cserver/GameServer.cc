#include <csignal>
#include <iostream>
#include <random>
#include <vector>

#include "GameController.h"
#include "user.h"
#include "wfrest/HttpServer.h"
#include "wfrest/json.hpp"
#include "workflow/WFFacilities.h"

using namespace wfrest;
using namespace ctl;
using namespace std;

static WFFacilities::WaitGroup wait_group(1);

void sig_handler(int signo) { wait_group.done(); }

mt19937 ran(time(nullptr));

string RandomString();
vector<string> ParseJsonToVector(const Json &json);

int main() {
    signal(SIGINT, sig_handler);

    HttpServer svr;

    string responseString = "default";
    GameController& controller = GameController::getInstance(responseString);

    UserAction action;

    // init game
    svr.GET("/api/init", [&](const HttpReq *req, HttpResp *resp) {
        vector<string> result = ParseJsonToVector(req->json());
        action.InitGame(controller);

        resp->String(controller.GetResponse());
        // CORS
        resp->add_header_pair("Access-Control-Allow-Origin", "*");
    });

    // gaming operations (move right, move left, move up, move down, interact, interact special)
    svr.GET("/api/operation", [&](const HttpReq *req, HttpResp *resp) {
        cout << "Round: " << req->query("round") << endl;
        action.SendOperation(controller);
        resp->String(controller.GetResponse());
        // CORS
        resp->add_header_pair("Access-Control-Allow-Origin", "*");
    });

    // gaming events (e.g. recipe delivered, recipe failed, recipe list, total score, time left, overcooked warning)
    svr.POST("/api/events", [&](const HttpReq *req, HttpResp *resp) {
        cout << "Received events: " << req->json() << endl;
        vector<string> result = ParseJsonToVector(req->json());

        action.ReceiveEvents(controller, result);
        resp->String(controller.GetResponse());
        // CORS
        resp->add_header_pair("Access-Control-Allow-Origin", "*");
    });

    // curl -v http://ip:port/hello
    svr.GET("/hello", [](const HttpReq *req, HttpResp *resp) {
        resp->String("world\n");
    });

    // curl -v http://ip:port/data
    svr.GET("/data", [](const HttpReq *req, HttpResp *resp) {
        string str = "Hello world";
        resp->String(move(str));
    });

    svr.ROUTE("/multi",
              [](const HttpReq *req, HttpResp *resp) {
                  string method(req->get_method());
                  resp->String(move(method));
              },
              {"GET", "POST"});

    // curl -v http://ip:port/post -d 'post hello world'
    svr.POST("/post", [](const HttpReq *req, HttpResp *resp) {
        // reference, no copy here
        string &body = req->body();
        fprintf(stderr, "post data : %s\n", body.c_str());
    });

    // curl -v http://ip:port/any_path
    svr.set_default_route("/data");

    if (svr.track().start(8887) == 0) {
        svr.list_routes();
        wait_group.wait();
        svr.stop();
    } else {
        fprintf(stderr, "Cannot start server");
        exit(1);
    }
    return 0;
}

vector<string> ParseJsonToVector(const Json &json) {
    vector<string> result;
    for (auto &item : json) {
        // cout << item.dump() << endl;
        if (item.key() == "NewRecipe") {
            
            // template
            // std::string json_string = "{\"kitchenObjectSOList\":[{\"instanceID\":28018},{\"instanceID\":28066}],\"recipeName\":\"Salad\",\"id\":1}";
            // Json ajson = Json::parse(json_string);
            // cout << "NewRecipe a: " << ajson.dump() << endl;

            // print the type of item.value()
            Json recipe = Json::parse(item.value().dump());
            // Json recipe = item.value();
            cout << "NewRecipe: " << recipe.dump() << endl;
            // print number of keys
            cout << "Number of keys: " << recipe.size() << endl;
            // print the first key
            for (auto &ingredient : recipe) {
                cout << "Ingredient: " << ingredient.dump() << endl;
            }
        } else if (item.key() == "FryingState") {
            enum FryingState fryingState = (enum FryingState)item.value().get<int>();
            if (fryingState == Frying) {
                cout << "FryingState: Frying" << endl;
            } else if (fryingState == Fried) {
                cout << "FryingState: Fried" << endl;
            } else if (fryingState == Burnt) {
                cout << "FryingState: Burnt" << endl;
            } else {
                cout << "FryingState: Idle" << endl;
            }
        }
        result.emplace_back(item.dump());
    }
    return result;
}

string RandomString() {
    string charset = "abcdefghijklmnopqrstuvwxyz";
    string str;
    for (int i = 0; i < 10; i++) {
        str += charset[ran() % 26];
    }
    return str;
}
