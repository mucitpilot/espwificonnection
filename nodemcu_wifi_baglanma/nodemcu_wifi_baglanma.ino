#include <ESP8266WiFi.h>//zaten yüklü gelir. Yüklemenize gerek yok.

// ağ adı ve şifrenizi giriniz
const char* agAdi = "***********";
const char* sifresi = "***********";

unsigned long oncekiZaman = 0;
unsigned long aralik = 60000;//60sn de bir kontrol etmek için

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

void setup() {
  Serial.begin(115200);
  wifiBaglan();//ağ bağlantısını kur
  Serial.print("Sinyal Seviyesi: ");
  Serial.println(WiFi.RSSI());//ağın sinyal çekim gücü
}

void loop() {
  unsigned long simdikiZaman = millis();
  // Her 60sn'de bir ağda sorun var mı kontrol ediyoruz.
  if ((WiFi.status() != WL_CONNECTED) && (simdikiZaman - oncekiZaman >=aralik)) { //bağlanmamış ve belirlenen aralık geçmişse
    Serial.println("Yeniden Bağlantı Deneniyor...");
    WiFi.disconnect(); //mevcut bağlantı varsa sonlandır.
    WiFi.begin(agAdi, sifresi); //yeniden bağlantı oluştur.
    Serial.println(WiFi.localIP());//ip adresini yazdır.
    //Bunun dışında istenirse NodeMCU'ya restart atılarak da ağ yeniden başlatılabilir.
    //ESP.restart();
    Serial.println(WiFi.RSSI());//sinyal gücünü yazdır.
    oncekiZaman = simdikiZaman;//sayacları güncelle
  }
}
