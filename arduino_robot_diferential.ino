#include <NewPing.h>
//biblioteca pentru senzorii ultrasonici
#define MAX_DISTANCE_L_R 300 
//distanța maximă de înregistrare pentru senzorii laterali
#define MAX_DISTANCE 350
//distanța maximă de înregistrare pentru senzorul central
#define COLL_DIST_L 15
#define COLL_DIST_R 15
//distanțele de coliziune pentru senzorii laterali
#define COLL_DIST_C 20
//distanța de coliziune pentru senzorul central
#define ECHO_PIN_R 8
#define TRIG_PIN_R 9
#define ECHO_PIN_C 10
#define TRIG_PIN_C 11
#define ECHO_PIN_L 12
#define TRIG_PIN_L 13
int DrFr=3;int DrSp=2;
int StFr=4;int StSp=5;
//definirea corespondențelor pin-port pentru senzori și motoare (declarate prin "int")
//de la 2 la 13 de pe partea cu porturi digitale
NewPing sonarR(TRIG_PIN_R,ECHO_PIN_R,MAX_DISTANCE_L_R);
NewPing sonarC(TRIG_PIN_C,ECHO_PIN_C,MAX_DISTANCE);
NewPing sonarL(TRIG_PIN_L,ECHO_PIN_L,MAX_DISTANCE_L_R);
//declararea obiectelor (senzorii), folosindu-ne de biblioteca <NewPing.h>, cu 3 argumente :
//trigger pin, echo pin si distanta maxima
//setarea condițiilor inițiale
void setup(){
pinMode(DrFr,OUTPUT);pinMode(StFr,OUTPUT);pinMode(DrSp,OUTPUT);pinMode(StSp,OUTPUT);
//stabilim ieșirea din sistem, ieșirea fiind acțiunea motoarelor pe baza senzorilor
digitalWrite(DrFr,LOW);digitalWrite(StFr,LOW);digitalWrite(DrSp,LOW);digitalWrite(StSp,LOW);
//inițierea cu viteză zero pentru motoare
Serial.begin(9600);
//bits per second sau baud, în cazul nostru 9600 pentru comunicarea cu terminalul
}

//ciclarea programlui
void loop(){
  int  DIST_L = scan_L(),             
       DIST_C = scan_C(),
       DIST_R = scan_R();
  //declararea distanței măsurate de senzori, 
  const int interval = 250;
  long then = millis();
  //folosim millis() pentru a nu folosi funcția delay(ms), iar structura de repetiție (while-ul)
  //face trecerea de la o comandă la alta mai lină, asigurând un timp în care nu se execută linii de cod
  //acesta fiind de 250 ms
  //if-urile sunt vor fi parcurse asemenător unei structuri repetitive datorită lui void loop()
         while (millis()-then<=interval)
         {
         if ( DIST_L>COLL_DIST_L && DIST_R>COLL_DIST_R ) {moveForward();Serial.println("Front");}
         else if ( DIST_R>DIST_L ) {moveStop();turnRight();Serial.println("Right: ");Serial.println(DIST_R);Serial.println();}
         else if ( DIST_R<DIST_L ) {moveStop();turnLeft();Serial.print("Left: ");Serial.print(DIST_L);Serial.println();}
         else if ( DIST_L==DIST_R ) {moveStop();moveBackward();Serial.print("Back");Serial.println();}
         }
}
  int scan_R(){return (sonarR.ping() / US_ROUNDTRIP_CM);}
  int scan_C(){return (sonarC.ping() / US_ROUNDTRIP_CM);}
  int scan_L(){return (sonarL.ping() / US_ROUNDTRIP_CM);} 
  //subprogramele ce returnează distanțele măsurate în cm
  
  //subprogramele de schimbare a frecvenței de mișcare a motoarelor, respectiv 
  //HIGH sau LOW, pentru porturile analogice se mai pot face mici modificări de 
  //viteză, însă cele digitale schimbă doar frecvența.
  void moveStop(){
    digitalWrite(DrFr,LOW);
    digitalWrite(StFr,LOW);
    digitalWrite(DrSp,LOW);
    digitalWrite(StSp,LOW);
  }
  void moveForward(){
    digitalWrite(DrFr,HIGH);
    digitalWrite(StFr,HIGH);
    digitalWrite(DrSp,LOW);
    digitalWrite(StSp,LOW);
  }
  void moveBackward(){
    digitalWrite(DrFr,LOW);
    digitalWrite(StFr,LOW);
    digitalWrite(DrSp,HIGH);
    digitalWrite(StSp,HIGH);
  }
  void turnRight(){
    digitalWrite(DrFr,LOW);
    digitalWrite(StFr,HIGH);
    digitalWrite(DrSp,HIGH);
    digitalWrite(StSp,LOW);
}
  void turnLeft(){
    digitalWrite(DrFr,HIGH);
    digitalWrite(StFr,LOW);
    digitalWrite(DrSp,LOW);
    digitalWrite(StSp,HIGH);
}