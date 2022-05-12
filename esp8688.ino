#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <SocketIoClient.h>

#define USER_SERIAL Serial

const char* ssid = "BT-M2CK67";
const char* pass = "prgCMRpenR4ueE";

SocketIoClient webSocket;

void setup() {

  USER_SERIAL.begin(115200);

  searchWiFi();
  connectWiFi();
  
  webSocket.begin("socketio0.herokuapp.com", 443, "/socket.io/?transport=websocket");
  webSocket.emit("join", "{\"type\":\"WIFI\"}");
  webSocket.on("message", controlled);
}

void loop() {
  webSocket.loop();

}

void controlled(const char* message, size_t length){
  USER_SERIAL.println(message);
}


void searchWiFi(){
  int numberOfNetwork = WiFi.scanNetworks();
  USER_SERIAL.println("----");
  
  for(int i = 0; i < numberOfNetwork; i++ ){
    USER_SERIAL.print("Network name: ");
    USER_SERIAL.println(WiFi.SSID(i));
    USER_SERIAL.print("Signal strength: ");
    USER_SERIAL.println(WiFi.RSSI(i));
    USER_SERIAL.println("--------------");
  }
}


void connectWiFi(){
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED){
    USER_SERIAL.print(".");
    delay(1000);
  }

  USER_SERIAL.print("");
  USER_SERIAL.println("WiFi connected");
  USER_SERIAL.print("IP Address : ");
  USER_SERIAL.println(WiFi.localIP());
  
}
