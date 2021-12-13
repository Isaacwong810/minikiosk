//Network setup
#include "WiFiEsp.h"
#include "SoftwareSerial.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//Ultrasonic part
int tPin = 5;
int ePin = 4;

//RFID
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 53
#define RST_PIN 3
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

//OLED
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);

//WIFI
#define ESP_BAUDRATE  115200
char ssid[] = "";     //ID
char pass[] = ""; //PW
int status = WL_IDLE_STATUS;
WiFiEspClient client;


//Data
String ID = "eca91330";


void setup() {
  Serial.begin(74880);
  
  //setup Ultrasonic Pin
  pinMode(ePin, INPUT);
  pinMode(tPin, OUTPUT);
  
  //setup RFID
  SPI.begin();        // Init SPI bus
  mfrc522.PCD_Init();
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
  //setup OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  //connect to network
  /*
  Serial1.begin(ESP_BAUDRATE);
  WiFi.init(&Serial1);
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network 
      Serial.print(".");
      delay(5000);     
    }
  Serial.println("\nConnected");
  }
  */
}
//Ultrasonic part
bool ultrasonic(){
  display.clearDisplay();
  bool flag = false;
  flag = true;
  /*
  long duration;
  int distance;
  delay(2000);
  digitalWrite(tPin,LOW);
  delayMicroseconds(7);
  digitalWrite(tPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(tPin,LOW);
  duration = pulseIn(ePin,HIGH);
  distance = duration*0.034/2;
  Serial.print("distance(cm): ");
  Serial.println(distance);
  if(distance<10 && !flag){
    //Serial.println("hello");
    flag = true;
  }
  else if(distance>10 && flag){
    //Serial.println("bye");
    flag = false;
  }
  */
  return flag;
}

//RFID part
bool RFID(){
  return true;//disconnect
  
  if ( ! mfrc522.PICC_IsNewCardPresent()){
     return false;
  }
  
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) return false;
  String hex_num;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if(mfrc522.uid.uidByte[i]<0x10){
      hex_num=hex_num+"0";
    }
    hex_num=hex_num+String(mfrc522.uid.uidByte[i], HEX);
  }
  mfrc522.PICC_HaltA(); // Halt PICC
  mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
  ID=hex_num;
  return true;  
}
//OLED part
void oled_clear(){
  display.clearDisplay();
  display.display();
  Serial.println("oled_clear()");
}
void oled_welcome(){
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(F("Welcome!"));
  display.println(F("Please tap the card"));
  display.display();
  Serial.println("Welcome!");
}
void oled_card_wait(){
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(F(""));
  display.println(F(""));
  display.println(F("Waiting...dweet"));
  display.display();
  Serial.println("Waiting!");
}



//Dweet part
void send_to_PC(String id){
  /*
  client.stop();
  // put your setup code here, to run once:
  String data_ori;
  if (client.connect("dweet.io", 80)){
    client.println("POST /dweet/for/cityuArdtoPc?f=1 HTTP/1.1");
    client.println("Host: dweet.io");
    client.println("Connection: close");//keep-alive
    client.println();
    }
    client.stop();
  }
  */
  delay(1000);
}

void get_from_PC(){
  /*
  client.stop();
  // put your setup code here, to run once:
  String data_ori;
  if (client.connect("dweet.io", 80)){
    client.println("GET /get/latest/dweet/for/cityuArdtoPc HTTP/1.1");
    client.println("Host: dweet.io");
    client.println("Connection: close");//keep-alive
    client.println();
    while (!client.available());
    while (client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
      if(line[1]=='{'){
        data_ori=line;
      }
    }
    char copy[50];
    data_ori.toCharArray(copy, 50);
    Serial.println("---");
    Serial.println(copy);
    // the server's disconnected, stop the client:
    client.stop();
    Serial.println("disconnected");
  }
  */
  delay(1000);
  String a="{\"this\":\"succeeded\",\"by\":\"getting\",\"the\":\"dweets\",\"with\":[{\"thing\":\"cityutest\",\"created\":\"2021-03-14T04:40:09.953Z\",\"content\":{\"hello\":\"world\",\"foo\":\"bar\",\"foo\":\"bar\"}}]}disconnected";
}








String get_from_dweet(String id,int result){
  /*
  client.stop();
  // put your setup code here, to run once:
  String data_ori;
  if (client.connect("dweet.io", 80)){
    Serial.println("dweet connected----------------------------------------------------");
    client.println("GET /get/latest/dweet/for/cityutest HTTP/1.1");
    client.println("Host: dweet.io");
    client.println("Connection: close");//keep-alive
    client.println();
    while (!client.available());
    while (client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
      if(line[1]=='{'){
        data_ori=line;
      }
    }
    char copy[50];
    data_ori.toCharArray(copy, 50);
    Serial.println("---");
    Serial.println(copy);
    // the server's disconnected, stop the client:
    client.stop();
    Serial.println("disconnected");
  }
  */
  
  delay(1000);
  String a="{\"this\":\"succeeded\",\"by\":\"getting\",\"the\":\"dweets\",\"with\":[{\"thing\":\"cityutest\",\"created\":\"2021-03-14T04:40:09.953Z\",\"content\":{\"hello\":\"world\",\"foo\":\"bar\",\"foo\":\"bar\"}}]}disconnected";
  return a;
}
//
bool check_data(String* data_dweet){
  String check_data_dweet=*data_dweet;
  int index_a = check_data_dweet.indexOf('['); 
  int index_b = check_data_dweet.indexOf(']'); 
  check_data_dweet = check_data_dweet.substring(index_a+2, index_b-1);
  int index_c = check_data_dweet.indexOf('{'); 
  int index_d = check_data_dweet.indexOf('}'); 
  check_data_dweet = check_data_dweet.substring(index_c+1, index_d);
  *data_dweet = check_data_dweet;
  if(check_data_dweet==""){
    return false;
  }else{
    return true;
  }
}
int numofdata(String data_dweet){
  int a=1;
  int b = data_dweet.length();
  for(int i=0;i<b;i++){
    if(data_dweet[i]==','){
      a++;
    }
  }
  return a;
}
void data_to_array(String dataArray[],int datanum,String data_dweet){
  String partDone;
  String partOther = data_dweet;
  for(int i = 0;i<datanum-1;i++){
    int index = partOther.indexOf(','); 
    partDone = partOther.substring(0, index);
    partOther = partOther.substring(index+1, partOther.length());
    dataArray[i]=partDone;
  }
  dataArray[datanum-1]=partOther;
}
//{"this":"succeeded","by":"getting","the":"dweets","with":[{"thing":"cityutest","created":"2021-03-13T13:00:44.689Z","content":{"hello":"world"}}]}disconnected



const char server[] = "dweet.io";

void loop() { // run over and over
  String data_dweet;
  oled_clear();
  delay(1000);
  while(!ultrasonic());//loop and wait
  oled_welcome();
  delay(2000);
  while(!RFID());
  oled_card_wait();
  delay(2000);
  Serial.println(ID);
  send_to_PC(ID); //Send message to PC to get confirmation
  
  data_dweet=get_from_dweet(ID,true);
  if(check_data(&data_dweet)){
    Serial.print("Data: ");
    Serial.println(data_dweet);
    int datanum=numofdata(data_dweet);
    Serial.println(datanum);
    String dataArray[datanum];
    data_to_array(dataArray,datanum,data_dweet);
    
    
    for(int i = 0;i<datanum;i++){
      Serial.println(dataArray[i]);
    }
  }
  
  


  
  /*
  char *a;
  a=data_dweet.c_str();
  Serial.println(a);
  Serial.println(data_dweet.length());
  */

}
