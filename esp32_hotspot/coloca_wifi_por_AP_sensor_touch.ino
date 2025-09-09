//JULIOBRAUN DESENVOLVIMENTO IOT
//CONECTANDO O ESP32 EM QUAQUER REDE WIFI UTILIZANDO PUSH BOTTON

//Incluo biblioteca
#include <WiFiManager.h>

//Objeto do Wifi do AP
WiFiManager wifiManager;

//Defino o pino que funciona o LED que vem na placa
int LED_BUILTIN = 2;
int pinoTouch = 13; //pino com sensor touch
int capacitanciaMaxima = 20; //valor que nos da a certeza de toque

void setup() {
  //Definindo que o sinal irá sair para ligar o led da placa
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  //Cria um AP (Access Point) ("nome da rede", "senha da rede")
  wifiManager.setConfigPortalTimeout(240);
  if (!wifiManager.autoConnect("ESP32-WIFI", "12345678")) {
    Serial.println(F("Falha na conexao. Resetar e tentar novamente..."));
    delay(3000);
    ESP.restart();
    delay(5000);
  }
  //Mensagem caso conexao Ok
  Serial.println(F("Conectado na rede Wifi."));
  Serial.print(F("Endereco IP: "));
  Serial.println(WiFi.localIP());
}

void loop() {
    //faz 100 leituras de cada sensor touch e calcula a média do valor lido
    int media = 0;
    for(int i=0; i< 100; i++)
    {
      media += touchRead(pinoTouch);    
    }
    media = media / 100;

    //Se ativou o touch
    if(media < capacitanciaMaxima)
    {
      digitalWrite(LED_BUILTIN,LOW); //Apaga LED
    
      //Apaga os dados da rede wifi gravados na memoria e abre AP
      WiFiManager wifiManager;
      wifiManager.resetSettings();
      Serial.println("Configuracoes zeradas!");
      ESP.restart();
    }

    if(WiFi.status()== WL_CONNECTED){ //Se conectado na rede      
      digitalWrite(LED_BUILTIN,HIGH); //Acende LED              
    }else{
      digitalWrite(LED_BUILTIN,LOW); //Apaga LED
      wifiManager.autoConnect();//Função para se autoconectar na rede caso caia    
    }
}
