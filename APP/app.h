#ifndef APP_H
#define APP_H 

#include "../CARD/card.h"
#include "../TERMINAL/terminal.h"
#include "../SERVER/server.h"

ST_CardData_t card_obj;
ST_TerminalData_t terminal_obj = {
   .MaxTransAmount = 10000,
};
ST_Transaction_t trans_obj;
#endif