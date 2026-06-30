const int self = 2;
const int shock = 3;
const int should = 4;
int count = 0;
int time = 3600;
#include <SPI.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Servo myservo;

void setup() {
  Serial.begin(9600);
  pinMode(self, OUTPUT);
  pinMode(shock, OUTPUT);
  pinMode(should, INPUT);
  myservo.attach(5);

  digitalWrite(self, HIGH);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  // servo here
  myservo.write(90);
  delay(1000);
  myservo.write(0);
  delay(1000);
  myservo.write(90);

}

void loop() {
  int state = digitalRead(should);
  if(time <= 3595){
    if(state == LOW){
      Serial.println(";lkjsaf;lsakjfalk;fj");
    }else{
      digitalWrite(shock, HIGH);
      delay(100);
      digitalWrite(shock, LOW);
      time = 3600;
    }
  }
  
  // time to string
  int temp_time = time % 60;
  String string_time = "";
  string_time = String((time - temp_time)/60) + ":";
  string_time += String(temp_time);


  // screen
  display.clearDisplay();
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(0, 28);
  display.println(string_time); 
  display.display();
  if(count == 10){
    time--;
    count = 0;
  }
  count++;
  if(time <= 0){
    digitalWrite(self, LOW);
  }
  delay(100);
}
