#include "PreCompileHeaders/PCH.hpp"
#include "Engine/GameEngine.hpp"
int main(){
    srand(time(0));
    GameEngine gameengine;
    while(gameengine.Running()){
        gameengine.UpdateEvents();
        gameengine.Update();
        gameengine.Render();
    }
    return 0;
}