#include <iostream>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include "BasicEdgeDetector.h"
#include "BMPImage.h"
#include "stringhelpers.h"

using namespace std;

int main(int argc, char* argv[])
{
	string input = "";

	while(true)
	{
		cout << "Enter a file name (or path) to detect edges (BMP format), or QUIT to exit" << endl;
		cout << ">> ";

		cin >> input;

		if( toLower(input) == "quit" )
			break;

		if( !endsWith( input, ".bmp" ) )
		{
			cout << "Image file must be a BMP format (.bmp)" << endl;
			continue;
		}

		BMPImage bmp( input );
		BasicEdgeDetector edgy( &bmp );
		edgy.DetectEdges();
	}

	return 0;
}
