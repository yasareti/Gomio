# Gomio

Gomio Arduino için geliştirilmiş giriş/çıkış prinlerinin durumlarını okuyabileceğiniz ve çıkışları sürebileceğiniz
gömülü sistem yazılımıdır.

### Gomio'nun Seyir Defteri

#### v.1.0.0
* İlk genel yayınlama
#### v.0.9.0
* İlk kişisel kullanım

### Nasıl Kullanırım?
#### Gömülü sistemi Arduinoya yükleme
* Arduino kartınızı bilgisayarınıza bağlayınız.
* Aygıt yöneticisinden arduinonuzun hangi comporta bağlı olduğunu öğreniniz.
* Port bilgisini kenara kaydediniz.
* Kartınıza uygun Hex dosyasını indiriniz.
* Xloader indiriniz. http://www.hobbytronics.co.uk/download/XLoader.zip
* Xloader rarı açınız ve Xloader.exe'yi çalıştırınız.
* Xloader arayüzünden "Com port" kısmına kenara kaydettiğimiz arduino port bilgisini giriniz.
* "Device" bölümünden kartınızın modelini seçiniz.
* "Hex file" bölümünden indirdiğimiz hex dosyasının yolunu bulunuz ve aç deyiniz.
* Yükleme bittiğinde Xloader arayüzünün en altında yükleme bitti bilgisini göreceksiniz. 
* Yükleme başarılı.
#### Gömülü sistemle iletişim
* Putty indiriniz. https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html
* Putty'i bilgisayarınıza kurunuz.
* Putty çalıştırınız.
* Putty arayüzünden Serial radyo butonuna tıklayınız.
* "Serial line" kısmına arduinonuzun bağlı olduğu comport bilgisini giriniz.
* "Speed" kısmına gömülü sistemimizin iletişim hızı olan 115200 giriniz.
* Aşağıdan Open butonuna basınız.
* Gömülü sistem komutları karşınızda.
#### Gömülü sistemin ilk kullanımı
* Putty arayüzünde gömülü sistem komutları görüntülenecektir.
* Gomio proje dosyaları altından kartınıza uygun pin haritasını indiriniz.
* Pin haritasına göre projenize uygun bağlantıyı yapınız.
* İstenen komut klavyeden yazılıp "enter" tuşuna basıldığında komut işletilir.
* <b>Örneğin:</b> do 00 1 işletilecek olsun do: dijital out kısaltılmışıdır. 00 ise pin numarasıdır. 1 yada 0 yaparak bu pini aç kapa yapabiliriz. Pin haritasından bakarsak do 00 ın tüm kartlar için arduinoun 7.pini olduğu göörülür. Uygulama bağlantısı buna göre yapılmalıdır.


# Gömülü sistem komutları 

Komut|Açıklama|Örnek
:------|:-------------------------------|:----------------------|
help|GOMULU SISTEM DOSYALARINI LISTELER| help
do| DIJITAL OUTPUT KOMUTU|do 00 1 (00-44)
do_durum|DIJITAL OUTPUT DURUM BILGISI|do_durum
aidi|ANALOG VE DIGITAL GIRIS VE DIGITAL CIKIS BILGISI|aidi 1/0
pwm| PWM KOMUTU|pwm 00 10000 1 (00-02)
cls| TERMINAL EKRANI TEMIZLE|cls
reset| YAZILIMSAL RESET BUTONUNA BASILIR. |reset
ver| VERSIYON ve ID BILGISINI VERIR|ver
bip| 6 FARKLI BEEP SESI OLUSTURMAK ICIN KULLANILIR|bip 1 (1-6)
beep| KARTIN HOPARLORUNU KONTROL EDER.|beep on, beep off

