#pragma once

std::string searchingPath;

void setDefaultPath(){
    searchingPath=R"(D:\Proiecte\c++\Conti Challenge\Chatbot\Conversatie)";
    _chdir(searchingPath.c_str());
}

void changeDirectory(std::string toAdd){
    searchingPath=searchingPath+"\\";
    searchingPath=searchingPath+toAdd;
    _chdir(searchingPath.c_str());
}

