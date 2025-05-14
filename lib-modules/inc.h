#ifndef INC_H
#define INC_H
#define BASE_PATH "test/"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <filesystem>
#include <vector>
#include <string>
#include <cstdio>

uint8_t ssystem_control(){
	#if defined(__linux__)
		return 1;
	#elif defined(_WIN32) || defined(_WIN64)
		return 0;
	#else
		return -1;
	#endif
}

struct color_codes_strc{
    std::string color_success_inter_s = "\033[32m"; 
    std::string color_success_inter_f = "\033[0m";  
    std::string color_error_s = "\033[31m";
    std::string color_error_f = "\033[0m";
    std::string color_information_s = "\033[44;37m";
    std::string color_information_f = "\033[0m";
    std::string color_output_s = "\033[33m";
    std::string color_output_f = "\033[0m";
};

#endif
