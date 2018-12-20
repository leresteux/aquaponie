
//réglages
int tpsON_min = 0, tpsON_sec = 35, tpsOFF_min = 10, tpsOFF_sec = 0;
float dureePAUSSE = 0, tpsPAUSSE_min = 120, tpsRESTANT;

//interface
int  led=10,pin = 9, btn1=8,btn2=7;


//code
int tpsON = 0, tpsOFF = 0, tpsPAUSSE = 0, nbrCYCLE = 0;
boolean pausse = false, air, eau;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  digitalWrite(pin, HIGH);// OFF
  
  tpsON = (( tpsON_min * 60) + tpsON_sec);
  tpsOFF = (tpsOFF_min * 60) + tpsOFF_sec;
  tpsPAUSSE = tpsPAUSSE_min * 60;

//Serial
  Serial.begin(9600);
  Serial.println ("AQUAPONIQUE-2017-BY LERESTEUX JULIEN");
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
  Serial.print ("AutoRestart : ");
  Serial.print  (tpsPAUSSE_min);
  Serial.print  (" min ");
  Serial.print (" --- ");
  Serial.print (tpsPAUSSE);
  Serial.println  (" sec ");
  Serial.println ("setup:ok!!  -  Envoyer p pour mettre en pausse");
  delay(1000);
}

void loop() {

  Air();
  Eau();

}
void Eau() {
  eau = true;
  air = false;
  delay(100);
  nbrCYCLE++;
  Serial.println ("Cycle Eau");
  for (int i = 0; i < tpsON; i + 0) {
    Pause();
    if (pausse == false) {
      delay(1000);
      digitalWrite(pin, LOW);
      i++;    Serial.print (i);
      Serial.print ("/");
      Serial.println (tpsON);
      tpsRESTANT = tpsON - i;


    } else {
      restart();
    }
  }
}
void Air() {
  eau = false;
  air = true;
  Serial.println ("Cycle Air");
  for (int i = 0; i < tpsOFF; i + 0) {
    Pause();
    if (pausse == false) {

      delay(1000);
      digitalWrite(pin, HIGH);
      i++;    Serial.print (i);
      Serial.print ("/");
      Serial.println (tpsOFF);
      tpsRESTANT = tpsOFF - i;

    } else {
      restart();
    }
  }
}


void restart() {

  eau = false;
  air = false;
  delay(100);
  dureePAUSSE = dureePAUSSE + 0.1;
  tpsRESTANT = tpsPAUSSE-dureePAUSSE;
  Serial.print("temps de pausse : ");
  Serial.println(dureePAUSSE);
  
  if (tpsPAUSSE < dureePAUSSE) {
    Serial.println("Restart");
    dureePAUSSE = 0;
    pausse = false;
    
  }
}

void Pause() {
  boolean btnpausse = digitalRead(btn1);
    if (btnpausse)
    { Serial.print("PAUSSE : ");
      pausse = !pausse;
      Serial.println(pausse);
      if (pausse) {
        digitalWrite(pin, HIGH);
      } else {
        digitalWrite(pin, LOW);
      }
    }
  }



