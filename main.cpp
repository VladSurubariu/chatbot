#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <direct.h>
#include <cstdlib>

std::string path;

std::string readUserAnswer(){
    std::string answer;
    std::getline(std::cin, answer);
    return answer;
}

void changeDirectory(std::string toAdd){
    path=path+"\\";
    path=path+toAdd;
    _chdir(path.c_str());
}

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
    errno_t error;

    strcpy(searchFile, auxNumeFolder.c_str());
    error=_searchenv_s(searchFile, envvar, pathBuffer, _MAX_PATH);
    if (*pathBuffer !='\0'){
        return 1;
    }
    else{
        return 0;
    }
}

void processUserAnswer(){
    std::string userAnswer=readUserAnswer();
    while(userAnswer!="stop" && userAnswer!="Stop" && userAnswer!="STOP"){
        char userSentence[userAnswer.size()+1];
        strcpy(userSentence, userAnswer.c_str());
        char *wordToken=strtok(userSentence, " ");
        std::string wordFromSentence;
        while(wordToken != NULL){
            wordFromSentence=wordToken;
            if (wordFromSentence[wordFromSentence.size() - 1] == '?') {
                wordFromSentence[wordFromSentence.size() - 1] = '\0';
            }
            bool folderCheck=searchFolder(wordFromSentence);
            if(folderCheck==0){
                createNewFolder(path, wordFromSentence);
            }
            changeDirectory(wordFromSentence);
            wordToken=strtok(NULL, " ");
        }
        std::string chatbotAnswer;
        std::string denumireFisier = wordFromSentence + ".txt";
        std::ifstream answerFile;
        answerFile.open(denumireFisier);
        if(answerFile){
            while(answerFile>>chatbotAnswer){
                std::cout<<" "<<chatbotAnswer;
            }
            std::cout<<std::endl;
        }
        else{
            std::ofstream createAnswerFile(denumireFisier);
            std::cout<<"Nu am gasit un raspuns in baza de date. Ofera-mi o sugestie: ";
            std::getline(std::cin, chatbotAnswer);
            createAnswerFile<<chatbotAnswer;
            std::cout<<"Am inregistrat raspunsul. Multumesc. "<<std::endl;
            createAnswerFile.close();
        }

        userAnswer=readUserAnswer();
        path="D:\\Proiecte\\c++\\Conti Challenge\\Chatbot\\Conversatie";
        _chdir(path.c_str());
    }
}

int main(){
    path="D:\\Proiecte\\c++\\Conti Challenge\\Chatbot\\Conversatie";
    _chdir(path.c_str()); //path set
    processUserAnswer();
    return 0;
}
