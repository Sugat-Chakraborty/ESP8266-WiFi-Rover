#define ENA         D5    // GPIO14 - Enable/speed Right motors
#define ENB         D6    // GPIO12 - Enable/speed Left motors
#define IN_1        D7    // GPIO13 - Right motor IN1
#define IN_2        D2    // GPIO4  - Right motor IN2
#define IN_3        D1    // GPIO5  - Left motor IN3
#define IN_4        D0    // GPIO16 - Left motor IN4

#define HEADLIGHT_L D8    // GPIO15 - Left LED
#define HEADLIGHT_R D4    // GPIO2  - Right LED


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


String command;
int speedCar = 800;          
int speed_Coeff = 3;

const char* ssid = "NodeMCU Car";
ESP8266WebServer server(80);


void HTTP_handleRoot(void);
void stopRobot();


void setup() {
  Serial.begin(115200);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);

  pinMode(HEADLIGHT_L, OUTPUT);
  pinMode(HEADLIGHT_R, OUTPUT);

  analogWriteFreq(1000);   

  stopRobot();             

  
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_handleRoot);
  server.onNotFound(HTTP_handleRoot);
  server.begin();

  Serial.println("WiFi Robot with Dual Headlights Ready");
}


void headlightsOn() {
  digitalWrite(HEADLIGHT_L, HIGH);
  digitalWrite(HEADLIGHT_R, HIGH);
}

void headlightsOff() {
  digitalWrite(HEADLIGHT_L, LOW);
  digitalWrite(HEADLIGHT_R, LOW);
}


void goAhead() {
  headlightsOn();

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}

void goBack() {
  headlightsOn();

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}

void goRight() {
  headlightsOn();

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}

void goLeft() {
  headlightsOn();

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}

void goAheadRight() {
  headlightsOn();

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar / speed_Coeff);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}

void goAheadLeft() {
  headlightsOn();

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar / speed_Coeff);
}

void goBackRight() {
  headlightsOn();

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar / speed_Coeff);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}

void goBackLeft() {
  headlightsOn();

  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar / speed_Coeff);
}

void stopRobot() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, 0);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, 0);

  headlightsOff();
}


void loop() {
  server.handleClient();
  command = server.arg("State");

  if      (command == "F") goAhead();
  else if (command == "B") goBack();
  else if (command == "L") goLeft();
  else if (command == "R") goRight();
  else if (command == "I") goAheadRight();
  else if (command == "G") goAheadLeft();
  else if (command == "J") goBackRight();
  else if (command == "H") goBackLeft();
  else if (command == "0") speedCar = 400;
  else if (command == "1") speedCar = 470;
  else if (command == "2") speedCar = 540;
  else if (command == "3") speedCar = 610;
  else if (command == "4") speedCar = 680;
  else if (command == "5") speedCar = 750;
  else if (command == "6") speedCar = 820;
  else if (command == "7") speedCar = 890;
  else if (command == "8") speedCar = 960;
  else if (command == "9") speedCar = 1023;
  else if (command == "S") stopRobot();
}


void HTTP_handleRoot(void) {
  if (server.hasArg("State")) {
    Serial.println(server.arg("State"));
  }
  server.send(200, "text/html", "");
}
