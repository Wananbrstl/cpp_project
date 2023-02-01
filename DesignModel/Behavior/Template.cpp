#include <bits/stdc++.h>

using namespace std;

class Game {
public:
    virtual void init() {
        cout << "game init" << endl;
    }
    virtual void start() {
        cout << "game start" << endl;
    }
    virtual void end() {
        cout << "game end" << endl;
    }
};

class FootballGame : public Game {
public:
    void init() override {
        cout << "FootBall Game init" << endl;
    }
    void start() override {
        cout << "FootBall Game start" << endl;
    }
    void end() override {
        cout << "FootBall Game end" << endl;
    }
};

class FPSGame : public Game {
public:
    void init() override {
        cout << "FPS Game Game init" << endl;
    }
    void start() override {
        cout << "FPS Game start" << endl;
    }
    void end() override {
        cout << "FPS Game end" << endl;
    }
};

class GamePlayer {
public:
    GamePlayer() = delete;
    GamePlayer(Game* game) {
        game_ = game;
    }
    void play() {
        /* work flow*/  
        game_->init();
        game_->start();
        game_->end();
    }

    virtual ~GamePlayer() {
    }

private:
    Game* game_;
};

int main (int argc, char *argv[])
{
    Game* game = new FPSGame;
    GamePlayer* gameplayer = new GamePlayer(game);
    gameplayer->play();

    delete game;
    delete gameplayer;
    return 0;
}
