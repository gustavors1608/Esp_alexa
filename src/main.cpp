#include <Arduino.h>
//#include "WifiPortal.h"
#include "fauxmoESP.h"


fauxmoESP fauxmo;

// -----------------------------------------------------------------------------

#define ID_rele1           "rele 1"
#define ID_rele2           "rele 2"
#define ID_rele3           "rele 3"
#define ID_rele4           "rele 4"


//WifiPortal wifi_portal;

#define _PIN_OUT_WIFI_LED 12// out
#define _PIN_OUT_STATUS_LED 14// out

#define _PIN_LED_OUT_4 33// out
#define _PIN_LED_OUT_3 25// out
#define _PIN_LED_OUT_2 26// out
#define _PIN_LED_OUT_1 27// out

#define _PIN_OUT_1 16// out
#define _PIN_OUT_2 18// out
#define _PIN_OUT_3 21// out
#define _PIN_OUT_4 23// out

#define _PIN_OUT_1_FEEDBACK 4 // in
#define _PIN_OUT_2_FEEDBACK 17 // in
#define _PIN_OUT_3_FEEDBACK 19 // in
#define _PIN_OUT_4_FEEDBACK 22  // in

#define _PIN_GIGA_TESTER 2 // in

#define _PIN_INPUT_ONDEMAND 34 // in

void wifiSetup() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, senha do wifi);

    // Aguarda a conexão
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println();

    // Conexão estabelecida
    Serial.printf("[WIFI] SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}

void set_out(char pin, bool state);
void callback_config(){
  digitalWrite(_PIN_OUT_WIFI_LED, !digitalRead(_PIN_OUT_WIFI_LED));
}

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(115200);

  pinMode(_PIN_INPUT_ONDEMAND, INPUT_PULLUP);
  pinMode(_PIN_OUT_WIFI_LED,OUTPUT);
  pinMode(_PIN_OUT_STATUS_LED,OUTPUT);

  pinMode(_PIN_OUT_1,OUTPUT);
  pinMode(_PIN_OUT_2,OUTPUT);
  pinMode(_PIN_OUT_3,OUTPUT);
  pinMode(_PIN_OUT_4,OUTPUT);

  pinMode(_PIN_LED_OUT_1,OUTPUT);
  pinMode(_PIN_LED_OUT_2,OUTPUT);
  pinMode(_PIN_LED_OUT_3,OUTPUT);
  pinMode(_PIN_LED_OUT_4,OUTPUT);

  wifiSetup();
  set_out(_PIN_OUT_WIFI_LED,true);
  // Define o callback e o intervalo para avisar que ta em config e já abre o portal
  //wifi_portal.set_config_callback(callback_config, 100);
  //wifi_portal.connect();


    // By default, fauxmoESP creates it's own webserver on the defined port
    // The TCP port must be 80 for gen3 devices (default is 1901)
    // This has to be done before the call to enable()
    fauxmo.createServer(true); // not needed, this is the default value
    fauxmo.setPort(80); // This is required for gen3 devices

    // You have to call enable(true) once you have a WiFi connection
    // You can enable or disable the library at any moment
    // Disabling it will prevent the devices from being discovered and switched
    fauxmo.enable(true);

    // Add virtual devices
    fauxmo.addDevice(ID_rele1);
    fauxmo.addDevice(ID_rele2);
    fauxmo.addDevice(ID_rele3);
    fauxmo.addDevice(ID_rele4);

    fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
        
        // Callback when a command from Alexa is received. 
        // You can use device_id or device_name to choose the element to perform an action onto (relay, LED,...)
        // State is a boolean (ON/OFF) and value a number from 0 to 255 (if you say "set kitchen light to 50%" you will receive a 128 here).
        // Just remember not to delay too much here, this is a callback, exit as soon as possible.
        // If you have to do something more involved here set a flag and process it in your main loop.
        
        Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

        // Checking for device_id is simpler if you are certain about the order they are loaded and it does not change.
        // Otherwise comparing the device_name is safer.

        if (strcmp(device_name, ID_rele1)==0) {
            set_out(_PIN_OUT_1,state);
            set_out(_PIN_LED_OUT_1,state);
        } else if (strcmp(device_name, ID_rele2)==0) {
            set_out(_PIN_OUT_2,state);
            set_out(_PIN_LED_OUT_2,state);
        } else if (strcmp(device_name, ID_rele3)==0) {
            set_out(_PIN_OUT_3,state);
            set_out(_PIN_LED_OUT_3,state);
        } else if (strcmp(device_name, ID_rele4)==0) {
            set_out(_PIN_OUT_4,state);
            set_out(_PIN_LED_OUT_4,state);
        } 
    });
}

void loop() {  



  fauxmo.handle();

  static unsigned long last = millis();
  if (millis() - last > 100) {
      last = millis();
      set_out(_PIN_OUT_STATUS_LED, !digitalRead(_PIN_OUT_STATUS_LED));
  }

}



inline void set_out(char pin, bool state){
  digitalWrite(pin,state);
}