#include <ESP8266WiFi.h>
#include <Ambient.h>

const char* ssid = "ctc-g-2be8fe";
const char* password = "2eae0a2471cf2";
const int channelId = 44960;
const char* writeKey = "160cea692249a60c";
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
