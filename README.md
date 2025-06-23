# ESP8266/ESP32 para sistema de casa inteligente

<div align="center">

  [![Platform](https://img.shields.io/badge/platform-ESP8266-blue.svg)](https://www.espressif.com/en/products/socs/esp8266)
  [![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
  [![Arduino IDE](https://img.shields.io/badge/IDE-Arduino-orange.svg)](https://www.arduino.cc/en/software)
  [![MQTT HiveMQ Cloud](https://img.shields.io/badge/MQTT-HiveMQ%20Cloud-yellow.svg)](https://www.hivemq.com/mqtt-cloud-broker/)
  [![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)](#)
  [![GitHub issues](https://img.shields.io/github/issues/DiRezze/smart_house_mcu.svg)](https://github.com/DiRezze/smart_house_mcu/issues)

</div>

---

## Resumo

Esse projeto implementa um cliente MQTT nas plataformas ESP8266 e ESP32, projetado para Internet das Coisas(IoT) e automação residencial. Os módulo se conectam a um broker MQTT, como um cluster no [HiveMQ Cloud](https://www.hivemq.com/mqtt-cloud-broker/), podendo então serem utilizados para controlar saídas independentes(relés, lâmpadas, eletrônicos no geral) ou receber entradas de variáveis ambientais(vazamentos de gás ou alterações na temperatura). Além disso, utiliza os LEDS embutidos dos módulos como feedback em tempo real da conexão Wi-Fi.

---

## Funcionalidades

- 🔒 **Conexão MQTT Segura:** Utiliza SSL/TLS (`WiFiClientSecure`) para comunicação segura.
- 🟢 **Saída de status do Wi-Fi:** Exibe o status da conexão através do led embutido.
- 📨 **Subscrição em vários tópicos:** Escuta e reage a tópicos MQTT independentes.
- 🛠️ **Configuração fácil:** Credenciais separadas no arquivo `main/env.h`.
- 🖥️ **Feedback serial:** Todas as mensagens recebidas são impressas no monitor serial.


> **DICA:** Instruções mais detalhadas da configuração e funcionamento dos clientes ESP32 e ESP8266 podem ser encontradas nos arquivos `README.md` do respectivo diretório índice.
