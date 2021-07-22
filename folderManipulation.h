// header-ul cu functiile pentru a crea foldere si pentru a scrie in ele

#pragma once
#include "pathSetter.h"


void createNewFolder(std::string auxDirector, std::string newFolderName){ //functie care creaza un folder nou
    auxDirector=auxDirector+"\\";
    auxDirector=auxDirector+newFolderName;

    char pathToCreate[auxDirector.size()+1];
    strcpy(pathToCreate, auxDirector.c_str());
    _mkdir(pathToCreate);
}

bool searchFolder(std::string auxNumeFolder){ //functia care cauta folderul cu numele auxNumeFolder in path-ul actual
    char pathBuffer[_MAX_PATH];
    char searchFile[auxNumeFolder.size()+1];
    char envvar[]="PATH";

    strcpy(searchFile, auxNumeFolder.c_str());
    errno_t error=_searchenv_s(searchFile, envvar, pathBuffer, _MAX_PATH);
    if (*pathBuffer !='\0'){
        return true;
    }
    else{
        return false;
    }
}

void createAnswerFolder(std::string wordFromSentence){ //functie care creaza fisierele txt
    bool folderCheck=searchFolder(wordFromSentence);
    if(folderCheck==0){
        createNewFolder(searchingPath, wordFromSentence);
    }
}
