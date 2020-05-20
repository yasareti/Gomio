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
* "Speed" kısmına gömülü sistemimizin iletişim hızı olan 115200 giriniz. Bir sonraki adıma geçmeden önce bu bağlantıya isim verip Putty'e kaydedebilirsiniz. Bu sizi bilgileri tekraren girmekten kurtarır.
* Aşağıdan Open butonuna basınız.
* Gömülü sistem komutları karşınızda.
#### Gömülü sistemin ilk kullanımı
* Putty arayüzünde gömülü sistem komutları görüntülenecektir.
* Gomio proje dosyaları altından kartınıza uygun pin haritasını indiriniz.
* Pin haritasına göre projenize uygun bağlantıyı yapınız.
* İstenen komut klavyeden yazılıp "enter" tuşuna basıldığında komut işletilir.
* <b>Örneğin:</b> do 00 1 işletilecek olsun do: dijital out kısaltılmışıdır. 00 ise pin numarasıdır. 1 yada 0 yaparak bu pini aç kapa yapabiliriz. Pin haritasından bakarsak do 00 ın tüm kartlar için arduinoun 7.pini olduğu görülür. Uygulama bağlantısı pin haritalarına göre yapılmalıdır.
#### Gömülü sistemin görsel arayüz programları ile kullanımı
* Gömülü sistem komutları arduino ile seri iletişim bağlantısı kurabilen tüm arayüzlerle çalışır. 
* Fiziksel dünyadan sensörler aracılığıya ölçülen tüm bilgiyi bu arayüzlerde gösterbiliriz.
* Görsel arayüz programını kodlarken seri gömülü sistem komutlarından birisini gönderdiğimiz zaman arkasından mutlaka
enter tuşuna basma işlemini de göndermeliyiz.
<b>Örneğin:</b> Görsel arayüz yazılımınızdan bir butona basıldığında gömülü sisteme "do 03 1" bilgisini göndermek ve işletmek istiyorsak.
<b>C#</b> serialPort.Write("do 03 1" + "\n \r"); sonuna mutlaka <b>"\n \r"</b> eklenmelidir.
<b>Delphi</b> ComPort1.WriteStr('do 03 1' + #13#10); sonuna mutlaka <b>#13#10</b> eklenmelidir.



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

