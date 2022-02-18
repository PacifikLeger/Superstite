#pragma once
#include "../PreCompileHeaders/PCH.hpp"
class Collision {
public:
    Collision(){
    }
    void CheckCollision(std::unordered_map<int, sf::FloatRect> Hitbox, std::unordered_map<int, bool> UserInputtable, sf::Vector2f &UserInputtableVector){
        //Broad Phase or sweep and prune
        //UserInputtable component (player most likely)
        for(auto& i : UserInputtable){
            //Looping through all the hitboxes
            for(auto& j : Hitbox){
                if(Intersect(j.second, Hitbox[i.first])){
                    UserInputtableVector.x = 0;
                    UserInputtableVector.y = 0;
                }
            }
        }
    }
private:
    bool Intersect(sf::FloatRect HitBoxA, sf::FloatRect HitBoxB){
        if((HitBoxA.left <= HitBoxB.left + HitBoxB.width && HitBoxA.left + HitBoxA.width >= HitBoxB.left) &&
        (HitBoxA.top <= HitBoxB.top + HitBoxB.height && HitBoxA.top + HitBoxA.height >= HitBoxB.top)){
            std::cout << HitBoxA.top << "\n";
            return true;
        }
        else 
            return false;
    }
};