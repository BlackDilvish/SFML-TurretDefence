#ifndef MENU_H
#define MENU_H

#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include<sstream>
#include"Turret.h"

class Menu
{
    public:
        Menu(sf::RenderWindow &window);
        virtual ~Menu();

        void update(sf::Vector2i &mousePos,bool &gameOver,bool &restart,bool &newgame,int &availableTurret,float currTime);
        void render(sf::RenderTarget &window);

        void setHealth(size_t currentHealthPoints,size_t maxHealth);
        size_t getState();
        void setState(size_t state);
        size_t getChosenTurret();
        void resetChosenTurret();
        int getMoney();
        void setMoney(int newMoney);
        void updateTurretTexts(int availableTurrets);
        void updateTimeText(float currTime);

        enum State{home, buy, sell, upgrade, deploy, paused, gameover, win};

    protected:

    private:
        void initTex();
        void initText();

        size_t currentState;
        size_t chosenTurret;

        sf::RectangleShape menuCanvas;
        sf::Font defaultFont;

        //Buttons
            //Home
        sf::RectangleShape exitButton;
        sf::RectangleShape pauseButton;

        sf::RectangleShape buyTurretButton;
        sf::RectangleShape sellTurretButton;
        sf::RectangleShape upgradeButton;

        sf::RectangleShape returnButton;
            //Pause
        sf::RectangleShape unpauseButton;
        sf::RectangleShape pauseCanvas;
            //Buy
        sf::RectangleShape buyFirstTurret;
        sf::RectangleShape buySecondTurret;
        sf::RectangleShape buyThirdTurret;
        sf::RectangleShape buyFourthTurret;
            //GameOver
        sf::RectangleShape gameoverCanvas;
        sf::RectangleShape gameoverNewgameButton;
        sf::RectangleShape gameoverRestartButton;
        sf::RectangleShape gameoverExitButton;
            //Win
        sf::RectangleShape winCanvas;
        //Buttons - End

        //Text
        sf::Text baseHealthPoints;
        sf::Text gameoverText;
        sf::Text winText;
        sf::Text finishTimeText;

        sf::Text buyTurretText;
        sf::Text sellTurretText;
        sf::Text upgradeText;

        sf::Text buyFirstText;
        sf::Text buySecondText;
        sf::Text buyThirdText;
        sf::Text buyFourthText;

        sf::Text availableTurretsText;

        bool drawBuyText;
        bool drawSellText;
        bool drawUpgradeText;

        bool drawFirstText;
        bool drawSecondText;
        bool drawThirdText;
        bool drawFourthText;

        //Health
        sf::RectangleShape redHealthBar;
        sf::RectangleShape greenHealhBar;

        //Money
        int money;
        int startMoney;
        sf::Text moneyText;

        //Textures
        sf::Texture canvasTex;

        sf::Texture closeTex;
        sf::Texture pauseTex;
        sf::Texture unpauseTex;
        sf::Texture returnTex;

        sf::Texture buyTex;
        sf::Texture sellTex;
        sf::Texture upgradeTex;

        sf::Texture place1Tex;
        sf::Texture place2Tex;
        sf::Texture place3Tex;
        sf::Texture place4Tex;

        sf::Texture exitTex;
        sf::Texture newgameTex;
        sf::Texture restartTex;

};

#endif // MENU_H
