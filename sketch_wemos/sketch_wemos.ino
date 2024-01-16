#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "Lapanik";
const char *password = "0769191a";
const char *ap_password = "12345678";

const int redPin = D1;
const int greenPin = D6;
const int bluePin = D7;

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "OK");
}

void colorHandler() {
    String boolRedPin = server.arg("red");
    String boolGreenPin = server.arg("green");
    String boolBluePin = server.arg("blue");

    if (boolRedPin == "True") {
      digitalWrite(redPin, HIGH);
    } else {
      digitalWrite(redPin, LOW);
    }
    if (boolGreenPin == "True") {
      digitalWrite(greenPin, HIGH);
    } else {
      digitalWrite(greenPin, LOW);
    }
    if (boolBluePin == "True") {
      digitalWrite(bluePin, HIGH);
    } else {
      digitalWrite(bluePin, LOW);
    }
    server.send(200, "text/plain", "OK");
}

void analogColorHandler() {
    Serial.println("123");
    String boolRedPin = server.arg("red");
    String boolGreenPin = server.arg("green");
    String boolBluePin = server.arg("blue");
    String brightness = server.arg("brightness");

    if (boolRedPin == "true") {
      Serial.print("red");
      Serial.print(brightness);
      analogWrite(redPin, brightness.toInt());
    } else {
      analogWrite(redPin, 0);
    }
    if (boolGreenPin == "true") {
      analogWrite(greenPin, brightness.toInt());
    } else {
      analogWrite(greenPin, 0);
    }
    if (boolBluePin == "true") {
      analogWrite(bluePin, brightness.toInt());
    } else {
      analogWrite(bluePin, 0);
    }
    Serial.println("123");
    server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected to Wi-Fi");
  Serial.println(WiFi.localIP());
  IPAddress localIP = WiFi.localIP();
  String ap_ssid = "ip: " + localIP.toString();

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ap_ssid.c_str(), ap_password);
  delay(10000);

  WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected to Wi-Fi");
  server.on("/", HTTP_GET, handleRoot);
  server.on("/color", HTTP_GET, analogColorHandler);

  server.begin();
  Serial.println("HTTP-сервер запущен");
}

void loop() {
  server.handleClient();
}
