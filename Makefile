make:
	g++ -Wall -std=c++11 server.cpp Client.cpp functions.cpp GpioOpt.cpp -o server -lwiringPi

clean:
	rm server
