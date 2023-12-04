/*
  Universidad Nacional Autónoma de México
  Facultad de Ciencias
  Licenciatura en Ciencias de la Computación
  Seminario de Ciencias de la Computación A: Introducción al Internet de las Cosas

  Escrito por:
  García Padrilla Rodrigo 
  Giron Jimenez Emmanuel
  Última modificación: 30-diciembre-2023
*/

//====================================================================
//====================================================================
//Variables del bot ====================================================================
//====================================================================
//====================================================================

// Descargar el .ZIP de la página: https://github.com/shurillu/CTBot .Programa -> Incluir Librería -> Añadir blibloteca .ZIP... -> Agregar el .ZIP que se descargo.
#include "CTBot.h" //Herramientas -> Administrar Biblotecas -> buscar e instalar "CTBot" y tambien buscar e instalar "ArduinoJson". 
#include <EasyBuzzer.h>
// #include <WiFi.h>

CTBot myBot; // Crea un objeto para interactuar con el bot de Telegram.

// Detalles de la red Wi-Fi y el token de autenticación del bot de Telegram.
String ssid = "SistemasSimbolicos2.4GH";  // Reemplazar con tu SSID de Wi-Fi.
String pass = ""; // Reemplazar con tu contraseña de Wi-Fi.
String token = "6719092961:AAFkNk6LvP36SeXs_8tu-5NvFfqfV8o-tgs"; // Reemplazar con el token de tu bot de Telegram.

//====================================================================
//====================================================================
//Variables de la alarma =============================================
//====================================================================
//====================================================================

bool activatedAlarm = false;
int pinLed = 23;
int pinSoundSensor = 13;
//Defino el pin del buzzer
int pinBuzzer = 4;

void setup() {
  Serial.begin(115200); // Inicia la comunicación serial.
  pinMode(pinSoundSensor, INPUT);
  setupBot();
  setupAlarma();
}

void setupBot(){
  Serial.print("Comenzando TelegramBot...  ");
  
  myBot.wifiConnect(ssid, pass); // Conecta a la red Wi-Fi especificada.
  myBot.setTelegramToken(token); // Establece el token de autenticación para el bot de Telegram.
  delay(2000); // Espera un momento para que la conexión se establezca.

  // Verifica si la conexión con el bot de Telegram se ha establecido correctamente.
  if (myBot.testConnection())
    Serial.println("Conectado con Bot");
  else
    Serial.println("Error en la conexión");
  }

void setupAlarma(){
  pinMode(pinLed, OUTPUT);
  
  // Pin del zumbador
  EasyBuzzer.setPin(4);
  // Ajustes del tono
}
void sonidoFinal(){
  EasyBuzzer.beep(
    1350, //Frecuencia en Hz
    3000 // Duración del pitido
  );
}

void loop() {
  Serial.print(analogRead(13));
  Serial.print("\n");
  delay(250);
  // loopBot();
  // loopSoundSensor();
  // if(activatedAlarm){
  //   activateAlarm();
  // }
  // delay(1000);
}

void loopBot(){
  TBMessage msg; // Crea un objeto para almacenar los mensajes entrantes de Telegram.

  // Verifica si hay un nuevo mensaje para el bot de Telegram.
  if (myBot.getNewMessage(msg)) {
    if (msg.text.equalsIgnoreCase("/start")) {
      // Si el comando es "/start", responde con un mensaje de bienvenida e instrucciones.
      Serial.print("Nueva interacción de: ");
      Serial.println(msg.sender.username);
      myBot.sendMessage(msg.sender.id, "Teclea /encender, para encontrar tu objeto: ");
    }
    else if (msg.text.equalsIgnoreCase("/encender")){
      //aqui va el codigo para encender la alarma.
        activatedAlarm = true;
    }
    else if (msg.text.equalsIgnoreCase("/Alto")){
        //aqui va el codigo para apagar la alarma
        activatedAlarm = false;
    }
    else {
      // Si el mensaje recibido no coincide con ninguno de los comandos anteriores, envía un mensaje de error.
      myBot.sendMessage(msg.sender.id, "Mensaje no válido, intenta de nuevo con: /start");
    }
  }

  delay(50);
}

void loopSoundSensor(){
  Serial.print(analogRead(13));
  Serial.print("\n");
  delay(250);
  if(analogRead(pinSoundSensor)>150){
    activatedAlarm = true;
  }
}
void activateAlarm(){
    // Bucle de actualización de la biblioteca
    digitalWrite(pinLed, HIGH);
    EasyBuzzer.beep(
      1500, //Frecuencia en Hz
      700, // Duración del pitido
      500, // Duración del silencio entre pitidos
      5, // Número de pitidos
      3000, // Pausa final entre ciclos
      3, // Número de ciclos
      sonidoFinal // Llamada a función
    );
    EasyBuzzer.update();
    delay(1500);
    EasyBuzzer.stopBeep();
    digitalWrite(pinLed, LOW);
}





