
/*
    Usco protokolü üzerine arduino için hazırlanmış gömülü sistemdir 2019-2020 tarihleri arasında İstanbulda üretilmiştir.    
*/


#include <pt.h>
#include <DynamicCommandParser.h>
#define ARRAY_SIZE(array) ((sizeof(array))/(sizeof(array[0])))

String inByte;
float ver = 1.1;
String card = "UNO";
String id = "00000001";

bool debug = 0;
bool aidi = 0; //paketi ekrana basma default 0;

int x0 = 2;
int x1 = 4;

int y0 = 7;
int y1 = 8;
int y2 = 9;
int y3 = 10;
int y4 = 11;
int y5 = 12;
int bipPin = 13; ///bip pin

int pwm0 = 3;
int pwm1 = 5;
int pwm2 = 6;

int _di[2] = {x0,x1};
int _do[6] = {y0,y1,y2,y3,y4,y5};
int _ai[6] = {A0,A1,A2,A3,A4,A5};
int _pwm[3] = {pwm0,pwm1,pwm2};
int _bipMs[7] = {0,100,200,300,400,500,600};
int _bipVal = 0;
bool isBip = false;
bool isBeep = false;
String pocket;


static struct pt pt1, pt2, pt3, pt4;

void stateBadCode(){
   if(!aidi){
      Serial.println("Kotu komut!");
   }else{
      Serial.write(27);
      Serial.print("[2J"); // ekranı temizle
   }
}

void setIO(int _arr[],int _size, char _io){
  if(!(_io=='i' || _io=='o')){
    Serial.println("ikinci parametreye 'i' yada 'o' giriniz!");
  }
  for(int i=0; i<_size;i++){
    pinMode(_arr[i],_io == 'i'?0:1);
    if(debug){    
      Serial.print("index : --->");
      Serial.print(_arr[i]);
      Serial.print("--->");
      Serial.println(_io == 'i'?0:1);
    }
  }
  if(debug) Serial.println("------->Ok<-------");
}

/*
  _val gelen string
*/
bool numberValidation(String _val,int len){
  bool _bl = 0; 
  if(len != _val.length() || _val == "") return false;
  for(int i=0; i<_val.length();i++){     
    _bl = isDigit(char(_val[i]));
    if(debug)Serial.println(String(_val[i]) +"---"+  String(_bl?"True":"False"));
    if(_bl){
      continue;
    }else{
      break;
    }
  }
  return _bl;
}

void setVer(float _ver){
   ver = _ver;
}

float getVer(){  
  return ver;
}

void setId(String _id){
   id = _id;
}

String getId(){  
  return id;
}

String getDo(){   
  String sumStr = "<"; 
  for(int i=0; i<ARRAY_SIZE(_do);i++){
    sumStr += String(digitalRead(_do[i]));
    sumStr += i < ARRAY_SIZE(_do)-1 ?  "" :  "0000>" ;
  }
  return sumStr;
}

String getDi(){
  String sumStr = "DI:"; 
  for(int i=0; i<ARRAY_SIZE(_di);i++){
    sumStr += String(digitalRead(_di[i]));
    sumStr += i < ARRAY_SIZE(_di)-1 ?  "" :  "," ;
  }
  return sumStr;
}

String getAi(){
  String sumStr = ":"; 
  for(int i=0; i<ARRAY_SIZE(_ai);i++){
    sumStr += strFormatter(String(map(analogRead(_ai[i]),0,1023,0,4095)),'0',4);
    sumStr += i < ARRAY_SIZE(_ai)-1 ?  ":" :  ":0000:0000," ;
  }
  return sumStr;
}

String getTempHum(){
  String sumStr = "T:"; 
  sumStr += strFormatter("0",' ',3) + ",";
  sumStr += "H:"; 
  sumStr += strFormatter("0",' ',3) + ",";  
  sumStr += "D0:"; 
  sumStr += strFormatter("0",' ',5) + ",";  
  sumStr += "D1:"; 
  sumStr += strFormatter("0",' ',5) + ",";  
  return sumStr;
}

String sendPocket(){
  String sumStr = "{";
  sumStr += getAi() ;
  sumStr += getDi();
  sumStr += getTempHum();
  sumStr += getDo() + ",Saniye:    00}";
  /*if(sumStr.length() > 103){
    return sumStr;
  }else{
    return String(String(sumStr.length()) + "---------------- Hata ---------------");
  }*/
  return sumStr;
}

