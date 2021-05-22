#include <ESP8266WiFi.h>//zaten yüklü gelir. Yüklemenize gerek yok.

// ağ adı ve şifrenizi giriniz
const char* agAdi = "***********";
const char* sifresi = "***********";

WiFiEventHandler wifiBaglandiDurumu;
WiFiEventHandler wifiKoptuDurumu; 


void wifiBaglan() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(agAdi, sifresi);
  Serial.print("Ağa Bağlanılıyor ..");
  while (WiFi.status() != WL_CONNECTED) { //ağ bağlantısı sağlanmış.  WL_NO_SSID_AVAIL,  WL_CONNECT_FAILED
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP()); //otomatik alınan ip adresi yazdırılıyor.
  /*sabit ip alınmak istenirse
  IPAddress local_IP(192, 168, 1, 100);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  */
}

void baglanincaYap(const WiFiEventStationModeGotIP & event) {
  Serial.println("Ağ Bağlantısı Sağlandı");
  Serial.print("IP adresi: ");
  Serial.println(WiFi.localIP());
}

void kopuncaYap(const WiFiEventStationModeDisconnected& event) {
  Serial.println("Ağ bağlantısı koptu, yeniden deniyor...");
  WiFi.disconnect();
  WiFi.begin(agAdi, sifresi);
}

void setup() {
  Serial.begin(115200);

  //bu iki handler nesnesi ile iki fonksiyonu bağlayalım. 
  wifiBaglandiDurumu = WiFi.onStationModeGotIP(baglanincaYap);
  wifiKoptuDurumu = WiFi.onStationModeDisconnected(kopuncaYap);  

   
  wifiBaglan();//ağ bağlantısını kur
  Serial.print("Sinyal Seviyesi: ");
  Serial.println(WiFi.RSSI());//ağın sinyal çekim gücü
}

void loop() {
   //sistem handler'ları kendisi sürekli kontrol edecek. Bizim kontrol etmemize gerek olmayacak.
}
