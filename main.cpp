#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <direct.h>
#include <cstdlib>

void searchFolder(std::string aux){
    char pathBuffer[_MAX_PATH];
    char searchFile[aux.size()+1];
    char envvar[]="PATH";
    errno_t error;

    strcpy(searchFile, aux.c_str());
    error=_searchenv_s(searchFile, envvar, pathBuffer, _MAX_PATH);
    if (error!=0){
        std::cout<<"Error number "<<error<<std::endl;
    }
    if (*pathBuffer !='\0'){
        std::cout<<"Folderul "<<searchFile<<" a fost gasit in "<<pathBuffer<<std::endl;
    }
    else{
        std::cout<<searchFile<<" was not found"<<std::endl;
    }
}

void createNewFolder(std::string aux){
    std::string newFolderName;
    std::cout<<"Introduceti numele noului folder: ";
    std::cin>>newFolderName;
    aux=aux+"\\";
    aux=aux+newFolderName;

    char pathToCreate[aux.size()+1];

    strcpy(pathToCreate, aux.c_str());

    if(_mkdir(pathToCreate)==0){
        std::cout<<"The folder has been created. The path is: "<<aux;
    }
    else{
            if(errno==2)
                std::cout<<"No such file or directory."<<std::endl;
            if(errno==17)
                std::cout<<"This folder already exists."<<std::endl;
        }
    }


int main(){
    //(D:\Proiecte\c++\Conti Challenge\Chatbot\Conversatie //path
    /*_chdir(R"(D:\Proiecte\c++\Conti Challenge\Chatbot)"); //path set
    std::string aux="Conversatie";
    searchFolder(aux);
    _chdir(R"(D:\Proiecte\c++\Conti Challenge\Chatbot\Conversatie)");
    aux="Salut";
    searchFolder(aux);
    */

    createNewFolder(R"(D:\Proiecte\c++\Conti Challenge\Chatbot\Conversatie)");

    return 0;
}
