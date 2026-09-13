#include <WiFi.h>
#include <WebServer.h>

const char* ap_ssid = "ESP32-Config";
const char* ap_password = "12345678";

WebServer server(80);
String  htmlPage() {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<title>ตั้งค่า WiFi</title></head><body>";
  html += "<h2>ตั้งค่า WiFi ของ ESP32</h2>";
  html += "<form action='/save' method='POST'>";
  html += "SSID: <input type='text' name='ssid'><br><br>";
  html += "Password: <input type='password' name='password'><br><br>";
  html += "<input type='submit' value='บันทึก'>";
  html += "</form></body></html>";
  return html;
}

void handleRoot() {
  server.send(200, "text/html; charset=utf-8", htmlPage());
}

void handleSave() {
  String ssid = server.arg("ssid");
  String password = server.arg("password");

  Serial.println("ได้รัยค่าจากฟอร์ม:");
  Serial.println("SSID: " + ssid);
  Serial.println("Password: " + password);

  server.send(200, "text/html; charset=utf-8",
              "<h3>ได้รับค่าแล้ว (ยังไม่ได้เซฟจริง แค่ทดสอบ)</h3><a href='/'>กลับ</a>");
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_MODE_AP);
  WiFi.softAP(ap_ssid, ap_password);


  Serial.println();
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/save", HTTP_POST, handleSave);

  server.begin();
  Serial.println("Web  Server Stated !!");
}

void loop() {
  server.handleClient();
}
