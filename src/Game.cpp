#include "Game.h"

Game::Game()
{
    initWindow();
    initVariables();
    initTextures();
    initGrids();
    initMap(currentMap);
    initText();
    initTurrets();
}

Game::~Game()
{
    delete window;
    delete menu;

    delete cursorTemp1;
    delete cursorTemp2;
    delete cursorTemp3;
    delete cursorTemp4;
}

//inits

void Game::initWindow()
{
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();

    window=new sf::RenderWindow(mode,"Turret Defence",sf::Style::Fullscreen);

    window->setFramerateLimit(60);
    window->setIcon(bowIcon.width,bowIcon.height,bowIcon.pixel_data);
}

void Game::initVariables()
{
    srand(time(0));

    gridSize=60.f;

    gridDefault=sf::Color::White;
    gridHover=sf::Color(176, 174, 174);

    menu=new Menu(*window);

    gameOver = false;
    restart = false;
    newgame = false;

    baseHealthPoints=10;
    currentHealtPoints=baseHealthPoints;

    font.loadFromFile("assets/fonts/Lato.ttf");

    currentMap = 1;
}

void Game::initText()
{
    waveText.setFont(font);

    updateText();
}

void Game::initTextures()
{
    grassTex.loadFromFile("assets/images/GrassTex.png");
    pathTex.loadFromFile("assets/images/PathTex.png");
    baseTex.loadFromFile("assets/images/BaseTex.png");

    angel1.loadFromFile("assets/images/Angel1.png");
    angel2.loadFromFile("assets/images/Angel2.png");
    angel3.loadFromFile("assets/images/Angel3.png");

    golem1.loadFromFile("assets/images/Golem1.png");
    golem2.loadFromFile("assets/images/Golem2.png");
    golem3.loadFromFile("assets/images/Golem3.png");

    turretTex1v1.loadFromFile("assets/images/Turret1_1.png");
    turretTex2v1.loadFromFile("assets/images/Turret2_1.png");
    turretTex3v1.loadFromFile("assets/images/Turret3_1.png");
    turretTex4v1.loadFromFile("assets/images/Turret4_1.png");
}

void Game::initGrids()
{
    grid.setSize(sf::Vector2f(gridSize,gridSize));
    grid.setFillColor(gridDefault);

    numberOfXgrids= (window->getSize().x - 420)/int(gridSize);
    numberOfYgrids= (window->getSize().y)/int(gridSize);

    for(size_t i=0;i<numberOfYgrids;i++)
        for(size_t j=0;j<numberOfXgrids;j++)
        {
            grid.setPosition(sf::Vector2f(j*gridSize,i*gridSize));
            gridsVector.push_back(grid);
        }
}

void Game::initMap(size_t mapNr)
{
    enemies.clear();
    turrets1.clear();
    turrets2.clear();
    turrets3.clear();
    turrets4.clear();
    gridsTypeVector.clear();

    clock.restart();
    enemyTimer=0;

    currentHealtPoints = baseHealthPoints;
    menu->setHealth(currentHealtPoints,baseHealthPoints);
    menu->setMoney(300);

    std::stringstream ss;
    ss<<"assets/data/level"<<mapNr<<".txt";

    std::ifstream loadFile(ss.str());
    if(loadFile.is_open())
    {
        int temp;
        for(size_t i=0;i<gridsVector.size();i++)
        {
            loadFile>>temp;
            gridsTypeVector.push_back(temp);

            switch(temp)
            {
            case 0:
                gridsVector[i].setTexture(&grassTex); // pole
                break;
            case 1:
                gridsVector[i].setTexture(&pathTex); // droga
                break;
            case 2:
                gridsVector[i].setTexture(&pathTex); // spawn
                break;
            case 3:
                gridsVector[i].setTexture(&baseTex); // baza
                break;
            default:
                break;
            }
        }

        loadFile>>enemiesHP;
        loadFile>>spawnCooldown;
        loadFile>>enemiesPrize;
        loadFile>>waveMax;
        loadFile>>bossHP;
        loadFile>>availableTurrets;

        enemiesInWave=waveMax;
        loadFile.close();

        menu->updateTurretTexts(availableTurrets);
    }

}

