#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <direct.h>
#include <cstdlib>

std::string path="D:\\Proiecte\\c++\\Conti Challenge\\Chatbot\\Conversatie";

void myFirstWords(){
    std::cout<<"Salut. Eu sunt Chatbot. Intreaba-ma orice si voi incerca sa iti raspund"<<std::endl;
}

void answerNotFound(){
    std::cout<<"Nu am gasit un raspuns la intrebarea ta. Te rog sa introduci tu raspunsul pe care ar trebui sa ti-l ofer: ";
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

void createNewFolder(std::string auxDirector){
    std::string newFolderName;
    std::cout<<"Introduceti numele noului folder: ";
    std::cin>>newFolderName;
    auxDirector=auxDirector+"\\";
    auxDirector=auxDirector+newFolderName;

    char pathToCreate[auxDirector.size()+1];
    strcpy(pathToCreate, auxDirector.c_str());

    if(_mkdir(pathToCreate)==0){
        std::cout<<"The folder has been created. The path is: "<<auxDirector;
    }
    else{
        if(errno==2)
            std::cout<<"No such file or directory."<<std::endl;
        if(errno==17)
            std::cout<<"This folder already exists."<<std::endl;
        }
}


bool searchFolder(std::string auxNumeFolder){
    char pathBuffer[_MAX_PATH];
    char searchFile[auxNumeFolder.size()+1];
    char envvar[]="PATH";
    errno_t error;

    strcpy(searchFile, auxNumeFolder.c_str());
    error=_searchenv_s(searchFile, envvar, pathBuffer, _MAX_PATH);
    if (error!=0){
        std::cout<<"Error number "<<error<<std::endl;
        return 0;
    }
    if (*pathBuffer !='\0'){
        return 1;
    }
    else{
        return 0;
    }
}

void processUserAnswer(){
    const char questionMark='?';
    const char exclamantionMark='!';
    const char fullStop='.';
    std::string chatbotAnswer;
    std::string userAnswer=readUserAnswer();
    char userSentence[userAnswer.size()+1];
    strcpy(userSentence, userAnswer.c_str());
    char* wordToken=strtok(userSentence, " ");
    while(wordToken!=NULL){
        std::cout<<wordToken<<std::endl;
        bool folderCheck=searchFolder(wordToken);
        if(folderCheck){
            std::string word=wordToken;
            if(word[word.size()-1]==questionMark || word[word.size()-1]==exclamantionMark || word[word.size()-1]==fullStop)
            {
                word=word+".txt";
                std::ifstream f(word);
                f>>chatbotAnswer;
                std::cout<<chatbotAnswer;
            }
            else{
            changeDirectory(wordToken);
            }
        }
        else{
            std::cout<<"Folderul trebuie creat"<<std::endl;
        }
        wordToken=strtok(NULL, " ");
    }
}

int main(){

    _chdir(path.c_str()); //path set
    //std::string aux="Saluttxt";
    //std::cout<<searchFolder(aux);
    /*_chdir(R"(D:\Proiecte\c++\Conti Challenge\Chatbot\Conversatie)");
    aux="Salut";
    searchFolder(aux);
    createNewFolder(R"(D:\Proiecte\c++\Conti Challenge\Chatbot\Conversatie)");
    */
    //changeDirectory()
    processUserAnswer();



    return 0;
}
