#include <SoftwareSerialParity.h>
//power supply 1 params: pins 3,4 - Vop = 41.09
//power supply 2 params: pins 7,6 (order matters!) - Vop = 41.11
SoftwareSerialParity powerSupply4(10, 11);
SoftwareSerialParity powerSupply3(8, 9);
SoftwareSerialParity powerSupply2(6, 7);
SoftwareSerialParity powerSupply1(3, 4);

float VoltConversion = 1.812e-3;// Volts
float QuadTempCoeffConversion = 1.507e-3;// mV/(degC)^2
float LinTempCoeffConversion = 5.225e-2;// mV/degC
float CurrConversion = 5.194e-3;// mA

void setup() {
  Serial.begin(38400);
  Serial.print("------------------------------------------------------------------- \n");
  Serial.println("Remember to attach power source for the supplies before continuing!");
  Serial.print("------------------------------------------------------------------- \n");

  
  float inputTemp = 0.0;
  Serial.print("Enter reference temperature in degC for Power Supplies: ");
  while (Serial.available() == 0) { /* waiting for the response */ }
  inputTemp = Serial.parseFloat();
  Serial.println(inputTemp);
  while (Serial.available() > 0) { Serial.read(); }
  Serial.flush();

  // Power Supply 1a
  float inputVoltage1 = 0.0;
  while (inputVoltage1 == 0.0) {
    Serial.print("Enter operating voltage for Power Supply 1a in Volts: ");
    while (Serial.available() == 0) { /* waiting for the response */ }
    inputVoltage1 = Serial.parseFloat();
    Serial.println(inputVoltage1);
    while (Serial.available() > 0) { Serial.read(); }
    if (inputVoltage1 < 20 || inputVoltage1 > 46) {
      Serial.println("Input voltage outside of safe range [20V, 42V], try again.");
      inputVoltage1 = 0;
    }
  }
  Serial.flush();

  // Convert input voltage from Volts -> decimal -> hex
  int decVoltage1 = inputVoltage1 / VoltConversion;
  char hexVoltage1[5];
  sprintf(hexVoltage1, "%X", decVoltage1);

  // Power Supply 1b
  float inputVoltage2 = 0.0;
  while (inputVoltage2 == 0.0) {
    Serial.print("Enter operating voltage for Power Supply 1b in Volts: ");
    while (Serial.available() == 0) { /* waiting for the response */ }
    inputVoltage2 = Serial.parseFloat();
    Serial.println(inputVoltage2);
    while (Serial.available() > 0) { Serial.read(); }
    if (inputVoltage2 < 20 || inputVoltage2 > 46) {
      Serial.println("Input voltage outside of safe range [20V, 42V], try again.");
      inputVoltage2 = 0;
    }
  }
  Serial.flush();

  // Convert input voltage from Volts -> decimal -> hex
  int decVoltage2 = inputVoltage2 / VoltConversion;
  char hexVoltage2[5];
  sprintf(hexVoltage2, "%X", decVoltage2);

  // Power Supply 2a
  float inputVoltage3 = 0.0;
  while (inputVoltage3 == 0.0) {
    Serial.print("Enter operating voltage for Power Supply 2a in Volts: ");
    while (Serial.available() == 0) { /* waiting for the response */ }
    inputVoltage3 = Serial.parseFloat();
    Serial.println(inputVoltage3);
    while (Serial.available() > 0) { Serial.read(); }
    if (inputVoltage3 < 20 || inputVoltage3 > 46) {
      Serial.println("Input voltage outside of safe range [20V, 42V], try again.");
      inputVoltage3 = 0;
    }
  }
  Serial.flush();

  // Convert input voltage from Volts -> decimal -> hex
  int decVoltage3 = inputVoltage3 / VoltConversion;
  char hexVoltage3[5];
  sprintf(hexVoltage3, "%X", decVoltage3);

  // Power Supply 2b
  float inputVoltage4 = 0.0;
  while (inputVoltage4 == 0.0) {
    Serial.print("Enter operating voltage for Power Supply 2b in Volts: ");
    while (Serial.available() == 0) { /* waiting for the response */ }
    inputVoltage4 = Serial.parseFloat();
    Serial.println(inputVoltage4);
    while (Serial.available() > 0) { Serial.read(); }
    if (inputVoltage4 < 20 || inputVoltage4 > 46) {
      Serial.println("Input voltage outside of safe range [20V, 42V], try again.");
      inputVoltage4 = 0;
    }
  }
  Serial.flush();

  // Convert input voltage from Volts -> decimal -> hex
  int decVoltage4 = inputVoltage4 / VoltConversion;
  char hexVoltage4[5];
  sprintf(hexVoltage4, "%X", decVoltage4);

  // Convert temperature from degC -> decimal -> hex
  int decTemp = (1.035 - inputTemp * 5.5e-3) / (1.907e-5);
  char hexTemp[5];
  sprintf(hexTemp, "%X", decTemp);

  Serial.println();
  Serial.println("Power Supply 1a");

  // Initialize and configure powerSupply1
  powerSupply1.begin(38400, EVEN);
  powerSupply1.listen();
  hreCommand(powerSupply1);
  hstCommand(hexVoltage1, hexTemp, powerSupply1);
  hrtCommand(powerSupply1);
  delay(1000);
  powerSupply1.end();
  powerSupply1.stopListening();

  // Print separator for clarity
  Serial.println();
  Serial.println("Power Supply 1b");

  // Initialize and configure powerSupply2
  powerSupply2.begin(38400, EVEN);
  powerSupply2.listen();
  hreCommand(powerSupply2);
  hstCommand(hexVoltage2, hexTemp, powerSupply2);
  hrtCommand(powerSupply2);
  delay(1000);
  powerSupply2.end();
  powerSupply2.stopListening();

  // Print separator for clarity
  Serial.println();
  Serial.println("Power Supply 2a");

  // Initialize and configure powerSupply3
  powerSupply3.begin(38400, EVEN);
  powerSupply3.listen();
  hreCommand(powerSupply3);
  hstCommand(hexVoltage3, hexTemp, powerSupply3);
  hrtCommand(powerSupply3);
  delay(1000);
  powerSupply3.end();
  powerSupply3.stopListening();

  // Print separator for clarity
  Serial.println();
  Serial.println("Power Supply 2b");

  // Initialize and configure powerSupply4
  powerSupply4.begin(38400, EVEN);
  powerSupply4.listen();
  hreCommand(powerSupply4);
  hstCommand(hexVoltage4, hexTemp, powerSupply4);
  hrtCommand(powerSupply4);
  delay(1000);
  powerSupply4.end();
  powerSupply4.stopListening();

  Serial.println();
}


