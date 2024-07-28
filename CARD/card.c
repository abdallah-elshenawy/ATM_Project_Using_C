#include "card.h"

EN_card_error_t GetCardHolderName(ST_CardData_t *cardData) {
   EN_card_error_t ret = card_ok;
   printf("Enter your card name: ");
   gets(cardData->CardHolderName);
   uint8_t length = mystrlen(cardData->CardHolderName);
   if ((length > 24) || (length < 20)) {
      printf("Wrong name !\n");
      ret = wrong_name;
   }
   return ret;
}

EN_card_error_t GetCardExpDate(ST_CardData_t *cardData) {
   EN_card_error_t ret = card_ok;
   printf("Enter your card expiration date (MM/YY): ");
   gets(cardData->CardExpiraton);
   uint8_t length = mystrlen(cardData->CardExpiraton);
   if ((length > 5) || (length < 5)) {
      ret = wrong_exp_date;
      printf("Wrong expiration date !\n");
   }
   return ret;
}

EN_card_error_t GetCardPAN(ST_CardData_t *cardData) {
   EN_card_error_t ret = card_ok;
   printf("Enter your card primary account number: ");
   gets(cardData->PrimaryAccountNumber);
   uint8_t length = mystrlen(cardData->PrimaryAccountNumber);
   if (((length > 16) || (length < 16))) {
      ret = wrong_pan;
      printf("Wrong primary account number !\n");
   }
   return ret;
}

uint8_t mystrlen(char *str) {
   uint8_t length = 0;
   if (str == NULL) {
      length = 0;   
   } else {
      while (*str) {
         length++;
         str++;
      }
   }
   return length;
}