String strFormatter(String str,char addC, int _length){
  if(str.length() < _length){
    String _str = "";
    for(int i = 0; i<(_length - str.length()); i++){
      _str += addC;
    }
    _str += str;
    return _str;
  }else{
    return str; 
  }
}

void setDo(int _pin,bool HL){
  digitalWrite(_pin,HL);
}

void updatePwms(String _chnl, int _val, bool _bl){
   int selectedPWM = _pwm[_chnl.toInt()];
   if(_bl){
      int val = map(_val,0,10000,0,255);
      analogWrite(selectedPWM,val); 
      if(!aidi)Serial.println(String("PWM "+_chnl+" ON"));
   }else{
      analogWrite(selectedPWM,0);
      if(!aidi)Serial.println(String("PWM "+_chnl+" OFF"));    
   }
}

void help(){
  Serial.println("GOMIO 01 GOMULU SISTEM KOMUTLARI (USCO 01 PROTOKOLU)");
  Serial.println("-----------------------------------------------------------");
  Serial.println("help        : GOMULU SISTEM DOSYALARINI LISTELER. Ornek: help");
  Serial.println("do          : DIJITAL OUTPUT KOMUTU. Ornek: do 00 1 (00-06)");
  Serial.println("do_durum    : DIJITAL OUTPUT DURUM BILGISI");
  Serial.println("aidi        : ANALOG VE DIGITAL GIRIS VE DIGITAL CIKIS BILGISI. Ornek: aidi 1/0");
  Serial.println("pwm         : PWM KOMUTU. Ornek: pwm 00 10000 1 (00-02)");
  Serial.println("cls         : TERMINAL EKRANI TEMIZLE Ornek: cls");
  Serial.println("reset       : YAZILIMSAL RESET BUTONUNA BASILIR. Ornek: reset");
  Serial.println("ver         : VERSIYON ve ID BILGISINI VERIR. Ornek: ver");
  Serial.println("bip         : 6 FARKLI BEEP SESI OLUSTURMAK ICIN KULLANILIR. Ornek: bip 1 (1-6)");
  Serial.println("beep        : KARTIN HOPARLORUNU KONTROL EDER. Ornek: beep on, beep off");
  Serial.println("-----------------------------------------------------------");
}

void intro(){
  Serial.println("-------------------------------------------");
  Serial.println(String("..:: ARDUINO "+ card +" CONTROL CARD - GOMIO ::.."));
  Serial.println(String("     CARD:"+ card +"  "+"ID:"+id+"   VER:"+ ver +"     "));
  Serial.println("              2020 Istanbul                ");
  Serial.println("-------------------------------------------");
  help();
}

void reset(){;
  aidi = 0;
  for(int i = 0;i<ARRAY_SIZE(_do);i++){
    setDo(_do[i],0);
  }
  if(aidi)clearTerminal();
}

DynamicCommandParser dcp('^', '$', ' ');

String Param_1,Param_2,Param_3,Param_4;//Komut seti komutları en fazla 4 aşamalı parçalamaya tabi tutuluyor
void multipleVariableParser(char **values, int valueCount)
{
    Param_1  = values[1];
    Param_2  = values[2];
    Param_3  = values[3];
    Param_4  = values[4];

   if(Param_1 == "do"){  
        //if(isBeep)beep();         
        if(!(numberValidation(Param_2,2) && numberValidation(Param_3,1))) return;
        switch (Param_3.toInt()) {
        case 0: 
                  setDo(_do[String(Param_2[1]).toInt()],0); 
                  if(!aidi) Serial.println(String("do " + strFormatter(String(Param_2[1]),'0',2)+ "---0 Ok"));
                  break;
        case 1: 
                  setDo(_do[String(Param_2[1]).toInt()],1); 
                  if(!aidi) Serial.println(String("do " + strFormatter(String(Param_2[1]),'0',2)+ "---1 Ok"));
                  break;
        }
    }else if(Param_1 == "aidi" && numberValidation(Param_2,1)){
        switch (Param_2.toInt()) {
          case 0: aidi = 0;
                  //if(isBeep)beep(); 
          break;
          case 1: aidi = 1;
                  //if(isBeep)beep();
                  break;
        }
    }else if((Param_1 == "pwm"))
    {
        String _chnl = Param_2;
        int    _val  = Param_3.toInt();
        bool   _bl   = bool(Param_4.toInt());
        //if(isBeep)beep();
        updatePwms(_chnl,_val,_bl);
              
    }else if(Param_1 == "bip"){
       _bipVal = _bipMs[Param_2.toInt()];
       if(Param_2.toInt() <= 0) isBip = true;
    }else if(Param_1 == "beep"){
      if(Param_2 == "on"){
        //isBeep = true;
        //beep();
      }else if(Param_2 == "off"){
        //isBeep = false;
      }
    }else if(Param_1 == "help" && !aidi){
      help();
      //if(isBeep)beep();
    }else if(Param_1 == "cls" && !aidi){
      clearTerminal();
      homeCursor(); 
      //if(isBeep)beep();
    }else if(Param_1 == "reset"){
      reset();
      //if(isBeep)beep();
    }else if(Param_1 == "ver"){
      Serial.println(String("Ver: " + String(getVer()) + " Id: " + getId()));
      //if(isBeep)beep();
    }else if(Param_1 == "do_durum" && !aidi){
      Serial.println(getDo());
      //if(isBeep)beep();
    }else {
      stateBadCode();
    }
}

