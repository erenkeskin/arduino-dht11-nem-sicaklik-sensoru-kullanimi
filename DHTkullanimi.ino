/*

  Sensörün kullanımı için öncelikle sensörün bağlantısını gerçekleştirmeniz gerekmektedir.
  Sensörün bağlantında - 3 bacaklı DHT modülü için anlatım yapılacaktır - sensör size dönük haldeyken 
  soldaki bacak Sinyal bacağı, ortadaki bacak VCC yani güç bacağı, sağdaki bacak ise GND yani toprak 
  hattı bacağınızdır. 

  Sensörün kullanımı için sinyal bacağını PWM sinyali veren bir digital pine, VCC bacağını 3V'a, GND 
  bacağını ise NodeMCU üzerindeki herhangi bir GND pinine bağlayabilirsiniz.
  
*/

// Kütüptanemize attığımız DHT.h dosyamızı projemize dahil ediyoruz.
#include "DHT.h"

#define DHTPIN 2             // Sensörümüzün sinyal bacağının bağlı olduğu pini belirliyoruz.
#define DHTTYPE DHT11        // DHT 11 kullanacağımız için tipimizi belirliyoruz.
                             // DHT 22 veya DHT 21 tipi sensörleri olanlar burayı o ayara göre düzenleyebilirler.

DHT dht(DHTPIN, DHTTYPE);    // Kütüphane içerisinden kendimize bir sınıf oluşturarak kullanmaya başlıyoruz.
                             // Küçük şekilde yazılan dht kısmını istediğiniz şekilde değiştirebilirsiniz.

void setup() {
  
  Serial.begin(115200);      // Serial Monitörümüzü başlatıyoruz.

  Serial.println("DHTxx test!");
  dht.begin();               // DHT sınıfımızı başlatıyoruz.
}

void loop() {

  delay(2000);               // Ölçümler arasındaki değişimleri daha iyi görebilmek için bir geçikme veriyoruz.

  /* Nem oranın ölçümü */
  float h = dht.readHumidity();
  /* Sıcaklık değerinin Celcius cinsinden ölçümü */
  float t = dht.readTemperature();
  /* Sıcaklık değerinin Fahrenheit cinsinden ölçümü */
  float f = dht.readTemperature(true);

  /* Ölçümde hata olup olmadının kontrolünü yapıyoruz. */
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("DHT sensorunun olcumunde hata oldu!");
    return;
  }

  /* Sıcaklık indexinin Fahrenheit cinsinden değeri */
  float hif = dht.computeHeatIndex(f, h);
  /* Sıcaklık indexinin Celcius cinsinden değeri */
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Nem Orani: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Sıcaklık: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Sicaklik indexi: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
  
}
