///---------------naglowki---------------///

#pragma comment(lib, "sfml-network.lib")
#include <SFML/Network.hpp>

#include "statek.h"
#include "Strzaly.h"
#include "Asteorida.h"
#include "Statek_Wroga.h"
#include "PociskWroga.h"
#include "Collision.h"
#include "Eksplozja.h"
#include "Statystyki.h"
#include "Boss.h"

///--------------Rozdzielczosc-----------------///
extern unsigned Width = 1024;
extern unsigned Height = 768;

///----------------Ruch-----------------------///

extern float Przeskocz_O_pixeli = 0.1; ///gora dol lewo prawo - bohater
extern float Automatyczny_ruch_wrog = 0.05f; ///Ruch wroga lewo prawo
extern float Ruch_w_dol_wroga = 0.01f;
extern float Ruch_asteroidy = 0.03f;
extern float Ruch_pocisku_wroga = 0.2f;
extern float Ruch_Pocisku_bohatera = 0.6f;
extern float Ruch_Bossa = 0.07f;
extern float Ruch_Pocisku_Bossa = 0.7;

///----------------------Kontenery:------------------///

///strzaly bohatera
std::deque < Strzaly > TablicaKul;
///asteoridy
std::deque < Asteroida > TabAsteroid;
///przeciwnicy - statki wrogow
std::deque < Statek_Wroga > Przeciwnicy;
///Strzaly przeciwnikow
std::deque < PociskWroga > StrzalyWroga;
///Eksplozje
std::deque < Explozja > Eksplozja;

///----------------Deklaracje-----------------///

void sendScore(int score, int lv, int liczbaStatkow, const std::string& name);
void UstawZmienne(int & i);
void ResetKontenerow();
int LiczbaPetli = 0;

///------------------Main----------------------///

