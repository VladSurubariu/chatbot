//header-ul in care sunt stocate functiile folosite pentru a oferi raspuns userului

#pragma once

std::string readUserAnswer(){ //functie care citeste propozitia user-ului
    std::string answer;
    std::getline(std::cin, answer);
    return answer;
}

void recordNewAnswer(std::string denumireFisier){ //functia prin care se inregistreaza raspunsul unei intrebari
    //ce nu se gaseste in baza de date
    std::string chatbotAnswer;
    std::ofstream createAnswerFile(denumireFisier);

    std::cout<<"Nu am gasit un raspuns in baza de date. Ofera-mi o sugestie:";
    std::getline(std::cin, chatbotAnswer);
    createAnswerFile<<chatbotAnswer;
    std::cout<<"Am inregistrat raspunsul."<<std::endl;
    createAnswerFile.close();
}

void offerAnswer(std::string denumireFisier){ //functia prin care se ofera raspunsul la intrebarea pe care a pus-o userul
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

std::string tokeniseSentence(char *userSentence){ //functia pentru a tokeniza input-ul oferit de user
    char *wordToken=strtok(userSentence, " ");
    std::string wordFromSentence;
    while(wordToken != NULL){
        wordFromSentence=wordToken;
        if (wordFromSentence[wordFromSentence.size() - 1] == '?') { //daca propozitia oferita drept input are semnul intrebarii
            //acesta va fi eliminat, deoarece nu se poate folosi "?" in denumirea folderelor
            wordFromSentence[wordFromSentence.size() - 1] = '\0';
        }
        createAnswerFolder(wordFromSentence);
        changeDirectory(wordFromSentence);
        wordToken=strtok(NULL, " ");
    }
    return wordFromSentence;
}

void processUserAnswer(){ //functia principala prin care se controleaza actiunile Chatbotului
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