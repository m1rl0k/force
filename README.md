# force


These files are based on my research with Force, in newtons using Arduino, - and Piezo Electric fabric known as Eeyonex.
The project was hand-crafted material using silver threads as wires to the arduino both analog and digital sensors, using smoothing buffering and a butterworth low-pass filter written in C++, as well as processing sketch to simulate the interaction in real time 3D representation along the physical and software models. 
The arduino was updated with sketches OTA - Over the AIR using BLUETOOTH 4.1 stack. (Provided by Texas Instruments) - 
All sensors crafted were connected to "A1" or "D1" for analog or digital pins.

The force voltage was modified to match that of the actual battery, and resistance was calculated to be a dynamic variable to give accurate newton readings on fabric, while the resistance changed, as the material moved through space.

As newtons reached a certain threshhold, they were either counted as individual hits (physical hits to the material), indicated by either a red, yellow or green light depending on the amount of FORCE, Given a sound tone emitted through a piezo-buzzer, and /or transmitted in numerical value the actual amount of FORCE via bluetooth to both 3D models in processing, and eventually to an iOS app written in swift. Simultaineously the device was able to handle all of these functions within the same loop, seamlessly.


A 9DOF accelerometor, magnetormeter, and gyroscope were used to embed actual absolute orientation on a scientific level in all studies. This matched real world orientation and positioning in motion, while the serial output was mapped to a 3d processing sketch ran along side the device to give display.

This concludes the research of 5+ years with the ATmega32 processor, several conductive fabrics and materials, the iteration of the butterworth low-pass filter at the beginning of the C++ Loop, various smoothing techniques and buffering of real time data, passed via Bluetooth, and marks as a success that all theories presented and questioned by the author were met.