void Game::initTurrets()
{
    cursorTemp1 = new FirstTurret(0,gridsVector);
    cursorTemp2 = new SecondTurret(0,gridsVector);
    cursorTemp3 = new ThirdTurret(0,gridsVector);
    cursorTemp4 = new FourthTurret(0,gridsVector);

    cursorTemp1->setTexture(&turretTex1v1);
    cursorTemp2->setTexture(&turretTex2v1);
    cursorTemp3->setTexture(&turretTex3v1);
    cursorTemp4->setTexture(&turretTex4v1);
}

//updates

void Game::pollEvents()
{
    sf::Event event;

    while(window->pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            switch(event.key.code)
            {
            case sf::Keyboard::Escape:
                window->close();
                break;
            case sf::Keyboard::D:
                menu->setState(Menu::gameover);
                break;
            case sf::Keyboard::A:
                menu->updateTimeText(gameTimer.asSeconds());
                menu->setState(Menu::win);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }

}

void Game::updateMouse()
{
    mousePos = sf::Mouse::getPosition(*window);
    int currentGrid = v2iToGrid(mousePos);

    //-----Darker on hover-----//

    for(size_t i=0;i<gridsVector.size();i++)
        if(int(i) == currentGrid && mousePos.x<numberOfXgrids*gridSize)
            gridsVector[i].setFillColor(gridHover);
        else
            gridsVector[i].setFillColor(gridDefault);

    //-----Deploy new turret-----//

    if(menu->getState() == Menu::deploy)
        switch(menu->getChosenTurret())
        {
        case 0:
            std::cout<<"Nie wybrano tureta\n";
            break;
        case 1:
            cursorTemp1->drawTemp=true;
            cursorTemp1->drawRange=true;
            cursorTemp1->shape.setPosition(sf::Vector2f(mousePos.x-cursorTemp1->shape.getSize().x/2.f, mousePos.y-cursorTemp1->shape.getSize().y/2.f));
            cursorTemp1->rangeShape.setPosition(sf::Vector2f(mousePos));

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePos.x<numberOfXgrids*gridSize && gridsTypeVector[currentGrid]==0)
            {
                menu->resetChosenTurret();
                cursorTemp1->drawTemp=false;
                cursorTemp1->drawRange=false;

                gridsTypeVector[currentGrid]=5;
                FirstTurret temp(currentGrid,gridsVector);
                temp.setTexture(&turretTex1v1);
                temp.rangeShape.setPosition(sf::Vector2f(temp.shape.getPosition().x + temp.shape.getSize().x/2.f,temp.shape.getPosition().y + temp.shape.getSize().y/2.f));

                turrets1.push_back(temp);
            }
            break;
        case 2:
            cursorTemp2->drawTemp=true;
            cursorTemp2->drawRange=true;
            cursorTemp2->shape.setPosition(sf::Vector2f(mousePos.x-cursorTemp2->shape.getSize().x/2.f, mousePos.y-cursorTemp2->shape.getSize().y/2.f));
            cursorTemp2->rangeShape.setPosition(sf::Vector2f(mousePos));

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePos.x<numberOfXgrids*gridSize && gridsTypeVector[currentGrid]==0)
            {
                menu->resetChosenTurret();
                cursorTemp2->drawTemp=false;
                cursorTemp2->drawRange=false;

                gridsTypeVector[currentGrid]=5;
                SecondTurret temp(currentGrid,gridsVector);
                temp.setTexture(&turretTex2v1);
                temp.rangeShape.setPosition(sf::Vector2f(temp.shape.getPosition().x + temp.shape.getSize().x/2.f,temp.shape.getPosition().y + temp.shape.getSize().y/2.f));

                turrets2.push_back(temp);
            }
            break;
        case 3:
            cursorTemp3->drawTemp=true;
            cursorTemp3->drawRange=true;
            cursorTemp3->shape.setPosition(sf::Vector2f(mousePos.x-cursorTemp2->shape.getSize().x/2.f, mousePos.y-cursorTemp2->shape.getSize().y/2.f));
            cursorTemp3->rangeShape.setPosition(sf::Vector2f(mousePos));

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePos.x<numberOfXgrids*gridSize && gridsTypeVector[currentGrid]==0)
            {
                menu->resetChosenTurret();
                cursorTemp3->drawTemp=false;
                cursorTemp3->drawRange=false;

                gridsTypeVector[currentGrid]=5;
                ThirdTurret temp(currentGrid,gridsVector);
                temp.setTexture(&turretTex3v1);
                temp.rangeShape.setPosition(sf::Vector2f(temp.shape.getPosition().x + temp.shape.getSize().x/2.f,temp.shape.getPosition().y + temp.shape.getSize().y/2.f));

                turrets3.push_back(temp);
            }
            break;
        case 4:
            cursorTemp4->drawTemp=true;
            cursorTemp4->drawRange=true;
            cursorTemp4->shape.setPosition(sf::Vector2f(mousePos.x-cursorTemp2->shape.getSize().x/2.f, mousePos.y-cursorTemp2->shape.getSize().y/2.f));
            cursorTemp4->rangeShape.setPosition(sf::Vector2f(mousePos));

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePos.x<numberOfXgrids*gridSize && gridsTypeVector[currentGrid]==0)
            {
                menu->resetChosenTurret();
                cursorTemp4->drawTemp=false;
                cursorTemp4->drawRange=false;

                gridsTypeVector[currentGrid]=5;
                FourthTurret temp(currentGrid,gridsVector);
                temp.setTexture(&turretTex4v1);
                temp.rangeShape.setPosition(sf::Vector2f(temp.shape.getPosition().x + temp.shape.getSize().x/2.f,temp.shape.getPosition().y + temp.shape.getSize().y/2.f));

                turrets4.push_back(temp);
            }
            break;
        }

        //-----Sell turret-----//

        for(size_t i=0; i<turrets1.size(); i++)
            if(turrets1[i].shape.getGlobalBounds().contains(sf::Vector2f(mousePos)))
            {
                turrets1[i].drawRange = true;

                if(menu->getState() == Menu::sell && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    turrets1.erase(turrets1.begin() + i);
                    menu->setMoney(menu->getMoney() + Turret::first);
                    gridsTypeVector[currentGrid] = 0;

                    availableTurrets++;
                    menu->updateTurretTexts(availableTurrets);
                }
                else if(menu->getState() == Menu::upgrade && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if(turrets1[i].upgradeStage<2 && menu->getMoney() >= turrets1[i].upgradeCost[turrets1[i].upgradeStage])
                    {
                        menu->setMoney(menu->getMoney() - turrets1[i].upgradeCost[turrets1[i].upgradeStage]);
                        turrets1[i].upgrade();
                        sf::Mouse::setPosition(sf::Vector2i(0,0));
                    }
                }

            }
            else
                turrets1[i].drawRange = false;

        for(size_t i=0; i<turrets2.size(); i++)
            if(turrets2[i].shape.getGlobalBounds().contains(sf::Vector2f(mousePos)))
            {
                turrets2[i].drawRange = true;

                if(menu->getState() == Menu::sell && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    turrets2.erase(turrets2.begin() + i);
                    menu->setMoney(menu->getMoney() + Turret::second);
                    gridsTypeVector[currentGrid] = 0;

                    availableTurrets++;
                    menu->updateTurretTexts(availableTurrets);
                }
                else if(menu->getState() == Menu::upgrade && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if(turrets2[i].upgradeStage<2 && menu->getMoney() >= turrets2[i].upgradeCost[turrets2[i].upgradeStage])
                    {
                        menu->setMoney(menu->getMoney() - turrets2[i].upgradeCost[turrets2[i].upgradeStage]);
                        turrets2[i].upgrade();
                        sf::Mouse::setPosition(sf::Vector2i(mousePos.x+60,mousePos.y+60));
                    }
                }

            }
            else
                turrets2[i].drawRange = false;

        for(size_t i=0; i<turrets3.size(); i++)
            if(turrets3[i].shape.getGlobalBounds().contains(sf::Vector2f(mousePos)))
            {
                turrets3[i].drawRange = true;

                if(menu->getState() == Menu::sell && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    turrets3.erase(turrets3.begin() + i);
                    menu->setMoney(menu->getMoney() + Turret::third);
                    gridsTypeVector[currentGrid] = 0;

                    availableTurrets++;
                    menu->updateTurretTexts(availableTurrets);
                }
                else if(menu->getState() == Menu::upgrade && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if(turrets3[i].upgradeStage<2 && menu->getMoney() >= turrets3[i].upgradeCost[turrets3[i].upgradeStage])
                    {
                        menu->setMoney(menu->getMoney() - turrets3[i].upgradeCost[turrets3[i].upgradeStage]);
                        turrets3[i].upgrade();
                        sf::Mouse::setPosition(sf::Vector2i(mousePos.x+60,mousePos.y+60));
                    }
                }

            }
            else
                turrets3[i].drawRange = false;

        for(size_t i=0; i<turrets4.size(); i++)
            if(turrets4[i].shape.getGlobalBounds().contains(sf::Vector2f(mousePos)))
            {
                turrets4[i].drawRange = true;

                if(menu->getState() == Menu::sell && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    turrets4.erase(turrets4.begin() + i);
                    menu->setMoney(menu->getMoney() + Turret::fourth);
                    gridsTypeVector[currentGrid] = 0;

                    availableTurrets++;
                    menu->updateTurretTexts(availableTurrets);
                }
                else if(menu->getState() == Menu::upgrade && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if(turrets4[i].upgradeStage<2 && menu->getMoney() >= turrets4[i].upgradeCost[turrets2[i].upgradeStage])
                    {
                        menu->setMoney(menu->getMoney() - turrets4[i].upgradeCost[turrets4[i].upgradeStage]);
                        turrets4[i].upgrade();
                        sf::Mouse::setPosition(sf::Vector2i(0,0));
                    }
                }

            }
            else
                turrets4[i].drawRange = false;


}

