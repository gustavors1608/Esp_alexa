#ifndef WIFIPORTAL_H
#define WIFIPORTAL_H

#include "Arduino.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <DNSServer.h>
#include <set>
#include "SPIFFS.h"
#include "FS.h"
#include "site.h"

// Definições de parâmetros e caminhos
#define RSSI_minimo_sinal -85 // Sinal mínimo em dbm para aparecer na pesquisa de WiFis
#define PARAM_INPUT_1 "ssid"
#define PARAM_INPUT_2 "pass"
#define PARAM_INPUT_3 "e"
#define ssidPath "/ssid.txt"
#define passPath "/pass.txt"
#define userPath "/user.txt"
#define reconectPath "/recon.txt" //salva quantas vezes ja se conectou naquela rede
#define html_home "/index.html"
#define timeout_conection_limit 5000 // Tempo máximo para conectar ao WiFi como STATION
#define get_email_user false //deve habilitar a funcao de requisitar o email ao user?

class WifiPortal {
    private:
        String criar_div_wifi(const char* nome_wifi, unsigned char potencia_porcentagem, const char* potencia_simbolo, unsigned char id, signed char rssi);
        String criar_pagina_wifi(String divs_wifi);
        String criar_pagina_user();
        void config_server_ap();
        void abrir_portal();
        inline unsigned char get_quality_signal(char rssi);
        void montar_captive_wifi();
        bool connect_wifi_sta();
        byte scan_wifis();
        byte vrf_counter_reconect();
        void increment_counter_reconect();

        unsigned short time_ms_callback_config = 300;
        void (*_callback)(void) = nullptr;

    public:
        WifiPortal(); 
        ~WifiPortal();
        void connect();
        void reset_data();
        void set_config_callback(void (*name_callback)(void), unsigned short ms_interval_call = 100);
        bool vrf_conexao();
        #if get_email_user ==true
            String get_email();
        #endif
};

#endif // WIFIPORTAL_H
