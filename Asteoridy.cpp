#include "Asteorida.h"

Asteroida::Asteroida(sf::Texture *pAsteroida) : oslabienie(0)
{
    Asteroid = pAsteroida;
    int i;

    srand(time(NULL));
    i = rand() % 9 + 1;
    X_Asteroida = i * ((Width-Asteroid->getSize().x)/10);

    Y_Asteroida = 0-Y_Asteroida_tekstura();
}

void Asteroida::Rysuj(sf::RenderWindow & app)
{
    sf::Sprite tmp;
    tmp.setTexture(*Asteroid);
    tmp.setPosition(X_Asteroida,Y_Asteroida);
    app.draw(tmp);
}

bool Asteroida::bPozaOknem()
{
    if ( Y_Asteroida > Height )
        return true;
    else
        return false;
}
sf::Sprite Asteroida::Zwroc_Sprite()
{
    sf::Sprite tmp;
    tmp.setTexture(*Asteroid);
    tmp.setPosition(X_Asteroida,Y_Asteroida);
    return tmp;
}

void Asteroida::Ustaw_Asteroide(Asteroida & przede_mna)
{
    if ( X_Asteroida > przede_mna.X_Skala() + przede_mna.X_Asteroida_tekstura() )
        return;
    else
        X_Asteroida-=X_Asteroida_tekstura();
    return;
}