void Game::updateTime()
{
    gameTimer += clock.getElapsedTime();

    enemyTimer += clock.getElapsedTime().asSeconds();

    clock.restart();
}

void Game::updateText()
{
    int prec = log10(gameTimer.asSeconds()) + 3;

    std::stringstream ss;
    ss<<"Fala: "<<currentMap<<", Pozostali przeciwnicy: "<<enemiesInWave<<"\nCzas w grze: "<<std::setprecision(prec)<<gameTimer.asSeconds()<<" s";
    waveText.setString(ss.str());
}

void Game::updateEnemies()
{
    if(enemyTimer > spawnCooldown && enemiesInWave > 1)
    {
        enemiesInWave--;
        enemyTimer=0;
        Enemy temp(gridsVector,gridsTypeVector,enemiesHP + ((waveMax - enemiesInWave)/3),enemiesPrize);
        temp.initText(font);

        switch(rand()%3)
        {
        case 0:
            temp.setTexture(&angel1);
            break;
        case 1:
            temp.setTexture(&angel2);
            break;
        case 2:
            temp.setTexture(&angel3);
            break;
        }

        enemies.push_back(temp);
    }

    if(enemiesInWave == 1 && enemies.size() == 0)
    {
        enemiesInWave--;
        Enemy boss(gridsVector,gridsTypeVector,bossHP,enemiesPrize);
        boss.initText(font);

        switch(rand()%3)
        {
        case 0:
            boss.setTexture(&golem1);
            break;
        case 1:
            boss.setTexture(&golem2);
            break;
        case 2:
            boss.setTexture(&golem3);
            break;
        }

        enemies.push_back(boss);
    }

    for(size_t i=0; i < enemies.size(); i++)
    {
        enemies[i].update(gridsVector,gridsTypeVector,numberOfYgrids,numberOfXgrids);

        if(enemies[i].isInBase())
        {
            enemies.erase(enemies.begin() + i);
            currentHealtPoints--;
            menu->setHealth(currentHealtPoints,baseHealthPoints);

            if(enemiesInWave == 0)
                menu->setState(Menu::gameover);
        }

        if(!enemies[i].isAlive())
        {
            menu->setMoney(menu->getMoney() + enemies[i].getPrize());

            enemies.erase(enemies.begin() + i);
        }
    }

}

