#ifndef STATYSTYKI_H_INCLUDED
#define STATYSTYKI_H_INCLUDED

#include "space.h"
#include "Statek.h"
#include <strstream>
class Statystyki
{
private:
    sf::Font *font;
    int life;
    int LiczbaStraconychStatkow;
    int level;
public:
    Statystyki(Statek & x, sf::Font *pFont);
    void Rysuj(Statek & ship, sf::RenderWindow & app);

    inline int getStraconychStatkow() {return LiczbaStraconychStatkow;}
    inline int getLevel() {return level;}
    inline void AddLiczbaStatkow() { ++LiczbaStraconychStatkow;}
    inline void AddLevel() {++level; }
    inline void Reset() {LiczbaStraconychStatkow = 0; level = 1;}
};


#endif // STATYSTYKI_H_INCLUDED
