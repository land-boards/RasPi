/* ========================================
 *
 * Copyright LAND BOARDS, LLC, 2019
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Land Boards.
 *
 * Menu for the card testing software
 *
 * ========================================
*/

#include "RPI_PSOC5.h"
#include <project.h>

uint8 receiveBuffer[80];
uint8 receiveBufferPtr;
uint8 gotCRorLF;
uint16 cardType = UNSELECTED_CARD;

////////////////////////////////////////////////////////////////////////////
// void printMenu(void) - Print the menu

void printMenuOptions(void)
{
    putStringToUSB("\n\rLand Boards, LLC - RPi Card Test Station\n\r");
    putStringToUSB("1 - Select RPP-UIO-16 Card\n\r");
    putStringToUSB("2 - Select RPPSOC Card\n\r");
    putStringToUSB("3 - Select RASPI-PLUS-GVS-CFG Card\n\r");
    putStringToUSB("4 - Select RASPI-GVS Card\n\r");
    putStringToUSB("5 - Select RASPI-PLUS-GVS Card\n\r");
    putStringToUSB("6 - Select RPI-I2C-HUB Card\n\r");
    putStringToUSB("7 - Select RPI-SPI8 Card\n\r");
    putStringToUSB("8 - Select SPI-POTX2 Card (via RPI-SPI8)\n\r");
    putStringToUSB("R - Read EEPROM\n\r");
    putStringToUSB("W - Write EEPROM\n\r");
    putStringToUSB("B - Bounce LED across Card GPIOs\n\r");
    putStringToUSB("T - Test Card\n\r");
    putStringToUSB("D - Debug Card\n\r");
    putStringToUSB("? - Print this menu\n\r");
}

////////////////////////////////////////////////////////////////////////////
// void psocMenu(void)
//	uint8 uartReadBuffer[USBUART_Buffer_SIZE];
//    uint16 uartReadBufferOff = 0;

