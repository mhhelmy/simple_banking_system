//
//  terminal.c
//  C play ground
//
//  Created by Mohamed Khalil on 17.09.22.
//

#include <time.h>
#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
  // raw time field
  time_t rawtime;
  
  // formatted time pointer
  struct tm * p_time_info;
  uint32_t current_year;
  uint32_t current_month;
  
  
  // get raw time
  time( &rawtime );
  
  // convert the raw time to local time
  p_time_info = localtime ( &rawtime );
  
  // This local time function returns the tm_year param as the time since 1900, So it needs adjustment to match the Human readable format.
  current_year = p_time_info->tm_year + 1900;
  
  /*tm_mon returns the months since January [0-11], so it needs some adjustment */
  current_month = p_time_info->tm_mon + 1;
  
  termData->transactionDate[0] = p_time_info->tm_mday / 10 + '0';
  termData->transactionDate[1] = p_time_info->tm_mday % 10 + '0';
  termData->transactionDate[2] = '/';
  termData->transactionDate[3] = current_month / 10 + '0';
  termData->transactionDate[4] = current_month % 10 + '0';
  termData->transactionDate[5] = '/';
  termData->transactionDate[6] = current_year / 1000 + '0';
  termData->transactionDate[7] = (current_year % 1000) / 100 + '0';
  termData->transactionDate[8] = (current_year % 100) / 10 + '0';
  termData->transactionDate[9] = current_year % 10 + '0';
  termData->transactionDate[10] = '\0';
  
  return TERMINAL_OK;
}


EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
  
  uint32_t terminal_year;
  uint32_t terminal_month;
  uint32_t card_expiry_year;
  uint32_t card_expiry_month;
  
  terminal_year = ((termData.transactionDate[6] - '0') * 1000) +
  ((termData.transactionDate[7] - '0') * 100) +
  ((termData.transactionDate[8] - '0') * 10) +
  (termData.transactionDate[9] - '0');
  
  card_expiry_year = 2000 + (cardData.cardExpirationDate[3] - '0') * 10 + (cardData.cardExpirationDate[4] - '0');
  
  if (terminal_year > card_expiry_year)
  {
    return EXPIRED_CARD;
  }
  
  if (card_expiry_year >terminal_year)
  {
    return TERMINAL_OK;
  }
  
  terminal_month = ((termData.transactionDate[3] - '0') * 10) + (termData.transactionDate[4] - '0');
  card_expiry_month = (cardData.cardExpirationDate[0] - '0') * 10 + (cardData.cardExpirationDate[1] - '0');
  
  if (terminal_month > card_expiry_month)
    return EXPIRED_CARD;
  
  return TERMINAL_OK;
}

EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData)
{
  return TERMINAL_OK;
}


EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
  printf("Maximum allowed amount for withdrawal = %d \n", (uint32_t)TERMINAL_MAX_TRANSACTION_AMOUNT);
  printf("Please enter The transaction amount: \n");
  scanf("%f", &termData->transAmount);
  printf("\n");
  
  if (termData->transAmount <= 0)
    return INVALID_AMOUNT;
  
  return TERMINAL_OK;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
  if (termData->transAmount > termData->maxTransAmount)
    return EXCEED_MAX_AMOUNT;
  
  return TERMINAL_OK;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
  if (TERMINAL_MAX_TRANSACTION_AMOUNT >0)
  {
    termData->maxTransAmount = TERMINAL_MAX_TRANSACTION_AMOUNT;
    return TERMINAL_OK;
  }
  else
  {
    return INVALID_MAX_AMOUNT;
  }
}
