#include <usbhid.h>
#include <usbhub.h>
#include <hiduniversal.h>
#include <hidboot.h>
#include <SPI.h>
#include <Keyboard.h>

#include <Parser.h>
#include <Scripts.h>

String msg;

void MyParser::OnKeyScanned(bool upper, uint8_t mod, uint8_t key) {
  uint8_t ascii = KeyToAscii(upper, mod, key);
  msg += (char)ascii;
}

void MyParser::OnScanFinished() {
  //barcodeAndId(msg);
  FCPSON_finish(msg);
}

USB          Usb;
USBHub       Hub(&Usb);
HIDUniversal Hid(&Usb);
MyParser     Parser;

void setup() {
  if (Usb.Init() == -1) {Keyboard.print("No Scanner Detected");}

  delay( 200 );

  Hid.SetReportParser(0, &Parser);

  Keyboard.begin();
}

void loop() {
  Usb.Task();
}