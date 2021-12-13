//Network setup
#include "WiFiEsp.h"
#include "SoftwareSerial.h"
#define ESP_BAUDRATE  115200

char ssid[] = "EE3070_P1404";
char pass[] = "EE3070P1404";
int status = WL_IDLE_STATUS;
WiFiEspClient client;

void setup() {
  Serial.begin(19200);
  //connect to network
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
  //end of connect to network

  //setting
  String cardID;
  bool succ;
  String data;
  //sample step
  while(ultrasonic()){}
  welcome();
  do{
    cardID,succ=RFID;
  }while(succ==false);
  //endWelcome
  data=database(cardID,succ);
  Serial.print(data);
}

bool ultrasonic(){
  Serial.print("???");
  delay(3000);
  Serial.print("!!!");
  return true;
}
void welcome(){
  //welcome
  Serial.print("welcome");
}

//RFID part
int RFID(){
  String id="";
  bool result=true;
  return id,result;  
}


String database(String id,int result){
  //if result, use id to find information in database.
  //
  client.stop();
  char server[] = "www.dweet.io";
  if (client.connect(server, 80)){
    Serial.println("connected");
  }else{
    Serial.println("connection failed");
  }
  //String s = "POST /dweet/for/cityu111?A0=0";
  String s = "GET /dweet/for/cityu111";
  client.println(s);
  client.println("Host: www.dweet.io");
  client.println("Connection: close");
  client.println();
  
  while(client.available()){
    // read an incoming byte from the server and print them to serial monitor:
    char c = client.read();
    Serial.print(c);
  }
  if(!client.connected()){
    // if the server's disconnected, stop the client:
    Serial.println("disconnected");
    client.stop();
  }
  String a="abc";
  return a; //a[]=list of product information e.g. *product ID, product name, Number, price
  //b[]= list of promote product information e.g. *product ID, product name, Number, price
}


/*
//displayProduct
String displayProduct(String a[]){
  //display product one by one.
  return a[0]; //update list of product information e.g. the number of product.
}
//EX-promote information.
String displayPromoteProduct(String a[]){
  //display promote product one by one.
  String b,count;
  return b,count; //update list of promote product information e.g. the number of product.
}

String addArray(String a[],String b[],int count){
  //if count>0 c[]=a[]+b[]
  //else c[]=a[]
  String c;
  return c;//return result
}
//Show result.
String showList(String c[]){
  //print out the list of product and confirm
  String c,result;
  return c,result;
}
void confirmOnServer(){
  //send the list of product, total price, ID to the server and get confirm result.
  return result;
}

//print result and product list.
void printResult(){
}
*/




void loop() { // run over and over
  
}
