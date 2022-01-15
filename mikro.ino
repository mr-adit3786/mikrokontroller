#include <OneWire.h> //Library OneWire
#include <DallasTemperature.h> // Library untuk Dallas temperature
#include <LiquidCrystal_I2C.h> //Library I2C LCD
#include "CTBot.h" //Library CTBot untuk Telegram

LiquidCrystal_I2C lcd(0x27,16,2); //alamat I2C

#define buzzer D5 //pin D3 untuk buzzer
#define ONE_WIRE_BUS D6 // pin D4 digunakan untuk data hasil baca sensor

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire); 
CTBot myBot;

String ssid = "PRC36";    //nama ssid wifi kalian
String pass = "bayardongbos";  //password wifi kalian
String token = "5067578285:AAGASe3VGuuArb-Rv0a_u-a2QzWHYCUoVoI";    //token bot baru kalian
const int id = 1343961954;      //id telegram kalian

void setup(void)
{
  Serial.begin(115200);
  sensors.begin(); //memulai baca sensor
  lcd.begin(); //memulai LCD
  lcd.backlight(); //menyalakan Lampu latar belakang LCD
  pinMode(buzzer, OUTPUT); //inisialisasi buzzer sebagai output
  myBot.wifiConnect(ssid, pass); //koneksi dengan hotspot
  myBot.setTelegramToken(token); //memastikan token

  //tes koneksi dengan hotspot
  if (myBot.testConnection()) {
    Serial.println("Koneksi Bagus");
  } else {
    Serial.println("Koneksi Jelek");
  }
}

void loop(void)
{ 
  sensors.requestTemperatures(); //baca sensor
  int suhu = sensors.getTempCByIndex(0);
  //Penulisan suhu pada LCD dan serial monitor
  Serial.println(suhu);
  

  //Jika suhu lebih dari 30
  if (suhu > 30) {
    myBot.sendMessage(id, "Suhu Akuarium Terlalu Panas!"); //mengirimkan pesan ke telegram
    buzzerNyala(); //menyalakan buzzer
    lcd.setCursor(0,0);
    lcd.print("SUHU PANAS!"); //menampilkan SUHU PANAS di LCD
    delay(1000);
    }

  else if (suhu < 25) {
    myBot.sendMessage(id, "Suhu Akuarium Terlalu Dingin!"); //mengirimkan pesan ke telegram
    buzzerNyala(); //menyalakan buzzer
    lcd.setCursor(0,0);
    lcd.print("SUHU DINGIN!"); //menampilkan SUHU DINGIN di LCD
    delay(1000);
  }
  else {
    digitalWrite(buzzer, LOW);
    lcd.setCursor(0,0);
    lcd.print("Suhu air : ");
    lcd.setCursor(0,1);
    lcd.print(suhu);
    delay(1000);
  }
  delay(1000);
  lcd.clear();
}


void buzzerNyala(){ //Function untuk menyalakan buzzer
  digitalWrite(buzzer, HIGH);
  delay (500);
  digitalWrite(buzzer, LOW);
  delay (500);

}