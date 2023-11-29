// For a connection via I2C using the Arduino Wire include:
#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>     
#include <VL53L0X.h>         
#include <Adafruit_MLX90614.h>
#include "SSD1306Wire.h"
#include "EEPROM.h"

#include "termoviu.h"
#include "termoviu_logo.h"

// -----------------------------------------------
// Uncomment Your Desired Langage for Audio
// -----------------------------------------------
//#define LANG_BR       // Português Brasil
//#define LANG_ES     // Espanhol
#define LANG_EN     // Inglês
// -----------------------------------------------
#ifdef LANG_BR
#include "br_audio-ola.h"
#include "br_audio-posicione.h"
#include "br_audio-e.h"
#include "br_audio-virgula.h"
#include "br_audio-trinta.h"
#include "br_audio-quarenta.h"
//#include "br_audio-18cm.h"
#include "br_audio-um.h"
#include "br_audio-dois.h"
#include "br_audio-tres.h"
#include "br_audio-quatro.h"
#include "br_audio-cinco.h"
#include "br_audio-seis.h"
#include "br_audio-sete.h"
#include "br_audio-oito.h"
#include "br_audio-nove.h"
#include "br_audio-sua_temperatura.h"
#include "br_audio-graus.h"
#include "br_audio-obrigada.h"
#endif
#ifdef LANG_ES
#include "es_audio-ola.h"
#include "es_audio-posicione.h"
#include "es_audio-e.h"
#include "es_audio-virgula.h"
#include "es_audio-trinta.h"
#include "es_audio-quarenta.h"
//#include "es_audio-18cm.h"
#include "es_audio-um.h"
#include "es_audio-dois.h"
#include "es_audio-tres.h"
#include "es_audio-quatro.h"
#include "es_audio-cinco.h"
#include "es_audio-seis.h"
#include "es_audio-sete.h"
#include "es_audio-oito.h"
#include "es_audio-nove.h"
#include "es_audio-sua_temperatura.h"
#include "es_audio-graus.h"
#include "es_audio-obrigada.h"
#endif
#ifdef LANG_EN
#include "en_audio-ola.h"
#include "en_audio-posicione.h"
#include "en_audio-e.h"
#include "en_audio-virgula.h"
#include "en_audio-trinta.h"
#include "en_audio-quarenta.h"
//#include "en_audio-18cm.h"
#include "en_audio-um.h"
#include "en_audio-dois.h"
#include "en_audio-tres.h"
#include "en_audio-quatro.h"
#include "en_audio-cinco.h"
#include "en_audio-seis.h"
#include "en_audio-sete.h"
#include "en_audio-oito.h"
#include "en_audio-nove.h"
#include "en_audio-sua_temperatura.h"
#include "en_audio-graus.h"
#include "en_audio-obrigada.h"
#endif
// -----------------------------------------------

#define EEPROMSIZE 4095
#define BOOTTIMES 10
#define READINGCOUNTER 20
#define KEYCOUNTER 30
char codeBuffer[25];
int codeBufferPos;
bool isUnlimited;
// wZScrgDKM2A8Ev3ba5yY

// ********************************************************************
// Global Variables, Matrices and  Function Prototypes
// ********************************************************************

const char *ssid = "TermoVIU";
const char *password = "";

char screenBuffer[5];  // Used in renderScreen
double temp;           // Global Readed Temperature of System
int distance;          // Last Distance measured in Laser Ruller
int noOfReading;       // Number of Valid Temperature Samples Reading
double tempCollection[STABILIZATION_N_TIMES+1]; // Collection of reading samples for integrate

double integrateSample(double readSample);
void renderScreen(void);
void renderLogoScreen(void);

// Set web server port number to 80
WiFiServer server(80);


// -----------------------------------------------
SSD1306Wire display(0x3c, SDA, SCL);   
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
VL53L0X sensor;

#define BUZZER 4
#define SENSOR 5
#define RELAY  12
#define RELAY2  13
#define DAC1 25

