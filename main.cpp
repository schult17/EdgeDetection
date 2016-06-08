#include <iostream>

#ifdef __cplusplus      //include the jpeg library as a C file.
extern "C"{
#endif
#include </usr/local/libjpeg-9b/include/jpeglib.h>
#ifdef __cplusplus
}
#endif

using namespace std;

int main(int argc, char* argv[])
{
	cout << "This is Tanner's edge detection program" << endl;	
	return 0;
}
