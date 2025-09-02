
//JULIOBRAUN DESENVOLVIMENTO IOT 
//ESP32 NA REDE WIFI UTILIZANDO ACCESS POINT E LIGA LED DA PLACA


//IncluSsão da biblioteca
#include <WiFiManager.h>

//Objeto do Wifi do AP
WiFiManager wifiManager;

//Defino o pino que funciona o LED que vem na placa
int LED_BUILTIN = 2;

//Define o pino para reset das definicoes de wifi
int pino_reset = 4;

//Configurações iniciais *******************
void setup() {
  //Definindo que o sinal irá sair para ligar o led da placa
  pinMode(LED_BUILTIN, OUTPUT);
  //Definindo que o interruptor irá receber um sinal
  pinMode(pino_reset, INPUT);

  //Especifico a comunicação com o monitor
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

//Programa principal ***********************
void loop() {
  //Se o botão de reset for pressionado
  if (digitalRead(pino_reset) == HIGH) {
  
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

