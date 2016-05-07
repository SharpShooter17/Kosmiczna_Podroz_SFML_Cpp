#ifndef SPACE_H_INCLUDED
#define SPACE_H_INCLUDED

///----------------------Naglowki-----------------------///

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <deque>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>

///-----------------Wymiary ekranu-----------------///

extern unsigned Width;
extern unsigned Height;

///-----------------Struktury------------------///
struct Point
{
    float X;
    float Y;
};

///-----------------Timery---------------------///

const float Pocisk_Bohatera_co = 0.2f;
const float Nowy_Przeciwnik_co =  4.0f;
const float Nowa_Asteroida_co = 3.0f;
const float Dlugosc_Eksplozji = 0.3f;
const float Statek_Wroga_Wystrzal_co = 0.5f;
const float Wystrzal_Bossa = 0.80f;
const float Uderzenie_w_bossa_co = 1.5f;
const float Timer_petli = 1.0f;

///---------------Czcionki----------------///

const char Czcionka[] = "fonty/IMMRTLT_.ttf";
const char Menu[] = "fonty/comicbd.ttf";

///---------------Sciezki dzwiekowe------------///

const char dzwiek_strzalu[] = "sounds/fire.wav";
const char dzwiek_wybuchu[] = "sounds/explo.flac";
const char dzwiek_smiechu[] = "sounds/smiech.ogg";

///----------------Sciezki do obrazko-------------///

const char tlo_gry[] = "graphics/tlo.jpg";
const char Wrogi_statek[] = "graphics/Statek_wroga.png";
const char Tekstura_Asteroidy[] = "graphics/asteroida.png";
const char Tekstura_eksplozji[] = "graphics/eksplozja.png";
const char Tekstura_PociskuWroga[] = "graphics/Pocisk_wroga.png";
const char Tekstura_statku_bohatera[] = "graphics/space.png";
const char Tekstura_strzal_bohatera[] = "graphics/Bullet.png";
const char StatekBossa[] = "graphics/boss.png";
const char Tekstura_Pocisku_Bossa[] = "graphics/BossBullet.png";

///---------------Uszkodzenia statku--------------///

const int Kula_uderza_bohatera = -15;
const int Bohater_uderzyl_w_statek_przeciwnika = -30;
const int Pocisk_bohatera_uderzyl_w_wroga = -25;
const int Asteroida_uderza_w_statek = -25;
const int Pocisk_bohatera_uderzyl_w_Bossa = -50;

///--------------Ruch---------------------///

extern float Przeskocz_O_pixeli; ///gora dol lewo prawo - bohater
extern float Automatyczny_ruch_wrog; ///Ruch wroga lewo prawo
extern float Ruch_w_dol_wroga;
extern float Ruch_asteroidy;
extern float Ruch_pocisku_wroga;
extern float Ruch_Pocisku_bohatera;
extern float Ruch_Bossa;
extern float Ruch_Pocisku_Bossa;

///----------------Punkty------------------///

const int Kula_W_Asteroide = 10;
const int Kula_Niszczy_Asteoride = 25;
const int Kula_W_statek_wroga = 25;
const int Kula_Niszczy_statek_wroga = 40;
const int Statek_uderza_w_statek_wroga = 5;
const int Kula_o_kule = 5;
const int Kula_W_Statek_Bossa = 60;
const int Kula_Niszczy_statek_Bossa = 500;

///----------------Teksty------------------///

const std::string witam = "Kosmiczna podroz!";
const std::string StartGry = "Start gry";
const std::string TextNick = "Podaj nickname: ";
const std::string CzyDzwiekON = "Dzwiek ON";
const std::string CzyDzwiekOFF = "Dzwiek OFF";

//////////////////////////////////////////////////////////////////////////

#endif // SPACE_H_INCLUDED
