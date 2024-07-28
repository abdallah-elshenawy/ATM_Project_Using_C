#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <stdint.h>

typedef enum {
   card_ok,
   wrong_name,
   wrong_exp_date,
   wrong_pan,
} EN_card_error_t;

typedef struct {
   uint8_t CardHolderName[25];
   uint8_t PrimaryAccountNumber[20];
   uint8_t CardExpiraton[6];
} ST_CardData_t;

EN_card_error_t GetCardHolderName(ST_CardData_t *cardData);
EN_card_error_t GetCardExpDate(ST_CardData_t *cardData);
EN_card_error_t GetCardPAN(ST_CardData_t *cardData);

EN_card_error_t card(ST_CardData_t *cardData);
uint8_t mystrlen(char *str);

#endif