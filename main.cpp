#include <iostream>
#include <direct.h>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <string>

using namespace std;

//string aux;

void searchFolder(string aux){
    //char auxC[aux.size()+1];
    //strcpy(auxC, aux.c_str());
    //cout<<auxC;
    char pathbuffer[_MAX_PATH];
    char searchfile[aux.size()+1];
    strcpy(searchfile, aux.c_str());
    char envvar[] = "PATH";
    errno_t err;

    /* Search for file in PATH environment variable: */
    err = _searchenv_s( searchfile, envvar, pathbuffer, _MAX_PATH );
    if (err != 0)
    {
        printf("Error searching the path. Error code: %d\n", err);
    }
    if( *pathbuffer != '\0' )
        printf( "Path for %s:\n%s\n", searchfile, pathbuffer );
    else
        printf( "%s not found\n", searchfile );

}

int main(){
    //(D:\Proiecte\c++\Conti Challenge\Chatbot\Conversatie //path
    _chdir(R"(D:\Proiecte\c++\Conti Challenge\Chatbot)"); //changing the working folder
    string aux="Conversatie";
    searchFolder(aux);


    return 0;
}
