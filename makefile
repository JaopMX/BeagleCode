helloworld: helloworld.c
	${gccbeagle} helloworld.c -o helloworld

clean:
	rm helloworld

transfer:
	scp helloworld debian@192.168.7.2:/home/debian/

gpiotest:
	${gccbeagle} -c gpio.c
	${gccbeagle} -c gpio_test.c
	${gccbeagle} -o gpio_test gpio_test.o gpio.o
	scp gpio_test debian@192.168.7.2:/home/debian/

gpiopy:
	scp gpio_python.py debian@192.168.7.2:/home/debian/

udpclient:
	${gccbeagle} udpclient.c -o udpclient
	scp udpclient debian@192.168.7.2:/home/debian/

udpmessage:
	${gccbeagle} udpmessage.c -o udpmessage
	scp udpmessage debian@192.168.7.2:/home/debian/

udptest:
	${gccbeagle} -c udpmessage.c
	${gccbeagle} -c udp_test.c
	${gccbeagle} -o udp_test udp_test.o udpmessage.o
	scp udp_test debian@192.168.7.2:/home/debian/

controller:
	${gccbeagle} -c udpmessage.c
	${gccbeagle} -c gpio.c
	${gccbeagle} -c controller.c
	${gccbeagle} -o controller controller.o udpmessage.o gpio.o
	scp controller debian@192.168.7.2:/home/debian/

controller_python:
	scp controller_python.py debian@192.168.7.2:/home/debian/