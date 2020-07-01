# Scanner Macro Pro V2
Takes USB input from a barcode scanner and sends the message to the computer with customizable macros.

### Current Build
[![Build Status](https://travis-ci.com/oschwartz10612/Scanner-Macro-Pro-V2.svg?branch=master)](https://travis-ci.org/oschwartz10612/Scanner-Macro-Pro-V2)

## Install Dependencies
Download and install [platformio](https://docs.platformio.org/en/latest/core/installation.html).

Download the repository.

## How to pick a script?

In the src/main.cpp file change the .h file in the following line to one of the below.

```cpp
#include <scripts/distribution.h> //User script
```

`distribution.h`

`pxiFCPSON.h`

`pxiID.h`

`rackLocation.h`

`rackLocationFCPSON.h`

`rackLocationLOANER.h`

Short descriptions of the scripts can be found at the top of the scripts in the src/scripts folder.

## How to upload?

Save main.cpp.

Run upload.bat with your computer connected to the Arduino (bottom) board.
