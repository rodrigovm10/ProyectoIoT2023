#include <WiFi.h>
#include <WiFiClientSecure.h>
//#include <Servo.h>
#include <ESP32Servo.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <PubSubClient.h> //MQTT Connection

Servo myservo;  // crea el objeto servo
Servo myservo2;

// GPIO de salida del servo
static const int servoPin = 13;
static const int servoPin2 = 33;
// Definición de las pines del sensor y del relay
const int trigPin3 = 18;
const int echoPin3 = 19;
const int relayPin = 4;

//Variables del Primer Sensor
#define trigPin 12
#define echoPin 14
//Variables del Segundo Sensor
#define trigPin2 27
#define echoPin2 26
//Variable del Buzzer 1  
#define buzzerPin 25
//Pantalla OLED
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
//Variable del sensor de agua
#define WATER_SENSOR_PIN 15


//Variable contador
int contador = 0;
char cadena[20];

//Declaración del display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Reemplazar con tus credenciales de Wifi
const char* ssid     = "Redmi Note 9 Pro";
const char* password = "4181497740";

//Conexión con mqtt
const char* mqtt_server = "192.168.80.246";
IPAddress server(192,168,80,246);
WiFiClient espClient;
PubSubClient client1(espClient);

//Variables para mqtt
long timeNow, timeLast; //Not blocking time
int wait = 5000; //Wait 5 seconds to send new message

// Inicializa Bot Telegram
#define BOTtoken "6050598764:AAHy2rLYhymgJrNg22k5SIzTZ7aFiCvp-Lg"  // Tu Bot Token (Obtener de Botfather)

#define CHAT_ID "1307446655"

WiFiClientSecure client2;

UniversalTelegramBot bot(BOTtoken, client2);

void handleNewMessages(int numNewMessages) {

  for (int i=0; i<numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Usuario no autorizado", "");
      continue;
    }

    String text = bot.messages[i].text;

    if (text == "/comida") {
      bot.sendMessage(chat_id, "Alimentando", "");
      digitalWrite(buzzerPin, HIGH);
      myservo.write(85);             
      delay(500);
      digitalWrite(buzzerPin, LOW);                       
      myservo.write(0);
      contador += 1;              
    }
    
    if(text == "/vecesAlimentado"){
      char contador_texto[10]; // Crear un buffer para la cadena de texto del contador
      sprintf(contador_texto, "%d", contador); // Convertir el valor del contador en una cadena
      bot.sendMessage(chat_id, contador_texto, ""); // Enviar la cadena como respuesta
    }
  }
}

//Declaración de variables de estados de los sensores


void setup() {
  Serial.begin(115200);

  myservo.attach(servoPin);  // vincula el servo en el servoPin

  // Conecta a red WiFi con SSID y password
  Serial.print("Conectado a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  client2.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Muestra IP local 
  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "Bot iniciado", "");

  //Inicializar variables del sensor ultrasonico
  pinMode(trigPin, OUTPUT); // Configura el pin del trigger como salida
  pinMode(echoPin, INPUT); // Configura el pin del echo como entrada
  pinMode(trigPin2, OUTPUT); // Configura el pin del trigger como salida
  pinMode(echoPin2, INPUT); // Configura el pin del echo como entrada

  //Display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;) {
      // Stop the program if the display can't be initialized
    }
  }

  display.clearDisplay();
  display.setTextSize(1.8);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);

  //Relay 
  // Display a static message initially
  display.println("Checking water sensor...");
  display.display();

    // Configurar las pines del sensor y del relay
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(relayPin, OUTPUT);

  //Broker connect
  client1.setServer(server, 1883);
  client1.setCallback(callback);
  delay(1500);
  //Control time initializing
  timeLast = millis();
}

