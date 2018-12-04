#pragma once
#define RED "\e[38;2;219;125;31m"
#define BLUE "\e[38;2;71;59;240m"
#define YELLOW "\e[38;2;224;242;62"
#define CLEAR "\e[0m"
#define filemsg std::string("[") + __FILE__ + ':' + std::to_string(__LINE__) + ']'
#define errormsg std::string(RED) + "[ERROR]" + filemsg + CLEAR + ' '
#define infomsg std::string(BLUE) + "[INFO]" + filemsg + CLEAR + ' '
#define warningmsg std::string(YELLOW) + "[WARNING]" + filemsg + CLEAR + ' '
