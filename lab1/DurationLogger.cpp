#include <iostream>
#include "DurationLogger.h"

DurationLogger::DurationLogger(const std::string& name){
    this->name = name;
    this->c_start = std::clock();
    std::cout << ">>>>>>>>>>>>>>> starting [" << this->name << "]" << std::endl;
}

DurationLogger::~DurationLogger(){
    this->c_end = std::clock();
    this->c_duration = ( std::clock() - c_start ) / (double) CLOCKS_PER_SEC; // ms
    std::cout << "<<<<<<<<<<<<<<< ending [" << this->name << "]: [" << (this->c_duration)/1000 << "] sec" << std::endl;

}