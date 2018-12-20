
//réglages

/* tpsON_min = duree en minute de l'alimentation en eau 
 *  tpsON_sec = duree en seconte de l'alimentation en eau
 *  
 *  tpsOFF_min = duree en mionute de la NON alimentation en eau
 *  tpsOFF_sec = duree en seconte de la NON alimentation en eau
 */


int tpsON_min = 0, tpsON_sec = 30, tpsOFF_min = 10, tpsOFF_sec = 0; //@home


// NE RIEN CHANGER ICI

//interface
int pin = 9;


//code
int  tpsON = 0; 
int tpsOFF = 0;
int nbrCYCLE = 0 ;
boolean air, eau;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);// OFF
  
  tpsON = (( tpsON_min * 60) + tpsON_sec);
  tpsOFF = (tpsOFF_min * 60) + tpsOFF_sec;

//Serial
  Serial.begin(9600);
  Serial.println ("AQUAPONIQUE-2017-BY Young Makers from fablabke");
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
  Serial.print  (" min ");
  Serial.println ("setup: ok");
}

void loop() {
  Eau();
  Air();
}
void Eau() {
  eau = true;
  air = false;
  delay(100);
  nbrCYCLE++;
  Serial.println ("Cycle Eau");
  for (int i = 0; i < tpsON; i + 0) {
      delay(1000);
      digitalWrite(pin, LOW);
      i++;    Serial.print (i);
      Serial.print ("/");
      Serial.println (tpsON);
  }
}
void Air() {
  eau = false;
  air = true;
  Serial.println ("Cycle Air");
  for (int i = 0; i < tpsOFF; i + 0) {


      delay(1000);
      digitalWrite(pin, HIGH);
      i++;    Serial.print (i);
      Serial.print ("/");
      Serial.println (tpsOFF);

  }
}





