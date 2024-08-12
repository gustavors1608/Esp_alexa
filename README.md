
# Sistema de Automação Residencial com ESP32 e Alexa 💡

Este projeto implementa um sistema de automação residencial que permite controlar quatro dispositivos (relés) através de comandos de voz com a Alexa. 🗣️ O sistema utiliza um ESP32 como plataforma principal e a biblioteca FauxmoESP para emular dispositivos inteligentes compatíveis com a Alexa. 🔌

### Recursos ✨

- Controle de até quatro dispositivos (relés) individualmente.
- Integração com a Alexa para controle por voz.
- LEDs indicadores de status para conexão Wi-Fi e atividade do sistema.
- Código bem documentado com comentários Doxygen.

### Hardware Necessário 🧰

- Placa ESP32.
- 4 Relés.
- 6 LEDs.
- Resistores para os LEDs (220 ohms recomendado).
- Protoboard e fios jumper.

### Esquema de Conexão

**Em breve!** ⏳

### Instalação 🚀

1. Faça o download ou clone este repositório:

```bash
git clone https://github.com/seu-usuario/seu-repositorio.git
```

2. Instale a biblioteca FauxmoESP através do Gerenciador de Bibliotecas do Arduino IDE.
3. Abra o arquivo `main.cpp` no Arduino IDE.
4. Altere as seguintes linhas no arquivo `main.cpp` com suas credenciais de Wi-Fi:

```cpp
WiFi.begin("SEU_SSID", "SUA_SENHA"); 
```

5. Faça o upload do código para o seu ESP32.

### Utilização ▶️

1. Após o ESP32 iniciar, ele se conectará à sua rede Wi-Fi.
2. Abra o aplicativo Alexa no seu smartphone ou tablet.
3. Diga "Alexa, procurar dispositivos".
4. A Alexa irá encontrar os quatro dispositivos virtuais (relés) que você configurou.
5. Você já pode controlar os dispositivos usando comandos de voz, como:

- "Alexa, ligar Relé 1"
- "Alexa, desligar Relé 2"

### Personalização 🛠️

- **Nomes dos Dispositivos:** Altere os IDs dos dispositivos virtuais (`ID_RELE1`, `ID_RELE2`, etc.) no código para nomes mais descritivos.
- **Pinos GPIO:** Ajuste os números dos pinos GPIO no código de acordo com a sua fiação.

### Próximos Passos ⏭️

- Implementar uma interface web para controle dos dispositivos através de um navegador. 💻
- Adicionar sensores (temperatura, luminosidade, etc.) para automatizar as ações dos relés. 🌡️
- Criar um sistema de segurança com notificações no smartphone. 🔐

### Licença

Este projeto está licenciado sob a licença MIT - veja o arquivo [LICENSE](LICENSE) para mais detalhes.


