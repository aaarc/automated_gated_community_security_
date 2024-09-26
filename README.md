# automated_gated_community_security
 A Automated Gated Community Security System which detects intruders and alerting users.a dual-module system for real-time trespasser detection and customizable passcodes, remotely managed via a web interface hosted on an ESP32 server 
 
there are 2 modules a gate module and an intruder detection module 

### Gate Module
-> follow the schematic and make the  connections, then before loading the program into the boards, open the code for esp32 and change details about the wifi network you want to connect to,(like username and password)(once the website is up and everything is running the esp32 will print its ip address, copy it and open it a device connected to the same network to access website to modify password)(note to host website in a way it can be accessed from everywhere you will need to port forward for this contact your isp)
-> connect the rx and tx of adruino uno to the rx,tx of esp32 to establish connection between them and so that the password updated in the website is accepted by the arduino, 

### Intruder Detection module
-> the receiver / hub node : this receives info from all other detection nodes and data from them is processed to understand near which part/ intruder detection node  has the trespassing occured 

### General instructions 
-> load the code into the respective boards ( upload the gate_module_ard_uno file in the Arduino Uno ) 

-> then connect the boards according to the given Schematic


