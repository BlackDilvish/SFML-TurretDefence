#include "Menu.h"

Menu::Menu(sf::RenderWindow &window)
{
    initTex();

    menuCanvas.setSize(sf::Vector2f(420,window.getSize().y));
    menuCanvas.setPosition(sf::Vector2f(window.getSize().x-420,0));
    menuCanvas.setTexture(&canvasTex);

    exitButton.setSize(sf::Vector2f(40.f,40.f));
    exitButton.setTexture(&closeTex);
    exitButton.setPosition(sf::Vector2f(menuCanvas.getPosition().x+menuCanvas.getSize().x-2*exitButton.getSize().x,exitButton.getSize().y));

    pauseButton.setSize(sf::Vector2f(40.f,40.f));
    pauseButton.setTexture(&pauseTex);
    pauseButton.setPosition(sf::Vector2f(menuCanvas.getPosition().x+pauseButton.getSize().x,pauseButton.getSize().y));

    redHealthBar.setSize(sf::Vector2f(menuCanvas.getSize().x-40.f,40.f));
    redHealthBar.setPosition(sf::Vector2f(menuCanvas.getPosition().x+20.f,pauseButton.getPosition().y + 2*redHealthBar.getSize().y));
    redHealthBar.setFillColor(sf::Color::Red);

    greenHealhBar.setSize(redHealthBar.getSize());
    greenHealhBar.setPosition(redHealthBar.getPosition());
    greenHealhBar.setFillColor(sf::Color::Green);

    baseHealthPoints.setFont(defaultFont);
    baseHealthPoints.setString("Zdrowie");
    baseHealthPoints.setPosition(redHealthBar.getPosition());

    buyTurretButton.setSize(sf::Vector2f(200.f,75.f));
    buyTurretButton.setTexture(&buyTex);
    buyTurretButton.setPosition(sf::Vector2f(menuCanvas.getPosition().x + menuCanvas.getSize().x/2.f - buyTurretButton.getSize().x/2.f, redHealthBar.getPosition().y + 2*buyTurretButton.getSize().y));

    sellTurretButton.setSize(buyTurretButton.getSize());
    sellTurretButton.setTexture(&sellTex);
    sellTurretButton.setPosition(sf::Vector2f(buyTurretButton.getPosition().x, buyTurretButton.getPosition().y + 2*sellTurretButton.getSize().y));

    upgradeButton.setSize(buyTurretButton.getSize());
    upgradeButton.setTexture(&upgradeTex);
    upgradeButton.setPosition(sf::Vector2f(sellTurretButton.getPosition().x, sellTurretButton.getPosition().y + 2*upgradeButton.getSize().y));

    returnButton.setSize(sf::Vector2f(100.f,40.f));
    returnButton.setTexture(&returnTex);
    returnButton.setPosition(sf::Vector2f(menuCanvas.getPosition().x + menuCanvas.getSize().x/2.f - returnButton.getSize().x/2.f, menuCanvas.getSize().y - 2*returnButton.getSize().y));

    //-----PAUSE-----//

    pauseCanvas.setSize(sf::Vector2f(window.getSize().x,window.getSize().y));
    pauseCanvas.setFillColor(sf::Color(0,0,0,100));

    unpauseButton.setSize(sf::Vector2f(200.f,200.f));
    unpauseButton.setTexture(&unpauseTex);
    unpauseButton.setPosition(sf::Vector2f(pauseCanvas.getSize().x/2.f-unpauseButton.getSize().x/2.f, pauseCanvas.getSize().y/2.f-unpauseButton.getSize().y/2.f));

    //-----BUY-----//

    buyFirstTurret.setSize(sf::Vector2f(75.f,75.f));
    buyFirstTurret.setTexture(&place1Tex);
    buyFirstTurret.setPosition(sf::Vector2f(buyTurretButton.getPosition().x,buyTurretButton.getPosition().y + 2*buyFirstTurret.getSize().y));

    buySecondTurret.setSize(buyFirstTurret.getSize());
    buySecondTurret.setTexture(&place2Tex);
    buySecondTurret.setPosition(sf::Vector2f(buyTurretButton.getPosition().x + buyTurretButton.getSize().x - buySecondTurret.getSize().x, buyTurretButton.getPosition().y + 2*buyFirstTurret.getSize().y));

    buyThirdTurret.setSize(buyFirstTurret.getSize());
    buyThirdTurret.setTexture(&place3Tex);
    buyThirdTurret.setPosition(sf::Vector2f(buyTurretButton.getPosition().x,buyFirstTurret.getPosition().y + 2*buyFirstTurret.getSize().y));

    buyFourthTurret.setSize(buyFirstTurret.getSize());
    buyFourthTurret.setTexture(&place4Tex);
    buyFourthTurret.setPosition(sf::Vector2f(buyTurretButton.getPosition().x + buyTurretButton.getSize().x - buySecondTurret.getSize().x,buyFirstTurret.getPosition().y + 2*buyFirstTurret.getSize().y));

    currentState=Menu::home;

    //-----GameOver-----//

    gameoverCanvas.setSize(sf::Vector2f(window.getSize()));
    gameoverCanvas.setFillColor(sf::Color(255,0,0,100));

    gameoverNewgameButton.setSize(sf::Vector2f(270.f, 100.f));
    gameoverNewgameButton.setTexture(&newgameTex);
    gameoverNewgameButton.setPosition(sf::Vector2f(gameoverCanvas.getSize().x/2.f - gameoverNewgameButton.getSize().x/2.f, gameoverCanvas.getSize().y/2.f - gameoverNewgameButton.getSize().y/2.f));

    gameoverRestartButton.setSize(gameoverNewgameButton.getSize());
    gameoverRestartButton.setTexture(&restartTex);
    gameoverRestartButton.setPosition(sf::Vector2f(gameoverNewgameButton.getPosition().x, gameoverCanvas.getSize().y/2.f + gameoverRestartButton.getSize().y ));

    gameoverExitButton.setSize(gameoverNewgameButton.getSize());
    gameoverExitButton.setTexture(&exitTex);
    gameoverExitButton.setPosition(sf::Vector2f(gameoverCanvas.getSize().x/2.f - gameoverExitButton.getSize().x/2.f, gameoverCanvas.getSize().y/2.f + 3*gameoverNewgameButton.getSize().y));

    //-----WIN-----//

    winCanvas.setSize(sf::Vector2f(window.getSize()));
    winCanvas.setFillColor(sf::Color(0,255,0,100));

    //-----Money-----//

    startMoney = 300;
    money = startMoney;

    initText();

    }

