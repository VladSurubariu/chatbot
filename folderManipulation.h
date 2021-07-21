#pragma once
#include "pathSetter.h"

void createNewFolder(std::string auxDirector, std::string newFolderName){
    auxDirector=auxDirector+"\\";
    auxDirector=auxDirector+newFolderName;

    char pathToCreate[auxDirector.size()+1];
    strcpy(pathToCreate, auxDirector.c_str());
    _mkdir(pathToCreate);
}

bool searchFolder(std::string auxNumeFolder){
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

void createAnswerFolder(std::string wordFromSentence){
    bool folderCheck=searchFolder(wordFromSentence);
    if(folderCheck==0){
        createNewFolder(searchingPath, wordFromSentence);
    }
}

