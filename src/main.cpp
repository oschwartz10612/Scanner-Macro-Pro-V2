#include <usbhid.h>
#include <usbhub.h>
#include <hiduniversal.h>
#include <hidboot.h>
#include <SPI.h>
#include <Keyboard.h>

String msg;
int delayTime = 50;

class MyParser : public HIDReportParser {
  public:
    MyParser();
    void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
  protected:
    uint8_t KeyToAscii(bool upper, uint8_t mod, uint8_t key);
    virtual void OnKeyScanned(bool upper, uint8_t mod, uint8_t key);
    virtual void OnScanFinished();
};

MyParser::MyParser() {}

void MyParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
  // If error or empty, return
  if (buf[2] == 1 || buf[2] == 0) return;

  for (uint8_t i = 7; i >= 2; i--) {
    // If empty, skip
    if (buf[i] == 0) continue;

    // If enter signal emitted, scan finished
    if (buf[i] == UHS_HID_BOOT_KEY_ENTER) {
      OnScanFinished();
    }

    // If not, continue normally
    else {
      // If bit position not in 2, it's uppercase words
      OnKeyScanned(i > 2, buf, buf[i]);
    }

    return;
  }
}

uint8_t MyParser::KeyToAscii(bool upper, uint8_t mod, uint8_t key) {
  // Letters
  if (VALUE_WITHIN(key, 0x04, 0x1d)) {
    if (upper) return (key - 4 + 'A');
    else return (key - 4 + 'a');
  }

  // Numbers
  else if (VALUE_WITHIN(key, 0x1e, 0x27)) {
    return ((key == UHS_HID_BOOT_KEY_ZERO) ? '0' : key - 0x1e + '1');
  }

  return 0;
}

void MyParser::OnKeyScanned(bool upper, uint8_t mod, uint8_t key) {
  uint8_t ascii = KeyToAscii(upper, mod, key);
  msg += (char)ascii;
}

void MyParser::OnScanFinished() {
  if (msg != "") {
    //Check if it is a barcode by looking at the first two numbers
    bool barcode = false;
    for (int i = 0; i < 2; i++) {
      if (String(msg[i]) == "0") {
        barcode = true;
      } else {
        barcode = false;
      }
    }
    
    if(barcode) {
      Keyboard.write(9); //TAB
      delay(delayTime);
      Keyboard.print("2390N");
      delay(delayTime);
      Keyboard.print(msg);
      delay(delayTime);
      Keyboard.write(9); //TAB
    } else {
      Keyboard.print(msg);
      delay(delayTime);
      Keyboard.write(9); //TAB
      delay(delayTime);
      Keyboard.write(9); //TAB
      delay(delayTime);
      Keyboard.write(9); //TAB
      delay(delayTime);
      Keyboard.write(111); //o
      delay(delayTime);
      Keyboard.write(176); //Enter
      delay(delayTime);
      Keyboard.write(176); //Enter
    }
    
    msg = "";
  }
}

USB          Usb;
USBHub       Hub(&Usb);
HIDUniversal Hid(&Usb);
MyParser     Parser;

void setup() {
  Keyboard.begin();

  if (Usb.Init() == -1) {Keyboard.print("No Scanner Detected");}

  delay( 200 );

  Hid.SetReportParser(0, &Parser);
}

void loop() {
  Usb.Task();
}