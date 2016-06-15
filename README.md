# EdgeDetection

Creator:	Tanner Young-Schultz
Date:		7 June, 2016

C++ implementation of common edge detection algorithms in DSP

Directories and Files:
	/src				All of the C++ source files
	
	/h				All of the C++ header files
	
	/test_images			A few test bitmap images for testing
		lena512.bmp		8-bit grayscale test image
		airplane.bmp		24-bit RGB test image
		baboon.bmp		24-bit RGB test image
		
	makefile		Makefile used by 'make' utility (You must have make installed)
	input.txt		A simple text file to pass input to the program using '< input.txt'
	README.md		This file


Building and Executing:
Using the input file 'input.txt', a nice test is to run these commands from the EdgeDetection directory with the make file 'makefile':

	make
	./edgedetection < input.txt
	

Limitations:

BMPImage:

-Supports 8-Bit grayscale and 24-Bit RGB pixel types. A message will be printed if you provide an image that does not use one of these formats.

-Does not support any bitmap compression/decompression. A message will be printed if you provide an image that is compressed

-The user must check if the file read was 8-bit or 24-bit (automatically detected by the class) when using the class to determine
 whether to use a GrayPixel8 (8-bit gray scale) or RGBPixel24 (24-bit rgb value). Both of these pixel types are subclasses of
 BMPPixel.
