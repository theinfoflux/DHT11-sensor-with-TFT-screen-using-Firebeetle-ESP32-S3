 #include "DFRobot_GDL.h"  
#include "DHT.h"
int DHTPIN= D9;
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
/*M0*/ 
#if defined ARDUINO_SAM_ZERO
#define TFT_DC  7
#define TFT_CS  5
#define TFT_RST 6
/*ESP32 and ESP8266*/
#elif defined(ESP32) || defined(ESP8266)
#define TFT_DC  D2
#define TFT_CS  D6
#define TFT_RST D3
/*AVR series mainboard*/
#else
#define TFT_DC  2
#define TFT_CS  3
#define TFT_RST 4
#endif

/**
 * @brief Constructor  Constructors for hardware SPI communication
 * @param dc  Command pin or data line pin of SPI communication 
 * @param cs  Chip select pin for SPI communication
 * @param rst Reset pin of the screen
 * @param bl  Screen backlight pin
 */
//DFRobot_ST7789_240x240_HW_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);
DFRobot_ST7789_240x320_HW_SPI tft(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);
//DFRobot_ILI9341_240x320_HW_SPI  screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);
//DFRobot_ILI9488_320x480_HW_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);
/* M0 mainboard DMA transfer */
//DFRobot_ST7789_240x240_DMA_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);
//DFRobot_ST7789_240x320_DMA_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);
//DFRobot_ILI9341_240x320_DMA_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);
//DFRobot_ILI9488_320x480_DMA_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);


#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
float temp =0;
float hum =0;
float pretemp =0;
float prehum =0;
float currtemp =50;
float currhum=100;
float i=0;
float j=0;

void setup(void)
{
    Serial.begin(9600);
////    uint16_t ID = tft.readID();
//    Serial.print("TFT ID = 0x");
//    Serial.println(ID, HEX);
//    Serial.println("Calibrate for your Touch Panel");
//    if (ID == 0xD3D3) ID = 0x9486; // write-only shield
  dht.begin();
    tft.begin();
    tft.setRotation(1);            //PORTRAIT
    tft.fillScreen(COLOR_RGB565_BLACK);
    tft.setTextColor(COLOR_RGB565_YELLOW, COLOR_RGB565_BLACK);
    tft.setTextSize(2);
    // testing();
    tft.setTextSize(2);
    tft.setCursor(15, 240);
    tft.setTextColor(COLOR_RGB565_GREEN,COLOR_RGB565_BLACK);
    tft.print("theinfoflux");
   // delay(1000);
    tft.fillScreen(COLOR_RGB565_BLACK);
    tft.setTextColor(COLOR_RGB565_GREEN,COLOR_RGB565_BLACK);
    tft.setCursor(55, 180);
    tft.print("0");
    tft.setCursor(95, 180);
    tft.print("100");
    tft.setCursor(55, 120);
    tft.print((char)247);
   tft.print("C");

   tft.setTextColor(COLOR_RGB565_WHITE  ,COLOR_RGB565_BLACK);
    tft.setCursor(215, 180);
    tft.print("0");
    tft.setCursor(235, 180);
    tft.print("100");
    tft.setCursor(220, 120);
       tft.print("%");
    tft.setCursor(45, 10);
    tft.fillRect(0,0,320,45,COLOR_RGB565_BLACK);
    tft.setTextColor(COLOR_RGB565_YELLOW,COLOR_RGB565_BLACK);
    tft.print("DHT11 Monitor");
    
  
}


void loop(void)
{
 
    tft.fillRect(55, 150,60,20,COLOR_RGB565_BLACK);
    tft.fillRect(212,150,60,20,COLOR_RGB565_BLACK);
    tft.setCursor(55, 150);
    tft.print(temp);
     tft.setCursor(212, 150);
    tft.print(hum);
    i=map(pretemp,0,100,0,300);
   j=map(currtemp,0,100,0,300);
   for (i; i<=j; i=i+0.1)
    {
    float j=i-150 ;
    float angle = (j / 57.2958)  - 1.57; 
    float x1= 80 + cos(angle) * 55;
    float y1 = 130+sin(angle) * 55;
    float x2= 80 + cos(angle) * 75;
    float y2 = 130+sin(angle) * 75;
    tft.drawLine(x1, y1,x2,y2, COLOR_RGB565_GREEN);
    }
   i=map(pretemp,0,100,0,300);
   j=map(currtemp,0,100,0,300);  
  for (i-2; i>=j; i=i-0.05)
    {
    float j=i-150 ;
    float angle = (j / 57.2958)  - 1.57; 
    float x1= 80 + cos(angle) * 55;
    float y1 = 130+sin(angle) * 55;
    float x2= 80 + cos(angle) * 75;
    float y2 = 130+sin(angle) * 75;
    tft.drawLine(x1, y1,x2,y2, COLOR_RGB565_BLACK);
   // tft.drawLine(x1+160, y1,x2+160,y2, MAGENTA);
    }
i=map(prehum,0,212,0,300);
    j=map(currhum,0,212,0,300);   
  for (i; i<=j; i=i+0.1)
    {
    float j=i-150 ;
    float angle = (j / 57.2958)  - 1.57; 
    float x1= 80 + cos(angle) * 55;
    float y1 = 130+sin(angle) * 55;
    float x2= 80 + cos(angle) * 75;
    float y2 = 130+sin(angle) * 75;
    
    tft.drawLine(x1+160, y1,x2+160,y2, COLOR_RGB565_MAGENTA);
    }
   i=map(prehum,0,100,0,300);
   j=map(currhum,0,100,0,300);  
 for (i-2; i>=j; i=i-0.05)
    {
    float j=i-150 ;
    float angle = (j / 57.2958)  - 1.57; 
    float x1= 80 + cos(angle) * 55;
    float y1 = 130+sin(angle) * 55;
    float x2= 80 + cos(angle) * 75;
    float y2 = 130+sin(angle) * 75;
    
    tft.drawLine(x1+160, y1,x2+160,y2, COLOR_RGB565_BLACK);
    }
 

  prehum=currhum;
  pretemp=currtemp;
 temp = dht.readTemperature();
 hum = dht.readHumidity();  
currtemp=temp;
currhum=hum;
delay(1000);

    
}
