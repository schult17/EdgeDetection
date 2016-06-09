#include <iostream>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include "JpegImage.h"
#include "stringhelpers.h"

using namespace std;

int main(int argc, char* argv[])
{
	string input = "";

	while(true)
	{
		cout << "Enter a file name (or path) to detect edges (JPEG format), or QUIT to exit" << endl;
		cout << ">> ";

		cin >> input;

		if( toLower(input) == "quit" )
			break;

		if( !endsWith( input, ".jpg" ) || endsWith( input, ".jpeg" ) )
		{
			cout << "Image file must be a JPEG format (.jpg, .jpeg)" << endl;
			continue;
		}

		JpegImage jpeg( input );
		jpeg.Decompress();
	}

	return 0;
}