void psocMenu(void)
{
    uint8 eepromBuffer[256];

    while (0u == USBUART_CDCIsReady());
    if ((receiveBuffer[0] == 'r') || (receiveBuffer[0] == 'R'))
    {
        putStringToUSB("Read from the EEPROM\n\r");
        readEEPROM(eepromBuffer);
        dumpEEPROM(eepromBuffer);
        while (0u == USBUART_CDCIsReady());
    }
    else if ((receiveBuffer[0] == 'w') || (receiveBuffer[0] == 'W'))
    {
        if (cardType == UNSELECTED_CARD)
        {
            putStringToUSB("Must first select card type\n\r");
        }
        else
        {
            putStringToUSB("Write to the EEPROM...");
            if (writeEEPROM(cardType) == 1)
                putStringToUSB("Completed EEPROM write\n\r");
            else
                putStringToUSB("EEPROM write failed (does this card have an EEPROM?\n\r");
        }
    }
    else if ((receiveBuffer[0] == 't') || (receiveBuffer[0] == 'T'))
    {
        if (cardType == UNSELECTED_CARD)
        {
            putStringToUSB("Must first select card type\n\r");
        }
        else if (cardType == RPII2CHUB)
        {
            putStringToUSB("Testing RPI-I2C-HUB input, please wait\n\r");
            test_RPII2CHUB();
            putStringToUSB("Completed Testing RPI-I2C-HUB input\n\r");
        }
        else if (cardType == RPISPI8)
        {
            putStringToUSB("Testing RPI-SPI8 input, please wait\n\r");
            testRPISPI8();
            putStringToUSB("Completed Testing RPI-SPI8 input\n\r");
        }
        else if (cardType == SPIPOTX2)
        {
            putStringToUSB("Testing SPI-POTX2 card (via RPI-SPI8), please wait\n\r");
            // test_SPI_POTX2();
            putStringToUSB("Completed Testing SPI-POTX2 card (via RPI-SPI8)\n\r");
        }
        else
        {
            putStringToUSB("Card not yet implemented\n\r");
        }
    }
    else if ((receiveBuffer[0] == 'b') || (receiveBuffer[0] == 'B'))
    {
        if (cardType == UNSELECTED_CARD)
        {
            putStringToUSB("Must first select card type\n\r");
        }
        else if (cardType == RPPGVSCFG)
        {
            putStringToUSB("Blinking the LEDs on the RasPI-PLUS-GVS-CFG card, please wait\n\r");
            testRPPUIO16();
            putStringToUSB("Completed blinking the LEDs on the RasPI-PLUS-GVS-CFG card\n\r");
        }
        else if (cardType == RASPIPLUSGVS)
        {
            putStringToUSB("Blinking the LEDs on the RASPI-PLUS-GVS card, please wait\n\r");
            testRPPGVS();
            putStringToUSB("Completed blinking the LEDs on the RASPI-PLUS-GVS card\n\r");
        }
        else if (cardType == RASPIGVS)
        {
            putStringToUSB("Blinking the LEDs on the RASPI-GVS card, please wait\n\r");
            testRASPIGVS();
            putStringToUSB("Completed blinking the LEDs on the RASPI-GVS card\n\r");
        }
        else if (cardType == RPPUIO16)
        {
            putStringToUSB("Blinking the LEDs on the RPP-UIO-16 card, please wait\n\r");
            testRPPUIO16();
            putStringToUSB("Completed blinking the LEDs on the RPP-UIO-16 card\n\r");
        }
        else if (cardType == RPII2CHUB)
        {
            putStringToUSB("Blinking the DIGIO-8 Card LEDs, please wait\n\r");
            bounceRPIHubLEDs();
            putStringToUSB("Completed blinking the LEDs\n\r");
        }
        else if (cardType == RPISPI8)
        {
            putStringToUSB("Blinking the RPI-SPI8 Card LEDs, hit ENTER to exit\n\r");
            testRPISPI8();
            putStringToUSB("Completed blinking the LEDs\n\r");
        }
        else if (cardType == SPIPOTX2)
        {
            putStringToUSB("Not supported\n\r");
        }
        
        else
        {
            putStringToUSB("Card not yet implemented\n\r");
        }
    }
    else if ((receiveBuffer[0] == 'd') || (receiveBuffer[0] == 'D'))
    {
        if (cardType == UNSELECTED_CARD)
        {
            putStringToUSB("Must first select card type\n\r");
        }
        else if (cardType == RPPGVSCFG)
        {
            putStringToUSB("Debugging the RasPI-PLUS-GVS-CFG card\n\r");
            debugRPPGVSCFG();
            putStringToUSB("Completed debugging the RasPI-PLUS-GVS-CFG card\n\r");
        }
        else if (cardType == RASPIPLUSGVS)
        {
            putStringToUSB("Debugging the RASPI-PLUS-GVS card\n\r");
            debugRPPGVS();
            putStringToUSB("Completed debugging the RASPI-PLUS-GVS card\n\r");
        }
        else if (cardType == RASPIGVS)
        {
            putStringToUSB("Debugging the RASPI-GVS card\n\r");
            debugRASPIGVS();
            putStringToUSB("Completed debugging the RASPI-GVS card\n\r");
        }
        else if (cardType == RPPUIO16)
        {
            putStringToUSB("Debugging the RPP-UIO-16 card\n\r");
            debugRPPUIO16();
            putStringToUSB("Completed debugging the RPP-UIO-16 card\n\r");
        }
        else if (cardType == RPII2CHUB)
        {
            putStringToUSB("Debugging the RPI-I2C-HUB card\n\r");
            debugRPIHub();
            putStringToUSB("Completed debugging the RPI-I2C-HUB Card\n\r");
        }
        else if (cardType == RPISPI8)
        {
            putStringToUSB("Debugging the RPI-SPI8 card\n\r");
            debugRPISPI8();
            putStringToUSB("Completed debugging the RPI-SPI8 Card\n\r");
        }
        else
        {
            putStringToUSB("Card not yet implemented\n\r");
        }
    }
    else if (receiveBuffer[0] == '1')
    {
        cardType = RPPUIO16;
        putStringToUSB("Selected RPP-UIO-16 card\n\r");
    }
    else if (receiveBuffer[0] == '2')
    {
        cardType = RPPSOC;
        putStringToUSB("Selected RPPSOC card\n\r");
    }
    else if (receiveBuffer[0] == '3')
    {
        cardType = RPPGVSCFG;
        putStringToUSB("Selected RASPI-PLUS-GVS-CFG card\n\r");
    }
    else if (receiveBuffer[0] == '4')
    {
        cardType = RASPIGVS;
        putStringToUSB("Selected RASPIGVS card\n\r");
    }
    else if (receiveBuffer[0] == '5')
    {
        cardType = RASPIPLUSGVS;
        putStringToUSB("Selected RASPI-PLUS-GVS card\n\r");
    }
    else if (receiveBuffer[0] == '6')
    {
        cardType = RPII2CHUB;
        putStringToUSB("Selected RPI-I2C-HUB card\n\r");
    }
    else if (receiveBuffer[0] == '7')
    {
        cardType = RPISPI8;
        putStringToUSB("Selected RPI-SPI8 card\n\r");
    }
    else if (receiveBuffer[0] == '8')
    {
        cardType = SPIPOTX2;
        putStringToUSB("Selected SPI-POTX2 card (vis RPI-SPI8)\n\r");
    }
    
    else
    {
        putStringToUSB("ERROR - Unrecognized option");
        printMenuOptions();
    }
    clearReceiveBuffer();
}

