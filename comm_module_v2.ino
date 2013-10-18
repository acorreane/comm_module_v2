// -- INCLUDES -- //
#include <avr/io.h>
#include <avr/wdt.h>
#include "etherShield.h"
#include "ETHER_28J60.h"

// -- VAR's" -- //
char* params;
String inData;

// -- SHIELD CONFIG -- //

static uint8_t mac[6] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x25}; //MAC
static uint8_t ip[4] = {172, 168, 1, 178}; // IP
static uint16_t port = 80; // HTTP PORT

ETHER_28J60 e; // SERVER NAME

byte login;
byte auth;


int cnt;

long virtualmillis = 0;   
long resetmillis = 0;     
long interval = 10000;    

void setup(){
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  
  digitalWrite(6, HIGH);
  delay(50);
  digitalWrite(6, LOW); 
  Serial.begin(9600); 
  e.setup(mac, ip, port);
  digitalWrite(8, HIGH);
}

void reset(){
    digitalWrite(5, HIGH);
    delay(100);
    pinMode(19, OUTPUT);             
   }

void loop(){ 

  if (params = e.serviceRequest()){

   cnt++;
   inData = params;
   if (cnt >10){
 
   if (params = e.serviceRequest()){
   String CompinData = params;
   if (CompinData == inData){
      reset();
   }
   else{
   cnt = 0;
   }
  }
  
  if (auth == 1){
    if (inData == "logout"){
     e.print("Access Closed");
     e.respond();
     login = 0;
     auth = 0;
    }
    Serial.print(inData);
    e.print("DATA OK");
    e.respond();
    digitalWrite(7, HIGH);
    delay(50);
    digitalWrite(7, LOW);
    }
   }
   if (auth == 0){
    if (login == 0){ 
     if (inData == "login"){
     e.print("Enter Password");
     e.respond();
     login = 1;

   }
   else{
   e.print("Protected Resource");
   e.respond();
     }
    }
   }
   if (login == 1){
    if (inData == "1234"){
    e.print("Access Allowed");
    e.respond();
    login = 0;
    auth = 1;

    }
    else{
    e.print("Access Denied");
    e.respond();
    }
   }
  }
 }
 
