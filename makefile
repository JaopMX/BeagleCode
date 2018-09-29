compile: helloworld.c
	${gccbeagle} helloworld.c -o helloworld

clean:
	rm helloworld

transfer:
	scp helloworld debian@192.168.7.2:/home/debian/