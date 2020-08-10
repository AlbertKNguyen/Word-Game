#include <server.h>
#include <algorithm>
#include <game.h>

using namespace ucm;

int main(int argc, char** argv) {

    Server server(argc, argv);

    server.renderHTML("/", "index.html");

    game::Game game;

    server.get("/list", [&](const request& req, response& res) {
        json result;
        result = game.generateList();
        res.sendJSON(result);
    });

    server.get("/checkWord", [&](const request& req, response& res) {
        if (req.has_params({"word"})){
            std::string word = req.url_params.get("word");
            json result;
            result["word"] = word;
            result["valid"] = game.check(word);
            res.sendJSON(result);
        }
        else {
            res.sendError400();
        }
    });
    
    server.get("/solution", [&](const request& req, response& res) {
        json result;
        result = game.getSolution();
        res.sendJSON(result);
    });

    server.post("/setHighscore", [&](const request& req, response& res) {
        if ((req.body).substr(0, 9) == "highscore" && std::all_of((req.body).begin() + 10, (req.body).end(), ::isdigit)) {
            int highscore = stoi((req.body).substr(10, req.body.length()));
            json result;
            game.setHighscore(highscore);
            result["status"] = 200;
            res.sendJSON(result);
        }
        else {
            res.sendError400();
        }
    });

    server.get("/getHighscore", [&](const request& req, response& res) {
        json result;
        result = game.getHighscore();
        res.sendJSON(result);
    });

    server.run();
}
