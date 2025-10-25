# 🐟 Máy Cho Cá Ăn Tự Động IoT

## 📘 Giới thiệu
Dự án IoT sử dụng **ESP32**, **Adafruit IO**, **DHT11**, và **Servo** để tự động cho cá ăn, thu thập dữ liệu môi trường và điều khiển từ xa.

## ⚙️ Chức năng chính
- Cho cá ăn tự động mỗi giờ hoặc bằng nút nhấn thủ công.
- Đo và gửi dữ liệu nhiệt độ, độ ẩm, pH nước lên **Adafruit IO Dashboard**.
- LED báo trạng thái khi đang cho ăn.
- Mô phỏng và lập trình hoàn toàn trên **Wokwi**.

## 🔧 Phần cứng sử dụng
- ESP32
- DHT11
- Servo SG90
- Cảm biến pH (giả lập analog)
- Nút nhấn, LED

## 🧠 Phần mềm & Thư viện
- Arduino IDE
- Thư viện: Adafruit IO Arduino, ESP32Servo, Adafruit MQTT
- Mô phỏng: [Wokwi](https://wokwi.com/)
- Giao diện IoT: [Adafruit IO](https://io.adafruit.com/nnsang824/overview)

## 📸 Hình ảnh
![Mô phỏng Wokwi](HinhAnh/wokwi_circuit.png)
![Dashboard Adafruit IO](HinhAnh/dashboard_adafruit.png)

## 👤 Tác giả
Nguyễn Ngọc Sang – Dự án môn Internet of Things (IoT)
