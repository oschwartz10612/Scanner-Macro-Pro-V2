#include <Arduino.h>
#include <hidboot.h>
#include <usbhub.h>
#include <SPI.h>

int msg1[100];
int msg1ptr = 0;

int msgCount = 0;

String msg1Prepend = "2390N";
int finishingMsg[] = {9, 9, 9, 111, 176, 176};

#define DELAYTIME 50

class KbdRptParser : public KeyboardReportParser {
  protected:
    void OnKeyPressed(uint8_t key);
};

USB     Usb;
//USBHub     Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);

KbdRptParser Prs;

void KbdRptParser::OnKeyPressed(uint8_t key) {
    Serial.print("ASCII: ");
    Serial.println((char)key);

    if (msgCount == 0) {
        if ((char)key != 9) {
            msg1[msg1ptr++] = (char)key;
        } else {
            Serial.print(msg1Prepend);
            for (int i = 0; i <= msg1ptr; i++) {
                Serial.print(msg1[i]);
                delay(DELAYTIME);
            }
            Serial.print("tab");
            msgCount++;
        }
    }

    if (msgCount == 1) {
        if ((char)key != 9) {
            Serial.print((char)key);
        } else {
            for (unsigned int i = 0; i <= sizeof(finishingMsg); i++) {
                Serial.print(finishingMsg[i]);
                delay(DELAYTIME);
            }
            msgCount++;
        }
    }
};

void setup() {
    Serial.begin(9600);
    while (!Serial);
    Serial.println("Start");

    if (Usb.Init() == -1)
        Serial.println("OSC did not start.");

  delay(200);

  HidKeyboard.SetReportParser(0, &Prs);
}

void loop() {
    Usb.Task();
}