void loop() {
  // put your main code here, to run repeatedly:

//  tell the serial port to listen for output
  Serial.println("Power Supply 1 Status:");
  powerSupply1.listen();
  hpoCommand(powerSupply1);
  Serial.println();

  Serial.println("Power Supply 2 Status:");
  powerSupply2.listen();
  hpoCommand(powerSupply2);
  Serial.println();

  Serial.println("Power Supply 3 Status:");
  powerSupply3.listen();
  hpoCommand(powerSupply3);
  Serial.println();

  Serial.println("Power Supply 4 Status:");
  powerSupply4.listen();
  hpoCommand(powerSupply4);
  Serial.println();
  
}

void hstCommand(char voltage[], char temperature[], const SoftwareSerialParity& powerSupply)
{
  //Using function 4-1 from command ref to set parameters of power supply
  //first determine checksum, convert to hex
  int checksum = 0x02+'H'+'S'+'T'+//STX and command name
                  '0'+'0'+'0'+'0'+'0'+'0'+'0'+'0'+//set quadratic temp correction coefficients to 0
                  '0'+'2'+'8'+'B'+'0'+'2'+'8'+'B'+//set both linear temp correction coeffs to datasheet value (34 mV/degC)
                  voltage[0]+voltage[1]+voltage[2]+voltage[3]+//set voltage
                  temperature[0]+temperature[1]+temperature[2]+temperature[3]+//set temperature
                  0x03;//ETX

  char hexChecksum[4];
  sprintf(hexChecksum, "%X", checksum);//only use hexChecksum[1,2]
  
  //STX
  powerSupply.write(0x02);
  //HST = command name
  powerSupply.write('H');
  powerSupply.write('S');
  powerSupply.write('T');
  //Setting quadratic temp correction factors to 0 = (0000)_16
  //DeltaT'1
  powerSupply.write('0');
  powerSupply.write('0');
  powerSupply.write('0');
  powerSupply.write('0');
  //DeltaT'2
  powerSupply.write('0');
  powerSupply.write('0');
  powerSupply.write('0');
  powerSupply.write('0');
  //Setting linear temp correction factors to recommended value in data sheet
  //DeltaT1 = 34mV/degC/(5.225e-2 mV/degC) = 651 -> 028B
  powerSupply.write('0');
  powerSupply.write('2');
  powerSupply.write('8');
  powerSupply.write('B');
  //DeltaT2 to same value
  powerSupply.write('0');
  powerSupply.write('2');
  powerSupply.write('8');
  powerSupply.write('B');
  //Reference Voltage
  powerSupply.write(voltage[0]);
  powerSupply.write(voltage[1]);
  powerSupply.write(voltage[2]);
  powerSupply.write(voltage[3]);
  //Reference Temperature
  powerSupply.write(temperature[0]);
  powerSupply.write(temperature[1]);
  powerSupply.write(temperature[2]);
  powerSupply.write(temperature[3]);
  //ETX
  powerSupply.write(0x03);
  //checksum
  powerSupply.write(hexChecksum[1]);
  powerSupply.write(hexChecksum[2]);
  //CR
  powerSupply.write(0x0D);

  powerSupply.flush();//makes sure to wait until everything written
  
  GetResponse("Parameter Set response: ", powerSupply);
  
  delay(1000);
}