////////////////////////////////////////////////////////////////////////////
// void clearReceiveBuffer(void)

void clearReceiveBuffer(void)
{
    receiveBufferPtr = 0;
    receiveBuffer[0] = 0;
    gotCRorLF = 0;
}

////////////////////////////////////////////////////////////////////////////
// void addToReceiveBuffer(uint16, uint8 *)

void addToReceiveBuffer(uint16 inCount, uint8 * inBuffer)
{
    uint8 echoString[80];
    echoString[0] = 0;
    for (uint8 receiveCt = 0; receiveCt < inCount; receiveCt++)
    {
        // First check if the character is an end of line
        if ((inBuffer[receiveCt] == 0x0a) || (inBuffer[receiveCt] == 0x0d))
        {
            gotCRorLF = 1;
            putStringToUSB("\n\r");
        }
        // check if the character is not a RUBOUT and if the line length is OK
        else if ((inBuffer[receiveCt] != 0x7f) && (receiveCt < 80))
        {
            receiveBuffer[receiveBufferPtr] = inBuffer[receiveCt];
            receiveBufferPtr++;
            echoString[inCount] = 0;
            echoString[receiveCt] = inBuffer[receiveCt];
            echoString[receiveCt+1] = 0;
            putStringToUSB((char *)echoString);
        }
        // If the character is rubout and not the 0th character
        else if ((receiveBufferPtr > 0) && (inBuffer[receiveCt] == 0x7f))
        {
            receiveBufferPtr--;
            echoString[0] = 0x08;       // Backspace
            echoString[1] = 0x20;       // Space
            echoString[2] = 0x08;       // Backspace
            echoString[3] = 0;
            putStringToUSB((char *)echoString);
        }
    }
}

////////////////////////////////////////////////////////////////////////////
// void putStringToUSB(char *)

void putStringToUSB(char * stringToPutOutUSB)
{
    USBUART_PutData((uint8 *)stringToPutOutUSB, strlen(stringToPutOutUSB));
    while (0u == USBUART_CDCIsReady());
}

////////////////////////////////////////////////////////////////////////////
// asciiNibbleToVal(uint8)

uint32 asciiNibbleToVal(uint8 charVal)
{
    if ((charVal >= '0') && (charVal <= '9'))
        return (charVal-'0');
    else if ((charVal >= 'A') && (charVal <= 'F'))
        return (charVal-'A'+10);
    else if ((charVal >= 'a') && (charVal <= 'f'))
        return (charVal-'a'+10);
    return(0);
}

////////////////////////////////////////////////////////////////////////////
// uint32 extractLong(uint8 *)

uint32 extractLong(uint8 * commandString)
{
    uint8 linePtr = 1;
    uint32 rVal = 0;
    while ((commandString[linePtr] != 0) && (linePtr < 32) && (commandString[linePtr] != '\n') && (commandString[linePtr] != '\r'))
    {
        rVal <<= 4;
        rVal |= asciiNibbleToVal(commandString[linePtr]);
        linePtr++;
    }
    return (rVal);
}

/* [] END OF FILE */
