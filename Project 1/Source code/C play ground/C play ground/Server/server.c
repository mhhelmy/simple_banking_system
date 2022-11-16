//
//  server.c
//  C play ground
//
//  Created by Mohamed Khalil on 17.09.22.
//

#include "server.h"

ST_accountsDB_t bank_account_DB [255] =
{
  {500, "111111111111111111"},
  {20000,"222222222222222222"},
  {170000,"333333333333333333"}
};
uint8_t account_db_index = 3;
uint8_t current_account_index;


ST_transaction bank_transaction_DB [TRANSACTION_DB_SIZE];
uint8_t transaction_db_index = 0;


EN_transStat_t recieveTransactionData(ST_transaction *transData)
{
  
  current_account_index = 0;
  
  if (isValidAccount(&transData->cardHolderData) != Server_OK)
  {
    printf("This card is declined \n");
    return DECLINED_STOLEN_CARD;
  }
  
  if (isAmountAvailable(&transData->terminalData) != Server_OK)
  {
    printf("You have insuffecient fund in your account \n");
    return DECLINED_INSUFFECIENT_FUND;
  }
  
  if (transaction_db_index == 255)
  {
    printf("Sorry, Server is busy now \n Please try again later \n");
    return INTERNAL_SERVER_ERROR;
  }
  
  return APPROVED;
}
EN_serverError_t isValidAccount(ST_cardData_t *cardData)
{
  uint32_t i;
  
  for (i = 0; i< account_db_index; i++)
  {
    if (strcmp( (char *)cardData->primaryAccountNumber, (char *)bank_account_DB[i].primaryAccountNumber) == 0)
    {
      break;
    }
  }
  
  if (i == account_db_index)
  {
    return ACCOUNT_NOT_FOUND;
  }
  
  current_account_index = i;
  
  return Server_OK;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
  if (termData -> transAmount > bank_account_DB[current_account_index].balance)
  {
    return LOW_BALANCE;
  }
  
  return Server_OK;
}
EN_serverError_t saveTransaction(ST_transaction *transData)
{
  if (transaction_db_index == TRANSACTION_DB_SIZE)
  {
    return SAVING_FAILED;
  }
  
  bank_transaction_DB[transaction_db_index] = *transData;
  bank_transaction_DB[transaction_db_index].transState = APPROVED;
  bank_transaction_DB[transaction_db_index].transactionSequenceNumber = transaction_db_index;
  
  transaction_db_index++;
  
  // update the balance
  bank_account_DB[current_account_index].balance -= transData->terminalData.transAmount;
  
  printf("Your new balance = %d EGP \n", (uint32_t)bank_account_DB[current_account_index].balance);
  
  return Server_OK;
}
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction *transData)
{
  uint32_t i;
  
  for (i = 0; i < transaction_db_index; i++)
  {
    if(bank_transaction_DB[i].transactionSequenceNumber ==  transactionSequenceNumber)
    {
      transData = &bank_transaction_DB[i];
      return Server_OK;
    }
  }
  
  return TRANSACTION_NOT_FOUND;
}