int main()
{
    sf::RenderWindow app(sf::VideoMode(Width, Height), "Kosmiczna Podroz");
    ///Tlo gry
    sf::Texture tlo;
    if (!tlo.loadFromFile(tlo_gry))
        return EXIT_FAILURE;

    sf::Sprite sprite(tlo);
    sprite.setPosition(0,0);

    ///----------------------Timery---------------------///

    ///Timer pocikow bohatera
    sf::Clock Clock;
    sf::Time FireGranica = sf::seconds(Pocisk_Bohatera_co); /// co ile sekund wystrzal?
    sf::Time Fire;

    ///Timer - nowy Przeciwnik co
    sf::Clock cPrzeciwnik;
    sf::Time tPrzeciwnik = sf::seconds(Nowy_Przeciwnik_co); /// co ile sekund nowy przeciwnik?
    sf::Time tPrzeciwnikNowy;

    ///Timer asteorid
    sf::Clock Asteorid;
    sf::Time Asteorida_co = sf::seconds(Nowa_Asteroida_co); /// co ile sekund skalal?
    sf::Time Asteorida;

    ///Timer statek uderzyl w bossa...
    sf::Clock cHit;
    sf::Time tUderzenie_co = sf::seconds(Uderzenie_w_bossa_co);
    sf::Time tUderzenie;
    ///Timer licznika pêtli
    sf::Clock cLicznik;
    sf::Time tLicznikRestart= sf::seconds(Timer_petli);
    sf::Time tLicznik;
    ///----------------------Zmienne---------------------///

    std::string nickname;
    nickname = "Twój nickname!"; ///Domyslny nick

    ///--------------------Dzwieki-----------------///

    ///strzal
    sf::SoundBuffer fire;
    fire.loadFromFile(dzwiek_strzalu);
    sf::Sound shot;
    shot.setBuffer(fire);
    ///Wybuch!
    sf::SoundBuffer explo;
    explo.loadFromFile(dzwiek_wybuchu);
    sf::Sound bom;
    bom.setBuffer(explo);
    ///smiech!
    sf::SoundBuffer smiech;
    explo.loadFromFile(dzwiek_smiechu);
    sf::Sound muhahaha;
    muhahaha.setBuffer(smiech);

    ///-------------Fonty------------------///
    sf::Font menu;
    menu.loadFromFile(Menu);

    sf::Font Punkty;
    Punkty.loadFromFile(Czcionka);
    sf::Font *pPunkty;
    pPunkty = &Punkty;

    ///-------------Teksty-----------------///

    ///Powitanie
    sf::Text Welcome;
    Welcome.setFont(menu);
    Welcome.setString(witam);
    Welcome.setCharacterSize(60);
    Welcome.setColor(sf::Color::Green);
    Welcome.setPosition( (Width/2 - Welcome.getLocalBounds().width/2) ,25);

    ///Start gry
    sf::Text StartGame;
    StartGame.setFont(menu);
    StartGame.setString(StartGry);
    StartGame.setCharacterSize(40);
    StartGame.setColor(sf::Color::Green);
    StartGame.setPosition((Width/2 - StartGame.getLocalBounds().width/2) ,150);

    ///Wpisz nickname

    sf::Text Nickname;
    Nickname.setFont(menu);
    Nickname.setString(TextNick);
    Nickname.setCharacterSize(30);
    Nickname.setColor(sf::Color::Green);
    Nickname.setPosition(100,Height - 200);

    ///Wyswietla nicname

    sf::Text Nick;
    Nick.setFont(menu);
    Nick.setString(nickname);
    Nick.setCharacterSize(30);
    Nick.setColor(sf::Color::Green);
    Nick.setPosition(100,Height - 150);

    ///Rozdzielczosc ekranu..
    unsigned iRozdzielczoscX[13] = { 800, 1024, 1152, 1280,
                                1280,1280,1280,1360,
                                1366,1600,1600, 1600, 1920 };
    unsigned iRozdzielczoscY[13] = { 600, 768, 864, 768,
                                800,960,1024,768,
                                768,900,1024, 1200, 1080 };

    std::string RozdzielczoscStr[13] = { "800x600", "1024x768", "1152x864", "1280x768",
                                "1280x800","1280x960","1280x1024","1360x768",
                                "1366x768","1600x900","1600x1024", "1600x1200", "1080x1920" };

    sf::Text Rozdzielczosc[13];

    for (int i = 0; i <13; i++){
        Rozdzielczosc[i].setFont(menu);
        Rozdzielczosc[i].setString(RozdzielczoscStr[i]);
        Rozdzielczosc[i].setCharacterSize(30);
        Rozdzielczosc[i].setColor(sf::Color::Green);
        Rozdzielczosc[i].setPosition( (Width - 40 - Rozdzielczosc[i].getLocalBounds().width) ,200+i*35);
    }

    sf::Text Fullscreen;
    Fullscreen.setFont(menu);
    Fullscreen.setString("Pelny ekran");
    Fullscreen.setCharacterSize(30);
    Fullscreen.setColor(sf::Color::Green);
    Fullscreen.setPosition( (Width - 40 - Fullscreen.getLocalBounds().width), 165);

    ///Czy dzwiek?

    sf::Text Dzwiek;
    Dzwiek.setFont(menu);
    Dzwiek.setString(CzyDzwiekON);
    Dzwiek.setCharacterSize(30);
    Dzwiek.setColor(sf::Color::Green);
    Dzwiek.setPosition(100,Height - 250);

    ///--------------Kontrolki-------------///

    ///Stan gry
    bool bMenu = true; /// menu
    bool bGra = false; /// Gra
    bool bZmianaRozdzielczosci = false;
    bool bSendScores = false;
    bool bDzwiek = true;
    bool bPauza = false;
    ///odnosnie gry
    ///Boss
    bool bCzyBoss = false;
    bool bCzyUstawienia = true;
    bool bSprawdzajCzyBoss = true;
    bool bChangeFullScreen = false;

    ///--------------Tekstury-----------///
    ///Asteroida
    sf::Texture Meteoryt;
    if ( !Meteoryt.loadFromFile(Tekstura_Asteroidy) )
        return EXIT_FAILURE;

    sf::Texture *pMeteoryt;
    pMeteoryt = &Meteoryt;
    ///Statek Bossa
    sf::Texture BossStatek;
    if (!BossStatek.loadFromFile(StatekBossa))
        return EXIT_FAILURE;

    sf::Texture *pBossShip;
    pBossShip = &BossStatek;
    ///Statek gracza
    sf::Texture ShipPlayer;
    if (!ShipPlayer.loadFromFile(Tekstura_statku_bohatera))
        return EXIT_FAILURE;

    sf::Texture *pShipPlayer;
    pShipPlayer = &ShipPlayer;
    ///Statek Wroga
    sf::Texture EnemyShip;
    if (!EnemyShip.loadFromFile(Wrogi_statek) )
        return EXIT_FAILURE;

    sf::Texture *pEnemyShip;
    pEnemyShip = &EnemyShip;
    ///Pocisk Gracza
    sf::Texture PlayerBullet;
    if (!PlayerBullet.loadFromFile(Tekstura_strzal_bohatera))
        return EXIT_FAILURE;

    sf::Texture *pPlayerBullet;
    pPlayerBullet = &PlayerBullet;
    ///Pocisk wroga
    sf::Texture EnemyBullet;
    if (!EnemyBullet.loadFromFile(Tekstura_PociskuWroga))
        return EXIT_FAILURE;

    sf::Texture *pEnemyBullet;
    pEnemyBullet = &EnemyBullet;
    ///Pocisk Bossa
    sf::Texture BossBullet;
    if (!BossBullet.loadFromFile(Tekstura_Pocisku_Bossa))
        return EXIT_FAILURE;

    sf::Texture *pBossBullet;
    pBossBullet = &BossBullet;
    ///Explosia
    sf::Texture Boom;
    if (!Boom.loadFromFile(Tekstura_eksplozji))
        return EXIT_FAILURE;

    sf::Texture *pBoom;
    pBoom = &Boom;

    ///-------------Gracz itp klasy ------///
    Statek Ship(pShipPlayer); ///statek
    Statystyki Staty_Ship(Ship, pPunkty);
    Boss boss(pBossShip);

    ///------------------Petla Programu - Serducho!----------------------///
    while (app.isOpen()){

    ///---------------PETLA MENU---------------///

    while (bMenu)
    {

        sf::Event zdarzenie;
        while( app.pollEvent( zdarzenie ) )
        {
            ///zmiana koloru napisu Start gry
            if (sf::Mouse::getPosition(app).x > StartGame.getGlobalBounds().left &&
                sf::Mouse::getPosition(app).y > StartGame.getGlobalBounds().top &&
                sf::Mouse::getPosition(app).x < StartGame.getGlobalBounds().left + StartGame.getGlobalBounds().width &&
                sf::Mouse::getPosition(app).y < StartGame.getGlobalBounds().top +  StartGame.getGlobalBounds().height){
                StartGame.setColor(sf::Color::Red);
                }
                else{
                    StartGame.setColor(sf::Color::Green);
                }

            ///Start Gry! :D
            if ( ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) &&
                sf::Mouse::getPosition(app).x > StartGame.getGlobalBounds().left &&
                sf::Mouse::getPosition(app).y > StartGame.getGlobalBounds().top &&
                sf::Mouse::getPosition(app).x < StartGame.getGlobalBounds().left + StartGame.getGlobalBounds().width &&
                sf::Mouse::getPosition(app).y < StartGame.getGlobalBounds().top +  StartGame.getGlobalBounds().height) ||
                sf::Joystick::isButtonPressed(0, 8) ) {
                ///Ustawienie kontrolek
                bGra = true;
                bMenu = false;
                bCzyBoss = false;
                bCzyUstawienia = true;
                bSprawdzajCzyBoss = true;
                bPauza = false;
                ///Reset statystk gracza
                Ship.ResetLife();
                Ship.ResetScores();
                Ship.ResetXY();
                Staty_Ship.Reset();

                ResetKontenerow();
            }

            if ( zdarzenie.type == sf::Event::TextEntered && nickname.size() < 20 &&
                zdarzenie.key.code != sf::Keyboard::BackSpace
                ){
                nickname +=  zdarzenie.text.unicode;
                Nick.setString(nickname);
            }
                else if (zdarzenie.key.code == sf::Keyboard::BackSpace && nickname.size() > 0){
                    nickname.erase(nickname.end() - 1);
                    Nick.setString(nickname);
                }

            if (zdarzenie.type == sf::Event::Closed ||
                (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape) ||
                sf::Joystick::isButtonPressed(0, 9) ) {
                bMenu = false; /// menu
                bGra = false; /// Gra
                bZmianaRozdzielczosci = false;
                bChangeFullScreen = false;
                bSendScores = false;
                app.close(); ///zamkniecie okna po przez nacisniecie krzyzyk
            }
        }

        ///Zmiana rozdzielczoci ;]
        if ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) &&
                sf::Mouse::getPosition(app).x >  Fullscreen.getGlobalBounds().left &&
                sf::Mouse::getPosition(app).y >  Fullscreen.getGlobalBounds().top &&
                sf::Mouse::getPosition(app).x <  Fullscreen.getGlobalBounds().left + Fullscreen.getGlobalBounds().width &&
                sf::Mouse::getPosition(app).y <  Fullscreen.getGlobalBounds().top + Fullscreen.getGlobalBounds().height) {
                    bChangeFullScreen = !bChangeFullScreen;
            }


        for (int i = 0; i <13; i++){
            if ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) &&
                sf::Mouse::getPosition(app).x >  Rozdzielczosc[i].getGlobalBounds().left &&
                sf::Mouse::getPosition(app).y >  Rozdzielczosc[i].getGlobalBounds().top &&
                sf::Mouse::getPosition(app).x <  Rozdzielczosc[i].getGlobalBounds().left + Rozdzielczosc[i].getGlobalBounds().width &&
                sf::Mouse::getPosition(app).y <  Rozdzielczosc[i].getGlobalBounds().top + Rozdzielczosc[i].getGlobalBounds().height) {
                    Width = iRozdzielczoscX[i];
                    Height = iRozdzielczoscY[i];
                    bZmianaRozdzielczosci = true;
            }
        }

        ///on off dzwiek
        if ( ( sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
            sf::Mouse::getPosition(app).x > Dzwiek.getGlobalBounds().left &&
            sf::Mouse::getPosition(app).y > Dzwiek.getGlobalBounds().top &&
            sf::Mouse::getPosition(app).x < Dzwiek.getGlobalBounds().left + Dzwiek.getGlobalBounds().width &&
            sf::Mouse::getPosition(app).y < Dzwiek.getGlobalBounds().top + Dzwiek.getGlobalBounds().height ) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ){
                bDzwiek = !bDzwiek;
                if (bDzwiek){
                    Dzwiek.setString(CzyDzwiekON);
                    Dzwiek.setColor(sf::Color::Green);
                }
                else{
                    Dzwiek.setString(CzyDzwiekOFF);
                    Dzwiek.setColor(sf::Color::Red);
                }
            }

        app.clear();

        app.draw(sprite);
        app.draw(Welcome);
        app.draw(StartGame);
        app.draw(Nickname);
        app.draw(Nick);
        app.draw(Dzwiek);

        ///Wyswietlanie rozdzielczosci ;]

        if (sf::Mouse::getPosition(app).x > Fullscreen.getGlobalBounds().left &&
                sf::Mouse::getPosition(app).y > Fullscreen.getGlobalBounds().top &&
                sf::Mouse::getPosition(app).x < Fullscreen.getGlobalBounds().left + Fullscreen.getGlobalBounds().width &&
                sf::Mouse::getPosition(app).y < Fullscreen.getGlobalBounds().top +  Fullscreen.getGlobalBounds().height){
                Fullscreen.setColor(sf::Color::Red);
            }
        else if(bChangeFullScreen) {
                Fullscreen.setColor(sf::Color::Blue);
            }
        else{
                Fullscreen.setColor(sf::Color::Green);
            }

        app.draw(Fullscreen);
        for (int i = 0; i<13;i++){

            if (sf::Mouse::getPosition(app).x > Rozdzielczosc[i].getGlobalBounds().left &&
                sf::Mouse::getPosition(app).y > Rozdzielczosc[i].getGlobalBounds().top &&
                sf::Mouse::getPosition(app).x < Rozdzielczosc[i].getGlobalBounds().left + Rozdzielczosc[i].getGlobalBounds().width &&
                sf::Mouse::getPosition(app).y < Rozdzielczosc[i].getGlobalBounds().top +  Rozdzielczosc[i].getGlobalBounds().height){
                Rozdzielczosc[i].setColor(sf::Color::Red);
                }
            else if(iRozdzielczoscX[i] == Width && iRozdzielczoscY[i] == Height) {
                    Rozdzielczosc[i].setColor(sf::Color::Blue);
                }
            else{
                 Rozdzielczosc[i].setColor(sf::Color::Green);
                }

            app.draw(Rozdzielczosc[i]);
        }

        app.display();
    }

    ///Zmiana rozdzielczosci ekranu gry!
    if (bZmianaRozdzielczosci){
        app.create(sf::VideoMode(Width, Height ), "Kosmiczna Podroz");
        bZmianaRozdzielczosci = false;
         sprite.setScale( Width/1024.0f , Height/768.0f );
    }

    if (bChangeFullScreen){
        app.create(sf::VideoMode(Width, Height ), "Kosmiczna Podroz", sf::Style::Fullscreen);
    }

    ///------------------Petla Gry------------///

    tLicznik=sf::Time::Zero; ///reset licznika petli
    ///----------------Czy podany nick--------///

    if (nickname[0] == '\0'){
        nickname = "BRAK NICKU!";
    }

    while (bGra)
    {   ///--------------Licznik-pêtli-------------///

        ///--------------Petla zdarzen-------------///
        sf::Event event;
        while (app.pollEvent(event))
        {
            ///wLACZ WYLACZ DZWIEK W TRAKCIE GRY
            if ( (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::LShift) ||
                sf::Joystick::isButtonPressed(0,7) ){
                    bDzwiek = !bDzwiek;
                }

            ///Pauza
            if ( (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::P) ||
                sf::Joystick::isButtonPressed(0,6) ){
                    bPauza = !bPauza;
                }

            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) ||
                sf::Joystick::isButtonPressed(0, 9) ){
                bMenu = false; /// menu
                bGra = false; /// Gra
                bSendScores = false;
                app.close(); ///zamkniecie okna po przez nacisniecie krzyzyk
            }
        }

        if (!bPauza){

        tLicznik += cLicznik.restart();

        if (tLicznik >= tLicznikRestart){
            UstawZmienne(LiczbaPetli);
            LiczbaPetli = 0;
            tLicznik=sf::Time::Zero;
        }else {
            ++LiczbaPetli;
        }

        ///--------------Ruch-Klawiatura---------------///

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            Ship.Right();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            Ship.Left();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            Ship.Up();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            Ship.Down();

        ///strzal!
        Fire += Clock.restart();

        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && Fire >= FireGranica  ){
                    Strzaly kula(Ship.x_rakiety(), Ship.y_rakiety(), pPlayerBullet);
                    TablicaKul.push_back( kula );
                    Fire = sf::Time::Zero;
                    if (bDzwiek)
                        shot.play();
        }

        ///-----------------Joystick---------------------///

         if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) == 100)
            Ship.Right();
        if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) == -100)
            Ship.Left();
        if(sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == -100)
            Ship.Up();
        if(sf::Joystick::getAxisPosition(0, sf::Joystick::Y) == 100)
            Ship.Down();
        if ( sf::Joystick::isButtonPressed(0, 8) || sf::Keyboard::isKeyPressed(sf::Keyboard::R) ){
            ResetKontenerow();
            ///Ustawienie kontrolek
            bGra = true;
            bMenu = false;
            bCzyBoss = false;
            bCzyUstawienia = true;
            bSprawdzajCzyBoss = true;
            ///Reset statystk gracza
            Ship.ResetLife();
            Ship.ResetScores();
            Ship.ResetXY();
            Staty_Ship.Reset();
        }

        if ( Fire >= FireGranica
            && (sf::Joystick::isButtonPressed(0, 5) || sf::Joystick::isButtonPressed(0, 0) ) ){
                Strzaly kula(Ship.x_rakiety(), Ship.y_rakiety(), pPlayerBullet);
                TablicaKul.push_back( kula );
                Fire = sf::Time::Zero;
                if (bDzwiek)
                    shot.play();
            }


        ///--------------------Czy juz Boss??------------///
        if (bSprawdzajCzyBoss &&
            Ship.punkty() >= Staty_Ship.getLevel() * Staty_Ship.getLevel() * 1000  ){
            bCzyBoss = true;
            bSprawdzajCzyBoss = false;
        }

        ///-----------------Asteoridy----------------///

        Asteorida += Asteorid.restart();
        ///Nowe asteroidy
        if (TabAsteroid.size() >= 0 && TabAsteroid.size() <= 3 && Asteorida>=Asteorida_co ){
            Asteroida tmp(pMeteoryt);

            if (TabAsteroid.size() > 0)
                tmp.Ustaw_Asteroide( TabAsteroid[ TabAsteroid.size() - 1 ] );

            TabAsteroid.push_back(tmp);
            Asteorida = sf::Time::Zero;
        }

        ///Wyjscie asteoridy poza ekran
        if (TabAsteroid.size() > 0){
            if (TabAsteroid[0].bPozaOknem()){
                TabAsteroid[0].~Asteroida();
                TabAsteroid.pop_front();
            }
        }

        ///ruch asteroid
        for (int i = 0; i < TabAsteroid.size(); i++){
            TabAsteroid[i].Fly();
        }

        ///--------------Wrog------------------///

        if (!bCzyBoss){
        ///Nowy wrog
        tPrzeciwnikNowy += cPrzeciwnik.restart();
        if (Przeciwnicy.size() >= 0 && Przeciwnicy.size() <= 3 && tPrzeciwnikNowy>=tPrzeciwnik ){
            Statek_Wroga tmp(Automatyczny_ruch_wrog, pEnemyShip);
            Przeciwnicy.push_back(tmp);
            tPrzeciwnikNowy = sf::Time::Zero;
        }
        }

        ///Automatyczne strzelanie wroga
        for (int i = 0; i <Przeciwnicy.size();i++){
            if (Przeciwnicy[i].bAutomatyczne_strzelanie(Ship) && Przeciwnicy[i].bCzyMogeStrzelic() ){
                PociskWroga kula( Przeciwnicy[i].XWROG(), Przeciwnicy[i].YWROG(), Przeciwnicy[i].xWrogTekstura(), Ruch_pocisku_wroga, pEnemyBullet );
                StrzalyWroga.push_back( kula );
            }
        }
        ///Automatyczne poruszanie sie wroga
        for (int i = 0; i < Przeciwnicy.size(); i++){
            Przeciwnicy[i].Automatyczny_ruch(Ship, TabAsteroid); /// statki za 1 statkiem :D
        }

        ///Wyjscie wroga poza dolana krawedz ekranu
        if (Przeciwnicy.size() > 0){
            if ( Przeciwnicy[0].bPozaOknem() ){
                Przeciwnicy[0].~Statek_Wroga();
                Przeciwnicy.pop_front();
            }
        }

        ///Wyjscie kuli wroga poza ekran
        if (StrzalyWroga.size() > 0 ){
         if (StrzalyWroga[0].bPozaOknem()){
                StrzalyWroga[0].~PociskWroga();
                StrzalyWroga.pop_front();
            }
        }

        ///ruch pociskow wrogich statkow
        for (int i = 0; i < StrzalyWroga.size(); i++){
                StrzalyWroga[i].Fly();
        }

        ///------------------------bohater-------------------///

        ///Jak tam z zyciem panie kapitanie?
        if (Ship.zycie() <= 0){
            bGra = false;
            bMenu = true;
            bSendScores = true;
            bPauza = false;
        }

        ///ruch pociskow bohatera
        for (int i = 0; i < TablicaKul.size(); i++){
                TablicaKul[i].Fly();
        }

        ///Wyjscie kuli poza ekran
        if (TablicaKul.size() > 0 ){
         if (TablicaKul[0].bPozaOknem()){
                TablicaKul[0].~Strzaly();
                TablicaKul.pop_front();
            }
        }

        ///--------------------Boss----------------------///

        if (bCzyBoss){
                if (bCzyUstawienia){
                    boss.setLife(400 + 100*Staty_Ship.getLevel());
                    boss.setSpeed(Ruch_Bossa);
                    boss.setX( ( (Width/2)-(boss.getRozmiarTeksturyX()/2) ) );
                    boss.setY(-boss.getRozmiarTeksturyY());
                    boss.setTrasa();
                    boss.ResetI();
                    bCzyUstawienia = false;
                    if (bDzwiek)
                        muhahaha.play();
                }
            ///Ruchy bosssssa
            boss.Ruch(Ship.x_rakiety());
            ///Strzelanie bossa
            if (boss.bCzMogeStrzelac() &&
                boss.Automatyczne_Strzelanie( Ship.x_rakiety(), (Ship.x_rakiety() + Ship.X_statek_tekstura() ) ) ){
                PociskWroga kula( boss.BossX(), boss.BossY(), boss.getRozmiarTeksturyX(), Ruch_Pocisku_Bossa, pBossBullet );
                StrzalyWroga.push_back( kula );
            }
            ///Kolizja statku z bossem
            if ( Collision::BoundingBoxTest(boss.getSpriteBoss(), Ship.Zwroc_Sprite())
                && tUderzenie > tUderzenie_co
                && Collision::PixelPerfectTest(boss.getSpriteBoss(), Ship.Zwroc_Sprite())){
                Ship.change_life(-30);
                boss.ChangeLife(-50);
                tUderzenie = sf::Time::Zero;

                ///Wyswietla BOOM!
                Explozja tmp( Ship.x_rakiety(), Ship.y_rakiety(), pBoom);
                Eksplozja.push_back(tmp);
                if (bDzwiek)
                    bom.play();
            } else{
                tUderzenie += cHit.restart();
            }
            ///kolizja kuli bohatera z bossem
            for (int i = 0; i < TablicaKul.size(); i++){
                    if (Collision::BoundingBoxTest(boss.getSpriteBoss(), TablicaKul[i].Zwroc_Sprite() ) &&
                        Collision::PixelPerfectTest(boss.getSpriteBoss(), TablicaKul[i].Zwroc_Sprite() )){
                        ///zmiana hp bossa
                        boss.ChangeLife(Pocisk_bohatera_uderzyl_w_Bossa);
                        Ship.scores(Kula_W_Statek_Bossa);

                        ///Wyswietla BOOM!
                            Explozja tmp( TablicaKul[i].X_Bull(), TablicaKul[i].Y_Bull(), pBoom);
                            Eksplozja.push_back(tmp);
                            if (bDzwiek)
                                bom.play();
                        ///Wymazuje kule
                        TablicaKul[i].~Strzaly();
                        TablicaKul.erase(TablicaKul.begin() + i);

                        if ( boss.getLife() <= 0 ){
                            Ship.scores(Kula_Niszczy_statek_Bossa);
                            Staty_Ship.AddLevel();
                        }
                        }
            }
            if (boss.getLife() <= 0){
                bCzyBoss = false;
                bCzyUstawienia = true;
                bSprawdzajCzyBoss = true;
            }
        }

        ///---------------------kolizje------------------///

        ///kula uderzyla w asteroide - w cala teksture!!!! MOZE BYC TU PROBLEM! CRASH PROGRAMU ;/
        for (int j = 0; j < TabAsteroid.size();j++) {
            for (int i = 0; i < TablicaKul.size() ; ) {
                if (Collision::BoundingBoxTest( TablicaKul[i].Zwroc_Sprite(), TabAsteroid[j].Zwroc_Sprite()) &&
                    Collision::PixelPerfectTest(  TablicaKul[i].Zwroc_Sprite(), TabAsteroid[j].Zwroc_Sprite() )){
                        ///Wyswietla BOOM!
                        Explozja tmp( TablicaKul[i].X_Bull(), TablicaKul[i].Y_Bull(), pBoom);
                        Eksplozja.push_back(tmp);
                        if (bDzwiek)
                            bom.play();
                        ///dodaje punkty
                        Ship.scores(Kula_W_Asteroide);

                        TablicaKul[i].~Strzaly();
                        TablicaKul.erase(TablicaKul.begin() + i);
                        TabAsteroid[j].Asteroida_dostala_pociskiem();
                        ///jesli skala dostala 5 pociski to usun!
                            if (TabAsteroid[j].Oslabiebie_asteroidy() >= 5){
                                Ship.scores(Kula_Niszczy_Asteoride);
                                TabAsteroid[j].~Asteroida();
                                TabAsteroid.erase(TabAsteroid.begin() + j);
                       }
                }
                else
                    ++i;
            }
        }

        ///Asteorida uderzyla w statek ;/
        if (TabAsteroid.size() > 0){
            for (int i = 0; i < TabAsteroid.size(); i++){
                if ( Collision::BoundingBoxTest(Ship.Zwroc_Sprite() , TabAsteroid[i].Zwroc_Sprite() ) &&
                    Collision::PixelPerfectTest(Ship.Zwroc_Sprite() , TabAsteroid[i].Zwroc_Sprite() )){
                    ///Wyswietla BOOM!
                    Explozja tmp( TabAsteroid[i].X_Skala(), TabAsteroid[i].Y_Skala(), pBoom);
                    Eksplozja.push_back(tmp);
                    if (bDzwiek)
                        bom.play();

                    TabAsteroid[i].~Asteroida();
                    TabAsteroid.erase(TabAsteroid.begin() + i); ///usun skale
                    Ship.change_life(Asteroida_uderza_w_statek);
                }
            }
        }

        ///Pocisk bohatera uderzyl w statek wroga
        for (int i = 0; i < TablicaKul.size(); i++){
            for (int j = 0; j < Przeciwnicy.size(); j++){
                if ( Collision::BoundingBoxTest(TablicaKul[i].Zwroc_Sprite(), Przeciwnicy[j].Zwroc_Sprite() ) &&
                    Collision::PixelPerfectTest(TablicaKul[i].Zwroc_Sprite(), Przeciwnicy[j].Zwroc_Sprite() )){
                   ///Wyswietla BOOM!
                        Explozja tmp( TablicaKul[i].X_Bull(), TablicaKul[i].Y_Bull(), pBoom);
                        Eksplozja.push_back(tmp);
                        if (bDzwiek)
                            bom.play();
                    Ship.scores(Kula_W_statek_wroga);

                    TablicaKul[i].~Strzaly();
                    TablicaKul.erase(TablicaKul.begin() + i);
                    if (Przeciwnicy[j].changelife(Pocisk_bohatera_uderzyl_w_wroga) <= 0 ){
                        Ship.scores(Kula_Niszczy_statek_wroga);
                        Staty_Ship.AddLiczbaStatkow();
                        Przeciwnicy[j].~Statek_Wroga();
                        Przeciwnicy.erase(Przeciwnicy.begin() + j);
                    }
                }
            }
        }

        ///bohater uderzyl w statek przeciwnika
        for (int i = 0; i < Przeciwnicy.size(); i++){
            if (Collision::BoundingBoxTest(Ship.Zwroc_Sprite(), Przeciwnicy[i].Zwroc_Sprite()) &&
                Collision::PixelPerfectTest(Ship.Zwroc_Sprite(), Przeciwnicy[i].Zwroc_Sprite())){
                ///Wyswietla BOOM!
                Explozja tmp( Przeciwnicy[i].XWROG(), Przeciwnicy[i].YWROG(), pBoom);
                Eksplozja.push_back(tmp);
                if (bDzwiek)
                    bom.play();

                 Ship.scores(Statek_uderza_w_statek_wroga);

                Przeciwnicy[i].~Statek_Wroga();
                Przeciwnicy.erase(Przeciwnicy.begin() + i);
                Ship.change_life(Bohater_uderzyl_w_statek_przeciwnika);
            }
        }

        ///Kula wroga uderzyla bochatera :(
        for (int i = 0; i < StrzalyWroga.size(); i++){
            if (Collision::BoundingBoxTest(Ship.Zwroc_Sprite(), StrzalyWroga[i].Zwroc_Sprite()) &&
                Collision::PixelPerfectTest(Ship.Zwroc_Sprite(), StrzalyWroga[i].Zwroc_Sprite())){

                    ///Wyswietla BOOM!
                    Explozja tmp( StrzalyWroga[i].XPOCISK(), StrzalyWroga[i].YPOCISK(), pBoom);
                    Eksplozja.push_back(tmp);
                    if (bDzwiek)
                        bom.play();

                    StrzalyWroga[i].~PociskWroga();
                    StrzalyWroga.erase(StrzalyWroga.begin() + i);
                    Ship.change_life(Kula_uderza_bohatera);
            }
        }

        ///Kula wroga uderzyla w kule bohatera albo odwrotnie jeden pies...
        for (int i = 0; i < StrzalyWroga.size(); i++){
            for (int j = 0; j < TablicaKul.size(); j++){
                if (Collision::BoundingBoxTest(StrzalyWroga[i].Zwroc_Sprite(), TablicaKul[j].Zwroc_Sprite()) &&
                    Collision::PixelPerfectTest(StrzalyWroga[i].Zwroc_Sprite(), TablicaKul[j].Zwroc_Sprite())){

                    ///Wyswietla BOOM!
                    Explozja tmp( StrzalyWroga[i].XPOCISK(), StrzalyWroga[i].YPOCISK(), pBoom);
                    Eksplozja.push_back(tmp);
                    if (bDzwiek)
                        bom.play();

                    Ship.scores(Kula_o_kule);

                    StrzalyWroga[i].~PociskWroga();
                    StrzalyWroga.erase(StrzalyWroga.begin() + i);
                    TablicaKul[j].~Strzaly();
                    TablicaKul.erase(TablicaKul.begin() + j);
                }
            }
        }

        ///Kula wroga uderzyla asteroide
        for (int j = 0; j < TabAsteroid.size();j++) {
            for (int i = 0; i < StrzalyWroga.size() ; ) {
                if (Collision::BoundingBoxTest( StrzalyWroga[i].Zwroc_Sprite(), TabAsteroid[j].Zwroc_Sprite()) &&
                    Collision::PixelPerfectTest(  StrzalyWroga[i].Zwroc_Sprite(), TabAsteroid[j].Zwroc_Sprite() )){
                        ///Wyswietla BOOM!
                        Explozja tmp( StrzalyWroga[i].XPOCISK(), StrzalyWroga[i].YPOCISK(), pBoom);
                        Eksplozja.push_back(tmp);
                        if (bDzwiek)
                            bom.play();

                        StrzalyWroga[i].~PociskWroga();
                        StrzalyWroga.erase(StrzalyWroga.begin() + i);
                        TabAsteroid[j].Asteroida_dostala_pociskiem();
                        ///jesli skala dostala 5 pociski to usun!
                            if (TabAsteroid[j].Oslabiebie_asteroidy() >= 5){
                                TabAsteroid[j].~Asteroida();
                                TabAsteroid.erase(TabAsteroid.begin() + j);
                       }
                }
                else
                    ++i;
            }
        }


        ///---------------------Usuwa nie potrzebne elementy TYLKO BOOM!--------------///
        for (int i = 0; i < Eksplozja.size(); i++ ){
            if (Eksplozja[i].bCzyWybuchTrwa()){
                Eksplozja[i].~Explozja();
                Eksplozja.erase(Eksplozja.begin() + i);
            }
        }

        } ///koniec if'a pauzy ;]
        else {
            cLicznik.restart();
            cHit.restart();
            cPrzeciwnik.restart();
            Asteorid.restart();
            Clock.restart();
        }


        ///----------------------Rysowanie na ekranie-------------------------///
        app.clear();
        ///rysuje tlo
        app.draw(sprite);

        ///rysuje statek kosmiczny!! :Dbbb
        Ship.Rysuj(app);

        ///rysuje pocisk bohatera
        for (int i = 0; i < TablicaKul.size();i++){
            TablicaKul[i].Rysuj(app);
        }

        ///Rysuje statki wroga
        for (int i = 0; i < Przeciwnicy.size(); i++){
            Przeciwnicy[i].Rysuj(app);
        }

        ///rysuje pocisk wroga
        for (int i = 0; i< StrzalyWroga.size();i++){
            StrzalyWroga[i].Rysuj(app);
        }

        ///Rysuje asteroidy
        for (int i = 0; i < TabAsteroid.size(); i++){
            TabAsteroid[i].Rysuj(app);
        }

        ///Boss
        if (bCzyBoss){
            boss.Rysuj(app);
        }

        ///Rysuje eksplozje
        for (int i = 0; i < Eksplozja.size(); i++){
            Eksplozja[i].Rysuj(app);
        }

        ///Statystyki
        Staty_Ship.Rysuj(Ship, app);

        app.display();
    }

    if (bSendScores){
        sendScore(Ship.punkty(), Staty_Ship.getLevel(), Staty_Ship.getStraconychStatkow(), nickname);
        bSendScores = false;
    }

    }

    return EXIT_SUCCESS;
}