void hrtCommand(const SoftwareSerialParity& powerSupply)
{
  //Checking the set parameters of the power supply
  //STX
  powerSupply.write(0x02);
  //HRT
  powerSupply.write('H');
  powerSupply.write('R');
  powerSupply.write('T');
  //ETX
  powerSupply.write(0x03);
  //checksum
  powerSupply.write('F');
  powerSupply.write('3');
  //CR
  powerSupply.write(0x0D);

  powerSupply.flush();//makes sure to wait until everything written

  delay(1000);

  char hexQuadCoeff1[5] = "....";
  char hexQuadCoeff2[5] = "....";
  char hexLinCoeff1[5] = "....";
  char hexLinCoeff2[5] = "....";
  char hexRefVolt[5] = "....";
  char hexRefTemp[5] = "....";

  //Getting response
  while (powerSupply.read() != 't'); //sync with start of message
  powerSupply.readBytes(hexQuadCoeff1, 4);
  powerSupply.readBytes(hexQuadCoeff2, 4);
  powerSupply.readBytes(hexLinCoeff1, 4);
  powerSupply.readBytes(hexLinCoeff2, 4);
  powerSupply.readBytes(hexRefVolt, 4);
  powerSupply.readBytes(hexRefTemp, 4);
  while (powerSupply.read()!=0x0D);

  //convert hex to decimal
  long int decQuadCoeff1 = strtol(hexQuadCoeff1, NULL, 16);
  long int decQuadCoeff2 = strtol(hexQuadCoeff2, NULL, 16);
  long int decLinCoeff1 = strtol(hexLinCoeff1, NULL, 16);
  long int decLinCoeff2 = strtol(hexLinCoeff2, NULL, 16);
  long int decRefVolt = strtol(hexRefVolt, NULL, 16);
  long int decRefTemp = strtol(hexRefTemp, NULL, 16);

  //convert decimal to actual value with conversions from command reference
  float quadCoeff1 = decQuadCoeff1*QuadTempCoeffConversion;
  float quadCoeff2 = decQuadCoeff2*QuadTempCoeffConversion;
  float linCoeff1 = decLinCoeff1*LinTempCoeffConversion;
  float linCoeff2 = decLinCoeff2*LinTempCoeffConversion;
  float refVolt = decRefVolt*VoltConversion;
  float refTemp = (1.035 - decRefTemp*1.907e-5)/(5.5e-3);
  
  Serial.print("Quadratic temperature correction coefficients: ");
  Serial.print(quadCoeff1); Serial.print(", "); Serial.print(quadCoeff2); Serial.println();
  
  Serial.print("Linear temperature correction coefficients: ");
  Serial.print(linCoeff1); Serial.print(", "); Serial.print(linCoeff2); Serial.println();

  Serial.print("Reference Voltage: ");
  Serial.print(refVolt); Serial.println();

  Serial.print("Reference Temperature: ");
  Serial.print(refTemp); Serial.println();

  delay(1000);
}

