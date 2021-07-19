#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <direct.h>
#include <cstdlib>

std::string path;

void setConversationPath(){
    path="D:\\Proiecte\\c++\\Conti Challenge\\Chatbot\\Conversatie";
    _chdir(path.c_str());
}

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

    strcpy(searchFile, auxNumeFolder.c_str());
    errno_t error=_searchenv_s(searchFile, envvar, pathBuffer, _MAX_PATH);
    if (*pathBuffer !='\0'){
        return 1;
    }
    else{
        return 0;
    }
}

void createAnswerFolder(std::string wordFromSentence){
    bool folderCheck=searchFolder(wordFromSentence);
    if(folderCheck==0){
        createNewFolder(path, wordFromSentence);
    }
}

std::string tokeniseSentence(char *userSentence){
    char *wordToken=strtok(userSentence, " ");
    std::string wordFromSentence;
    while(wordToken != NULL){
        wordFromSentence=wordToken;
        if (wordFromSentence[wordFromSentence.size() - 1] == '?') {
            wordFromSentence[wordFromSentence.size() - 1] = '\0';
        }
        createAnswerFolder(wordFromSentence);
        changeDirectory(wordFromSentence);
        wordToken=strtok(NULL, " ");
    }
    return wordFromSentence;
}

void recordAnswer(std::string denumireFisier){
    std::string chatbotAnswer;
    std::ofstream createAnswerFile(denumireFisier);

    std::cout<<"Nu am gasit un raspuns in baza de date. Ofera-mi o sugestie: ";
    std::getline(std::cin, chatbotAnswer);
    createAnswerFile<<chatbotAnswer;
    std::cout<<"Am inregistrat raspunsul. Doresti sa imi oferi mai multe variante de raspuns? "<<std::endl;
    createAnswerFile.close();
}

void offerAnswer(std::string denumireFisier){
    std::string chatbotAnswer;
    std::ifstream answerFile;
    answerFile.open(denumireFisier);
    if(answerFile){
        while(answerFile>>chatbotAnswer){
            std::cout<<" "<<chatbotAnswer;
        }
        std::cout<<std::endl;
    }
    else{
        recordAnswer(denumireFisier);
    }
}

void processUserAnswer(){
    std::string userAnswer=readUserAnswer();
    std::string chatbotAnswer;
    while(userAnswer!="stop" && userAnswer!="Stop" && userAnswer!="STOP"){
        char userSentence[userAnswer.size()+1];
        strcpy(userSentence, userAnswer.c_str());
        std::string denumireFisier = tokeniseSentence(userSentence) + ".txt";
        offerAnswer(denumireFisier);
        userAnswer=readUserAnswer();
        setConversationPath();
    }
}

int main(){
    setConversationPath();
    processUserAnswer();
    return 0;
}
