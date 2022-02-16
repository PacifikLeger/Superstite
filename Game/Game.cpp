#include "Game.hpp"
Game::Game(): WindowSize(1000, 1000), InGameState(true){
    //Temporary just until I make starting game functions its actually horrible lol
    if(InGameState){
        GameStateView.reset(sf::FloatRect(0, 0, 1000, 1000));
        GameStateView.zoom(0.3);
        MapSize = sf::Vector2i(50, 50);
        //Setting the texture maping here cause idk where else TODO change this garbage
        sf::Texture MapedTexture;
        if(!MapedTexture.loadFromFile("Assets/PlayerTexture.png")) {std::cout << "Error loading Player" << "\n";}
        ecs.TextureMaping.insert(std::make_pair("Player", MapedTexture));
        if(!MapedTexture.loadFromFile("Assets/TreeTexture.png")) {std::cout << "Error loading Tree" << "\n";}
        ecs.TextureMaping.insert(std::make_pair("Tree", MapedTexture));
        RegisterGeneratedMap();
        RegisterPlayer();
    }
}
void Game::Update(float DeltaTime){
    //checking 
    if(InGameState){
        GameStateUpdate(DeltaTime);
    }
}
void Game::UpdateEvents(sf::Event Events){
    if(InGameState){
        GameStateUpdateEvents(Events);
    }
}
void Game::Render(sf::RenderWindow &Window){
    if(InGameState){
        GameStateRender(Window);
    }
}
//Corresponding member functions
//GameState
void Game::GameStateUpdate(float DeltaTime){
    //UserInputtable component assumes that it is a player
    for(auto& i : ecs.UserInputtable){
        //Setting gamestateview center to the userinputtable entity
        GameStateView.setCenter(ecs.Position[i.first].first, ecs.Position[i.first].second);
        //No accessing a emmpty queue
        if(!EventStream.empty()){
            switch(EventStream.back().type){
                case sf::Event::KeyPressed:
                    if(EventStream.back().key.code == sf::Keyboard::W){
                        ecs.Position[i.first].second -= ecs.Speed[i.first].second*DeltaTime;
                    }
                    if(EventStream.back().key.code == sf::Keyboard::S){
                        ecs.Position[i.first].second += ecs.Speed[i.first].second*DeltaTime;
                    }
                    if(EventStream.back().key.code == sf::Keyboard::A){
                        ecs.Position[i.first].first -= ecs.Speed[i.first].first*DeltaTime;
                    }
                    if(EventStream.back().key.code == sf::Keyboard::D){
                        ecs.Position[i.first].first += ecs.Speed[i.first].first*DeltaTime;
                    }
                break;
                case sf::Event::KeyReleased:
                    if(EventStream.back().key.code == sf::Keyboard::W){
                        EventStream.pop();
                    }
                    if(EventStream.back().key.code == sf::Keyboard::S){
                        EventStream.pop();
                    }
                    if(EventStream.back().key.code == sf::Keyboard::A){
                        EventStream.pop();
                    }
                    if(EventStream.back().key.code == sf::Keyboard::D){
                        EventStream.pop();
                    }
                break;
                default:
                break;
            }
            
        }
    }
}
void Game::GameStateUpdateEvents(sf::Event Events){
    switch(Events.type){
        case sf::Event::KeyPressed:
            if(Events.key.code == sf::Keyboard::W){
                EventStream.push(Events);
            }
            if(Events.key.code == sf::Keyboard::S){
                EventStream.push(Events);
            }
            if(Events.key.code == sf::Keyboard::A){
                EventStream.push(Events);
            }
            if(Events.key.code == sf::Keyboard::D){
                EventStream.push(Events);
            }
        break;
        case sf::Event::KeyReleased:
            if(Events.key.code == sf::Keyboard::W){
                EventStream.push(Events);
            }
            if(Events.key.code == sf::Keyboard::S){
                EventStream.push(Events);
            }
            if(Events.key.code == sf::Keyboard::A){
                EventStream.push(Events);
            }
            if(Events.key.code == sf::Keyboard::D){
                EventStream.push(Events);
            }
        break;
        default:
        break;
    }
    
}
void Game::GameStateRender(sf::RenderWindow &Window){
    //Game background
    Window.clear(sf::Color(100, 149, 237));
    //Setting the view
    Window.setView(GameStateView);
    //Tilemap loopp
    Window.draw(Grass, &Grass_t);
    std::unordered_map<std::string, sf::VertexArray> Buffer;
    sf::RenderStates RenderState;
    sf::VertexArray Vertices(sf::Quads, 4);
    for(auto& i : ecs.Texture){
        Vertices.clear();
        Vertices.append(sf::Vertex(sf::Vector2f(ecs.Position[i.first].first, ecs.Position[i.first].second), sf::Vector2f(0, 0)));
        Vertices.append(sf::Vertex(sf::Vector2f(ecs.Position[i.first].first + ecs.TextureMaping[i.second].getSize().x, ecs.Position[i.first].second), sf::Vector2f(ecs.TextureMaping[i.second].getSize().x, 0)));
        Vertices.append(sf::Vertex(sf::Vector2f(ecs.Position[i.first].first + ecs.TextureMaping[i.second].getSize().x, ecs.Position[i.first].second + ecs.TextureMaping[i.second].getSize().y), sf::Vector2f(ecs.TextureMaping[i.second].getSize().x, ecs.TextureMaping[i.second].getSize().y)));
        Vertices.append(sf::Vertex(sf::Vector2f(ecs.Position[i.first].first, ecs.Position[i.first].second + ecs.TextureMaping[i.second].getSize().y), sf::Vector2f(0, ecs.TextureMaping[i.second].getSize().y)));
        RenderState.texture = &ecs.TextureMaping[i.second];
        Window.draw(Vertices, RenderState);
    }
}
//Game functions 
//GameState registry
//Registers the map when starting a game
void Game::RegisterGeneratedMap(){
    Grass.setPrimitiveType(sf::Quads);
    Grass.resize(MapSize.x*MapSize.y*4);
    sf::Vertex GrassV[4];
    Grass_t.loadFromFile("Assets/GrassTexture.png");
    //loops for the entire map size
    for(int x = 0; x <= MapSize.x; x++){
        for(int y = 0; y <= MapSize.y; y++){
            //Spawn grass
            GrassV[0].position = sf::Vector2f(x*Grass_t.getSize().x, y*Grass_t.getSize().y);
            GrassV[1].position = sf::Vector2f(x*Grass_t.getSize().x + Grass_t.getSize().x, y*Grass_t.getSize().y);
            GrassV[2].position = sf::Vector2f(x*Grass_t.getSize().x + Grass_t.getSize().x, y*Grass_t.getSize().y + Grass_t.getSize().y);
            GrassV[3].position = sf::Vector2f(x*Grass_t.getSize().x, y*Grass_t.getSize().y + Grass_t.getSize().y);
            GrassV[0].texCoords = sf::Vector2f(0, 0);
            GrassV[1].texCoords = sf::Vector2f(Grass_t.getSize().x, 0);
            GrassV[2].texCoords = sf::Vector2f(Grass_t.getSize().x, Grass_t.getSize().y);
            GrassV[3].texCoords = sf::Vector2f(0, Grass_t.getSize().y);
            Grass.append(GrassV[0]);
            Grass.append(GrassV[1]);
            Grass.append(GrassV[2]);
            Grass.append(GrassV[3]);
        }
    }
    //Registering entities in map
    //Variables and objects init
    sf::Vector2i TreeDefMaxPos(MapSize.x - 1, MapSize.y - 1);
    bool TreeDefBreakable = true;
    bool TreeDefPlaceable = true;
    bool TreeDefRenderable = true;
    bool TreeDefMapGenerated = true;
    std::string TreeDefTextureKey = "Tree";
    //Registering the trees
    const siv::PerlinNoise::seed_type Seed = time(0);
    const siv::PerlinNoise Perlin{Seed};
    for(int i = 0; i <= MapSize.x; i++){
        for(int j = 0; j <= MapSize.y; j++){
            const double Noise = Perlin.octave2D_01((i * 0.1), (j * 0.1), 1);
            if(Noise >= 0.6){
                //Position inserting cause ill need to use it in vertices
                ecs.Position.insert(std::make_pair(ecs.EntityID, std::make_pair(i * ecs.TextureMaping[TreeDefTextureKey].getSize().x, j * ecs.TextureMaping[TreeDefTextureKey].getSize().y)));
                //Innserting the default values
                ecs.Breakable.insert(std::make_pair(ecs.EntityID, TreeDefBreakable));
                ecs.Placeable.insert(std::make_pair(ecs.EntityID, TreeDefPlaceable));
                ecs.Renderable.insert(std::make_pair(ecs.EntityID, TreeDefRenderable));
                ecs.MapGenerated.insert(std::make_pair(ecs.EntityID, TreeDefMapGenerated));
                ecs.Texture.insert(std::make_pair(ecs.EntityID, TreeDefTextureKey));
                ecs.EntityID++;
            }
        }
    }
}
//Registers players
void Game::RegisterPlayer(){
        //Variables and object init
        sf::Vector2i PlayerDefMaxPos(MapSize.x - 1, MapSize.y - 1);
        signed int PlayerDefHealth = 100;
        bool PlayerDefRenderable = true;
        bool PlayerDefInputtable = true;
        sf::Vector2f PlayerDefSpeed(5, 5);
        //Setting the texture key to "Player"
        std::string PlayerDefTextureKey = "Player";
        //Position insert here because ill need to use it in vertices
        ecs.Position.insert(std::make_pair(ecs.EntityID, std::make_pair(rand() % PlayerDefMaxPos.x * ecs.TextureMaping[PlayerDefTextureKey].getSize().x, rand() % PlayerDefMaxPos.y * ecs.TextureMaping[PlayerDefTextureKey].getSize().y)));
        //Inserting default values in components
        ecs.Health.insert(std::make_pair(ecs.EntityID, PlayerDefHealth));
        ecs.Renderable.insert(std::make_pair(ecs.EntityID, PlayerDefRenderable));
        ecs.UserInputtable.insert(std::make_pair(ecs.EntityID, PlayerDefInputtable));
        ecs.Speed.insert(std::make_pair(ecs.EntityID, std::make_pair(PlayerDefSpeed.x, PlayerDefSpeed.y)));
        ecs.Texture.insert(std::make_pair(ecs.EntityID, PlayerDefTextureKey));
        //Increments entity id cause random would be chaotic
        ecs.EntityID++;
}
