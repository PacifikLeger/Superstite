#pragma once
#include "../PreCompileHeaders/PCH.hpp"
class InputBroker {
public:
    InputBroker(){
        KeyStates.reserve(sf::Keyboard::KeyCount);
    }
    bool GetKey(sf::Keyboard::Key Key) const{
        return KeyStates.at(Key);
    }
private:
    std::unordered_map<sf::Keyboard::Key, bool> KeyStates;
};