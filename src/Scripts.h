//Snippit for barcodes with student ids in PXI
bool barcodeAndId(String msg) {
    int delayTime = 50;
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
    }
    return true;
}

//Scanning into racks with "LOANER"
bool barcodeLoanerAndRack(String msg) {
    int delayTime = 50;
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
            Keyboard.print("LOANER");
            delay(delayTime);
            Keyboard.write(9); //TAB
            delay(delayTime);
            Keyboard.print(msg);
            delay(delayTime);
            Keyboard.write(9); //TAB
        } else {
            Keyboard.print(msg);
            Keyboard.write(9); //TAB
        }
    }
    return true;
}

//Just scan barcode and finish with "FCPSON" in PXI
bool FCPSON_finish(String msg) {
    int delayTime = 50;
    if (msg != "") {
        Keyboard.write(9); //TAB
        delay(delayTime);
        Keyboard.print("2390N");
        delay(delayTime);
        Keyboard.print(msg);
        delay(delayTime);
        Keyboard.write(9); //TAB
        delay(delayTime);
        Keyboard.print("FCPSON");
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
  return true;
}

//Scan the rack location to store in memory. Then scan ID and barcode.
String rack = "";
bool eFlag = false;
bool rackLocaton(String msg) {
    int delayTime = 50;
    if (msg != "") {
        //Check if it is a barcode by looking at the first two numbers
        for (unsigned int i = 0; i < sizeof(msg); i++) {
            if (isalpha(msg[i])) {
                rack = msg;
                if(String(msg[i]) == "e") {
                    eFlag = true;
                } else {
                    eFlag = false;
                }
                return true;
            }
        }


        bool barcode = false;
        for (int i = 0; i < 2; i++) {
            if (String(msg[i]) == "0") {
                barcode = true;
            } else {
                barcode = false;
            }
        }

        if(barcode) {
            Keyboard.print(msg);
            delay(delayTime);
            Keyboard.write(9); //TAB
            Keyboard.print(rack);
            if (eFlag) {
                Keyboard.print("-");
            }
            Keyboard.write(9); //TAB
        } else {
            Keyboard.print(msg);
            Keyboard.write(9); //TAB
        }
    }
    return true;
}