void play_um(void) {
  unsigned long sampleNo = 0;
  byte sample = 0;
  unsigned int max_size = um_len;

  while(sampleNo < max_size) {
    sample = um[sampleNo++];
    dacWrite(25, sample);
    delayMicroseconds(125);
  }
}

void play_dois(void) {
  unsigned long sampleNo = 0;
  byte sample = 0;
  unsigned int max_size = dois_len;

  while(sampleNo < max_size) {
    sample = dois[sampleNo++];
    dacWrite(25, sample);
    delayMicroseconds(125);
  }
}

void play_tres(void) {
  unsigned long sampleNo = 0;
  byte sample = 0;
  unsigned int max_size = tres_len;

  while(sampleNo < max_size) {
    sample = tres[sampleNo++];
    dacWrite(25, sample);
    delayMicroseconds(125);
  }
}

void play_quatro(void) {
  unsigned long sampleNo = 0;
  byte sample = 0;
  unsigned int max_size = quatro_len;

  while(sampleNo < max_size) {
    sample = quatro[sampleNo++];
    dacWrite(25, sample);
    delayMicroseconds(125);
  }
}

void play_cinco(void) {
  unsigned long sampleNo = 0;
  byte sample = 0;
  unsigned int max_size = cinco_len;

  while(sampleNo < max_size) {
    sample = cinco[sampleNo++];
    dacWrite(25, sample);
    delayMicroseconds(125);
  }
}

void play_seis(void) {
  unsigned long sampleNo = 0;
  byte sample = 0;
  unsigned int max_size = seis_len;

  while(sampleNo < max_size) {
    sample = seis[sampleNo++];
    dacWrite(25, sample);
    delayMicroseconds(125);
  }
}

void play_sete(void) {
  unsigned long sampleNo = 0;
  byte sample = 0;
  unsigned int max_size = sete_len;

  while(sampleNo < max_size) {
    sample = sete[sampleNo++];
    dacWrite(25, sample);
    delayMicroseconds(125);
  }
}

void play_oito(void) {
  unsigned long sampleNo = 0;
  byte sample = 0;
  unsigned int max_size = oito_len;

  while(sampleNo < max_size) {
    sample = oito[sampleNo++];
    dacWrite(25, sample);
    delayMicroseconds(125);
  }
}

void play_nove(void) {
  unsigned long sampleNo = 0;
  byte sample = 0;
  unsigned int max_size = nove_len;

  while(sampleNo < max_size) {
    sample = nove[sampleNo++];
    dacWrite(25, sample);
    delayMicroseconds(125);
  }
}

void play_e(void) {
  unsigned long sampleNo = 0;
  byte sample = 0;
  unsigned int max_size = e_len;

  while(sampleNo < max_size) {
    sample = e[sampleNo++];
    dacWrite(25, sample);
    delayMicroseconds(125);
  }
}

void play_virgula(void) {
  unsigned long sampleNo = 0;
  byte sample = 0;
  unsigned int max_size = virgula_len;

  while(sampleNo < max_size) {
    sample = virgula[sampleNo++];
    dacWrite(25, sample);
    delayMicroseconds(125);
  }
}

void play_trinta(void) {
  unsigned long sampleNo = 0;
  byte sample = 0;
  unsigned int max_size = trinta_len;

  while(sampleNo < max_size) {
    sample = trinta[sampleNo++];
    dacWrite(25, sample);
    delayMicroseconds(125);
  }
}

void play_quarenta(void) {
  unsigned long sampleNo = 0;
  byte sample = 0;
  unsigned int max_size = quarenta_len;

  while(sampleNo < max_size) {
    sample = quarenta[sampleNo++];
    dacWrite(25, sample);
    delayMicroseconds(125);
  }
}

void play_ola(void) {
  unsigned long sampleNo = 0;
  byte sample = 0;
  unsigned int max_size = ola_len;

  while(sampleNo < max_size) {
    sample = ola[sampleNo++];
    dacWrite(25, sample);
    delayMicroseconds(125);
  }
}

void play_posicione(void) {
  unsigned long sampleNo = 0;
  byte sample = 0;
  unsigned int max_size = posicione_len;

  while(sampleNo < max_size) {
    sample = posicione[sampleNo++];
    dacWrite(25, sample);
    delayMicroseconds(125);
  }
}

