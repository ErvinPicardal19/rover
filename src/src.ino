#include <SocketIoClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Wire.h>

#include "creds/creds.h"

#define USER_SERIAL Serial
#define SPEED_PIN 14

SocketIoClient webSocket;

void setup(){
	USER_SERIAL.begin(115200);
	pinMode(SPEED_PIN, OUTPUT);
	Wire.begin();
	delay(50);

	// searchWifi();
	connectWifi();
	
	webSocket.begin("192.168.43.95", 5000);

	webSocket.on("connect", SEND_INFO); 
	webSocket.on("go_up", GO_UP_COMMAND);
	webSocket.on("go_left", GO_LEFT_COMMAND);
	webSocket.on("go_right", GO_RIGHT_COMMAND);
	webSocket.on("go_down", GO_DOWN_COMMAND);
	webSocket.on("stop", STOP);
	webSocket.on("speed_change", CHANGE_SPEED);
	webSocket.on("claw_change", CLAW_ANGLE);
}



void loop(){
	webSocket.loop();
}

void handleData(const char* message, size_t length){
	USER_SERIAL.println(message);

	// DynamicJsonDocument doc(1024);
	// deserializeJson(doc, message);

	// double r = doc["r"];
}

void searchWifi(){
	int numberOfNetwork = WiFi.scanNetworks();

	
	for(int i = 0; i < numberOfNetwork; i++){
		USER_SERIAL.print("Network name: ");
		USER_SERIAL.println(WiFi.SSID(i));
		USER_SERIAL.print("Signal Strength: ");
		USER_SERIAL.println(WiFi.RSSI(i));
		USER_SERIAL.println("--------------------");

	}
}

void connectWifi(){
	WiFi.begin(ssid, pass);

	USER_SERIAL.print(String("Connecting[" + String(ssid) + "]"));
	while(WiFi.status() != WL_CONNECTED){
		USER_SERIAL.print(".");
		delay(1000);
	}

	USER_SERIAL.print("");
	USER_SERIAL.println("WiFi connected");
	USER_SERIAL.print("IP Address: ");
	USER_SERIAL.println(WiFi.localIP());
}

void SEND_INFO(const char* payload, size_t length) {
	char roverId[255];
	// sprintf(roverId, "{\"Id\": %s}", "b2b4407f-6781-43a5-b726-bb04b1ee4b14");
	sprintf(roverId, "\"%s\"", "b2b4407f-6781-43a5-b726-bb04b1ee4b14");
	webSocket.emit("rover_found", roverId);
	USER_SERIAL.println("Sending Info");
	
}

void GO_UP_COMMAND(const char* payload, size_t length) {
	
	USER_SERIAL.println("GOING UP!");
	Wire.beginTransmission(4);
	Wire.write("control");
	Wire.write("u");
	Wire.endTransmission();
	delay(100);
}

void GO_LEFT_COMMAND(const char* payload, size_t length) {
	
	USER_SERIAL.println("GOING LEFT!");
	Wire.beginTransmission(4);
	Wire.write("control");
	Wire.write("l");
	Wire.endTransmission();
	delay(100);
}
void GO_RIGHT_COMMAND(const char* payload, size_t length) {
	
	USER_SERIAL.println("r");
	Wire.beginTransmission(4);
	Wire.write("control");
	Wire.write("r");
	Wire.endTransmission();
	delay(100);
}
void GO_DOWN_COMMAND(const char* payload, size_t length) {
	
	USER_SERIAL.println("d");
	Wire.beginTransmission(4);
	Wire.write("control");
	Wire.write("d");
	Wire.endTransmission();
	delay(100);
}

void STOP(const char* payload, size_t length) {
	
	USER_SERIAL.println("Stopping...");
	Wire.beginTransmission(4);
	Wire.write("control");
	Wire.write("s");
	Wire.endTransmission();
	delay(100);
}

void CHANGE_SPEED(const char* payload, size_t length) {
	byte val = String(payload).toInt();
	USER_SERIAL.println(val);
	Wire.beginTransmission(4);
	Wire.write("speed");
	Wire.write(val);
	Wire.endTransmission();
	delay(100);
	// send_to_slave(payload);
}

void CLAW_ANGLE(const char* payload, size_t length) {
	byte val = String(payload).toInt();
	USER_SERIAL.println(val);
	Wire.beginTransmission(4);
	Wire.write("claw");
	Wire.write(val);
	Wire.endTransmission();
	delay(100);
	// send_to_slave(payload);
}

void send_to_slave(const char* topic, byte data){
	Wire.beginTransmission(4);
	Wire.write(topic);
	Wire.write(data);
	Wire.endTransmission();
	delay(100);
}