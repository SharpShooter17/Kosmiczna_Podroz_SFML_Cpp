#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED

#include "space.h"

class Boss
{
private:

    float x;
    float y;
    int life;

    float SzybkoscRuchu;
    sf::Texture *textBoss;

    sf::Clock cBoss;
    sf::Time tBoss = sf::seconds(Wystrzal_Bossa);
    sf::Time tBossFire;

    Point Trasa[6];
    int i; ///Odnosi sie do trasy - nr polozenia w tablicy

public:
    Boss(sf::Texture *pBosstext);
    ~Boss() {}
    inline void setSpeed( float x) { SzybkoscRuchu = x; }
    inline void setX(float X) {x = X;}
    inline void setY(float Y) {y = Y;}
    inline void setLife(int x) {life =  x;}

    inline float BossX() {return x;}
    inline float BossY() {return y;}
    inline float getRozmiarTeksturyX() { return textBoss->getSize().x; }
    inline float getRozmiarTeksturyY() { return textBoss->getSize().y; }
    sf::Sprite getSpriteBoss();

    void Ruch(float GdzieJestStatek);
    void setTrasa();
    void Rysuj(sf::RenderWindow & app);

    bool bCzMogeStrzelac ();
    bool Automatyczne_Strzelanie(float StartX, float KoniecX);

    inline void ChangeLife(int x) { life +=x;}
    inline const int getLife() {return life;}

    inline void ResetI() {i = 0;}

};

#endif // BOSS_H_INCLUDED
