#include "Logger.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>


void Logger::Log(const std::string& message) {
    //TODO:
    //Print on the console the message:
    //LOG: [ DATE  TIME ] - Here goes the message...
    //This should be in green
    std::time_t tmNow;
    tmNow = time(NULL);
    struct tm t = *localtime(&tmNow);
    
    system("Color 0A");
    std::cout << "[" << t.tm_mday << "/" << t.tm_mon +1 << "/" << t.tm_year + 1900 << "]" << "[" << t.tm_hour << ":" << t.tm_min<< ":" << t.tm_sec<< "]"<< " - " << std::endl;

}

void Logger::Err(const std::string& message) {
    //TODO:
    //Print on the console the message:
    //ERR: [ DATE  TIME ] - Here goes the message...
    //This should be in red
    std::time_t tmNow;
    tmNow = time(NULL);
    struct tm t = *localtime(&tmNow);
    
    system("Color 0A");
    std::cout   << "[" 
                << t.tm_mday 
                << "/" 
                << t.tm_mon +1 
                << "/" 
                << t.tm_year + 1900 
                << "]" 
                << "[" 
                << t.tm_hour 
                << ":" 
                << t.tm_min
                << ":"
                << t.tm_sec
                << "]"
                << " - "
                << std::endl;

}