#include <includes.h>
#include <scripts/distribution.h> //User script

String msg = "";

class ScanParser : public HIDReportParser {
  public:
    ScanParser();
    void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
  protected:
    uint8_t KeyToAscii(bool upper, uint8_t mod, uint8_t key);
    virtual void OnKeyScanned(bool upper, uint8_t mod, uint8_t key);
    virtual void OnScanFinished();
};

ScanParser::ScanParser() {}

void ScanParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
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

uint8_t ScanParser::KeyToAscii(bool upper, uint8_t mod, uint8_t key) {
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

void ScanParser::OnKeyScanned(bool upper, uint8_t mod, uint8_t key) {
  uint8_t ascii = KeyToAscii(upper, mod, key);
  msg += (char)ascii;
}

void ScanParser::OnScanFinished() {
  if(script(msg)) {
    msg = "";
  } else {
    Keyboard.end();
  }
}

USB          Usb;
USBHub       Hub(&Usb);
HIDUniversal Hid(&Usb);
ScanParser     Parser;

void setup() {
  if (Usb.Init() == -1) {Keyboard.print("No Scanner Detected");}

  delay( 200 );

  Hid.SetReportParser(0, &Parser);

  Keyboard.begin();
}

void loop() {
  Usb.Task();
}