void sendScore(int score, int lv, int liczbaStatkow, const std::string& name)
{
    // prepare the request
    sf::Http::Request request("/KosmicznaPodroz/score.php", sf::Http::Request::Post);

    // encode the parameters in the request body
    std::ostringstream stream;
    stream << "score=" << score << "&level=" << lv << "&Statkow=" << liczbaStatkow << "&name=" << name ;
    request.setBody(stream.str());

    // send the request
    sf::Http http("http://matrixxx.cba.pl/");
    sf::Http::Response response = http.sendRequest(request);
}

void UstawZmienne(int & i)
{
    ///Predkosc dla 2500 petli na sekunde
    float x = 2500.0f/i;
    Przeskocz_O_pixeli = 0.1*x; ///gora dol lewo prawo - bohater
    Automatyczny_ruch_wrog = 0.05f*x; ///Ruch wroga lewo prawo
    Ruch_w_dol_wroga = 0.01f*x;
    Ruch_asteroidy = 0.03f*x;
    Ruch_pocisku_wroga = 0.2f*x;
    Ruch_Pocisku_bohatera = 0.1f*x;
    Ruch_Bossa = 0.07f*x;
    Ruch_Pocisku_Bossa = 0.3*x;
}

void ResetKontenerow()
{
    ///Reset kontenerow
    for (int i = TablicaKul.size()-1; i >= 0; i-- ){
        TablicaKul[i].~Strzaly();
        TablicaKul.erase(TablicaKul.begin() + i);
    }
    for (int i = TabAsteroid.size()-1; i >= 0; i-- ){
        TabAsteroid[i].~Asteroida();
        TabAsteroid.erase(TabAsteroid.begin() + i);
    }
    for (int i = Przeciwnicy.size()-1; i >= 0; i-- )
    {
        Przeciwnicy[i].~Statek_Wroga();
        Przeciwnicy.erase(Przeciwnicy.begin() + i);
    }
    for (int i = StrzalyWroga.size()-1; i >= 0; i-- ){
        StrzalyWroga[i].~PociskWroga();
        StrzalyWroga.erase(StrzalyWroga.begin() + i);
    }
    for (int i = Eksplozja.size()-1; i >= 0; i-- ){
        Eksplozja[i].~Explozja();
        Eksplozja.erase(Eksplozja.begin() + i);
    }
}
