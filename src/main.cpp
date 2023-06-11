#include <U8g2lib.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <time.h>
#define SCL 5
#define SDA 4

// 修改成功

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp1.aliyun.com",60*60*8, 30*60*1000);

const char* ssid = "物联网工程";
const char* passwd = "gfxy123456";
String week = "";

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0,SCL,SDA,U8X8_PIN_NONE);
void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  u8g2.begin();
  u8g2.enableUTF8Print();

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_unifont_t_chinese2);
  u8g2.setCursor(0, 14);
  u8g2.print("Waiting for WiFi");
  u8g2.setCursor(0, 30);
  u8g2.print("connection...");
  u8g2.sendBuffer();



  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,passwd);


  int count = 60;
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  timeClient.begin();
  Serial.println("网络已连接");


}

void loop()
{
  timeClient.update();

  Serial.println(timeClient.getFormattedTime());

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_unifont_t_chinese2);
  u8g2.setCursor(5,14);
  u8g2.print("当前时间(UTC+8)");

  u8g2.setFont(u8g2_font_logisoso24_tr);
  u8g2.setCursor(10,44);
  u8g2.print(timeClient.getFormattedTime());


  time_t t;
  struct tm *p;
  t=timeClient.getEpochTime();
  p=gmtime(&t);
  char s[100];
  //strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", p);
  strftime(s, sizeof(s), "%Y/%m/%d", p);


  switch(timeClient.getDay()){
      case 0:
            week = "Sun.";
            break;
      case 1:
            week = "Mon.";
            break;
      case 2:
            week = "Tues.";
            break;
      case 3:
            week = "Wed.";
            break;
      case 4:
            week = "Thur.";
            break;
      case 5:
            week = "Fri.";
            break;
      case 6:
            week = "Sat.";
            break;
      }

  u8g2.setFont(u8g2_font_unifont_t_chinese2);
  u8g2.setCursor(0,61);
  u8g2.print(s);

  u8g2.setFont(u8g2_font_unifont_t_chinese2);
  u8g2.setCursor(95,61);
  u8g2.print(week);

  u8g2.sendBuffer();
  delay(800);
}
