#include <WiFi.h>
#include <HTTPClient.h>

// Ganti dengan kredensial WiFi lo
const char* ssid = "ta";
const char* password = "12345678";

// Ganti dengan URL Firebase lo
const char* firebaseUrl = "https://bmsmipa-default-rtdb.asia-southeast1.firebasedatabase.app/sensor_data/sensor_test.json";

void setup() {
  Serial.begin(115200);
  
  // Connect ke WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Contoh data
  String batteryHealth = "Bagus";
  int current = 530; // mA
  float level = 0.8; // 80%
  int temp = 50; // Celsius
  int voltage = 42; // Volt

  // Membuat JSON
  String jsonData = String("{\"batteryHealth\":\"") + batteryHealth + 
                    "\",\"current\":" + current + 
                    ",\"level\":" + level + 
                    ",\"temp\":" + temp + 
                    ",\"voltage\":" + voltage + "}";

  // Mengirim data ke Firebase
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(firebaseUrl); // URL Firebase
    http.addHeader("Content-Type", "application/json"); // Set header

    // Mengirim POST request
    int httpResponseCode = http.PUT(jsonData);

    // Mengecek respon
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Data sent successfully");
      Serial.println("Response: " + response);
    } else {
      Serial.print("Error sending data: ");
      Serial.println(httpResponseCode);
    }

    http.end(); // Menutup koneksi
  } else {
    Serial.println("WiFi not connected");
  }

  // Delay sebelum mengirim data lagi
  delay(5000); // 5 detik
}
