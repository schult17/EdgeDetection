#include "helpers.h"
#include <iostream>
#include <sys/stat.h>

using namespace std;

bool endsWith( string str, string postfix )
{
        if( str.length() <= postfix.length() )
        {
                return false;
        }
        else
        {
                string::iterator str_it = str.end();
                string::iterator postfix_it = postfix.end();

                while( postfix_it != postfix.begin() )
                {
                        postfix_it--;
			str_it--;

                        if( *str_it != *postfix_it )
                                return false;
                }

                return true;
        }
}

string toLower( string str )
{
        //null terminated
        for( int i = 0; str[i]; i++ )
                str[i] = tolower(str[i]);

        return str;
}

bool fileExists( string filepath )
{
    struct stat dummy;
    
    return ( stat(filepath.c_str(), &dummy) == 0 );
}
