#include "MicroBit.h"
MicroBit uBit;
int gewicht = 0;
int essen = 0;
int menge = 0;
int kalorien = 0;
int ergebnisdistanz= 0;
int wunschdistanz = 0;
int deutlichNichtDistanz = 0;
int knappNichtDistanz = 0;
int knappJaDistanz = 0;
int deutlichDistanz = 0;
float gewichtAnalog;
float essenAnalog;
float mengeAnalog;
float joule;
float wunschdistanzAnalog;
float ergebnisdistanzAnalog;
bool gewichtsaufnahme = true;
bool essensaufnahme = true;
bool mengenaufnahme = true;
bool ergebnisanzeige = true;
bool distanzaufnahme = true;
int main()
{   uBit.init();
    //Definition der Ein- bzw. Ausgänge
    uBit.io.P0.isAnalog();//Analogeingang Poti
    uBit.io.P8.isInput();//Eingang Taster
    uBit.io.P12.isOutput();//LED Grün
    uBit.io.P13.isOutput();//LED Gelb
    uBit.io.P14.isOutput();//LED Orange
    uBit.io.P16.isOutput();//LED Rot
    //Start vom Ablauf
    uBit.display.scroll("1.G");
    while(gewichtsaufnahme){
        //Aufnahme des Werts von Poti
        gewichtAnalog = uBit.io.P0.getAnalogValue ();
        //Auflösung wird umgewandelt, sodass maxWert von Poti 150 ergbibt(150/1024)
        gewichtAnalog = (gewichtAnalog * 0.14648375) + 1;
        // Umwandlung von float zu int
        gewicht = (int) gewichtAnalog;
        uBit.display.scroll(gewicht);
        uBit.sleep(20);
        if(uBit.io.P8.getDigitalValue()){
            gewichtsaufnahme = false;
            uBit.display.print(gewicht);
        }
    }
    //Schleife zur Essensauswahl
    uBit.display.scroll("2.E");
    while(essensaufnahme) {
        //Aufnahme des Werts von Poti
        essenAnalog = uBit.io.P0.getAnalogValue();
        //Auflösung wird umgewandelt, sodass maxWert von Poti 150 ergibt =(150/1024)
        essenAnalog = (essenAnalog * 0.002) + 1;
        // Umwandlung von float zu int
        essen = (int) essenAnalog;
        uBit.display.scroll(essen);
        uBit.sleep(30);
        if (uBit.io.P8.getDigitalValue()) {
            uBit.sleep(500);
            //Banane
            if (essen == 1) {
                while (mengenaufnahme) {
                    //Kalorien = Kalorien(0.009, 1, 105000)
                    //Aufnahme des Werts von Poti
                    mengeAnalog = uBit.io.P0.getAnalogValue();
                    //Auflösung wird umgewandelt, sodass maxWert von Poti 10 ergibt =(10/1024) +1
                    mengeAnalog = (mengeAnalog * 0.009) + 1;
                    // Umwandlung von float zu int
                    menge = (int) mengeAnalog;
                    uBit.display.print(menge);
                    kalorien = menge * 105000;
                    if (uBit.io.P8.getDigitalValue()) {
                        uBit.display.scroll("");
                        uBit.sleep(500);
                        //Rücksetzen der Schleife Mengenaufnahme
                        mengenaufnahme = false;
                    }
                }
            }
            //0,5l Bier
            if (essen == 2) {
                while (mengenaufnahme) {
                    //Aufnahme des Werts von Poti
                    mengeAnalog = uBit.io.P0.getAnalogValue();
                    //Auflösung wird umgewandelt, sodass maxWert von Poti 10 ergibt =(10/1024) +1
                    mengeAnalog = (mengeAnalog * 0.009) + 1;
                    // Umwandlung von float zu int
                    menge = (int) mengeAnalog;
                    uBit.display.print(menge);
                    kalorien = menge * 200000;
                    if (uBit.io.P8.getDigitalValue()) {
                        uBit.display.scroll("");
                        uBit.sleep(500);
                        uBit.display.scroll(menge);
                        uBit.sleep(1000);
                        //Rücksetzen der Schleife Mengenaufnahme
                        mengenaufnahme = false;
                    }
                }
            }
            //Schübling
            if (essen == 3) {
                while (mengenaufnahme) {
                    //Aufnahme des Werts von Poti
                    mengeAnalog = uBit.io.P0.getAnalogValue();
                    //Auflösung wird umgewandelt, sodass maxWert von Poti 10 ergibt =(10/1024) +1
                    mengeAnalog = (mengeAnalog * 0.009) + 1;
                    // Umwandlung von float zu int
                    menge = (int) mengeAnalog;
                    uBit.display.print(menge);
                    kalorien = menge * 221000;
                    if (uBit.io.P8.getDigitalValue()) {
                        uBit.display.scroll("");
                        uBit.sleep(500);
                        uBit.display.scroll(menge);
                        uBit.sleep(1000);
                        //Rücksetzen der Schleife Mengenaufnahme
                        mengenaufnahme = false;
                    }
                }
            }
            //Rücksetzen der Schleife
            essensaufnahme = false;
        }
    }
    joule = 4.1868 * kalorien;
    ergebnisdistanz = joule / (10 * gewicht);
    //Umwandlung von float zu int
    wunschdistanz = (int) ergebnisdistanz;
    uBit.display.scroll("3.WD");
    while (distanzaufnahme){//Ablauf Distanzaufnahme mit Ausgabe
        uBit.sleep(1000);
        uBit.display.scroll(wunschdistanz);
        //Aufnahme des Werts von Poti
        wunschdistanzAnalog = uBit.io.P0.getAnalogValue();
        //Auflösung wird umgewandelt, sodass maxWert von Poti 10 ergibt =(10/1024) +1
        wunschdistanzAnalog = (wunschdistanzAnalog * 5);
        //Umwandlung von float zu int
        wunschdistanz = (int) wunschdistanzAnalog;
        //Definition der Ergebnisbereiche mit +-10%
        deutlichDistanz = wunschdistanz * 1.1;
        knappNichtDistanz = wunschdistanz * 0.9;
        if (uBit.io.P8.getDigitalValue()){
            uBit.display.print(wunschdistanz);
            //Ablauf nach Drücken des Bestätigungstasters zur Ergebnisausgabe
            //LED Alle
            if(ergebnisdistanz > deutlichDistanz){
                uBit.io.P12.setDigitalValue(1);
                uBit.io.P13.setDigitalValue(1);
                uBit.io.P14.setDigitalValue(1);
                uBit.io.P16.setDigitalValue(1);
                uBit.display.print(ergebnisdistanz);
            }
                //LED Rot + Orange + Gelb
            else if(ergebnisdistanz > wunschdistanz){
                uBit.io.P12.setDigitalValue(1);
                uBit.io.P13.setDigitalValue(1);
                uBit.io.P14.setDigitalValue(1);
                uBit.display.print(ergebnisdistanz);
            }
                // LED Rot + Orange
            else if(ergebnisdistanz > knappNichtDistanz){
                uBit.io.P12.setDigitalValue(1);
                uBit.io.P13.setDigitalValue(1);
                uBit.display.print(ergebnisdistanz);
            }
                // LED Rot
            else if(ergebnisdistanz < knappNichtDistanz){
                uBit.io.P12.setDigitalValue(1);
                uBit.display.print(ergebnisdistanz);
            }
            //Rücksetzen der Schleife für die Distanzaufnahme

            distanzaufnahme = false;
        }
    }
}