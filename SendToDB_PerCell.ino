#include <WiFi.h>
#include <HTTPClient.h>

// Ganti dengan SSID dan password WiFi Anda
const char* ssid = "ta";
const char* password = "12345678";

// URL API
const char* apiUrl = "https://bmsmipa-default-rtdb.asia-southeast1.firebasedatabase.app/sensorcel.json";

// Inisialisasi data dummy
float data[12] = {3.1, 3.5, 3.8, 4.0, 4.1, 3.2, 3.9, 4.2, 3.3, 3.6, 3.7, 4.0};

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    // Tunggu hingga terhubung ke WiFi
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Menghubungkan ke WiFi...");
    }
    Serial.println("Terhubung ke WiFi");

    // Meng-upload data ke API
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(apiUrl);
        http.addHeader("Content-Type", "application/json");

        // Membuat JSON dari data
        String jsonData = "[";
        for (int i = 0; i < 12; i++) {
            jsonData += String(data[i]);
            if (i < 11) jsonData += ",";
        }
        jsonData += "]";

        // Mengirim permintaan PUT
        int httpResponseCode = http.PUT(jsonData);

        if (httpResponseCode > 0) {
            Serial.printf("HTTP Response Code: %d\n", httpResponseCode);
        } else {
            Serial.printf("Error on sending: %s\n", http.errorToString(httpResponseCode).c_str());
        }

        http.end(); // Menutup koneksi
    }
}

void loop() {
    // Tidak ada yang dilakukan di loop
}