void loop() {
  //Estados
  int buzzerState;
  int relayState;
  int pulseWidth;    // Variable para almacenar el ancho del pulso
  int oledState;
  int servoState = -1;
  pinMode(buzzerPin, OUTPUT);
  relayState = digitalRead(relayPin);

  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

  while(numNewMessages) {
    handleNewMessages(numNewMessages);
    numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  }

  //Primer Sensor 
  digitalWrite(trigPin, LOW); // Establece el pin del trigger en LOW
  delayMicroseconds(2); // Espera 2 microsegundos
  digitalWrite(trigPin, HIGH); // Establece el pin del trigger en HIGH
  delayMicroseconds(10); // Espera 10 microsegundos
  digitalWrite(trigPin, LOW); // Establece el pin del trigger en LOW
  float duration = pulseIn(echoPin, HIGH); // Mide la duración del pulso en el pin del echo
  float distance = duration * 0.034 / 2; // Calcula la distancia en centímetros
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  if(distance < 15){
    servoState = 1;
    digitalWrite(buzzerPin, HIGH);
    myservo.write(85);
    delay(1000);
    digitalWrite(buzzerPin, LOW);
    myservo.write(0);
    delay(1000);
    if(buzzerPin == HIGH) buzzerState = 1;
    else buzzerState = 0;
  }else {
    buzzerState = 0;
    servoState = 0;
  }

  //Segundo Sensor
  digitalWrite(trigPin2, LOW); // Establece el pin del trigger en LOW
  delayMicroseconds(2); // Espera 2 microsegundos
  digitalWrite(trigPin2, HIGH); // Establece el pin del trigger en HIGH
  delayMicroseconds(10); // Espera 10 microsegundos
  digitalWrite(trigPin2, LOW); // Establece el pin del trigger en LOW
  float duration2 = pulseIn(echoPin2, HIGH); // Mide la duración del pulso en el pin del echo
  float distance2 = duration2 * 0.034 / 2; // Calcula la distancia en centímetros
  Serial.print("Distancia 2: ");
  Serial.print(distance2);
  Serial.println(" cm");
  if(distance2 > 4 && distance2 < 8){
    //digitalWrite(buzzerPin, HIGH);
    display.clearDisplay();
    display.setCursor(0, 40);
    display.println("Comida Llena");
    display.display();
    buzzerState = 0;
    //delay(1000);
    //digitalWrite(buzzerPin, LOW);
    //delay(1000);
  }else if(distance2 > 9 && distance2 < 13){
    //digitalWrite(buzzerPin, HIGH);
    display.clearDisplay();
    display.setCursor(0, 40);
    display.println("Comida a la Mitad");
    display.display();
    buzzerState = 0;
    //delay(1000);
    //digitalWrite(buzzerPin, LOW);
    //delay(1000);
  }else if(distance2 > 14){
    digitalWrite(buzzerPin, HIGH);
    display.clearDisplay();
    display.setCursor(0, 40);
    display.println("Rellenar recipiente de comida");
    display.display();
    buzzerState = 1;
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
  }
  
  delay(1000); // Espera un segundo antes de tomar otra medida

  //Sensor de agua con OLED
  // Read the state of the water sensor
  int waterSensorValue = digitalRead(WATER_SENSOR_PIN);

  // Change the message displayed based on the water sensor state
  if (waterSensorValue == HIGH) {
    display.clearDisplay();
    display.setCursor(0, 40);
    display.println("Hay Agua");
    display.display();
  } else {
    display.clearDisplay();
    display.setCursor(0, 40);
    display.println("No Hay Agua");
    display.display();
  }

  delay(100); // Wait a short time before checking the sensor again

  //Relay y Bomba
  // Enviar una señal de pulso al sensor
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  
  // Calcular la distancia medida por el sensor
  long duration3 = pulseIn(echoPin3, HIGH);
  float distance_cm = duration3 * 0.034 / 2;

  // Si la distancia es menor a 50 cm, activar el relay y imprimir la distancia en serial
  if (distance_cm < 15) {
    digitalWrite(relayPin, HIGH);
    Serial.println("Distancia 3: " + String(distance_cm) + " cm");
  } else {
    digitalWrite(relayPin, LOW);
  }
  
  // Esperar un momento antes de tomar otra lectura
  delay(100);

  //MQTT
    if(!client1.connected()){
    reconnect();
  }
  client1.loop();

  if(waterSensorValue == 1){
    oledState = 1;
  }else{
    oledState = 0;
  }

  timeNow = millis();
  if(timeNow - timeLast>wait){
    timeLast = timeNow;

    //Building JSON
    String json = "{\"id_sensor\":\"1\",\"valor\":\""+String(waterSensorValue)+"\"}";//Sensor de agua
    String json2 = "{\"id_sensor\":\"2\",\"valor\":\""+String(distance)+"\"}";//Sensor ultrasonico 1
    String json3 = "{\"id_sensor\":\"3\",\"valor\":\""+String(distance2)+"\"}";//Sensor ultrasonico 2
    String json4 = "{\"id_sensor\":\"4\",\"valor\":\""+String(distance_cm)+"\"}";//Sensor ultrasonico 3
    String json5 = "{\"id_sensor\":\"5\",\"valor\":\""+String(servoState)+"\"}";//Servo 
    String json6 = "{\"id_sensor\":\"6\",\"valor\":\""+String(relayState)+"\"}";//Relay
    String json7 = "{\"id_sensor\":\"7\",\"valor\":\""+String(oledState)+"\"}";//LCD
    String json8 = "{\"id_sensor\":\"8\",\"valor\":\""+String(buzzerState)+"\"}";//Buzzer
    //String json = "{\"id\":\"Equipo1\", \"equipo1\":\"1\", \"valor\":\""+String(waterSensorValue)+"\"}";

    //String json in serial
    //Sensor 1
    Serial.println(json);
    int str_len = json.length() + 1;//Calculte length of string
    char char_array[str_len];//Creating array with that length
    json.toCharArray(char_array, str_len);//Convert string to char array    
    client1.publish("aiot1/u3/equipo1", char_array); // Function send by MQTT with topic and value
    //Sensor 2
    Serial.println(json2);
    int str_len2 = json2.length() + 1;//Calculte length of string
    char char_array2[str_len2];//Creating array with that length
    json2.toCharArray(char_array2, str_len2);//Convert string to char array    
    client1.publish("aiot1/u3/equipo1", char_array2); // Function send by MQTT with topic and value
    //Sensor 3
    Serial.println(json3);
    int str_len3 = json3.length() + 1;//Calculte length of string
    char char_array3[str_len3];//Creating array with that length
    json3.toCharArray(char_array3, str_len3);//Convert string to char array    
    client1.publish("aiot1/u3/equipo1", char_array3); // Function send by MQTT with topic and value
    //Sensor 4
    Serial.println(json4);
    int str_len4 = json4.length() + 1;//Calculte length of string
    char char_array4[str_len4];//Creating array with that length
    json4.toCharArray(char_array4, str_len4);//Convert string to char array    
    client1.publish("aiot1/u3/equipo1", char_array4); // Function send by MQTT with topic and value
    //Sensor 5
    Serial.println(json5);
    int str_len5 = json5.length() + 1;//Calculte length of string
    char char_array5[str_len5];//Creating array with that length
    json5.toCharArray(char_array5, str_len5);//Convert string to char array    
    client1.publish("aiot1/u3/equipo1", char_array5); // Function send by MQTT with topic and value
    //Sensor 6
    Serial.println(json6);
    int str_len6 = json6.length() + 1;//Calculte length of string
    char char_array6[str_len6];//Creating array with that length
    json6.toCharArray(char_array6, str_len6);//Convert string to char array    
    client1.publish("aiot1/u3/equipo1", char_array6); // Function send by MQTT with topic and value
    //Sensor 7
    Serial.println(json7);
    int str_len7 = json7.length() + 1;//Calculte length of string
    char char_array7[str_len7];//Creating array with that length
    json7.toCharArray(char_array7, str_len7);//Convert string to char array    
    client1.publish("aiot1/u3/equipo1", char_array7); // Function send by MQTT with topic and value
    //Sensor 8
    Serial.println(json8);
    int str_len8 = json8.length() + 1;//Calculte length of string
    char char_array8[str_len8];//Creating array with that length
    json8.toCharArray(char_array8, str_len8);//Convert string to char array    
    client1.publish("aiot1/u3/equipo1", char_array8); // Function send by MQTT with topic and value
  }
}

void reconnect() {
  // Connection loop
  while (!client1.connected()) {
    Serial.print("Tying connect...");
    // Intentar reconexión
    if (client1.connect("client")) { 
      Serial.println("Connected");
      client1.subscribe("aiot1/u3/equipo1"); 
    }else {
      Serial.print("Failed connect, Error rc=");
      Serial.print(client1.state());
      Serial.println(" Trying in 5 seconds");
      delay(5000);
      Serial.println (client1.connected()); 
    }
  }
}

void callback(char* topic, byte* message, 
                unsigned int length){
  Serial.print("Recieved message in topic");
  Serial.print(topic);

  String messageTemp;
  for(int i = 0; i<length; i++){
    Serial.print((char)message[i]);
    messageTemp+= (char)message[i];
  }
  Serial.println(messageTemp);

  if(String(topic) == "aiot1/u3/equipo1"){
    if(messageTemp=="true"){
      Serial.println("Hay Agua");
    }else if(messageTemp=="false"){
      Serial.println("No hay Agua");
    }
  }
}
