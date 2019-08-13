/*

*/
String W =" ";
char w =' ';
int robot = 2;//numero de robot

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "GunnY";
const char* password = "abcde12345";
const char* mqtt_server = "192.168.1.200"; //ip del server 192.168.1.200
IPAddress ip(192, 168, 1, 102); // IP ROBOT
IPAddress gateway(192, 168, 1, 1);// GATEWAY
IPAddress subnet(255, 255, 255, 0); //AVERIGUAR
int timeout=2500;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883); //PUERTO
  client.setCallback(callback);
}

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    }
}

void callback(char* topic, byte* payload, unsigned int length) {
  for (int i = 0; i < length; i++) { }//cambiar
  //----------------------------------------
  if ((char)payload[0] == 'Q') {
    snprintf (msg, 75, "IZQUIERDAQ&");
    Serial.println(msg);
    snprintf (msg, 75, "robot%d,desplazamiento,doblando,izquierda,abierto",robot);
    client.publish("control", msg);
  } 
  if ((char)payload[0] == 'A'){
    snprintf (msg, 75, "IZQUIERDAA&");
    Serial.println(msg);
    snprintf (msg, 75, "robot%d,desplazamiento,doblando,izquierda,medio",robot);
    client.publish("control", msg); 
  }  
  if ((char)payload[0] == 'Z'){
    snprintf (msg, 75, "IZQUIERDAZ&");
    Serial.println(msg);
    snprintf (msg, 75, "robot%d,desplazamiento,doblando,izquierda,cerrado",robot);
    client.publish("control", msg);
  } 
  //----------------------------------------
  if ((char)payload[0] == 'W') {
    snprintf (msg, 75, "ADELANTEW&");
    Serial.println(msg);
    snprintf (msg, 75, "robot%d,desplazamiento,avanzando,rapido,0",robot);
    client.publish("control", msg);
  } 
  if ((char)payload[0] == 'S'){
    snprintf (msg, 75, "ADELANTES&");
    Serial.println(msg);
    snprintf (msg, 75, "robot%d,desplazamiento,avanzando,medio,0",robot);
    client.publish("control", msg); 
  }  
  if ((char)payload[0] == 'X'){
    snprintf (msg, 75, "ADELANTEX&");
    Serial.println(msg);
    snprintf (msg, 75, "robot%d,desplazamiento,avanzando,lento,0",robot);
    client.publish("control", msg);
  } 
  //----------------------------------------
  if ((char)payload[0] == 'E') {
    snprintf (msg, 75, "DERECHAE&");
    Serial.println(msg);
    snprintf (msg, 75, "robot%d,desplazamiento,doblando,derecha,abierto",robot);
    client.publish("control", msg);
  } 
  if ((char)payload[0] == 'D'){
    snprintf (msg, 75, "DERECHAD&");
    Serial.println(msg);
    snprintf (msg, 75, "robot%d,desplazamiento,doblando,derecha,medio",robot);
    client.publish("control", msg); 
  }  
  if ((char)payload[0] == 'C'){
    snprintf (msg, 75, "DERECHAC&");
    Serial.println(msg);
    snprintf (msg, 75, "robot%d,desplazamiento,doblando,derecha,cerrado",robot);
    client.publish("control", msg);
  }  
  //----------------------------------------
  if ((char)payload[0] == 'F'){
    snprintf (msg, 75, "DETENER&");
    Serial.println(msg);
    snprintf (msg, 75, "robot%d,desplazamiento,detenido,0,0",robot);
    client.publish("control", msg);    
  }
  if ((char)payload[0] == 'R'){
    snprintf (msg, 75, "ATRAS&");
    Serial.println(msg);
    snprintf (msg, 75, "robot%d,desplazamiento,retrocediendo,0,0",robot);
    client.publish("control", msg); 
  }  
  //----------------------------------------
  if ((char)payload[0] == 'P'){
    Serial.println("POSICION&");
    leerserial();  
    float lat = W.toFloat();
    W = "" ;  w = ' ' ; 
    leerserial();  
    float lon = W.toFloat();     
    snprintf (msg, 75, "robot%d,sensor,posicion,%f,%f",robot,lat,lon);
    client.publish("control", msg);
    W = "" ;  w = ' ' ; 
    Serial.println("");        
  } 
  //----------------------------------------
  if ((char)payload[0] == 'V'){
    Serial.println("VELOCIDAD&");
    leerserial();  
    float vel = W.toFloat(); 
    snprintf (msg, 75, "robot%d,sensor,velocidad,%f,0",robot,vel);
    client.publish("control", msg);
    W = "" ;  w = ' ' ; 
    Serial.println("");        
  } 
  //---------------------------------------
  if ((char)payload[0] == 'H'){
    Serial.println("ALTITUD&");
    leerserial();  
    float alt = W.toFloat(); 
    snprintf (msg, 75, "robot%d,sensor,altitud,%f,0",robot,alt);
    client.publish("control", msg);
    W = "" ;  w = ' ' ; 
    Serial.println("");        
  } 
  //---------------------------------------  
  if ((char)payload[0] == 'N'){
    Serial.println("SATELITE&");
    leerserial(); 
    int sat = W.toInt(); 
    snprintf (msg, 75, "robot%d,sensor,satelite,%d,0",robot, sat);
    client.publish("control", msg);
    W = "" ;  w = ' ' ;
    Serial.println("");   
  }
  //---------------------------------------
  if ((char)payload[0] == 'U'){
    Serial.println("ULTRA&");
    leerserial(); 
    int ultra = W.toInt(); 
    snprintf (msg, 75, "robot%d,sensor,ultrasonico,%d,0",robot, ultra);
    client.publish("control", msg);
    W = "" ;  w = ' ' ;
    Serial.println("");   
  }     
}
//---------------------------------------
//---------------------------------------
void reconnect() {
  while (!client.connected()) {
    if (client.connect("ROBOT2")) {
      client.publish("control", "robot2,enlinea,,");
      client.subscribe("campo/desplazamiento/robot2");
    } else {
      delay(1000);
    }
  }
}
//----------------------------------------
void leerserial(){
  long int time1 = millis();
  while(1){
 if (Serial.available()) {
         w = Serial.read() ;     
         if(w == '\n'){ return ; }
         W = W + w ;                   
      }
          long int time2=millis()-time1;
         if(time2 >= timeout){ W="99";return ;}//agregar timeout      
}}
//------------------------------
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
