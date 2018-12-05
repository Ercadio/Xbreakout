#pragma once

#include <iostream>

#define RED "\e[38;2;219;125;31m"
#define BLUE "\e[38;2;71;59;240m"
#define YELLOW "\e[38;2;224;242;62m"
#define ORANGE "\e[38;2;255;153;51m"
#define CLEAR "\e[0m"

#define filemsg std::string("[") + __FILE__ + ':' + std::to_string(__LINE__) + ']'

#define errormsg std::cerr << RED << "[ERROR]" << filemsg << CLEAR << '\t'
#define infomsg std::cout << BLUE << "[INFO]" << filemsg << CLEAR << '\t'
#define warningmsg std::cout << YELLOW << "[WARNING]" << filemsg << CLEAR << '\t'

#ifndef LOG_DEBUG
#define LOG_DEBUG false
#endif

#define debugmsg \
if(not LOG_DEBUG) {} \
else std::cout<< ORANGE << "[DEBUG]" << filemsg << CLEAR << '\t'
