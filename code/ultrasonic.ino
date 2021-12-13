

int tPin = 5;
int ePin = 4;
const int B = A1;  // Analog input pin that the potentiometer is attached to
const int G = A2;
const int R = A3;
bool flag = false;




long duration;
int distance;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(B, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(R, OUTPUT);
  
  pinMode(ePin, INPUT);
  pinMode(tPin, OUTPUT);
  
}
void loop() {
  // put your main code here, to run repeatedly:
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
    analogWrite(R,0);
    analogWrite(G,0);
    analogWrite(B,0);
    Serial.println("hello");
    flag = true;
  }
  else if(distance>10 && flag){
    analogWrite(R,100);
    analogWrite(G,0);
    analogWrite(B,0);
    Serial.println("bye");
    flag = false;
  }

  delay(2000);
}

