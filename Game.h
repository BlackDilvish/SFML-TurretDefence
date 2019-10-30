#ifndef GAME_H
#define GAME_H

#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<stdlib.h>
#include<iomanip>
#include<math.h>
#include "Menu.h"
#include "Enemy.h"
#include "Turret.h"
#include "FirstTurret.h"
#include "SecondTurret.cpp"
#include "ThirdTurret.cpp"
#include "FourthTurret.cpp"
#include "bowIcon.c"

#define MAP_MAX 5

class Game
{
    public:
        Game();
        virtual ~Game();

        const bool isPlaying();

        void update();
        void render();

    protected:

    private:
        //init_fun
        void initWindow();
        void initVariables();
        void initText();
        void initTextures();
        void initGrids();
        void initMap(size_t mapNr);
        void initTurrets();

        //update_fun
        void pollEvents();
        void updateMouse();
        void updateEnemies();
        void updateTime();
        void updateGameOver();
        void updateTurrets();
        void updateText();

        //render_fun
        void renderGrids();
        void renderEnemies();
        void renderTurrets();
        void renderText();

        //rest_fun
        int v2iToGrid(sf::Vector2i &mousePos);

        //---------------------------------//

        //variables
        sf::RenderWindow *window;
        sf::Vector2i mousePos;
        size_t baseHealthPoints;
        size_t currentHealtPoints;

        sf::Font font;
        //Grids
        float gridSize;
        size_t numberOfYgrids;
        size_t numberOfXgrids;

        sf::RectangleShape grid;

        std::vector<sf::RectangleShape> gridsVector;
        std::vector<int> gridsTypeVector;

        sf::Color gridDefault;
        sf::Color gridHover;

        sf::Texture grassTex;
        sf::Texture pathTex;
        sf::Texture baseTex;

        std::string map1;
        std::string map2;

        int currentMap;

        //Menu
        Menu *menu;
        bool gameOver;
        bool restart;
        bool newgame;

        //Enemies
        std::vector<Enemy> enemies;

        int enemiesHP;
        float spawnCooldown;
        int enemiesPrize;
        int enemiesInWave;
        int waveMax;
        int bossHP;

        sf::Text waveText;
        //Turrets
        std::vector<Turret> turrets;
        std::vector<FirstTurret> turrets1;
        std::vector<SecondTurret> turrets2;
        std::vector<ThirdTurret> turrets3;
        std::vector<FourthTurret> turrets4;

        FirstTurret *cursorTemp1;
        SecondTurret *cursorTemp2;
        ThirdTurret *cursorTemp3;
        FourthTurret *cursorTemp4;

        int availableTurrets;
        //Time
        sf::Clock clock;

        float enemyTimer;
        sf::Time gameTimer;
        //Textures
        sf::Texture angel1;
        sf::Texture angel2;
        sf::Texture angel3;

        sf::Texture golem1;
        sf::Texture golem2;
        sf::Texture golem3;

        sf::Texture turretTex1v1;
        sf::Texture turretTex1v2;
        sf::Texture turretTex1v3;

        sf::Texture turretTex2v1;
        sf::Texture turretTex2v2;
        sf::Texture turretTex2v3;

        sf::Texture turretTex3v1;
        sf::Texture turretTex3v2;
        sf::Texture turretTex3v3;

        sf::Texture turretTex4v1;
        sf::Texture turretTex4v2;
        sf::Texture turretTex4v3;
};

#endif // GAME_H
