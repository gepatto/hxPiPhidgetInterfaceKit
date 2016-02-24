#PhidgetInterfaceKit Extension for OpenFL

This is extension is an attempt to allow the use of an [Phidgets 888 USB interface](http://www.phidgets.com/products.php?category=0&product_id=1018_2)  
that enables you to read an write to 8 digital inputs and outputs and read from 8 analog inputs.

Only Tested on The Raspberry Pi 2 with haxe 3.2.1

![Phidgets 888](http://www.phidgets.com/images/1018_2_Web.jpg)


**Requirements**

- libphidget-2.1.8.20150410
- libusb-dev
- udev rule 30-phidget.rules from dependencies folder installed (copied to) to /etc/udev/rules.d/