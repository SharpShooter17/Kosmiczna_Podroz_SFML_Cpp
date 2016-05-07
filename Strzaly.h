#ifndef STRZALY_H_INCLUDED
#define STRZALY_H_INCLUDED

#include "space.h"

class Asteroida;

class Strzaly
{
private:
    float X_Bullet;
    float Y_Bullet;

     sf::Texture *Kula;

public:
    Strzaly(float x, float y, sf::Texture *pBullet);
    ~Strzaly();
    inline void Fly(){ Y_Bullet-=Ruch_Pocisku_bohatera; }
    bool bPozaOknem();
    void Rysuj(sf::RenderWindow & app);
    inline float X_Bull() { return X_Bullet; }
    inline float Y_Bull() { return Y_Bullet; }
    ///Rozmiar tekstury asteroidy!
    inline int X_Bullet_tekstura() { return Kula->getSize().x; }
    inline int Y_Bullet_tekstura() { return Kula->getSize().y; }
    sf::Sprite Zwroc_Sprite();
};

#endif // STRZALY_H_INCLUDED
