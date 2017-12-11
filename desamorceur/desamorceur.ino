/*
  Jeu pour Escape Game: désamorceur
  Decompteur allant de 999 à 0, -1 chaque seconde pour jeu
  3 signaux commandent soit l'arrêt du décompte soit l'accélération soit
  le passage à 0
  écrit par Jean ROGUIN en utilisant un exemple fourni avec la library SevSeg

  Dépendance :
  https://playground.arduino.cc/Main/SevenSegmentLibrary
  https://github.com/DeanIsMe/SevSeg
*/

#include "SevSeg.h"

SevSeg sevseg; // Instantiate a seven segment controller object
int analog0 = 0; // pin sur laquelle est connectee l accelerateur
int val0 = 0;
int analog1 = 1; // pin sur laquelle est connectee le 000
int val1 = 0;
int analog2 = 2; // pin sur laquelle est connectee l'arret du decompteur
int val2 = 0;
// int analog3 = 3; // pin sur laquelle est connectee
// int val3 = 0;

boolean accel = false;
boolean indicstop = false;
boolean indicarret = false;

void setup() {
  byte numDigits = 4; // nombre d'afficheur 7 segments (ici 4 digits = 1234)
  byte digitPins[] = {10, 11, 13, 12}; // cathode des digits de gauche à droite
  byte segmentPins[] = {6, 5, 4, 3, 7, 8, 9, 2}; // segments de a à g puis le .
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default. Recommended
  bool leadingZeros = true; // Use 'true' if you'd like to keep the leading zeros

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros);
  sevseg.setBrightness(100);
  pinMode(1, OUTPUT);  // pour generer un son, clic ou frequence
}

void loop() {
  static unsigned long timer = millis();
  static unsigned long Seconds = 0;
  static unsigned long secondarret = 0;
  static unsigned long numaffich;
  static unsigned long valtimer;

  if (accel == false) {
    val0 = analogRead(analog0);
  }

  if (indicstop == false) {
    val1 = analogRead(analog1);
  }

  if (indicarret == false) {
    val2 = analogRead(analog2);
  }

  if (millis() >= timer) {
    // generation du clic si pas arret ou passage à 0
    if (!indicarret && !indicstop) {
      digitalWrite(1, HIGH);
    }

    Seconds++; // 1000 milliSeconds is equal to 1 Second

    if (indicarret == false) {
      secondarret = Seconds;  // blocage du decompte si l'indicateur est vrai
    }

    // acceleration du decompte
    if (val0 > 100) {
      valtimer = 100;
      timer += valtimer;
      accel = true;
    }
    else {
      valtimer = 1000;
      timer += valtimer;
    }

    if (val1 > 100) {
      indicstop = true;
    }

    if (val2 > 100) {
      indicarret = true;
    }

    // remise à 0 après décompte
    if (Seconds == 100000) {
      Seconds = 0;
    }

    if (!indicstop) {
      numaffich = 1000 - secondarret;
      sevseg.setNumber(numaffich, 1);
    }
  }

  if (millis() >= (timer - valtimer + 5)) {
    digitalWrite(1, LOW); // creneau de 5ms sur la broche 1 pour le clic
  }

  // pour faire clignoter si passage à 0
  if (indicstop) {
    if (millis() % 1000 < 500) {
      sevseg.blank();
    }
    else {
      sevseg.setNumber(0, 1);
      sevseg.refreshDisplay(); // affichage
    }
    playfreq();
  }
  else {
    sevseg.refreshDisplay(); // affichage
  }
}

void playfreq() {
  static boolean tone1state = false;
  static unsigned long tone1timer = millis();
  unsigned long tone1delay = 10;
  int tone1Pin = 1;

  if (millis() - tone1timer > tone1delay) {
    tone1timer = millis(); // reset the timer
    tone1state = !tone1state; // toggle tone1state
    digitalWrite(tone1Pin, tone1state);
  }
}

/// END ///

