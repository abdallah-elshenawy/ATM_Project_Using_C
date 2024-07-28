#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdio.h>
#include <stdint.h>
#include "../CARD/card.h"

typedef enum {
   terminal_ok,
   wrong_date,
   expired_card,
   invalid_card,
   invalid_amount,
   exceed_max_amount,
   invalid_max_amount,
} EN_terminal_error_t;

typedef struct {
   float TransAmount;
   float MaxTransAmount;
   uint8_t TransactionDate[11];
} ST_TerminalData_t;

EN_terminal_error_t GetTransactionDate(ST_TerminalData_t *TermData);
EN_terminal_error_t IsCardExpired(ST_TerminalData_t *TermData, ST_CardData_t *CardData);
EN_terminal_error_t GetTransactionAmount(ST_TerminalData_t *TermData);
EN_terminal_error_t SetMaxAmount(ST_TerminalData_t *TermData);
EN_terminal_error_t IsBelowMaxAmount(ST_TerminalData_t *TermData);
EN_terminal_error_t TheAmount(ST_TerminalData_t *TermData);


#endif