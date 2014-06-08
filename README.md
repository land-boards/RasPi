pi_iot
======

[land-boards](http://land-boards.com) - first foray into the Internet of Things using the Raspberry Pi.

* Light an LED.
* Read a switch.
* Do it all from a webpage.

Physical computing at its most basic.

## To Run
 - Ensure dependencies are installed.
 - Run
```
sudo ./web_server.py
```
 - Navigate to "localhost:5000/led" to control LED functionality
 - Navigate to "localhost:5000/switch" to check the state of the switch

# Steps to configure on a fresh Raspbian Pi
 - git clone  adafruit rasbperry_pi_python_code.git
 - sudo apt-get install python-rpi-gpio
 - sudo apt-get install python-pip
