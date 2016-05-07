#ifndef STATEK_WROGA_H_INCLUDED
#define STATEK_WROGA_H_INCLUDED

#include "space.h"
#include "Statek.h"
#include "Asteorida.h"
#include "Collision.h"

class Statek_Wroga
{
private:
    float X_WROG;
    float Y_WROG;
    int life;
    bool bCzyZbalokowany;
    float SzybkoscRuchu;

    sf::Texture *wrog;

    sf::Clock cWrog;
    sf::Time tWrog = sf::seconds(Statek_Wroga_Wystrzal_co); /// co ile sekund wystrzal?
    sf::Time tWrogFire;

public:
    Statek_Wroga(float speed, sf::Texture *pwrog);
    ~Statek_Wroga() {}
    ///wspolrzedne
    inline float XWROG() {return X_WROG;}
    inline float YWROG() {return Y_WROG;}
    inline void setX(float x) { X_WROG = x; }
    inline void setY(float y) { Y_WROG = y; }
    ///rozmiary tekstur
    inline int xWrogTekstura() {return wrog->getSize().x;}
    inline int yWrogTekstura() {return wrog->getSize().y;}
    ///auto
    void Automatyczny_ruch(Statek & atakuj, std::deque < Asteroida > & Tablica); ///automatyczny ruch statku najblizszego dolnej krawedzi.
    bool bAutomatyczne_strzelanie(Statek & atakuj);
    bool bCzyMogeStrzelic();
    bool bPozaOknem();
    void Rysuj(sf::RenderWindow & app);
    sf::Sprite Zwroc_Sprite();
    inline int changelife(int x) {life +=x; return life;}
    inline bool bZablokowany() { return bCzyZbalokowany; }
};


#endif // STATEK_WROGA_H_INCLUDED
