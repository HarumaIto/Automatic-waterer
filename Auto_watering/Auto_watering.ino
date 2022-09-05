#include <ESP8266WiFi.h>
#include <Ambient.h>

const char* ssid = "ssid";
const char* password = "password";
const int channelId = channelId;
const char* writeKey = "writekey";
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
  pinMode(pump, OUTPUT);
  digitalWrite(pump, HIGH);

  // データ取得
  int data = analogRead(sensor);
  Serial.println(data);

  if (data > 710) {
    digitalWrite(pump, LOW);
    delay(8000);
    digitalWrite(pump, HIGH);
  }

  // データセット
  ambient.set(1, data);
  ambient.send();

  ESP.deepSleep(1800 * 1000000, RF_DEFAULT);
  delay(1000);
}

void loop() {}
