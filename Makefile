all: hexwrite hexdump

hexwrite: hexwrite.cpp

hexdump: hexdump.cpp

clean:
	rm -rf hexdump
	rm -rf hexwrite
