#include "statek.h"
///konstruktor statku bohatera!
Statek::Statek(sf::Texture *pShipPlayer) : life(0), Scores(0)
{
    rakieta = pShipPlayer;
    X_rakieta = Width/2-64;
    Y_rakieta = Height*0.8;
}

void Statek::Rysuj(sf::RenderWindow & app)
{
    sf::Sprite tmp;
    tmp.setTexture(*rakieta);
    tmp.setPosition(X_rakieta,Y_rakieta);
    app.draw(tmp);
}

sf::Sprite Statek::Zwroc_Sprite()
{
    sf::Sprite tmp;
    tmp.setTexture(*rakieta);
    tmp.setPosition(X_rakieta,Y_rakieta);
    return tmp;
}
