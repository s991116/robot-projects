Bygges fra build folder med kommandoerne
cmake ..
make

For Raspberry kræves at Rasperry har RaspiCam modullet. Det er sat til at ligge på
 ~/git/robidouille/raspicam_cv
 ~/git/raspberrypi/userland/build/lib
 
For at compilere uden dette skal cmake kaldes med
cmake -DCAMERA_MOCK=ON ..

For Script som køres via RemoteControl se Readme.txt i Script folderen.

Robot Pins:

Motor Rotationsensor pinout:

RED    -> +5V
BLACK  -> Gnd
BROWN  -> Transistor_1 
RED    -> Common Transistor
YELLOW -> Transistor_2

Rotationsensor Splitcabel pinout:

A BLACK   -> PIN 1
A BROWN   -> PIN 2
A RED     -> PIN 4
A ORANGE  -> PIN 5
A YELLOW  -> PIN 6

B BLACK   -> PIN 1
B BROWN   -> PIN 2
B RED     -> PIN 3
B ORANGE  -> PIN 5
B YELLOW  -> PIN 7
