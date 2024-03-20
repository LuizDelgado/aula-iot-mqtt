//Passo 1 - Importar as bibliotecas e instalar as dependencias
//Código de instalação da placa esp: .githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
#include <WiFi.h> //Incluir a biblioteca Wifi
WiFiClient esp_do_luizinho_209182022; //Criação do meu objeto cliente
#include <PubSubClient.h> //Incluindo a biblioteca do MQTT
PubSubClient MQTT(esp_do_luizinho_209182022); //Criação do meu objeto MQTT

// Passo 2 - Credenciais de acesso WiFi e MQTT
const char* ssid = "EXEMPLO"; //Nome da nossa rede Wifi
const char* password = "EXEMPLO"; //senha da nossa rede Wifi

const char* endereco_broker = "test.mosquitto.org"; //Endereço do servidor mqtt
int porta = 1883; //Port de comunicação do servidor
#define client_id "esp32_luizinho_209182022" //Nome do cliente que vai acessar o servidor 

void setup() {
  Serial.begin(115200);
  inicia_wifi();
  inicia_mqtt();
  pinMode(2, OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(27,OUTPUT);
}

void loop() {
reconecta_wifi();
reconecta_mqtt();
MQTT.loop();
}

//Passo 3 - Criação da função de WiFi 
void inicia_wifi()
{
  delay(10);
  Serial.println();
  Serial.println("------Iniciando conexão WiFi------");
  Serial.print("Tentando conectar na rede:");Serial.println(ssid);
  Serial.println("Aguarde a conexão");
  reconecta_wifi(); //Chamar a função de conexão com o WiFi
}

void reconecta_wifi(){
  if(WiFi.status() == WL_CONNECTED) return;//Caso conectado ele retorna para da função
  while(WiFi.status() != WL_CONNECTED){ //Enquanto o status do esp for diferente de conectado ele executa a função
    digitalWrite(2,LOW); //Mantem o led interno do esp apagado
    WiFi.begin(ssid, password);
    delay(5000);
  }
  digitalWrite(2,HIGH); //Liga o led interno do esp
  Serial.println(); //Pular uma linha
  Serial.println("Conectado com sucesso!");
}

//Passo 4 - Criação da função do MQTT  
void inicia_mqtt (){
  Serial.println("------ Iniciando MQTT ------");
  reconecta_mqtt(); //Chamar a função de conexão com o MQTT
}

void reconecta_mqtt(){
  while(!MQTT.connected()){ //Enquanto o MQTT estiver desconectado
  reconecta_wifi();
  Serial.print("Tentando conectar ao broker: ");Serial.println(endereco_broker);
  MQTT.setServer(endereco_broker, porta);
  //            (endereço do servidor, porta de acesso
  MQTT.setCallback(mqtt_callback); //É a função para quando chega qualquer mensagem no tópico do broker MQTT
  delay(1000);
  if(MQTT.connect(client_id)){ //Se o cliente se conectou, ele executa
    Serial.println("Conectado com sucesso ao servidor MQTT");
    MQTT.subscribe("luizinho-209182022");
  }
  else { //Se ele não se conectou
    Serial.println("Falha na conexão com o servidor");
    delay(1000);
  } 
 }
}

//                (topico, mensagem, tamanho da minha mensagem)
void mqtt_callback(char* topic, byte* payload, unsigned int length){ //Função para recebo mensagem
  String msg = " "; //Criando uma variavel local para decodificar a mensagem
  //bruna - 5 letras
  for(int i = 0; i < length; i++) //Colocar letra por letra dentro da variavel msg
  {
    char c = (char)payload[i];
    msg += c;
  }

  if (msg == "OIE_GALERA"){
    digitalWrite(13,HIGH);
  }
  else if (msg == "TCHAU_GALERA"){
    digitalWrite(13,LOW);
  }
  
}

