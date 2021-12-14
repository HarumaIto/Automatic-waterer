#include <ESP8266WiFi.h>
#include <Ambient.h>

const char* ssid = "IPアドレス";
const char* password = "パスワード";
const int channelId = チャンネルID;
const char* writeKey = "書き込みキー";
const boolean displayMode = true;

WiFiClient client;
Ambient ambient;

const int sensor = A0;
const int pump = 7;

void setup() {
  Serial.begin(115200);

  // Wi-Fiの初期化
  Serial.println("WiFi connecting....");

  WiFi.begin(ssid, password);
  // Wi-Fiアクセスポイントへの接続待ち
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected!!!");
  ambient.begin(channelId, writeKey, &client);

  pinMode(sensor, INPUT);

  // データ取得
  int data = analogRead(sensor);
  Serial.println(data);

  /*
  // 数値は不確定
  if (data >= 700) {
    digitalWrite(pump, HIGH);
    delay(3000);
    digitalWrite(pump, LOW);
  }
   */
 

  // データセット
  ambient.set(1, data);
  ambient.send();

  ESP.deepSleep(1800 * 1000000, RF_DEFAULT);
  delay(1000);
}

void loop() {}
