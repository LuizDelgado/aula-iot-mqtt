#Importar as bibliotecas
import paho.mqtt.client as mqtt 

#Definição de informações do MQTT - Broker e porta 
broker = "test.mosquitto.org"
porta = 1883

#Criação do cliente
cliente = mqtt.Client(mqtt.CallbackAPIVersion.VERSION1)

#Definição de callbacks e handlers
def on_message(client, userdata, mensagem):
    print(f"A mensagem que foi recebida no tópico {mensagem.topic} foi {mensagem.payload.decode()}")

#Associação de callback com handlers
cliente.on_message = on_message 

#Se conectar com o servidor Broker MQTT
cliente.connect(broker,port=porta)

#Inscrever no tópico
topico = "aula_iot_3ano"
cliente.subscribe(topico)

#Criar o loop de recebimento de mensagens
cliente.loop_forever()