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
    while(userAnswer!="stop") {
        //std::cout<<"2."<<path<<" "<<std::endl;
        char userSentence[userAnswer.size() + 1];
        strcpy(userSentence, userAnswer.c_str());
        char *wordToken = strtok(userSentence, " ");
        while (wordToken != NULL) {
            //std::cout<<"3."<<path<<" "<<wordToken<<std::endl;
            std::string word = wordToken;
            //std::cout<<word<<" "<<wordToken<<" "<<path<<std::endl;
            if (word[word.size() - 1] == '?') {
                word[word.size() - 1] = '-';
            }
            //std::cout<<word<<std::endl;
            bool folderCheck = searchFolder(word);
            //std::cout<<folderCheck<<std::endl;
            if (folderCheck) {
                changeDirectory(word);
                //std::cout<<"3"<<path<<" "<<word<<std::endl;
                if (word[word.size() - 1] == '-' || word[word.size() - 1] == '!' || word[word.size() - 1] == '.') {
                    //std::cout<<"3b";
                    std::string chatbotAnswer;
                    std::string denumireFisier = word + ".txt";
                    std::ifstream f(denumireFisier);
                    while(f >> chatbotAnswer)
                        std::cout <<" "<< chatbotAnswer;
                }
            } else {
                createNewFolder(path, word);
                //std::cout<<"4."<<path<<" "<<word<<std::endl;
                changeDirectory(word);
                //std::cout<<"5."<<path<<" "<<word<<std::endl;
                if (word[word.size() - 1] == '-' || word[word.size() - 1] == '!' || word[word.size() - 1] == '.') {
                    std::string chatbotAnswer;
                    std::string denumireFisier = word + ".txt";
                    std::ofstream f(denumireFisier);
                    std::cout << "Nu am gasit un raspuns in baza de date. Ofera-mi o sugestie: ";
                    //std::cin >> chatbotAnswer;
                    std::getline(std::cin, chatbotAnswer);
                    std::cout<<chatbotAnswer<<std::endl;
                    f << chatbotAnswer;
                    // std::cout<<"6."<<path<<" "<<word<<std::endl;
                }
            }
            //std::cout<<"7."<<path<<" "<<word<<std::endl;
            wordToken = strtok(NULL, " ");
            if(wordToken==NULL){
                //std::cout<<"wordToken==NULL"<<std::endl;
            }
            //std::cout<<"8."<<path<<" "<<std::endl;
        }
        //std::cout<<"9";
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
