#pragma once
#include "../PreCompileHeaders/PCH.hpp"
#include "../Game/Game.hpp"
class GameEngine {
public:
    GameEngine();
    ~GameEngine() {}
    bool Running();
    void Render();
    void Update();
    void UpdateEvents();
    sf::Vector2f WindowSize;
    sf::RenderWindow Window;
    sf::Clock Clock;
    float DeltaTime;
    float DeltaTimeMult;
    Game game;
private:

};