void play_sua_temperatura(void) {
  unsigned long sampleNo = 0;
  byte sample = 0;
  unsigned int max_size = sua_temperatura_len;

  while(sampleNo < max_size) {
    sample = sua_temperatura[sampleNo++];
    dacWrite(25, sample);
    delayMicroseconds(125);
  }
}

void play_graus(void) {
  unsigned long sampleNo = 0;
  byte sample = 0;
  unsigned int max_size = graus_len;

  while(sampleNo < max_size) {
    sample = graus[sampleNo++];
    dacWrite(25, sample);
    delayMicroseconds(125);
  }
}

void play_obrigada(void) {
  unsigned long sampleNo = 0;
  byte sample = 0;
  unsigned int max_size = obrigada_len;

  while(sampleNo < max_size) {
    sample = obrigada[sampleNo++];
    dacWrite(25, sample);
    delayMicroseconds(125);
  }
}

void make_silence(void) {
    pinMode(14, OUTPUT);
    digitalWrite(14,LOW);
}

void showKeychain() {
  char keyChainCode[25];
  sprintf(keyChainCode, "wZScrgDKM2A8Ev3ba5yY");
  int keyCounter = EEPROM.readInt(KEYCOUNTER);
  if(keyCounter==99) {
    Serial.println("***** UNLIMITED *****");
    isUnlimited = true;
  } else {
    keyCounter--;
    if(keyCounter<0) {
      Serial.println(keyChainCode);
    } else {
      keyChainCode[keyCounter] = 'a' + keyCounter;
      Serial.println(keyChainCode);
      Serial.println(codeBuffer);
    }
    isUnlimited = false;
  }
}

