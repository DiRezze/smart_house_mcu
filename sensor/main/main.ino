#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "env.h"

const int pinoSensorGas = A0;
const int pinoRele = 5;
const int pinoLed = LED_BUILTIN;

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao broker MQTT...");
    if (client.connect("SensorGasNode", mqtt_user, mqtt_pass)) {
      Serial.println("conectado!");
      client.subscribe("casa/comandos"); 
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println("tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(pinoRele, OUTPUT);
  pinMode(pinoLed, OUTPUT);
  pinMode(pinoSensorGas, INPUT);
  digitalWrite(pinoRele, LOW);
  digitalWrite(pinoLed, LOW);

  Serial.begin(112500);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int valorSensor = analogRead(pinoSensorGas);
  Serial.print("Valor do sensor: ");
  Serial.println(valorSensor);

  if (valorSensor > 250) {
    digitalWrite(pinoRele, HIGH);
    digitalWrite(pinoLed, HIGH);
    Serial.println("Vazamento detectado!");
    client.publish("casa/sensor_gas", "1");
  } else {
    digitalWrite(pinoRele, LOW);
    digitalWrite(pinoLed, LOW);
    Serial.println("Sem vazamento");
    client.publish("casa/sensor_gas", "0");
  }

  delay(1000);
}