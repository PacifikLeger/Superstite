#pragma once
#include "../PreCompileHeaders/PCH.hpp"
class InputBroker {
public:
    InputBroker(){
    }
    bool PushKey(sf::Keyboard::Key Key, bool Value){
        KeyStates[Key] = Value;
    }
    bool GetKey(sf::Keyboard::Key Key) const{
        return KeyStates[Key];
    }
private:
    std::array<bool, sf::Keyboard::KeyCount> KeyStates;
};