void validateKeychain() {
  char keyChainCode[25];
  sprintf(keyChainCode, "wZScrgDKM2A8Ev3ba5yY");
  Serial.println(keyChainCode);
  int keyCounter = EEPROM.readInt(KEYCOUNTER);
  keyChainCode[keyCounter] = 'a' + keyCounter;
  Serial.println(keyChainCode);
  Serial.println(codeBuffer);

  Serial.println(strcmp(keyChainCode, codeBuffer));
  if(strcmp(keyChainCode, codeBuffer)==0) {
    Serial.println("The Keychain is accepted ... ");
    keyCounter++;
    if(keyCounter>=19) keyCounter=99;
    EEPROM.writeInt(KEYCOUNTER, keyCounter);
    EEPROM.writeInt(READINGCOUNTER, KEYLIMIT);
    EEPROM.commit();
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  
  delay(1000);

  pinMode(BUZZER, OUTPUT_OPEN_DRAIN);
  digitalWrite(BUZZER, HIGH);
  pinMode(SENSOR, OUTPUT);
  digitalWrite(SENSOR, HIGH);

  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
  pinMode(RELAY2, OUTPUT);
  digitalWrite(RELAY2, LOW);

  pinMode(14, OUTPUT);
  digitalWrite(14,LOW);

  // Connect to Wi-Fi network with SSID and password
  // Remove the password parameter, if you want the AP (Access Point) to be
  // open
  //WiFi.softAP(ssid);
  //IPAddress IP = WiFi.softAPIP();
  //Serial.print("AP IP address is: ");
  //Serial.println(IP);
  //server.begin();

  EEPROM.begin(EEPROMSIZE);

  // Reset EEPROM to factory default
  //EEPROM.writeInt(BOOTTIMES, 0);
  //EEPROM.writeInt(READINGCOUNTER, KEYLIMIT);
  //EEPROM.writeInt(KEYCOUNTER, 0);
  // -------------------------------

  // Verify if is the 1st BOOT
  int bootTimes = EEPROM.readInt(BOOTTIMES);
  if (bootTimes<=0) {
    bootTimes=0;
    EEPROM.writeInt(BOOTTIMES, bootTimes);
    EEPROM.writeInt(READINGCOUNTER, KEYLIMIT);
    EEPROM.writeInt(KEYCOUNTER, 0);
    EEPROM.commit();
  }
  bootTimes++;
  EEPROM.writeInt(BOOTTIMES, bootTimes);
  Serial.print("Boot Number -> ");
  Serial.println(bootTimes);
  int availableReadings = EEPROM.readInt(READINGCOUNTER);
  Serial.print("Available Readings -> ");
  Serial.println(availableReadings);
  Serial.print("Last Keychain Used is ");
  showKeychain();

  codeBufferPos = 0;

  mlx.begin(); /// <<<<--- Simply does a Wire.begin();
  Serial.print("New Emissivity Factor must be ");

  #ifdef USE_MELEXIS_CONFIG
  uint16_t newEmissivity = 65536 * 0.659; // According to Melexis Application Note 0.659
  #else
  uint16_t newEmissivity = 65536 * 0.98; // According to Testo Documentation About Humam Temperature Reading
  #endif
  mlx.writeEmissivityReg(newEmissivity);
  Serial.print(newEmissivity);
  Serial.println();
  Serial.print("Emissivity Register is ");
  Serial.print(mlx.readEmissivityReg());
  Serial.println();
  Serial.print("Emissivity Factor is ");
  Serial.print(mlx.readEmissivity());
  Serial.println();

  display.init();
  display.flipScreenVertically();
  renderLogoScreen();
  delay(2000);

  sensor.setTimeout(500);
  if (!sensor.init()) {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  sensor.startContinuous(200);
  
  // -----------------------------------------
  // ATARI LIKE - SOUND TEST
  // -----------------------------------------
  /*
  int t=1;
  while(1) {
    digitalWrite(25,HIGH);
    delay(1);
    digitalWrite(25,LOW);
    delay(t);
    t++;
    if(t==30) t=1;
  }
  */
  // -----------------------------------------
}

void renderLogoScreen() {
  display.clear();
  for(int y=0; y<63; y++) {
    for(int x=0; x<128; x++) {
      if(logo[(y*128)+x]==1) display.setPixelColor(x,y+1,WHITE);
    }
  }
  display.display();
}

void renderScreen() {
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(Arimo_Bold_48);
  sprintf(screenBuffer, "%.1f", temp);
  display.drawString(12, 4, screenBuffer);
  display.setFont(ArialMT_Plain_10);
  display.drawString(107, 12, "o");
  display.drawString(113, 14, "C");
  display.display();
}

void sayTemperature() {
  int primeiroDigito =  (int)(screenBuffer[0] - 48);
  int segundoDigito =   (int)(screenBuffer[1] - 48);
  int terceiroDigito =  (int)(screenBuffer[3] - 48);

  if(primeiroDigito == 3) { play_trinta(); }
  if(primeiroDigito == 4) { play_quarenta(); }
  if(segundoDigito != 0) {
    play_e();
    if(segundoDigito == 1) { play_um(); } 
    if(segundoDigito == 2) { play_dois(); } 
    if(segundoDigito == 3) { play_tres(); } 
    if(segundoDigito == 4) { play_quatro(); } 
    if(segundoDigito == 5) { play_cinco(); } 
    if(segundoDigito == 6) { play_seis(); } 
    if(segundoDigito == 7) { play_sete(); } 
    if(segundoDigito == 8) { play_oito(); } 
    if(segundoDigito == 9) { play_nove(); } 
    if(terceiroDigito != 0) {
      play_virgula();
      if(terceiroDigito == 1) { play_um(); } 
      if(terceiroDigito == 2) { play_dois(); } 
      if(terceiroDigito == 3) { play_tres(); } 
      if(terceiroDigito == 4) { play_quatro(); } 
      if(terceiroDigito == 5) { play_cinco(); } 
      if(terceiroDigito == 6) { play_seis(); } 
      if(terceiroDigito == 7) { play_sete(); } 
      if(terceiroDigito == 8) { play_oito(); } 
      if(terceiroDigito == 9) { play_nove(); } 
    }
  }
}

void loop() {

  //doHTMLConfiguration();

  if(Serial.available()) {
    char received = (char)Serial.read();
    if(received=='\t') {
      codeBufferPos = 0;
    } else {
      codeBuffer[codeBufferPos] = received;
      codeBufferPos ++;
      if(codeBufferPos==20) {
        Serial.println("Keychain Received ... ");
        Serial.println(codeBufferPos);
        validateKeychain();
      }
    }
    Serial.print("Next Key char index -> ");
    Serial.println(codeBufferPos);
  }

  // Draw the screen with global readed temperature
  if(noOfReading > STABILIZATION_N_TIMES) {

    if(!isUnlimited) {
      int availableReadings = EEPROM.readInt(READINGCOUNTER);

      availableReadings --;
      if(availableReadings <= 0) {
        Serial.println("No more readings Available ... ");
        Serial.println("Buy a use license ... ");
        while(1) asm("NOP");
      }
      EEPROM.writeInt(READINGCOUNTER, availableReadings);
      EEPROM.commit();
      Serial.print("Available Readings -> ");
      Serial.println(availableReadings);
    }

    if(temp<MIN_TEMP_RELAY) {
      digitalWrite(RELAY, HIGH);
      digitalWrite(RELAY2, HIGH);
    }
    renderScreen();
    noOfReading = 0;

    pinMode(14, INPUT);
    play_sua_temperatura();
    sayTemperature();
    play_graus();
    play_obrigada();
    delay(1500);
    digitalWrite(RELAY, LOW);
    digitalWrite(RELAY2, LOW);
    make_silence();
    renderLogoScreen();
  }

  distance = sensor.readRangeContinuousMillimeters();

  if((distance>DISTANCE_MAXIMUM) && (distance<DISTANCE_MESSAGE)) {
    pinMode(14, INPUT);
    play_ola();
    play_posicione();
    //play_18cm();
    make_silence();
    delay(800);
  }

  if( (distance>DISTANCE_MINIMUM) && (distance<DISTANCE_MAXIMUM) ) {

    // Force I2C to restart to preserve reading integrity of MLX90614 after messages
    //mlx.begin(); /// <<<<--- Simply does a Wire.begin();

    Serial.print("Near Object is detected about -> ");
    Serial.print(distance);
    Serial.print("mm");
    Serial.println();
    Serial.flush();

    double ambientCel = mlx.readAmbientTempC();
    double objectCel  = mlx.readObjectTempC();

  #ifdef USE_MELEXIS_CONFIG
    temp = objectCel + (distance * 0.01);
  #else
    temp = objectCel + (distance * DISTANCE_ADJ_FACTOR);
  #endif
    temp = integrateSample(temp);
    double emissivity = mlx.readEmissivity();
    Serial.print("Ambient in Celsius --------> ");
    Serial.println(ambientCel);
    Serial.print("Object  in Celsius --------> ");
    Serial.println(objectCel);
    Serial.print("Calculated in Celsius -----> ");
    Serial.println(temp);
    Serial.print("Emissivity ----------------> ");
    Serial.println(emissivity);
    Serial.println();

    if(noOfReading >= 2)  {
      pinMode(BUZZER, OUTPUT_OPEN_DRAIN);
      digitalWrite(BUZZER, LOW);
      delay(TIME_BETWEEN);
      digitalWrite(BUZZER, HIGH);
      pinMode(BUZZER, INPUT_PULLUP);
    }
    noOfReading ++;

  } else {

    noOfReading = 0;

  }

  delay(TIME_LASER_SAMPLE);
}


// This function add a sample to colection and return integrate of this sample collection
// is based of a simple Nyquist Teorem
double integrateSample(double readSample) {

    // Pull all samples to LIFO Stack
    int t=0;
    for(t=0; t<STABILIZATION_N_TIMES; t++) {
        tempCollection[t] = tempCollection[t+1];
    }
    tempCollection[t] = readSample;

    // integrate of a single sampling mediam
    double toReturn = 0;
    for(t=0; t<STABILIZATION_N_TIMES+1; t++) {
        toReturn += tempCollection[t];
    }
    toReturn=toReturn/(STABILIZATION_N_TIMES+1);

    // Return Calculated Integral of Samples
    return(toReturn);
}