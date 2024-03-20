#Importar as bibliteocas
import paho.mqtt.client as mqtt #Biblioteca do protocolo mqtt
import time

#Credenciais do broker
BROKER = "test.mosquitto.org"
PORT = 1883

#Criar função de conexão
def on_connect(client, userdata, flgs, rc):
    if rc==0:
        print("Conexão bem sucedida!")
    else:
        print("Não foi possivel se conectar ao servidor!")

#Criar o cliente
cliente = mqtt.Client() #mqtt.CallbackAPIVersion.VERSION1

#Conectar no broker
cliente.connect(BROKER, port=PORT)

#Verificar a conexão
cliente.on_connect = on_connect


#Publicar a mesagem
cliente.publish("aula_iot_3ano", "DESLIGA_LED_VERMELHO")
time.sleep(1)




#Desconectar do server
cliente.disconnect()