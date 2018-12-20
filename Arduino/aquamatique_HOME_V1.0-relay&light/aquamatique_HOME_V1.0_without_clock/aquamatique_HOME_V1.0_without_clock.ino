

#include <avr/wdt.h>            // Inclusion de la librairie WatchDog

//réglages
/*

  unsigned int heure_start = 7, minute_start = 00;           // heure de branche du systeme

  unsigned int tpsON_min = 0, tpsON_sec = 50;                // duree d'arrossage - cycle EAU
  unsigned int tpsOFF_min = 10, tpsOFF_sec = 0;              // duree sans arrossage - cycle AIR

  unsigned int LED_heure_start = 5, LED_heure_fin = 17 ;     // heures de debut et de fin de l'eclairage - cycle LUMIERE
*/

//test
unsigned int heure_start = 16, minute_start = 59;           // heure de branche du systeme

unsigned int tpsON_min = 0, tpsON_sec = 5;                // duree d'arrossage - cycle EAU
unsigned int tpsOFF_min = 0, tpsOFF_sec = 5;              // duree sans arrossage - cycle AIR

unsigned int LED_heure_start = 5, LED_heure_fin = 17 ;     // heures de debut et de fin de l'eclairage - cycle LUMIERE

// NE RIEN CHANGER ICI

//interface
const unsigned int pin_relay_pompe = 13;
const unsigned int pin_relay_LED = 12;
//code
int tpsON , tpsOFF , nbrCYCLE , H, M, S;
boolean air, eau, lumiere;
boolean debug = 1;

void setup() {

  //  wdt_disable(); // Desactiver le WatchDog

  wdt_enable(WDTO_8S); // Active le WatchDog sur une durée de 8 secondes


  pinMode(pin_relay_pompe, OUTPUT);
  digitalWrite(pin_relay_pompe, HIGH);// OFF
  pinMode(pin_relay_LED, OUTPUT);
  digitalWrite(pin_relay_LED, HIGH);// OFF

  delay(100);

  tpsON = (( tpsON_min * 60) + tpsON_sec);
  tpsOFF = (tpsOFF_min * 60) + tpsOFF_sec;

  H = heure_start; // heure de l'"horloge" mis à heure_start
  M = minute_start; // idem minute

  delay(100);

  if (LED_heure_start <= H && LED_heure_fin > H) {
    lumiere = 1;
    digitalWrite(pin_relay_LED, LOW);// OFF
    if (debug) {
      Serial.println ("LED_ON");
    }
  }
  else {
    lumiere = 0;
    digitalWrite(pin_relay_LED, HIGH);// OFF
    if (debug) {
      Serial.println ("LED_OFF");

    }

        Serial.begin(9600);
        info_start();

      }}

    void loop() {
      Eau();
      S = S + tpsON;
      Chronos();
      LED();

      Air();
      S = S + tpsON;
      Chronos();
      LED();
    }

    void Eau() {
      eau = true;
      air = false;
      delay(100);
      nbrCYCLE++;

      for (int i = 0; i < tpsON; i ++) {
        delay(1000);
        digitalWrite(pin_relay_pompe, LOW);
        wdt_reset();

        if (debug) {

          Serial.println ("Cycle Eau");
          Serial.print (i);
          Serial.print ("/");
          Serial.println (tpsON);
          Serial.print (H);
          Serial.print (":");
          Serial.print (M);
          Serial.print (":");
          Serial.println (S);
        }
      }
    }
    void Air() {
      eau = false;
      air = true;


      for (int i = 0; i < tpsOFF; i ++) {


        delay(1000);
        digitalWrite(pin_relay_pompe, HIGH);
        wdt_reset();

        if (debug) {
          Serial.println ("Cycle Air");
          Serial.print (i);
          Serial.print ("/");
          Serial.println (tpsOFF);
          Serial.print (H);
          Serial.print (":");
          Serial.print (M);
          Serial.print (":");
          Serial.println (S);
        }
      }
    }


    /*
      void wdt_delay(unsigned long msec)
      {
      wdt_reset();

      while (msec > 1000)
      {
        wdt_reset();
        delay(1000);
        msec -= 1000;
      }
      delay(msec);
      wdt_reset();
      }
    */

    void wdt_reload()
    {
      delay(8001);
    }


    void Chronos() {
      if (S >= 60) {
        M++;
        S = S - 60;
        if (M >= 60) {
          H++;
          M = M - 60;
          if (H >= 24) {
            wdt_reload();
          }
        }
      }
    }

    void LED() {
      if (H == LED_heure_start && lumiere == 0) {
        lumiere = 1;
        digitalWrite(pin_relay_LED, LOW);// OFF
        if (debug) {
          Serial.println ("LED_ON");
        }
      }
      else if (H == LED_heure_fin && lumiere == 1) {
        lumiere = 0;
        digitalWrite(pin_relay_LED, HIGH);// OFF
        if (debug) {
          Serial.println ("LED_OFF");
        }
      }
    }

    void info_start() {
      Serial.println ("AQUAPONIQUE-2018-BY Leresteux Julien");
      Serial.println (" --- ");
      Serial.print ("Il est, si tout va bien, ");
      Serial.print (heure_start);
      Serial.print ("H");
      Serial.println (minute_start);
      Serial.println (" --- ");
      Serial.print ("Debut du cycle lumiere à ");
      Serial.print (LED_heure_start);
      Serial.print ("H00 --- ");

      Serial.print ("Fin du cycle lumiere à ");
      Serial.print (LED_heure_fin);
      Serial.println ("H00");

      Serial.println (" --- ");
      Serial.print ("EAU : ");
      Serial.print  (tpsON_min);
      Serial.print  (" min ");
      Serial.print  (tpsON_sec);
      Serial.print  (" sec ");
      Serial.print (" --- ");
      Serial.print (tpsON);
      Serial.println  (" sec ");
      Serial.print ("AIR : ");
      Serial.print  (tpsOFF_min);
      Serial.print  (" min ");
      Serial.print  (tpsOFF_sec);
      Serial.print  (" sec ");
      Serial.print (" --- ");
      Serial.print (tpsOFF);
      Serial.println  (" sec ");
      Serial.println (" --- ");
      Serial.println ("setup: ok");
    }