Menu::~Menu()
{

}

void Menu::initTex()
{
    defaultFont.loadFromFile("assets/fonts/Lato.ttf");

    canvasTex.loadFromFile("assets/images/menuTex.png");

    closeTex.loadFromFile("assets/images/closeTex.png");
    pauseTex.loadFromFile("assets/images/pauseTex.png");
    unpauseTex.loadFromFile("assets/images/playTex.png");
    returnTex.loadFromFile("assets/images/returnTex.png");

    buyTex.loadFromFile("assets/images/buyTex.png");
    sellTex.loadFromFile("assets/images/sellTex.png");
    upgradeTex.loadFromFile("assets/images/upgradeTex.png");

    place1Tex.loadFromFile("assets/images/buy1Tex.png");
    place2Tex.loadFromFile("assets/images/buy2Tex.png");
    place3Tex.loadFromFile("assets/images/buy3Tex.png");
    place4Tex.loadFromFile("assets/images/buy4Tex.png");

    newgameTex.loadFromFile("assets/images/newgameTex.png");
    restartTex.loadFromFile("assets/images/restartTex.png");
    exitTex.loadFromFile("assets/images/exitTex.png");
}

void Menu::initText()
{
    std::stringstream temp;

    buyTurretText.setFont(defaultFont);
    buyTurretText.setString("Kup wieze");
    buyTurretText.setPosition(sf::Vector2f(buyTurretButton.getPosition().x,buyTurretButton.getPosition().y + buyTurretButton.getSize().y));
    drawBuyText = false;

    sellTurretText.setFont(defaultFont);
    sellTurretText.setString("Sprzedaj wieze");
    sellTurretText.setPosition(sf::Vector2f(sellTurretButton.getPosition().x,sellTurretButton.getPosition().y + sellTurretButton.getSize().y));
    drawSellText = false;

    upgradeText.setFont(defaultFont);
    upgradeText.setString("Ulepsz wieze");
    upgradeText.setPosition(sf::Vector2f(upgradeButton.getPosition().x, upgradeButton.getPosition().y + upgradeButton.getSize().y));
    drawUpgradeText = false;

    buyFirstText.setFont(defaultFont);
    temp<<Turret::first<<"$";
    buyFirstText.setString(temp.str());
    temp.str("");
    buyFirstText.setPosition(buyFirstTurret.getPosition().x, buyFirstTurret.getPosition().y + buyFirstTurret.getSize().y);
    drawFirstText=false;

    buySecondText.setFont(defaultFont);
    temp<<Turret::second<<"$";
    buySecondText.setString(temp.str());
    temp.str("");
    buySecondText.setPosition(buySecondTurret.getPosition().x, buySecondTurret.getPosition().y + buySecondTurret.getSize().y);
    drawSecondText=false;

    buyThirdText.setFont(defaultFont);
    temp<<Turret::third<<"$";
    buyThirdText.setString(temp.str());
    temp.str("");
    buyThirdText.setPosition(buyThirdTurret.getPosition().x, buyThirdTurret.getPosition().y + buyThirdTurret.getSize().y);
    drawThirdText=false;

    buyFourthText.setFont(defaultFont);
    temp<<Turret::fourth<<"$";
    buyFourthText.setString(temp.str());
    temp.str("");
    buyFourthText.setPosition(buyFourthTurret.getPosition().x, buyFourthTurret.getPosition().y + buyFourthTurret.getSize().y);
    drawFourthText=false;

    gameoverText.setFont(defaultFont);
    gameoverText.setString("Koniec gry...");
    gameoverText.setCharacterSize(128);
    gameoverText.setFillColor(sf::Color(220,0,0));
    gameoverText.setPosition(sf::Vector2f(gameoverNewgameButton.getPosition().x - 180, gameoverNewgameButton.getPosition().y - 300));

    winText.setFont(defaultFont);
    winText.setString("Wygrana!");
    winText.setCharacterSize(128);
    winText.setFillColor(sf::Color(15, 148, 0));
    winText.setPosition(sf::Vector2f(gameoverText.getPosition().x + 30.f, gameoverText.getPosition().y));

    finishTimeText.setFont(defaultFont);
    finishTimeText.setString("Czas gry: ");
    finishTimeText.setPosition(sf::Vector2f(gameoverText.getPosition().x + 170.f,gameoverText.getPosition().y + 200.f));

    moneyText.setFont(defaultFont);
    moneyText.setString("Monety: 300");
    moneyText.setPosition(sf::Vector2f(redHealthBar.getPosition().x,redHealthBar.getPosition().y + redHealthBar.getSize().y));

    availableTurretsText.setFont(defaultFont);
    availableTurretsText.setString("");
    availableTurretsText.setPosition(sf::Vector2f(menuCanvas.getPosition().x + 50.f,buyFirstTurret.getPosition().y-2*buyFirstTurret.getSize().y));
}