void Game::updateGameOver()
{
    if(currentHealtPoints == 0)
        menu->setState(Menu::gameover);

    if(gameOver)
        window->close();

    if(newgame)
    {
        newgame=false;
        menu->setState(Menu::home);
        gameTimer=sf::Time::Zero;
        initMap(1);
    }

    if(restart)
    {
        restart=false;
        menu->setState(Menu::home);
        initMap(currentMap);
    }

    if(enemiesInWave == 0 && enemies.size()==0 && menu->getState()!=Menu::gameover)
    {
        if(currentMap < MAP_MAX)
            initMap(++currentMap);
        else
        {
            menu->setState(Menu::win);
            menu->updateTimeText(gameTimer.asSeconds());
        }
    }
}

void Game::updateTurrets()
{
    for(size_t i=0; i<turrets.size(); i++)
        turrets[i].update(enemies);

    for(size_t i=0; i<turrets1.size(); i++)
        turrets1[i].update(enemies);

    for(size_t i=0; i<turrets2.size(); i++)
        turrets2[i].update(enemies);

    for(size_t i=0; i<turrets3.size(); i++)
        turrets3[i].update(enemies);

    for(size_t i=0; i<turrets4.size(); i++)
        turrets4[i].update(enemies);
}

void Game::update()
{
    pollEvents();
    updateGameOver();
    updateMouse();

    if(menu->getState() < Menu::paused)
    {
        updateTime();
        updateEnemies();
        updateTurrets();
        updateText();
    }

    menu->update(mousePos,gameOver,restart,newgame,availableTurrets,gameTimer.asSeconds());
}

