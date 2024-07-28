#include "terminal.h"
#include <time.h>

EN_terminal_error_t GetTransactionDate(ST_TerminalData_t *TermData) {
   EN_terminal_error_t ret = terminal_ok;
   time_t current_time;
   struct tm *local_time;
   current_time = time(NULL);
   local_time = localtime(&current_time);
   uint16_t years = local_time->tm_year + 1900;
   uint8_t months = local_time->tm_mon + 1;
   uint8_t days = local_time->tm_mday;
   
   uint8_t txt_year[5];
   uint8_t txt_month[3];
   uint8_t txt_day[3];
   sprintf(txt_year, "%d", years);
   sprintf(txt_month, "%d", months);
   sprintf(txt_day, "%d", days);
   if (days < 10) {
      txt_day[1] = txt_day[0];
      txt_day[0] = '0';
   }
   TermData->TransactionDate[0] = txt_day[0];
   TermData->TransactionDate[1] = txt_day[1];
   TermData->TransactionDate[2] = '/';

   if (months < 10) {
      txt_month[1] = txt_month[0];
      txt_month[0] = '0';
   }
   TermData->TransactionDate[3] = txt_month[0];
   TermData->TransactionDate[4] = txt_month[1];
   TermData->TransactionDate[5] = '/';

   TermData->TransactionDate[6] = txt_year[0];
   TermData->TransactionDate[7] = txt_year[1];
   TermData->TransactionDate[8] = txt_year[2];
   TermData->TransactionDate[9] = txt_year[3];
   TermData->TransactionDate[10] = '\0';
   if (mystrlen(TermData->TransactionDate) < 10) {
      ret = wrong_date;
   }
   return ret;
}

EN_terminal_error_t IsCardExpired(ST_TerminalData_t *TermData, ST_CardData_t *CardData) {
   EN_terminal_error_t ret = terminal_ok;
   uint8_t FiElemMon = (CardData->CardExpiraton[0] - 48);
   uint8_t SeElemMon = (CardData->CardExpiraton[1] - 48);
   uint8_t month_exp = (SeElemMon + FiElemMon * 10);

   uint8_t FiElemYear = (CardData->CardExpiraton[3] - 48);
   uint8_t SeElemYear = (CardData->CardExpiraton[4] - 48);
   uint8_t year_exp = (SeElemYear + FiElemYear * 10);

   FiElemMon = (TermData->TransactionDate[3] - 48);
   SeElemMon = (TermData->TransactionDate[4] - 48);
   uint8_t month_trans = (SeElemMon + FiElemMon * 10);

   FiElemYear = (TermData->TransactionDate[8] - 48);
   SeElemYear = (TermData->TransactionDate[9] - 48);
   uint8_t year_trans = (SeElemYear + FiElemYear * 10);

   if ((year_exp < year_trans) || ((year_exp == year_trans) && (month_exp < month_trans))) {
      ret = expired_card;
      printf("Expired card !\n");
   }
   return ret;
}


EN_terminal_error_t GetTransactionAmount(ST_TerminalData_t *TermData) {
   EN_terminal_error_t ret = terminal_ok;
   printf("Enter the transaction amount: ");
   scanf("%f", &TermData->TransAmount);
   if ((TermData->TransAmount < 0) || (TermData->TransAmount == 0)) {
      ret = invalid_amount;
      printf("Invalid amount !\n");
   }
   return ret;
}

EN_terminal_error_t SetMaxAmount(ST_TerminalData_t *TermData) {
   EN_terminal_error_t ret = terminal_ok;
   if ((TermData->MaxTransAmount < 0) || (TermData->MaxTransAmount == 0)) {
      ret = invalid_max_amount;
      printf("Invalid max amount !\n");
   }
   return ret;
}

EN_terminal_error_t IsBelowMaxAmount(ST_TerminalData_t *TermData) {
   EN_terminal_error_t ret = terminal_ok;
   if (TermData->TransAmount > TermData->MaxTransAmount) {
      ret = exceed_max_amount;
      printf("Exceed max amount !\n");
   }
   return ret;
}

EN_terminal_error_t TheAmount(ST_TerminalData_t *TermData) {
   EN_terminal_error_t ret = terminal_ok;
   ret = SetMaxAmount(TermData);
   if (ret == terminal_ok) {
      ret = GetTransactionAmount(TermData);
      if (ret == terminal_ok) {
         ret = IsBelowMaxAmount(TermData);
         if (ret != terminal_ok) {
            ret = exceed_max_amount;
         }
      } else {
         ret = invalid_amount;
      }
   } else {
      ret = invalid_max_amount;
   }
   return ret;
}