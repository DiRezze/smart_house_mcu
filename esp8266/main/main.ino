#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "env.h"

// ---- TOPIC LIST ----
const char* topic1 = "casaEtecMAM/luz1";
const char* topic2 = "casaEtecMAM/luz2";
const char* topic3 = "casaEtecMAM/luz3";

#define builtin  LED_BUILTIN
#define device1  5
#define device2  4
#define device3  14

WiFiClientSecure espClient;
PubSubClient client(espClient);

void statusLED(int state) {
  digitalWrite(builtin, state ? LOW : HIGH);
}

void connectWiFi() {
  WiFi.begin(ssid, password);
  byte tentativa = 0;
  while (WiFi.status() != WL_CONNECTED && tentativa < 20) {
    statusLED((tentativa % 2) == 0);
    delay(500);
    tentativa++;
  }
  statusLED(WiFi.status() == WL_CONNECTED);
}

bool connectMQTT() {
  String clientId = "ESP8266Client-" + String(ESP.getChipId(), HEX);
  bool mqttConnected = false;
  if (mqtt_user[0] != 0) {
    mqttConnected = client.connect(clientId.c_str(), mqtt_user, mqtt_pass);
  } else {
    mqttConnected = client.connect(clientId.c_str());
  }
  if (mqttConnected) {
    client.subscribe(topic1);
    client.subscribe(topic2);
    client.subscribe(topic3);
  }
  return mqttConnected;
}

void callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (unsigned int i = 0; i < length; i++)
    msg += (char)payload[i];

  if (strcmp(topic, topic1) == 0) {
    Serial.print("Mensagem no tópico 1: ");
    Serial.println(msg);
    digitalWrite(device1, msg == "1" ? HIGH : LOW);
  } else if (strcmp(topic, topic2) == 0) {
    Serial.print("Mensagem no tópico 2: ");
    Serial.println(msg);
    digitalWrite(device2, msg == "1" ? HIGH : LOW);
  } else if (strcmp(topic, topic3) == 0) {
    Serial.print("Mensagem no tópico 3: ");
    Serial.println(msg);
    digitalWrite(device3, msg == "1" ? HIGH : LOW);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(builtin, OUTPUT);
  pinMode(device1, OUTPUT);
  pinMode(device2, OUTPUT);
  pinMode(device3, OUTPUT);

  digitalWrite(device1, LOW);
  digitalWrite(device2, LOW);
  digitalWrite(device3, LOW);

  statusLED(false);

  connectWiFi();

  espClient.setInsecure();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  if (!client.connected()) {
    statusLED(0);
    byte tentativas = 0;
    while (!client.connected() && tentativas < 10) {
      connectMQTT();
      statusLED((tentativas % 2) == 0);
      delay(500);
      tentativas++;
    }
    statusLED(client.connected());
  }

  statusLED(client.connected() && WiFi.status() == WL_CONNECTED);

  client.loop();
}