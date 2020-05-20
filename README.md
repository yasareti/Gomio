# Gomio

Gomio Arduino için geliştirilmiş giriş/çıkış prinlerinin durumlarını okuyabileceğiniz ve çıkışları sürebileceğiniz
gömülü sistem yazılımıdır.

İndirdiğiniz "hex" dosyasını arduinoya yükledikten sonra herhangi bir "SerialMonitor" yazılımı ile arduinonuzla iletişime geçeilirsiniz.
Arduinonun hangi seri porta bağlı olduğunu aygıt yöneticisinden öğrenebilrisiniz. İletişim hızı olarak 115200 (Baudrate) belirlenmiştir.
Başarılı bir bağlantıdan sonra sizi seri monütörde aşağıdaki bilgileri içeren bir ekran karşılayacaktır.
Ekranda gömülü sistemin işlettiği komutlar görüntülenecektir.
Komutlardan herhangi birini işletmek için komutu yazıp ENTER butonun basarsanız komut işletilecektir.
Herkese kolaylıklar dilerim.


-------------------------------------------
..:: ARDUINO MEGA CONTROL CARD - GOMIO ::..
      CARD:MEGA  ID:000000   VER:1.0.0
              2020 Istanbul
-------------------------------------------
GOMIO 01 GOMULU SISTEM KOMUTLARI (USCO 01 PROTOKOLU)
-----------------------------------------------------------
help-------->:GOMULU SISTEM DOSYALARINI LISTELER. Ornek: help
do---------->: DIJITAL OUTPUT KOMUTU. Ornek: do 00 1 (00-44)
do_durum---->: DIJITAL OUTPUT DURUM BILGISI
aidi-------->: ANALOG VE DIGITAL GIRIS VE DIGITAL CIKIS BILGISI. Ornek: aidi 1/0
pwm--------->: PWM KOMUTU. Ornek: pwm 00 10000 1 (00-02)
cls--------->: TERMINAL EKRANI TEMIZLE Ornek: cls
reset------->: YAZILIMSAL RESET BUTONUNA BASILIR. Ornek: reset
ver--------->: VERSIYON ve ID BILGISINI VERIR. Ornek: ver
bip--------->: 6 FARKLI BEEP SESI OLUSTURMAK ICIN KULLANILIR. Ornek: bip 1 (1-6)
beep-------->: KARTIN HOPARLORUNU KONTROL EDER. Ornek: beep on, beep off
-----------------------------------------------------------
