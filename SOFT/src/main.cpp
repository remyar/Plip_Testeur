#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>

bool trigger = false;
uint16_t nbBits = 0;
bool bits[3][24];
uint8_t frameNumber = 0;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // LCD Shield

String code = "";
void _ISR() // ISR function excutes when push button at pinD2 is pressed
{
    if (!digitalRead(3))
    {
        trigger = true;
        delayMicroseconds(1250);
        digitalWrite(12, HIGH);
        delayMicroseconds(5);
        bits[frameNumber][nbBits] = digitalRead(3);
        nbBits++;
        if (nbBits >= 24)
        {
            nbBits = 0;
            frameNumber++;
        }
        digitalWrite(12, LOW);
    }
}

void setup()
{
    pinMode(3, INPUT_PULLUP);
    // put your setup code here, to run once:
    attachInterrupt(digitalPinToInterrupt(3), _ISR, CHANGE);
    pinMode(12, OUTPUT);

    Serial.begin(9600);

    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    GoodRace    ");
    Serial.println("GoodRace");
    lcd.setCursor(0, 1);
    lcd.print("  Plip Testeur  ");
    Serial.println("Plip Testeur");
    delay(5000);
    lcd.clear();
    nbBits = 0;
    frameNumber = 0;
}

int8_t decode(uint8_t idx)
{
    int8_t val = -1;
    bool bit0 = bits[0][(idx * 2)];
    bool bit1 = bits[0][(idx * 2) + 1];

    if ((bit0 == true) && (bit1 == false))
    {
        val = 0;
    }
    else if ((bit0 == true) && (bit1 == true))
    {
        val = 1;
    }

    return val;
}

uint8_t decode_2(int8_t E0, int8_t E1)
{
    uint8_t val = 9;
    if (E0 == 0 && E1 == 0)
    {
        val = 4;
    }
    else if (E0 == -1 && E1 == 0)
    {
        val = 1;
    }
    else if (E0 == 1 && E1 == 0)
    {
        val = 7;
    }
    else if (E0 == 0 && E1 == -1)
    {
        val = 3;
    }
    else if (E0 == -1 && E1 == -1)
    {
        val = 0;
    }
    else if (E0 == 1 && E1 == -1)
    {
        val = 6;
    }
    else if (E0 == 0 && E1 == 1)
    {
        val = 5;
    }
    else if (E0 == -1 && E1 == 1)
    {
        val = 2;
    }
    else if (E0 == 1 && E1 == 1)
    {
        val = 8;
    }
    return val;
}

void loop()
{
    // put your main code here, to run repeatedly:
    if (trigger)
    {
        delay(250);
        nbBits = 0;
        frameNumber = 0;
        bool success = true;
        for (int i = 0; i < 24; i++)
        {
            if ((bits[0][i] != bits[1][i]) || (bits[0][i] != bits[2][i]) || (bits[1][i] != bits[2][i]))
            {
                success = false;
            }
        }

        int8_t E[10];

        lcd.setCursor(0, 0);
        lcd.print("                ");
        lcd.setCursor(0, 0);
        
        if (success)
        {
            Serial.println("");

            for (int i = 0; i < 10; i++)
            {
                E[i] = decode(i);
            }

            uint8_t testTab[5];
            for (int i = 0; i < 10; i += 2)
            {
                testTab[(i / 2)] = decode_2(E[i], E[i + 1]);
            }
            if (testTab[0] == 8 && testTab[1] == 8 && testTab[2] == 8 && testTab[3] == 8 && testTab[4] == 8)
            {
                success = false;
            }
            if (testTab[0] == 0 && testTab[1] == 0 && testTab[2] == 0 && testTab[3] == 0 && testTab[4] == 0)
            {
                success = false;
            }
        }
        if (success)
        {
            Serial.println("");
            Serial.print("Code clef : ");
            lcd.print("Code clef: ");

            for (int i = 0; i < 10; i += 2)
            {
                Serial.print(decode_2(E[i], E[i + 1]));
                lcd.print(decode_2(E[i], E[i + 1]));
            }
            Serial.println("");
            Serial.print("Code reco : ");
            Serial.print(bits[0][1]);
            Serial.print(bits[0][2]);
            Serial.print(bits[0][3]);
            Serial.println(bits[0][4]);

            lcd.setCursor(0, 1);
            lcd.print("Code reco: ");
            lcd.print(bits[0][1]);
            lcd.print(bits[0][2]);
            lcd.print(bits[0][3]);
            lcd.print(bits[0][4]);
        }
        else
        {
            Serial.println("ERROR !!!");
            lcd.print("ERROR !!!");
        }
        trigger = false;
    }
}