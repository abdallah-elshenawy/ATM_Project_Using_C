#include "server.h"

#define NUMBER_OF_ACCOUNT 8

uint8_t trans_index[100];

ST_AccountDB_t TheAccounts[NUMBER_OF_ACCOUNT] = {   
   {1000.0,   running,  "1234567898765432"},
   {3000.0,   running,  "2274567835475432"},
   {7000.0,   running,  "8284552898795432"},
   {500.5,    running,  "7892167898765438"},
   {12000.0,  running,  "3753456159765432"},
   {1400.0,   running,  "9575367898765432"},
   {2000.00,  blocked,  "9845367456321781"},
   {700.00,   blocked,  "5085361287456962"},
};

ST_Transaction_t transactions[100];
uint8_t IndexAccount = 0;
static uint8_t TransSeqNum = 0;

EN_TransState_t RecieveTransactionData(ST_Transaction_t *TransData) {
   EN_TransState_t ret = approved;
   EN_terminal_error_t ret_term;
   EN_ServerError_t ret_serv = server_ok;
   transactions[TransSeqNum].TransactionSequenceNumber = TransSeqNum;
   TransData->TransactionSequenceNumber = TransSeqNum;
   uint8_t i, j;
   transactions[TransSeqNum].TransState = TransData->TransState;
   transactions[TransSeqNum].TerminalData.MaxTransAmount = TransData->TerminalData.MaxTransAmount;
   transactions[TransSeqNum].TerminalData.TransAmount = TransData->TerminalData.TransAmount;
   ret_serv = IsBlockedAccount(TheAccounts);
   if (ret_serv == blocked_account) {
      ret = declined_stolen_card;
      printf("Declined stolen card !\n");
   } else {
      ret_serv = IsAmountAvailable(&TransData->TerminalData);
      if (ret_serv == low_balance) {
         ret = declined_insufficient_fund;
         printf("Declined insufficient fund !\n");
      } else {
         TheAccounts[IndexAccount].balance -= TransData->TerminalData.TransAmount;
      } 
   }
   TransData->TerminalData.TransAmount = TheAccounts[IndexAccount].balance;
   TransSeqNum++;
   return ret;
}

EN_ServerError_t IsValidAccount(ST_CardData_t *CardData) {
   EN_ServerError_t ret = server_ok;
   uint8_t i, j;
   for (i = 0; i < 16; i++) {
      transactions[TransSeqNum].CardHolderData.PrimaryAccountNumber[i] = CardData->PrimaryAccountNumber[i];
   }
   for (i = 0; i < 8; i++) {
      for (j = 0; j < 16; j++) {
         if (CardData->PrimaryAccountNumber[j] != TheAccounts[i].PrimaryAccountNumber[j]) {
            break;
         }
      }
      if ((CardData->PrimaryAccountNumber[j]  != TheAccounts[i].PrimaryAccountNumber[j]) && (i == 7)) {
         printf("The account is not found !\n");
         ret = account_not_found;
      } else if (CardData->PrimaryAccountNumber[j] == TheAccounts[i].PrimaryAccountNumber[j]) {
         IndexAccount = i;
         break;
      }
   }
   return ret;
}

EN_ServerError_t IsBlockedAccount(ST_AccountDB_t *AccountReference) {
   EN_ServerError_t ret = server_ok;
   if (AccountReference[IndexAccount].state == blocked) {
      ret = blocked_account;
   }
   return ret;
}

EN_ServerError_t IsAmountAvailable(ST_TerminalData_t *TermData) {
   EN_ServerError_t ret = server_ok;
   if (TheAccounts[IndexAccount].balance < TermData->TransAmount) {
      ret = low_balance;
   }
   return ret;
}
