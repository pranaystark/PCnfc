# PCnfc
For many days I have been curious about making a device that unlocks my pc using a smartphone. I have been looking for ways to unlock the machine. I have tested messenger bots sends HTTP requests, I tested BLE protocols but one day I have stumbled upon #NFC payment interface. I personally use #iphone, it uses #applepay to emulate cards so, I started researching about its functionality and I started to interface required components to read it values, I strangely encountered that these payment interfaces always generates a new set of serial numbers every single time. That's fascinating.

I started to gather related code examples and worked on them.  I noticed a common thing in those serial numbers. The first two digits of every serial number is always the same so, I came up with a logic that only accepts those two digits and triggers a #ducky script that injects keystrokes.

I could have used a lightweight microcontroller like #arduino but I still wanted to experiment with #wifi based controllers like #esp8266.

I have made this project #opensource feel free to check it out, any comments and changes are highly appreciated.

Disclaimer. Except NFC tag use remaining possible usage demonstrated in the video. NFCta tag is not a secure method of unlocking 
#apple #alexa #amazon #espressif 
# **Do not use it for any security related applications!**


## Requirements
You have to install Arduino IDE 1.6.10 or later. Links are listed below.
* **Arduino** > **Preferences** > "Additional Boards Manager URLs:" and add: **http://arduino.esp8266.com/stable/package_esp8266com_index.json** and for programmming Attiny85 add this **http://digistump.com/package_digistump_index.json** also.
* **Arduino** > **Tools** > **Board** > **Boards Manager** > type in **ESP8266** and install the board
* Download MFRC522 library and extract to Arduino library folder or you can use "Library Manager" on the IDE itself to install the MFRC522 library.
* Realy 5v
* ATtiny85


### Download Links
* [Arduino IDE](https://www.arduino.cc/en/Main/Software) - The development IDE
* [ESP8266 Core for Arduino IDE](https://github.com/esp8266/Arduino) - ESP8266 Core
* [MFRC522 Library](https://github.com/miguelbalboa/rfid) - MFRC522 RFID Library
* [Digistump Attiny85 Library](https://github.com/digistump/DigistumpArduino) - Digistump Library (Attiny85)



### Wiring RFID RC522 module
The following table shows the typical pin layout used:

| Signal        | MFRC522       | WeMos D1 mini  | NodeMcu | Generic      |
|---------------|:-------------:|:--------------:| :------:|:------------:|
| RST/Reset     | RST           | D3 [1]         | D3 [1]  | GPIO-0 [1]   |
| SPI SS        | SDA [3]       | D8 [2]         | D8 [2]  | GPIO-15 [2]  |
| SPI MOSI      | MOSI          | D7             | D7      | GPIO-13      |
| SPI MISO      | MISO          | D6             | D6      | GPIO-12      |
| SPI SCK       | SCK           | D5             | D5      | GPIO-14      |

* Connect relay IN pin to D8 on ESP
and i have ripped USB cables negative lead as demonstrated in this figure
![Capture](https://user-images.githubusercontent.com/13132083/109596721-e7c30680-7b6a-11eb-9b86-cb8a10c73835.PNG)


Security
-------
* The **UID** of a card **can not be used** as an unique identification for security related projects. Some Chinese cards allow to change the UID which means you can easily clone a card. For projects like *access control*, *door opener* or *payment systems* you **must implement** an **additional security mechanism** like a password or normal key.

* This library does not offer 3DES or AES authentication used by cards like the Mifare DESFire, it may be possible to be implemented because the datasheet says there is support. We hope for pull requests :).


License
-------
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to https://unlicense.org/

<a href="https://www.buymeacoffee.com/pranaystark" target="_blank"><img src="https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png" alt="Buy Me A Coffee" style="height: 41px !important;width: 174px !important;box-shadow: 0px 3px 2px 0px rgba(190, 190, 190, 0.5) !important;-webkit-box-shadow: 0px 3px 2px 0px rgba(190, 190, 190, 0.5) !important;" ></a>
