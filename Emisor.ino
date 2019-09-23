/**********************************************************************
** Descripción  : Transmite una secuencia de números (12345678) mas un           
**                identificador de mensaje CAN.
**                
**  Target       : Arduino UNO
**  ToolChain    : Arduino IDE 1.8.9 bajo Linux Debian
**  www.firtec.com.ar 
**********************************************************************/
#include <SPI.h>
#include <mcp_can.h>

const int spiCSPin = 10;

MCP_CAN CAN(spiCSPin);

void setup()
{
    Serial.begin(9600);

    while (CAN_OK != CAN.begin(CAN_500KBPS))
    {
        Serial.println(F("ERROR al iniciar CAN"));
        delay(100);
    }
    Serial.println(F("CAN BUS OK!"));
}

unsigned char stmp[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    
void loop()
{   
  Serial.println(F("Transmitiendo"));
  CAN.sendMsgBuf(0x01, 0, 8, stmp);	// Envía 8 carácteres en modo normal con ID 0x01
  delay(1000);
}
