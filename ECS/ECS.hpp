#pragma once
#include "../PreCompileHeaders/PCH.hpp"
class ECS{
public:
    ECS();
    int EntityID;
    //components
    std::unordered_map<int, std::pair<float, float>> Position;
    std::unordered_map<int, signed int> Health;
    std::unordered_map<int, std::string> Texture;
    std::unordered_map<std::string, sf::Texture> TextureMaping;
    std::unordered_map<int, std::pair<float, float>> Speed;
    std::unordered_map<int, bool> Renderable;
    std::unordered_map<int, bool> UserInputtable;
    std::unordered_map<int, bool> Breakable;
    std::unordered_map<int, bool> Placeable;
    std::unordered_map<int, bool> MapGenerated;
};