#include "GameEngine.hpp"
GameEngine::GameEngine(): WindowSize(1000, 1000), Window(sf::VideoMode(WindowSize.x, WindowSize.y), "sfml", sf::Style::Titlebar | sf::Style::Close), DeltaTimeMult(60){
}
bool GameEngine::Running(){
    if(Window.isOpen())
        return true;
    else
        return false;
}
void GameEngine::Update(){
    game.Update(DeltaTime*DeltaTimeMult);
}
void GameEngine::UpdateEvents(){
    sf::Event Events;
    while(Window.pollEvent(Events)){
        switch(Events.type){
            case sf::Event::Closed:
                Window.close();
                break;
            case sf::Event::KeyPressed:
                if(Events.key.code == sf::Keyboard::Escape)
                    Window.close();
                break;
            default:
                break;
        }
        game.UpdateEvents(Events);
    }
}
void GameEngine::Render(){
    DeltaTime = Clock.restart().asSeconds();
    Window.clear(sf::Color::Red);
    game.Render(Window);
    Window.display();
}