//renders

void Game::renderGrids()
{
    for(size_t i=0;i<gridsVector.size();i++)
        window->draw(gridsVector[i]);
}

void Game::renderEnemies()
{
    for(size_t i=0; i<enemies.size(); i++)
        enemies[i].render(*window);
}

void Game::renderTurrets()
{
    for(size_t i=0; i<turrets.size(); i++)
        turrets[i].render(*window);

    for(size_t i=0; i<turrets1.size(); i++)
        turrets1[i].render(*window);

    for(size_t i=0; i<turrets2.size(); i++)
        turrets2[i].render(*window);

    for(size_t i=0; i<turrets3.size(); i++)
        turrets3[i].render(*window);

    for(size_t i=0; i<turrets4.size(); i++)
        turrets4[i].render(*window);

    if(cursorTemp1->drawTemp)
        cursorTemp1->render(*window);

    if(cursorTemp2->drawTemp)
        cursorTemp2->render(*window);

    if(cursorTemp3->drawTemp)
        cursorTemp3->render(*window);

    if(cursorTemp4->drawTemp)
        cursorTemp4->render(*window);
}

void Game::renderText()
{
    window->draw(waveText);
}

void Game::render()
{
    window->clear();

    renderGrids();
    renderEnemies();
    renderTurrets();
    renderText();
    menu->render(*window);

    window->display();
}

//rest of all functions

const bool Game::isPlaying()
{
    return window->isOpen();
}

int Game::v2iToGrid(sf::Vector2i &mousePos)
{
    return ((mousePos.y/int(gridSize))*numberOfXgrids + (mousePos.x/int(gridSize)));
}
