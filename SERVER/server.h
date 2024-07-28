#ifndef SERVER_H
#define SERVER_H

#include <stdint.h>
#include "../CARD/card.h"
#include "../TERMINAL/terminal.h"

typedef enum {
   approved,
   declined_insufficient_fund,
   declined_stolen_card,
   fraud_card,
   internal_server_error,
} EN_TransState_t;

typedef enum {
   server_ok,
   saving_failed,
   transaction_not_found,
   account_not_found,
   low_balance,
   blocked_account,
} EN_ServerError_t;

typedef enum {
   running,
   blocked,
} EN_AccountState_t;

typedef struct {
   ST_CardData_t CardHolderData;
   ST_TerminalData_t TerminalData;
   EN_TransState_t TransState;
   uint32_t TransactionSequenceNumber;
} ST_Transaction_t;

typedef struct {
   float balance;
   EN_AccountState_t state;
   uint8_t PrimaryAccountNumber[20];
} ST_AccountDB_t;

EN_TransState_t RecieveTransactionData(ST_Transaction_t *TransData);
EN_ServerError_t IsValidAccount(ST_CardData_t *CardData);
EN_ServerError_t IsBlockedAccount(ST_AccountDB_t *AccountReference);  
EN_ServerError_t IsAmountAvailable(ST_TerminalData_t *TermData);  
EN_ServerError_t SaveTransaction(ST_Transaction_t *TransData);  
EN_ServerError_t GetTransaction(uint32_t TransactionSequenceNumber, ST_Transaction_t *TransData);  

void mystrcpy(char *dest, char *s);
#endif