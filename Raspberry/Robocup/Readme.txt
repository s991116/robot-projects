Bygges fra build folder med kommandoerne
cmake ..
make

For Raspberry kræves at Rasperry har RaspiCam modullet. Det er sat til at ligge på
 ~/git/robidouille/raspicam_cv
 ~/git/raspberrypi/userland/build/lib
 
For at compilere uden dette skal cmake kaldes med
cmake -DCAMERA_MOCK=ON ..