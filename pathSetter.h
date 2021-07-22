#pragma once

std::string searchingPath;

void setDefaultPath(){ //functia care seteaza path-ul default
    searchingPath=R"(D:\Proiecte\c++\Conti Challenge\Chatbot\Conversatie)";
    _chdir(searchingPath.c_str());
}

void changeDirectory(std::string toAdd){ //functia cu ajutorul careia se schimba path-ul
    searchingPath=searchingPath+"\\";
    searchingPath=searchingPath+toAdd;
    _chdir(searchingPath.c_str());
}