void Menu::updateTurretTexts(int availableTurrets)
{
    std::stringstream ss;
    ss<<"Dostepne wiezyczki: "<<availableTurrets;
    availableTurretsText.setString(ss.str());
}

void Menu::updateTimeText(float currTime)
{
    std::stringstream ss;
    ss<<"Czas gry: "<<currTime<<" s";
    finishTimeText.setString(ss.str());
}

void Menu::update(sf::Vector2i &mousePos,bool &gameOver,bool &restart,bool &newgame,int &availableTurret,float currTime)
{
    if(exitButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
    {
        exitButton.setFillColor(sf::Color::Red);

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            gameOver=true;
    }
    else
        exitButton.setFillColor(sf::Color::White);

    switch(currentState)
    {
    case Menu::home:
        if(pauseButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        {
            pauseButton.setFillColor(sf::Color(167, 167, 167));

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                currentState = Menu::paused;
        }
        else if(buyTurretButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        {
            buyTurretButton.setFillColor(sf::Color::Green);
            drawBuyText = true;

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                drawBuyText = false;
                currentState = Menu::buy;
            }
        }
        else if(sellTurretButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        {
            sellTurretButton.setFillColor(sf::Color::Red);
            drawSellText = true;

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                drawSellText = false;
                currentState = Menu::sell;
            }
        }
        else if(upgradeButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        {
            upgradeButton.setFillColor(sf::Color::Cyan);
            drawUpgradeText = true;

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                drawUpgradeText = false;
                currentState = Menu::upgrade;
            }
        }
        else
        {
            pauseButton.setFillColor(sf::Color::White);
            buyTurretButton.setFillColor(sf::Color::White);
            sellTurretButton.setFillColor(sf::Color::White);
            upgradeButton.setFillColor(sf::Color::White);
            drawBuyText = false;
            drawSellText = false;
            drawUpgradeText = false;
        }
        break;
    case Menu::paused:
        if(unpauseButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        {
            unpauseButton.setFillColor(sf::Color(167, 167, 167));

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                currentState = Menu::home;
        }
        else
            unpauseButton.setFillColor(sf::Color::White);
        break;
    case Menu::buy:
        if(pauseButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        {
            pauseButton.setFillColor(sf::Color(167, 167, 167));

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                currentState = Menu::paused;
        }
        else if(buyFirstTurret.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        {
            buyFirstTurret.setFillColor(sf::Color::Yellow);
            drawFirstText = true;

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(money >= Turret::first && availableTurret>0)
                {
                    availableTurret--;
                    updateTurretTexts(availableTurret);

                    drawFirstText = false;
                    setMoney(money - Turret::first);
                    currentState = Menu::deploy;
                    chosenTurret = 1;
                }
                else
                    std::cout<<"Nie stac cie na to\n";
            }
        }
        else if(buySecondTurret.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        {
            buySecondTurret.setFillColor(sf::Color::Yellow);
            drawSecondText = true;

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(money >= Turret::second && availableTurret>0)
                {
                    availableTurret--;
                    updateTurretTexts(availableTurret);

                    drawSecondText = false;
                    setMoney(money - Turret::second);
                    currentState = Menu::deploy;
                    chosenTurret = 2;
                }
                else
                    std::cout<<"Nie stac cie na to\n";
            }
        }
        else if(buyThirdTurret.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        {
            buyThirdTurret.setFillColor(sf::Color::Yellow);
            drawThirdText = true;

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(money >= Turret::third && availableTurret>0)
                {
                    availableTurret--;
                    updateTurretTexts(availableTurret);

                    drawThirdText = false;
                    setMoney(money - Turret::third);
                    currentState = Menu::deploy;
                    chosenTurret = 3;
                }
                else
                    std::cout<<"Nie stac cie na to\n";
            }
        }
        else if(buyFourthTurret.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        {
            buyFourthTurret.setFillColor(sf::Color::Yellow);
            drawFourthText = true;

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(money >= Turret::fourth && availableTurret>0)
                {
                    availableTurret--;
                    updateTurretTexts(availableTurret);

                    drawFourthText = false;
                    setMoney(money - Turret::fourth);
                    currentState = Menu::deploy;
                    chosenTurret = 4;
                }
                else
                    std::cout<<"Nie stac cie na to\n";
            }
        }
        else if(returnButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        {
            returnButton.setFillColor(sf::Color(167, 167, 167));

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                currentState = Menu::home;
            }
        }
        else
        {
            pauseButton.setFillColor(sf::Color::White);
            returnButton.setFillColor(sf::Color::White);
            buyFirstTurret.setFillColor(sf::Color::White);
            buySecondTurret.setFillColor(sf::Color::White);
            buyThirdTurret.setFillColor(sf::Color::White);
            buyFourthTurret.setFillColor(sf::Color::White);

            drawFirstText = false;
            drawSecondText = false;
            drawThirdText = false;
            drawFourthText = false;
        }
        break;
    case Menu::sell:
        if(pauseButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        {
            pauseButton.setFillColor(sf::Color(167, 167, 167));

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                currentState = Menu::paused;
        }
        else if(returnButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        {
            returnButton.setFillColor(sf::Color(167, 167, 167));

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                currentState = Menu::home;
            }
        }
        else
        {
            returnButton.setFillColor(sf::Color::White);
            pauseButton.setFillColor(sf::Color::White);
        }
        break;
    case Menu::upgrade:
        if(pauseButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        {
            pauseButton.setFillColor(sf::Color(167, 167, 167));

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                currentState = Menu::paused;
        }
        else if(returnButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        {
            returnButton.setFillColor(sf::Color(167, 167, 167));

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                currentState = Menu::home;
            }
        }
        else
        {
            returnButton.setFillColor(sf::Color::White);
            pauseButton.setFillColor(sf::Color::White);
        }
        break;
    case Menu::deploy:
        if(pauseButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        {
            pauseButton.setFillColor(sf::Color(167, 167, 167));

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                currentState = Menu::paused;
        }
        else
            pauseButton.setFillColor(sf::Color::White);
        break;
    case Menu::gameover:
        if(gameoverNewgameButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        {
            gameoverNewgameButton.setFillColor(sf::Color::Green);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                newgame=true;
        }
        else if(gameoverRestartButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        {
            gameoverRestartButton.setFillColor(sf::Color::Cyan);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                restart=true;
        }
        else if(gameoverExitButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        {
            gameoverExitButton.setFillColor(sf::Color::Red);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                gameOver=true;
        }
        else
        {
            gameoverNewgameButton.setFillColor(sf::Color::White);
            gameoverExitButton.setFillColor(sf::Color::White);
            gameoverRestartButton.setFillColor(sf::Color::White);
        }
        break;
    case Menu::win:
        if(gameoverNewgameButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        {
            gameoverNewgameButton.setFillColor(sf::Color::Green);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                newgame=true;
        }
        else if(gameoverExitButton.getGlobalBounds().contains(sf::Vector2f(mousePos)))
        {
            gameoverExitButton.setFillColor(sf::Color::Red);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                gameOver=true;
        }
        else
        {
            gameoverNewgameButton.setFillColor(sf::Color::White);
            gameoverExitButton.setFillColor(sf::Color::White);
        }
        break;
    default:
        break;
    }

}

void Menu::render(sf::RenderTarget &window)
{
    window.draw(menuCanvas);

    window.draw(exitButton);
    window.draw(pauseButton);

    window.draw(redHealthBar);
    window.draw(greenHealhBar);
    window.draw(baseHealthPoints);

    window.draw(moneyText);

    switch(currentState)
    {
    case Menu::home:
        window.draw(buyTurretButton);
        window.draw(sellTurretButton);
        window.draw(upgradeButton);

        if(drawBuyText)
            window.draw(buyTurretText);
        if(drawSellText)
            window.draw(sellTurretText);
        if(drawUpgradeText)
            window.draw(upgradeText);
        break;
    case Menu::paused:
        window.draw(pauseCanvas);
        window.draw(unpauseButton);
        break;
    case Menu::buy:
        window.draw(buyFirstTurret);
        window.draw(buySecondTurret);
        window.draw(buyThirdTurret);
        window.draw(buyFourthTurret);
        window.draw(returnButton);

        if(drawFirstText)
            window.draw(buyFirstText);
        if(drawSecondText)
            window.draw(buySecondText);
        if(drawThirdText)
            window.draw(buyThirdText);
        if(drawFourthText)
            window.draw(buyFourthText);
        window.draw(availableTurretsText);
        break;
    case Menu::sell:
        window.draw(returnButton);
        break;
    case Menu::upgrade:
        window.draw(returnButton);
        break;
    case Menu::deploy:
        break;
    case Menu::gameover:
        window.draw(gameoverCanvas);
        window.draw(gameoverNewgameButton);
        window.draw(gameoverRestartButton);
        window.draw(gameoverExitButton);
        window.draw(gameoverText);
        break;
    case Menu::win:
        window.draw(winCanvas);
        window.draw(gameoverNewgameButton);
        window.draw(gameoverExitButton);
        window.draw(winText);
        window.draw(finishTimeText);
        break;
    default:
        break;
    }
}

void Menu::setHealth(size_t currentHealthPoints,size_t maxHealth)
{
    greenHealhBar.setSize(sf::Vector2f((currentHealthPoints/float(maxHealth))*redHealthBar.getSize().x,redHealthBar.getSize().y));
}

size_t Menu::getState()             { return currentState;           }

void Menu::setState(size_t state)   { currentState = state;          }

size_t Menu::getChosenTurret()      { return chosenTurret;           }

void Menu::resetChosenTurret()      { chosenTurret = 0;
                                      currentState = Menu::buy;      }

int Menu::getMoney()                { return money;                  }

void Menu::setMoney(int newMoney)   { money = newMoney;
                                      std::stringstream ss;
                                      ss<<"Monety "<<money;
                                      moneyText.setString(ss.str()); }
