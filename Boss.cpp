#include "Boss.h"

Boss::Boss(sf::Texture *pBosstext)
{
    textBoss = pBosstext;
    i = 0;
    setTrasa();
}

void Boss::Rysuj(sf::RenderWindow & app)
{
    sf::Sprite tmp;
    tmp.setTexture(*textBoss);
    tmp.setPosition(x,y);
    app.draw(tmp);
}

void Boss::Ruch(float GdzieJestStatek)
{
    Trasa[4].X = GdzieJestStatek;
    Trasa[5].X = GdzieJestStatek;

    ///Wejscie na scene
    if (i == 0 && Trasa[1].Y >= y){
        y+=Ruch_Bossa;
        return;
    }
    if (i == 0 && Trasa[1].Y <= y)
        ++i;
    ///W lewo
    if ( i == 1 && Trasa[2].X <= x ){
        x -= Ruch_Bossa;
        return;
    }
    if ( x <= Trasa[2].X ){
        i=2;
    }
    ///Od lewej w prawo
    if ( i == 2 && x < Trasa[3].X){
        x +=Ruch_Bossa;
        return;
    }
    if ( i== 2 && x >= Trasa[3].X)
        i++;
    ///Od prawej do lewej
    if (i==3 && x >= Trasa[4].X){
        x-=Ruch_Bossa;
        return;
    }
    if (i==3 && x <= Trasa[4].X )
        i++;
    ///Ze srodka w dol
    if (i==4 && y <= Trasa[5].Y){
        y +=Ruch_Bossa;
        return;
    }
    if (i==4 && y >= Trasa[5].Y)
        i++;
    ///Do gory!
    if (i == 5 && y >= Trasa[1].Y){
        y -=Ruch_Bossa;
        return;
    }
    if ( i == 5 && y <=Trasa[1].Y)
        i = 1;

}

void Boss::setTrasa()
{
    ///Wejscie na scenê
    Trasa[0].X = Width/2 - getRozmiarTeksturyX()/2;
    Trasa[0].Y = -getRozmiarTeksturyY();
    ///srodek
    Trasa[1].X = Width/2 - getRozmiarTeksturyX()/2;
    Trasa[1].Y = 25;
    ///lewo
    Trasa[2].X = 0;
    Trasa[2].Y = 25;
    ///Prawo
    Trasa[3].X = Width - getRozmiarTeksturyX();
    Trasa[3].Y = 25;
    ///srodek
    Trasa[4].X = Width/2 - getRozmiarTeksturyX()/2;
    Trasa[4].Y = 25;
    ///dol
    Trasa[5].X = Width/2 - getRozmiarTeksturyX()/2;
    Trasa[5].Y = Height - getRozmiarTeksturyY();
}

bool Boss::bCzMogeStrzelac()
{
    if ( tBossFire < tBoss ){
        tBossFire +=cBoss.restart();
        return false;
    }
    else {
        tBossFire = sf::Time::Zero;
        return true;
    }
}

bool Boss::Automatyczne_Strzelanie(float StartX, float KoniecX)
{
    if ( (x >= StartX && x <= StartX + KoniecX ) ||
            ( x + getRozmiarTeksturyX() >= StartX && x + getRozmiarTeksturyX() <= StartX + KoniecX )
        )
       return true;
       else
        return false;
}

sf::Sprite Boss::getSpriteBoss()
{
    sf::Sprite tmp;
    tmp.setTexture(*textBoss);
    tmp.setPosition(x,y);
    return tmp;
}
