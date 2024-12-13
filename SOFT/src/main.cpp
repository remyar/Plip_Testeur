#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire, -1);

volatile bool trigger = false;
uint16_t nbBits = 0;
bool bits[3][24];
uint8_t frameNumber = 0;

unsigned long _ms = millis();
int8_t E[10];
uint8_t testTab[5];
String code = "";
bool success = false;
unsigned long time;
uint8_t state = 0;

enum
{
    NO_STATE = 0,

};

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

void _ISR() // ISR function excutes when push button at pinD2 is pressed
{
    trigger = true;
}

void _PowerKey(bool val)
{
    pinMode(A1, OUTPUT);
    digitalWrite(A1, val);
}

void _Rcos(bool val)
{
    pinMode(A0, OUTPUT);
    digitalWrite(A0, val);
}

void _Prog(bool val)
{
    pinMode(10, OUTPUT);
    digitalWrite(10, val);
}

void _SerClk(bool val)
{
    pinMode(9, OUTPUT);
    digitalWrite(9, val);
}

void setup()
{
    pinMode(2, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);
    pinMode(12, OUTPUT);
    digitalWrite(12, LOW);
    // put your setup code here, to run once:
    attachInterrupt(digitalPinToInterrupt(3), _ISR, RISING);

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
    display.clearDisplay();
    display.display();

    // text display tests
    display.setCursor(0, 16);
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);

    display.print("    Plip\n   Reader");

    display.setCursor(32, 0);
    display.setTextSize(1);
    display.print("  AR' Tech");

    /*   display.print("connected!");
      display.println("IP: 10.0.1.23");
      display.println("Sending val #0");
      display.setCursor(0,0);*/
    display.display(); // actually display all of the above

    Serial.begin(115200);

    Serial.println("AR'Tech");
    Serial.println("Plip Testeur");

    trigger = false;
    success = false;
    nbBits = 0;
    frameNumber = 0;
    _ms = millis();

    //-- try programming key

    _Prog(true);
    _Rcos(false);
    _SerClk(false);

    _PowerKey(true);
    delayMicroseconds(10000);

    for (uint8_t i = 0; i < 24; i++)
    {
        _SerClk(true);

        delayMicroseconds(10);
        _SerClk(false);
        delayMicroseconds(10);
    }

    delay(10);
    _PowerKey(false);
    _Prog(false);
    pinMode(A0, INPUT);
}

void loop()
{
    if (trigger == true)
    {
        digitalWrite(12, HIGH);
        trigger = false;
        delayMicroseconds(1250);
        bits[frameNumber][nbBits] = !trigger;

        nbBits++;
        if (nbBits >= 24)
        {
            nbBits = 0;
            frameNumber++;
        }
        _ms = millis();
        trigger = false;
        digitalWrite(12, LOW);
    }

    if ((millis() - _ms) >= 100)
    {
        if (frameNumber >= 3)
        {
            success = true;
            for (int i = 0; i < 24; i++)
            {
                if ((bits[0][i] != bits[1][i]) || (bits[0][i] != bits[2][i]) || (bits[1][i] != bits[2][i]))
                {
                    success = false;
                }
            }

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
                display.clearDisplay();
                display.setCursor(0, 0);
                display.setTextSize(2);
                display.print(" Code clef");

                display.setCursor(0, 24);
                display.setTextSize(2);
                display.print("   ");
                for (int i = 0; i < 10; i += 2)
                {
                    display.print(decode_2(E[i], E[i + 1]));
                }

                display.setCursor(0, 52);
                display.setTextSize(1);
                display.print("  Code reco : ");
                display.print(bits[0][1]);
                display.print(bits[0][2]);
                display.print(bits[0][3]);
                display.println(bits[0][4]);

                display.display(); // actually display all of the above

                Serial.println("");
                Serial.print("Code clef : ");

                for (int i = 0; i < 10; i += 2)
                {
                    Serial.print(decode_2(E[i], E[i + 1]));
                }
                Serial.println("");
                Serial.print("Code reco : ");
                Serial.print(bits[0][1]);
                Serial.print(bits[0][2]);
                Serial.print(bits[0][3]);
                Serial.println(bits[0][4]);
            }
            else
            {
                Serial.println("ERROR !!!");
            }
        }

        uint8_t val8 = digitalRead(2) << 1;
        val8 |= digitalRead(4);

        if (val8 == 0x1 || val8 == 0x2)
        {
            display.clearDisplay();
            display.setCursor(0, 0);
            display.setTextSize(2);
            display.print(" Reception ");
            display.setCursor(0, 32);
            display.setTextSize(2);
            display.print("  ");
            if (val8 == 0x01)
            {
                display.print("ouvert");
            }
            else
            {
                display.print("fermer");
            }
            display.display(); // actually display all of the above
        }

        nbBits = 0;
        frameNumber = 0;
        trigger = false;
        _ms = millis();
    }
}