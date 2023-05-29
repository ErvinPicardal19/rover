#include <SocketIoClient.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <NewPing.h>

#include "creds/creds.h"

#define USER_SERIAL Serial
#define SPEED_PIN 14

byte sonar_mode = 0;
byte stop_flag = 0;

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
	webSocket.on("sonar", SONAR_MODE);
}

unsigned long currentMillis = millis();

void loop(){

	if(sonar_mode == 1) {
		if(millis() - currentMillis > 100) {
				Wire.requestFrom(6, 1);    // request 6 bytes from peripheral device #8

				while (Wire.available()) { // peripheral may send less than requested
					char c = Wire.read(); // receive a byte as character
					//  Serial.print(c);       // print the character
					if(c == 's' && stop_flag == 0){
						USER_SERIAL.println("Stopping...");
						Wire.beginTransmission(4);
						Wire.write("control");
						Wire.write("s");
						Wire.endTransmission();
						stop_flag = 1;
					} else if(c == 'g') {
						stop_flag = 0;
					}
				}

				currentMillis = millis();
			}
	}
  

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
	if(stop_flag == 0 || sonar_mode == 0) {
		USER_SERIAL.println("GOING UP!");
		Wire.beginTransmission(4);
		Wire.write("control");
		Wire.write("u");
		Wire.endTransmission();
	}

}

void GO_LEFT_COMMAND(const char* payload, size_t length) {
		USER_SERIAL.println("GOING LEFT!");
		Wire.beginTransmission(4);
		Wire.write("control");
		Wire.write("l");
		Wire.endTransmission();
}
void GO_RIGHT_COMMAND(const char* payload, size_t length) {
		USER_SERIAL.println("r");
		Wire.beginTransmission(4);
		Wire.write("control");
		Wire.write("r");
		Wire.endTransmission();
}
void GO_DOWN_COMMAND(const char* payload, size_t length) {

		USER_SERIAL.println("d");
		Wire.beginTransmission(4);
		Wire.write("control");
		Wire.write("d");
		Wire.endTransmission();

}

void STOP(const char* payload, size_t length) {
	
	USER_SERIAL.println("Stopping...");
	Wire.beginTransmission(4);
	Wire.write("control");
	Wire.write("s");
	Wire.endTransmission();

}

void CHANGE_SPEED(const char* payload, size_t length) {
	byte val = String(payload).toInt();
	USER_SERIAL.println(val);
	Wire.beginTransmission(4);
	Wire.write("speed");
	Wire.write(val);
	Wire.endTransmission();

	// send_to_slave(payload);
}

void CLAW_ANGLE(const char* payload, size_t length) {
	byte val = String(payload).toInt();
	USER_SERIAL.println(val);
	Wire.beginTransmission(4);
	Wire.write("claw");
	Wire.write(val);
	Wire.endTransmission();

	// send_to_slave(payload);
}

void SONAR_MODE(const char* payload, size_t length) {
	Serial.println(payload);
   sonar_mode = String(payload).toInt();
}

void send_to_slave(const char* topic, byte data){
	Wire.beginTransmission(4);
	Wire.write(topic);
	Wire.write(data);
	Wire.endTransmission();

}