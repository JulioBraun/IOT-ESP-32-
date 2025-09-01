
//JULIOBRAUN DESEVOLVIMENTO IOT
//COLOCA O ESP32 NA REDE WIFI

//Para funcionar o WiFi incluir biblioteca
#include <WiFi.h>

const char* SSID = "REDE"; //Nome da rede WI-FI que deseja se conectar
const char* PASSWORD = "SENHA"; //Senha da rede WI-FI que deseja se conectar

//Configurações iniciais
void setup() {
  // comunicação com o monitor
  Serial.begin(9600);
  //Fica em loop até conectar
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      Serial.println(".");
  } 
  // IP obtido no monitor
  Serial.println("IP obtido: ");
  Serial.println(WiFi.localIP());
}

//Programa principal ***********************
void loop() {


}
