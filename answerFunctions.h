#pragma once

std::string readUserAnswer(){
    std::string answer;
    std::getline(std::cin, answer);
    return answer;
}

void checkforMultipleAnswers(){

}

void recordNewAnswer(std::string denumireFisier){
    std::string chatbotAnswer;
    std::ofstream createAnswerFile(denumireFisier);

    std::cout<<"Nu am gasit un raspuns in baza de date. Ofera-mi o sugestie:";
    std::getline(std::cin, chatbotAnswer);
    createAnswerFile<<chatbotAnswer;
    std::cout<<"Am inregistrat raspunsul."<<std::endl<<"Doresti sa imi oferi mai multe variante de raspuns? "<<std::endl;
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
        recordNewAnswer(denumireFisier);
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

void processUserAnswer(){
    std::string userAnswer=readUserAnswer();
    std::string chatbotAnswer;
    while(userAnswer!="stop" && userAnswer!="Stop" && userAnswer!="STOP"){
        char userSentence[userAnswer.size()+1];
        strcpy(userSentence, userAnswer.c_str());
        std::string denumireFisier = tokeniseSentence(userSentence) + ".txt";
        offerAnswer(denumireFisier);
        userAnswer=readUserAnswer();
        setDefaultPath();
    }
}