void hpoCommand(const SoftwareSerialParity& powerSupply)
{

//Writing command to get info and status of power supply one
  powerSupply.write(0x02);
  powerSupply.write('H');
  powerSupply.write('P');
  powerSupply.write('O');
  powerSupply.write(0x03);
  powerSupply.write('E');
  powerSupply.write('C');
  powerSupply.write(0x0D);
  powerSupply.flush();//wait for data to transmit
  delay(1000);

  char hexStatus[5] = "....";
  char hexReserve[5] = "....";
  char hexOutVolt[5] = "....";
  char hexOutCurr[5] = "....";
  char hexTemp[5] = "....";

  //Getting response
  while(powerSupply.read() != 'o');
  powerSupply.readBytes(hexStatus, 4);
  powerSupply.readBytes(hexReserve, 4);
  powerSupply.readBytes(hexOutVolt, 4);
  powerSupply.readBytes(hexOutCurr, 4);
  powerSupply.readBytes(hexTemp,4);
  while(powerSupply.read() != 0x0D);

  long int decOutVolt = strtol(hexOutVolt, NULL, 16);
  long int decOutCurr = strtol(hexOutCurr, NULL, 16);
  long int decTemp = strtol(hexTemp, NULL, 16);

  float outVolt = decOutVolt*VoltConversion;
  float outCurr = decOutCurr*CurrConversion;
  float Temp = (1.035 - decTemp*1.907e-5)/(5.5e-3);
  
  Serial.print("Output Voltage: "); Serial.println(outVolt);
  Serial.print("Output Current: "); Serial.println(outCurr);
  Serial.print("Temperature: "); Serial.println(Temp);
  
}

void hgsCommand(const SoftwareSerialParity& powerSupply)
{
  //get status
  //STX
  powerSupply.write(0x02);
  //HGS
  powerSupply.write(0x48);
  powerSupply.write(0x47);
  powerSupply.write(0x53);
  //ETX
  powerSupply.write(0x03);
  //checksum - fixed value in this case!
  powerSupply.write(0x45);
  powerSupply.write(0x37);
  //CR
  powerSupply.write(0x0D);

  powerSupply.flush();//makes sure to wait until everything written

  GetResponse("Status response: ", powerSupply);
}

void hreCommand(const SoftwareSerialParity& powerSupply)
{
  //Reset command
  //STX
  powerSupply.write(0x02);
  //HRE
  powerSupply.write('H');
  powerSupply.write('R');
  powerSupply.write('E');
  //ETX
  powerSupply.write(0x03);
  //checksum - fixed value in this case!
  powerSupply.write('E');//E
  powerSupply.write('4');//4
  //CR
  powerSupply.write(0x0D);
  
  powerSupply.flush();//makes sure to wait until everything written

  GetResponse("Reset Command: ", powerSupply);
  
}


void GetResponse(String command, const SoftwareSerialParity& powerSupply)
{
  
  delay(1000);//needs to be ~1sec
  
  Serial.println(command);
  //Getting response
  powerSupply.listen();
  while (powerSupply.available() > 0)
   {
     char inbyt = powerSupply.read();
     Serial.write(inbyt);
   }
  Serial.println();
  Serial.println();
}
