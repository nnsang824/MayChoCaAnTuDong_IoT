#include <WiFi.h>
#include "AdafruitIO_WiFi.h"
#include <ESP32Servo.h>
#include "DHT.h"

// ====== Cấu hình Adafruit IO ======
#define IO_USERNAME  "YOUR_USERNAME"
#define IO_KEY "YOUR_ADAFRUIT_IO_KEY"  // nhập key thật khi chạy local

// ====== WiFi ======
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASS ""

// ====== Khởi tạo Adafruit IO ======
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// ====== Feed ======
AdafruitIO_Feed *feeder = io.feed("fish_feeder");
AdafruitIO_Feed *tempFeed = io.feed("temperature");
AdafruitIO_Feed *humFeed  = io.feed("humidity");
AdafruitIO_Feed *phFeed   = io.feed("ph_value");

// ====== Servo + LED ======
Servo servo;
const int servoPin = 13;
const int ledPin = 2;

// ====== Nút bấm thủ công ======
const int buttonPin = 12;S

// ====== DHT11 ======
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ====== Cảm biến pH (giả lập analog) ======
const int phPin = 34;

// ====== Thời gian cho ăn tự động ======
unsigned long lastFeedTime = 0;
const unsigned long feedInterval = 60 * 1000; // 1 phút/lần

// ====== Gửi dữ liệu cảm biến mỗi 15s ======
unsigned long lastSensorTime = 0;
const unsigned long sensorInterval = 15 * 1000;

void setup() {
  Serial.begin(115200);
  servo.attach(servoPin);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // nhấn = LOW
  dht.begin();

  Serial.println("🔌 Kết nối tới Adafruit IO...");
  io.connect();

  // Khi Adafruit IO gửi lệnh
  feeder->onMessage(handleMessage);

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\n✅ Đã kết nối Adafruit IO!");
  feeder->get();
}

void loop() {
  io.run(); // duy trì kết nối IoT

  unsigned long currentTime = millis();

  // ====== Tự động cho ăn ======
  if (currentTime - lastFeedTime >= feedInterval) {
    feedFish();
    lastFeedTime = currentTime;
  }

  // ====== Cho ăn thủ công ======
  if (digitalRead(buttonPin) == LOW) {
    Serial.println("🔘 Nút thủ công được nhấn!");
    feedFish();
    delay(1000); // tránh lặp
  }

  // ====== Gửi dữ liệu cảm biến ======
  if (currentTime - lastSensorTime >= sensorInterval) {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    int phAnalog = analogRead(phPin);
    float phValue = map(phAnalog, 0, 4095, 0, 14);

    Serial.printf("🌡️ %.2f°C | 💧 %.2f%% | 🧪 pH: %.2f\n", t, h, phValue);

    tempFeed->save(t);
    humFeed->save(h);
    phFeed->save(phValue);

    lastSensorTime = currentTime;
  }
}

// ====== Khi có lệnh từ Adafruit IO ======
void handleMessage(AdafruitIO_Data *data) {
  String cmd = data->toString();
  Serial.print("📡 Lệnh từ Adafruit IO: ");
  Serial.println(cmd);

  if (cmd == "ON" || cmd == "1") {
    feedFish();
  }
}

// ====== Hàm cho cá ăn ======
void feedFish() {
  Serial.println("🐟 Đang cho cá ăn...");
  digitalWrite(ledPin, HIGH);
  servo.write(90);
  delay(2000);
  servo.write(0);
  digitalWrite(ledPin, LOW);
  Serial.println("✅ Đã cho ăn xong!\n");
  delay(500);  
}
