#include <Arduino.h>
#include "fauxmoESP.h"

// Define o nome do dispositivo para facilitar a identificação na rede
#define DEVICE_NAME "ESP32-ALEXA" 

// --- Constantes para os IDs dos dispositivos virtuais ---
#define ID_RELE1 "Relé 1"
#define ID_RELE2 "Relé 2"
#define ID_RELE3 "Relé 3"
#define ID_RELE4 "Relé 4"

// --- Constantes para os pinos GPIO ---
#define PIN_WIFI_LED 12 
#define PIN_STATUS_LED 14

#define PIN_LED_OUT_1 27 
#define PIN_LED_OUT_2 26 
#define PIN_LED_OUT_3 25 
#define PIN_LED_OUT_4 33 

#define PIN_OUT_1 16 
#define PIN_OUT_2 18 
#define PIN_OUT_3 21 
#define PIN_OUT_4 23 

#define PIN_OUT_1_FEEDBACK 4 
#define PIN_OUT_2_FEEDBACK 17 
#define PIN_OUT_3_FEEDBACK 19 
#define PIN_OUT_4_FEEDBACK 22  

// --- Variáveis Globais ---
fauxmoESP fauxmo;

// --- Protótipos de Funções ---
void wifiSetup();
void set_out(uint8_t pin, bool state);

/**
 * @brief Função de configuração do Arduino.
 * 
 * Inicializa a comunicação serial, configura os pinos GPIO,
 * conecta à rede Wi-Fi e configura os dispositivos virtuais com o FauxmoESP.
 */
void setup() {
  Serial.begin(115200);

  // --- Configuração dos pinos GPIO ---
  pinMode(PIN_WIFI_LED, OUTPUT);
  pinMode(PIN_STATUS_LED, OUTPUT);

  pinMode(PIN_LED_OUT_1, OUTPUT);
  pinMode(PIN_LED_OUT_2, OUTPUT);
  pinMode(PIN_LED_OUT_3, OUTPUT);
  pinMode(PIN_LED_OUT_4, OUTPUT);

  pinMode(PIN_OUT_1, OUTPUT);
  pinMode(PIN_OUT_2, OUTPUT);
  pinMode(PIN_OUT_3, OUTPUT);
  pinMode(PIN_OUT_4, OUTPUT);

  // --- Configuração da conexão Wi-Fi ---
  wifiSetup();
  digitalWrite(PIN_WIFI_LED, HIGH);

  // --- Configuração do FauxmoESP ---
  fauxmo.createServer(true); 
  fauxmo.setPort(80);  
  fauxmo.enable(true);

  // --- Adicionando dispositivos virtuais ---
  fauxmo.addDevice(ID_RELE1);
  fauxmo.addDevice(ID_RELE2);
  fauxmo.addDevice(ID_RELE3);
  fauxmo.addDevice(ID_RELE4);

  // --- Configuração do callback para quando um dispositivo virtual é acionado ---
  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
    Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

    if (strcmp(device_name, ID_RELE1) == 0) {
      set_out(PIN_OUT_1, state);
      set_out(PIN_LED_OUT_1, state);
    } else if (strcmp(device_name, ID_RELE2) == 0) {
      set_out(PIN_OUT_2, state);
      set_out(PIN_LED_OUT_2, state);
    } else if (strcmp(device_name, ID_RELE3) == 0) {
      set_out(PIN_OUT_3, state);
      set_out(PIN_LED_OUT_3, state);
    } else if (strcmp(device_name, ID_RELE4) == 0) {
      set_out(PIN_OUT_4, state);
      set_out(PIN_LED_OUT_4, state);
    } 
  });
}

/**
 * @brief Função de loop principal do Arduino.
 * 
 * Gerencia as requisições do FauxmoESP e atualiza o LED de status.
 */
void loop() {  
  fauxmo.handle();

  static unsigned long lastMillis = 0;
  if (millis() - lastMillis > 100) {
    lastMillis = millis();
    digitalWrite(PIN_STATUS_LED, !digitalRead(PIN_STATUS_LED));
  }
}

/**
 * @brief Função para configurar e conectar o ESP32 à rede Wi-Fi.
 * 
 * Tenta se conectar à rede Wi-Fi com o SSID e senha especificados.
 * Se a conexão for bem-sucedida, imprime informações sobre a rede na serial.
 */
void wifiSetup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin("SEU_SSID", "SUA_SENHA"); // Substitua pelo seu SSID e senha

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\nConexão Wi-Fi estabelecida!");
  Serial.printf("SSID: %s\n", WiFi.SSID().c_str());
  Serial.printf("Endereço IP: %s\n", WiFi.localIP().toString().c_str());
}

/**
 * @brief Define o estado de um pino GPIO.
 * 
 * @param pin Número do pino GPIO.
 * @param state Estado desejado do pino (HIGH ou LOW).
 */
void set_out(uint8_t pin, bool state) {
  digitalWrite(pin, state);
}