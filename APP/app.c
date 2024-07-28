#include "app.h"
#include <stdio.h>



EN_card_error_t card_ret;
EN_terminal_error_t terminal_ret;
EN_TransState_t server_ret;

uint8_t choice;

int main() {
   printf("Make a transaction: [1]\n");
   printf("Exit the program:   [2]\n");
   printf("Enter your choice: ");
   scanf("%d", &choice);
   while (choice) {
      if (choice == 2) {
         break;
      } 
      fflush(stdin);
      card_ret = GetCardHolderName(&card_obj);
      if (card_ret == card_ok) {
         card_ret = GetCardPAN(&card_obj);
         if (card_ret == card_ok) {
            card_ret = GetCardExpDate(&card_obj);
         }
      }
      if (card_ret == card_ok) {
         terminal_ret = GetTransactionDate(&terminal_obj);
         if (terminal_ret == terminal_ok) {
               server_ret = IsValidAccount(&card_obj);
            if (terminal_ret == terminal_ok) {
               terminal_ret = IsCardExpired(&terminal_obj, &card_obj);
               if (terminal_ret == terminal_ok) {
                  terminal_ret = TheAmount(&terminal_obj);
                  if (terminal_ret == terminal_ok) {
                     trans_obj.TerminalData = terminal_obj;
                     server_ret = RecieveTransactionData(&trans_obj);
                     if (server_ret == approved) {
                        printf("\nThe Transaction is approved !\n");
                        printf("Account info: \n\n");
                        printf("Name: %s\n", card_obj.CardHolderName);
                        printf("PAN : %s\n", card_obj.PrimaryAccountNumber);
                        printf("The new balance     : %.2f\n", trans_obj.TerminalData.TransAmount);
                        printf("The expiration date : %s\n", card_obj.CardExpiraton);
                        printf("The transaction date: %s\n", terminal_obj.TransactionDate);
                     }
                  }
               }
            }
         }   
      }
      printf("\n<------------------------------------->\n\n");
      printf("Make a transaction: [1]\n");
      printf("Exit the program  : [2]\n");
      printf("Enter your choice: ");
      scanf("%d", &choice);
   }
}
         
