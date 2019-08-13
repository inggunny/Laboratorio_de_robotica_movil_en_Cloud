/*
FINAL ROBOT COMPLETO
25 de junio
*/

#define in4  13
#define in3  12
#define enb  11
#define ena  10
#define in2  9
#define in1  8

#define WIFI_TX_PIN 6
#define WIFI_RX_PIN 7
#define GPS_TX_PIN 4
#define GPS_RX_PIN 5

#define trig  A1
#define echo  A0

#include <Ultrasonic.h>
#include <TinyGPS.h>
#include <SoftwareSerial.h>
#define DEBUG true
TinyGPS gps;
Ultrasonic ultrasonic(trig,echo); // (Trig PIN,Echo PIN)
SoftwareSerial WIFI(WIFI_RX_PIN, WIFI_TX_PIN);
int timeout = 1000;
String W =" ";
char w ;

SoftwareSerial GPS(GPS_RX_PIN, GPS_TX_PIN);// RX | TX
//VARIABLES PARA GPS
bool newData = false;
float lat, lon;
float latitud;
unsigned long fix_age;
char d;

//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
void setup(){
     pinMode(in1,OUTPUT);
     pinMode(in2,OUTPUT);
     pinMode(in3,OUTPUT);
     pinMode(in4,OUTPUT);
     pinMode(ena,OUTPUT);
     pinMode(enb,OUTPUT);     
     GPS.begin(9600);
     WIFI.begin(9600);
     Serial.begin(9600);//19200
     delay(100);
     WIFI.listen(); 
}
//--------------------------------------------------------------------------
void datosgps(){
  GPS.listen();
  long int time = millis();
  while( (time+timeout) > millis()) {
    while (GPS.available()){
      d = GPS.read();
      if (gps.encode(d))
        newData = true;
    }
    if(newData) {
      gps.f_get_position(&lat, &lon, &fix_age);
    }
  }
}
//--------------------------------------------------------------------------
void adelantew(){
  analogWrite(ena,255);
  analogWrite(enb,255);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  }
void adelantes(){
  analogWrite(ena,150);
  analogWrite(enb,150);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  }
void adelantex(){
  analogWrite(ena,75);
  analogWrite(enb,75);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  }
void atras(){
  analogWrite(ena,255);
  analogWrite(enb,255);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  }
void detener(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}

void derechae(){
  analogWrite(ena,255);
  analogWrite(enb,220);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}
void derechad(){
  analogWrite(ena,255);
  analogWrite(enb,150);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}
void derechac(){
  analogWrite(ena,255);
  analogWrite(enb,75);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

void izquierdaq(){
  analogWrite(ena,220);
  analogWrite(enb,255);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}
void izquierdaa(){
  analogWrite(ena,150);
  analogWrite(enb,255);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}
void izquierdaz(){
  analogWrite(ena,75);
  analogWrite(enb,255);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}
//--------------------------------------------------------------------------
void ultra(){
  WIFI.print(ultrasonic.Ranging(CM));
  WIFI.print("\r\n");
}

//--------------------------------------------------------------------------
void posicion(){
  datosgps();
  WIFI.listen();
  WIFI.print(String (lat== TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : lat, 6));
  Serial.print(String (lat== TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : lat, 6));
  WIFI.print("\r\n");
  Serial.print("\r\n");
  WIFI.print(String (lon== TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : lon, 6));
  Serial.print(String (lon== TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : lon, 6));
  WIFI.print("\r\n");
  Serial.print("\r\n");
}
void satelite(){
  datosgps();
  WIFI.listen();
  Serial.println(String (gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites()));
  WIFI.print(String (gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites()));
  WIFI.print("\r\n"); 
  Serial.print("\r\n");
}
void velocidad(){ //PROBAR ESTE
  WIFI.listen();
  Serial.print(String (gps.f_speed_kmph()));
  WIFI.print(String (gps.f_speed_kmph()));
  WIFI.print("\r\n");
  Serial.print("\r\n"); 
}

void altitud(){ //PROBAR ESTE
  WIFI.listen();
  Serial.print(String (gps.f_altitude()));
  WIFI.print(String (gps.f_altitude()));
  WIFI.print("\r\n");
  Serial.print("\r\n"); 
}
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
void loop(){
  if (WIFI.available()) {
      w = WIFI.read();
         Serial.print(w);
         Serial.print(".");
          W = W + w ;                    // Vamos montando un String con lo que entra
         }
  if ( w == '&'){                     // o un simbolo de control
         if ( W.indexOf("ADELANTEW") > 0 ){   
               adelantew();
               }
         if ( W.indexOf("ADELANTES") > 0 ){   
               adelantes();
               }
         if ( W.indexOf("ADELANTEX") > 0 ){   
               adelantex();
               }                              
         if ( W.indexOf("ATRAS") > 0 ){  
               atras();
               }
         if ( W.indexOf("IZQUIERDAQ") > 0 ){   
               izquierdaq();
               }
         if ( W.indexOf("IZQUIERDAA") > 0 ){   
               izquierdaa();
               }
         if ( W.indexOf("IZQUIERDAZ") > 0 ){   
               izquierdaz();
               }                              
         if ( W.indexOf("DERECHAE") > 0 ){
               derechae();
               }
         if ( W.indexOf("DERECHAD") > 0 ){
               derechad();
               } 
         if ( W.indexOf("DERECHAC") > 0 ){
               derechac();
               }                             
         if ( W.indexOf("DETENER") > 0 ){   
               detener();
               } 
         if ( W.indexOf("POSICION") > 0 ){   
               posicion();
               }   
         if ( W.indexOf("SATELITE") > 0 ){  
               satelite();
               }
         if ( W.indexOf("VELOCIDAD") > 0 ){   
               velocidad();
               }
         if ( W.indexOf("ULTRA") > 0 ){   
               ultra();
               }
         if ( W.indexOf("ALTITUD") > 0 ){   
               altitud();
               }                                                                                                         
         W = "" ;  w = ' ' ;                    // Limpiamos las variables
  } 
}
