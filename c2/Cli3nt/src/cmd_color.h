#ifndef _CMD_COLOR_H_
#define _CMD_COLOR_H_

/* frontground color */
#define PRINT_FONT_BLA  printf("\033[30m"); //black
#define PRINT_FONT_RED  printf("\033[31m"); //red
#define PRINT_FONT_GRE  printf("\033[32m"); //green
#define PRINT_FONT_YEL  printf("\033[33m"); //yellow
#define PRINT_FONT_BLU  printf("\033[34m"); //blue
#define PRINT_FONT_PUR  printf("\033[35m"); //purple
#define PRINT_FONT_CYA  printf("\033[36m"); //cyan-blue
#define PRINT_FONT_WHI  printf("\033[37m"); //white

#define PRINT_YEL \033[33m

/* background color*/ 
#define PRINT_BACK_BLA  printf("\033[40m"); //black
#define PRINT_BACK_RED  printf("\033[41m"); //red
#define PRINT_BACK_GRE  printf("\033[42m"); //green
#define PRINT_BACK_YEL  printf("\033[43m"); //yellow
#define PRINT_BACK_BLU  printf("\033[44m"); //blue
#define PRINT_BACK_PUR  printf("\033[45m"); //purple
#define PRINT_BACK_CYA  printf("\033[46m"); //cyan-blue
#define PRINT_BACK_WHI  printf("\033[47m"); //white

/* output attributes */
#define PRINT_ATTR_REC  printf("\033[0m");  //reset to default
#define PRINT_ATTR_BOL  printf("\033[1m");  //set bold
#define PRINT_ATTR_LIG  printf("\033[2m");  //set half brightness 
#define PRINT_ATTR_LIN  printf("\033[4m");  //set underline
#define PRINT_ATTR_GLI  printf("\033[5m");  //set flash
#define PRINT_ATTR_REV  printf("\033[7m");  //set reverse pattern
#define PRINT_ATTR_THI  printf("\033[22m"); //set common density
#define PRINT_ATTR_ULIN  printf("\033[24m");//unset underline
#define PRINT_ATTR_UGLI  printf("\033[25m");//unset flash
#define PRINT_ATTR_UREV  printf("\033[27m");//unset reverse pattern

#define PRINT_CLEAR printf("\033[0m");		//clear all attributes

#endif
