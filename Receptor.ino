/**********************************************************************
** Descripción  : Recibe una secuencia de números (12345678) mas un           
**                identificador de mensaje CAN desde un emisor CAN.
**                
**  Target       : Arduino NANO
**  ToolChain    : Arduino IDE 1.8.9 bajo Linux Debian
**  www.firtec.com.ar 
**********************************************************************/
#include <SPI.h>
#include "mcp_can.h"		// Biblioteca CAN
#include "LiquidCrystal.h"

// --- Inicia los pines de la pantalla LCD ---------
LiquidCrystal lcd(8,9,4,5,6,7);
const int spiCSPin = 10;		// Chip Set de placa CAN MCP2515
char buffer[10]=" ";			// Buffer para la conversión de ASCII
MCP_CAN CAN(spiCSPin);

void setup()
{
    lcd.begin(16,2);
    lcd.setCursor(2,0);
    lcd.print("Receptor CAN");
    lcd.setCursor(11,1);
    lcd.print("ID:");
    
    Serial.begin(9600);
    pinMode(ledPin,OUTPUT);

    while (CAN_OK != CAN.begin(CAN_500KBPS))	// Inicia placa CAN
    {
        Serial.println(F("CAN ERROR"));
        delay(100);
    }
    Serial.println(F("CAN BUS OK!"));
}


void loop()
{
    unsigned char len = 0;
    unsigned char buf[8];

    if(CAN_MSGAVAIL == CAN.checkReceive())  // Hay datos en el bus?
    {
        CAN.readMsgBuf(&len, buf);			// Recibir los datos en buf
        lcd.setCursor(0,1);
		for( int i = 0; i < 8; i++) {
			sprintf(buffer,"%d", buf[i]);	// Mostrar los datos en decimal
			lcd.print(buffer);
		}
        unsigned long canId = CAN.getCanId();	// Obtener el ID del mensaje
        lcd.setCursor(14,1);
        sprintf(buffer,"%02X", canId);		// Mostrar el ID en hexadecimal
        lcd.print(buffer);
    }
}
