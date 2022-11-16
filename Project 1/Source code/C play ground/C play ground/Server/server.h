//
//  server.h
//  C play ground
//
//  Created by Mohamed Khalil on 17.09.22.
//

#ifndef server_h
#define server_h

#include <stdio.h>
#include "../Card/card.h"
#include "../Terminal/terminal.h"

#ifndef TRANSACTION_DB_SIZE
#define TRANSACTION_DB_SIZE 255
#endif

typedef enum EN_transState_t
{
  APPROVED,
  DECLINED_INSUFFECIENT_FUND,
  DECLINED_STOLEN_CARD,
  INTERNAL_SERVER_ERROR
}EN_transStat_t;

typedef enum EN_serverError_t
{
  Server_OK,
  SAVING_FAILED,
  TRANSACTION_NOT_FOUND,
  ACCOUNT_NOT_FOUND,
  LOW_BALANCE
}EN_serverError_t ;

typedef struct ST_accountsDB_t
{
  float balance;
  uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

typedef struct ST_transaction_t
{
  ST_cardData_t cardHolderData;
  ST_terminalData_t terminalData;
  EN_transStat_t transState;
  uint32_t transactionSequenceNumber;
}ST_transaction;


EN_transStat_t recieveTransactionData(ST_transaction *transData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData);
EN_serverError_t saveTransaction(ST_transaction *transData);
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction *transData);




#endif /* server_h */