void beep(){
  _bipVal = 100;
  isBip = true;  
}

String _sumString;
static int protothreadCatchPocket(struct pt *pt)
{
  static unsigned long lastTimeBlink = 0;
  PT_BEGIN(pt);
  while(1) {
    lastTimeBlink = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > 50);
      char c;
      if (Serial.available() > 0) {   
         c = char(toLowerCase(Serial.read()));  
         Serial.print(c);   
     
        
        if ( c == '\n' || c == '\r' || c=='\0') {
          Serial.print('\n');
  
          inByte = String("^MVP " + _sumString + "$");  //Parser paket yapısı
                  
          for(int i = 0; i<inByte.length();i++){ 
            dcp.appendChar(char(inByte[i]));
          }
                
          _sumString = "";
          break;
        }else{_sumString += c;}
      }
  }
  PT_END(pt);
}

static int protothreadSendPocket(struct pt *pt)
{
  static unsigned long lastTimeBlink = 0;
  PT_BEGIN(pt);
  while(1) {
    lastTimeBlink = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > 250);
    if(aidi){
      clearTerminal();
      homeCursor();
      Serial.println(sendPocket()); 
    }
  }
  PT_END(pt);
}


static int protothreadBip(struct pt *pt)
{
  static unsigned long lastTimeBlink = 0;
  PT_BEGIN(pt);
  while(1) {

    lastTimeBlink = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > _bipVal);
    digitalWrite(bipPin, HIGH);
    lastTimeBlink = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > _bipVal);
    digitalWrite(bipPin, LOW);     
    lastTimeBlink = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > _bipVal);
    digitalWrite(bipPin, HIGH);
    lastTimeBlink = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > _bipVal);
    digitalWrite(bipPin, LOW);    
    isBip = false;
  }
  PT_END(pt);
}



static int protothreadDHT11(struct pt *pt)
{
  static unsigned long lastTimeCheck = 0;
  PT_BEGIN(pt);
  while (1) {
    lastTimeCheck = millis();
  }
  PT_END(pt);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(bipPin,OUTPUT);
  setIO(_di,ARRAY_SIZE(_di),'i');
  setIO(_ai,ARRAY_SIZE(_ai),'i');
  setIO(_do,ARRAY_SIZE(_do),'o');
  setIO(_pwm,ARRAY_SIZE(_pwm),'o');
  
  Serial.begin(115200);
  while(Serial.available()>0);
  
  intro();
  
  dcp.addParser("MVP", multipleVariableParser); 

  PT_INIT(&pt1);
  PT_INIT(&pt2);
  PT_INIT(&pt3);
  PT_INIT(&pt4);
}

void clearTerminal(){
    Serial.write(27); 
    Serial.print("[2J"); // ekranı temizle
}

void homeCursor(){
    Serial.write(27); // ESC 
    Serial.print("[H"); // cursoru başa al
}

void loop() {   
  protothreadCatchPocket(&pt1);
  protothreadSendPocket(&pt2);
  //protothreadDHT11(&pt3);
  if(isBip)protothreadBip(&pt3);
}
