#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "Smart Home"
#define APPSK "9+9+9-9-"
#endif

const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

    void handleRoot(){
                     server.send(200, "text/plain","READY");
                     }
                      
    void handle_a() {
                     digitalWrite(LED_BUILTIN,HIGH);
                     Serial.write('a');
                    server.send(200, "text/plain","Led Garage Off");
                    }
                      
    void handle_A() {
                     digitalWrite(LED_BUILTIN,LOW);
                     Serial.write('A');
                    server.send(200, "text/plain","Led Garage On");
                    }
    void handle_b() {
                     digitalWrite(LED_BUILTIN,HIGH);
                     Serial.write('B');
                     server.send(200, "text/plain","Led Salon Off");
                    }
                      
    void handle_B() {
                     digitalWrite(LED_BUILTIN,LOW);
                     Serial.write('b');
                    server.send(200, "text/plain","Led Salon On");
                    }
    void handle_c() {
                     digitalWrite(LED_BUILTIN,HIGH);
                      Serial.write('c');
                    server.send(200, "text/plain","Led Kitchen Off");
                    }
                      
    void handle_C() {
                     digitalWrite(LED_BUILTIN,LOW);
                     Serial.write('C');
                    server.send(200, "text/plain","Led Kitchen On");
                    }
    void handle_d() {
                     digitalWrite(LED_BUILTIN,HIGH);
                     Serial.write('d');
                    server.send(200, "text/plain","Led Room1 Off");
                    }
                      
    void handle_D() {
                     digitalWrite(LED_BUILTIN,LOW);
                     Serial.write('D');
                    server.send(200, "text/plain","Led Room1 On");
                    }
    void handle_e() {
                     digitalWrite(LED_BUILTIN,HIGH);
                     Serial.write('e');
                    server.send(200, "text/plain","Led Bathroom Off");
                    }
                      
    void handle_E() {
                     digitalWrite(LED_BUILTIN,LOW);
                     Serial.write('E');
                    server.send(200, "text/plain","Led Bathroom On");
                    }                                         
    void handle_f() {
                     digitalWrite(LED_BUILTIN,HIGH);
                     Serial.write('f');
                    server.send(200, "text/plain","Led Room2 Off");
                    }
                      
    void handle_F() {
                     digitalWrite(LED_BUILTIN,LOW);
                     Serial.write('F');
                    server.send(200, "text/plain","Led Room2 On");
                    }
    void handle_g() {
                     digitalWrite(LED_BUILTIN,HIGH);
                     Serial.write('g');
                    server.send(200, "text/plain","Window is Close");
                    }
                      
    void handle_G() {
                     digitalWrite(LED_BUILTIN,LOW);
                     Serial.write('G');
                    server.send(200, "text/plain","Window is Open");
                    }
    void handle_h() {
                     digitalWrite(LED_BUILTIN,HIGH);
                     Serial.write('h');
                    server.send(200, "text/plain","Home Door is Close ");
                    }
                      
    void handle_H() {
                     digitalWrite(LED_BUILTIN,LOW);
                     Serial.write('H');
                    server.send(200, "text/plain","Home Door is Open");
                    }
    void handle_i() {
                     digitalWrite(LED_BUILTIN,HIGH);
                     Serial.write('i');
                    server.send(200, "text/plain","Garage Door is Close");
                    }
                      
    void handle_I() {
                     digitalWrite(LED_BUILTIN,LOW);
                     Serial.write('I');
                    server.send(200, "text/plain","Garage Door is Open");
                    }   
    
void setup() {
  pinMode(LED_BUILTIN,OUTPUT);   
  digitalWrite(LED_BUILTIN,HIGH); 

  delay(1000);
  Serial.begin(9600);
  Serial.println();
  Serial.print("Configuring access point...");

  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  server.on("/", handleRoot);
  server.on("/A",handle_A);  
  server.on("/a",handle_a);
  server.on("/B",handle_B);  
  server.on("/b",handle_b);
  server.on("/C",handle_C);  
  server.on("/c",handle_c);
  server.on("/D",handle_D);  
  server.on("/d",handle_d);
  server.on("/E",handle_E);  
  server.on("/e",handle_e);
  server.on("/F",handle_F);  
  server.on("/f",handle_f);
  server.on("/G",handle_G);  
  server.on("/g",handle_g);
  server.on("/H",handle_H);  
  server.on("/h",handle_h);
  server.on("/I",handle_I);  
  server.on("/i",handle_i);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
