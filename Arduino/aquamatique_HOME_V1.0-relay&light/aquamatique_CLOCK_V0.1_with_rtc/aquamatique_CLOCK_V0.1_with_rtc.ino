#include <DS3231.h>
#include <avr/wdt.h>            // Inclusion de la librairie WatchDog

//réglages

unsigned int tpsON_min = 0, tpsON_sec = 48;                // duree d'arrossage - cycle EAU
unsigned int tpsOFF_min = 30, tpsOFF_sec = 0;              // duree sans arrossage - cycle AIR
unsigned int LED_heure_start = 5, LED_heure_fin = 17 ;     // heures de debut et de fin de l'eclairage - cycle LUMIERE

// NE RIEN CHANGER ICI

//output
const unsigned int pin_relay_pompe = 13;
const unsigned int pin_relay_LED = 12;
//var
int tpsON , tpsOFF;
boolean lumiere;
boolean debug = 0;

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);

// Init a Time-data structure
Time  t;

void setup() {

  //  wdt_disable(); // Desactiver le WatchDog

  wdt_enable(WDTO_8S); // Active le WatchDog sur une durée de 8 secondes


  pinMode(pin_relay_pompe, OUTPUT);
  digitalWrite(pin_relay_pompe, HIGH);// OFF
  pinMode(pin_relay_LED, OUTPUT);
  digitalWrite(pin_relay_LED, HIGH);// OFF

  delay(100);

  // Initialize the rtc object
  rtc.begin();
  // The following lines can be uncommented to set the date and time
  //rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(12, 0, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(1, 1, 2014);   // Set the date to January 1st, 2014

  //convertion en sec
  tpsON = (( tpsON_min * 60) + tpsON_sec);
  tpsOFF = (tpsOFF_min * 60) + tpsOFF_sec;

  delay(100);
  Serial.begin(9600);

  info_start();
}

void loop() {
  t = rtc.getTime();
  LED();
  Eau();
  LED();
  Air();
  
}

void Eau() {
  
  delay(100);
  Serial.println ("Cycle Eau");
  digitalWrite(pin_relay_pompe, LOW);
  for (int i = 0; i < tpsON; i ++) {
    delay(1000);
  
    wdt_reset();

    if (debug) {


      Serial.print (i);
      Serial.print ("/");
      Serial.println (tpsON);

    }
  }
}
void Air() {
  Serial.println ("Cycle Air");
digitalWrite(pin_relay_pompe, HIGH);
  for (int i = 0; i < tpsOFF; i ++) {


    delay(1000);
    digitalWrite(pin_relay_pompe, HIGH);
    wdt_reset();

    if (debug) {

      Serial.print (i);
      Serial.print ("/");
      Serial.println (tpsOFF);
    }


  }
}


void wdt_reload()
{
  delay(8001);
}


void LED() {
  if (t.hour == LED_heure_start && lumiere == 0) {
    lumiere = 1;
    digitalWrite(pin_relay_LED, LOW);// OFF
    if (debug) {
      Serial.println ("LED_ON");
    }
  }
  else if (t.hour == LED_heure_fin && lumiere == 1) {
    lumiere = 0;
    digitalWrite(pin_relay_LED, HIGH);// OFF
    if (debug) {
      Serial.println ("LED_OFF");
    }
  }
}

void info_start() {
  t = rtc.getTime();
  Serial.println ("AQUAPONIQUE-DEC-2018-BY Leresteux Julien");

  Serial.println (" --- ");

  Serial.print("Il est " );
  Serial.print(t.hour);
  Serial.print(":");
  Serial.println(t.min);

  Serial.println (" --- ");

  Serial.print ("Debut du cycle lumiere à ");
  Serial.print (LED_heure_start);
  Serial.println ("H00");

  Serial.println (" --- ");

  Serial.print ("Fin du cycle lumiere à ");
  Serial.print (LED_heure_fin);
  Serial.println ("H00");

  Serial.println (" --- ");
  
  Serial.print ("Durée cycle EAU : ");
  Serial.print  (tpsON_min);
  Serial.print  (" min ");
  Serial.print  (tpsON_sec);
  Serial.println  (" sec ");
  Serial.println (" --- ");
  Serial.print ("Durée cycle AIR : ");
  Serial.print  (tpsOFF_min);
  Serial.print  (" min ");
  Serial.print  (tpsOFF_sec);
  Serial.println  (" sec ");
  Serial.println (" --- ");
  Serial.println ("setup: ok");
}
