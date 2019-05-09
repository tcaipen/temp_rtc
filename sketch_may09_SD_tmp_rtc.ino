/*
 SD card read/write
 This example shows how to read and write data to and from an SD card file
 The circuit:
 ** SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK  - pin 13
 ** CS   - pin 10 (for MKRZero SD: SDCARD_SS_PIN)

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 Modified 16 Apr 2019 
 Terry Caipen
 Ouput file names must be in all caps.

 This example code is in the public domain.
 */

#include <SPI.h>
#include <SD.h>

int cs=10;
const int analogIn = A0;
int RawValue= 0;
double Voltage = 0;
double tempC = 0;
double tempF = 0;
char filename[10];

File myFile;
void setup(void) {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("Enter the temperature filename");
  delay(10000);
  Serial.readBytes(filename,8);
  Serial.print("data filename is "); 
  Serial.println(filename);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("card failed or not present!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open(filename, FILE_WRITE);
  Serial.print("Open file is " );
  Serial.println(filename);
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to ");
    Serial.println(filename);
    myFile.println("09 May 2019");
    myFile.flush();
    // close the file:
    // myFile.close();
    //Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening filename");
  }

}

void loop() {
  myFile = SD.open(filename, FILE_WRITE);
  RawValue = analogRead(analogIn);
  Voltage = (RawValue / 1023.0) * 5000; // 5000 to get millivots.
  tempC = (Voltage+133) * 0.1; // 500 is the offset
  tempF = (tempC * 1.8) + 32; // conver to F  
  Serial.print("\t Raw Value = " );  // shows pre-scaled value
  Serial.println(RawValue); 
  myFile.print("\t Raw Value = " );  // shows pre-scaled value                    
  myFile.println(RawValue); 
  myFile.flush();     
  myFile.print("\t milli volts = "); // shows the voltage measured     
  myFile.println(Voltage,0); //
  myFile.flush();
  myFile.print("\t Temperature in C = ");
  myFile.println(tempC,1);
  myFile.flush();
  myFile.print("\t Temperature in F = ");
  myFile.println(tempF,1);
  myFile.flush();
  delay(6000);  
}
