#pragma once
#include "../PreCompileHeaders/PCH.hpp"
#include "../ECS/ECS.hpp"
#include "../EventHandling/InputBroker.hpp"
class Game{
public:
    Game();
    //Objects
    //InputBroker
    InputBroker inputbroker;
    //ECS
    ECS ecs;
    //member functions
    //General state functions
    void Update(float DeltaTime);
    void UpdateEvents(sf::Event Events);
    void Render(sf::RenderWindow &window);
    //GameState functions
    void GameStateUpdate(float DeltaTime);
    void GameStateUpdateEvents(sf::Event Events);
    void GameStateRender(sf::RenderWindow &window);
    //GameState sub functions
    void RegisterGeneratedMap();
    void RegisterPlayer();
    //Variables
    //WindowSize cause I dont know how to put it globally
    sf::Vector2i WindowSize;
    //TileMapObjects
    //Grass
    sf::VertexArray Grass;
    sf::Texture Grass_t;
    sf::Vector2i MapSize;
    //Events
    std::queue<sf::Event> EventStream;
    //Gamestate
    bool InGameState;
    sf::View GameStateView;

private:
};