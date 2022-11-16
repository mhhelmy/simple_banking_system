//
//  app.c
//  C play ground
//
//  Created by Mohamed Khalil on 17.09.22.
//

#include "card.h"
#include "terminal.h"
#include "server.h"
#include "app.h"

void appStart(void)
{
  ST_cardData_t cardData;
  ST_terminalData_t termData;
  EN_cardError_t card_error_id;
  EN_terminalError_t terminal_error_id;
  EN_transStat_t server_state;
  ST_transaction transData;
  EN_serverError_t server_error;
  
  card_error_id = getCardHolderName(&cardData);
  
  if (card_error_id != OK)
  {
    
    printf("Card holder name is invalid \n");
    return;
  }
  
  card_error_id = getCardExpiryDate(&cardData);
  if (card_error_id != OK)
  {
    printf("Card Expiry date is in invalid format \n");
    return;
  }
  
  card_error_id = getCardPAN(&cardData);
  
  if (card_error_id != OK)
  {
    printf("PAN is invalid \n");
    return;
  }
  
  
  
  terminal_error_id = isValidCardPAN(&cardData);
  if(terminal_error_id != TERMINAL_OK)
  {
    printf ("PAN is invalid \n");
    return;
  }
  
  terminal_error_id = getTransactionDate(&termData);
  if(terminal_error_id != TERMINAL_OK)
  {
    printf ("Internal terminal OS error \n");
    return;
  }
  
  terminal_error_id = isCardExpired(cardData, termData);
  if(terminal_error_id != TERMINAL_OK)
  {
    printf ("Your card has expired \n");
    return;
  }
  
  terminal_error_id = setMaxAmount(&termData);
  if(terminal_error_id != TERMINAL_OK)
  {
    printf ("Internal terminal OS error \n");
    return;
  }
  
  terminal_error_id = getTransactionAmount(&termData);
  
  if(terminal_error_id != TERMINAL_OK)
  {
    printf ("Invalid Amount \n");
    return;
  }
  
  terminal_error_id = isBelowMaxAmount(&termData);
  
  if(terminal_error_id != TERMINAL_OK)
  {
    printf ("Maximum allowed amount exceeded \n");
    return;
  }
  
  transData.terminalData = termData;
  transData.cardHolderData = cardData;
  
  server_state = recieveTransactionData(&transData);
  
  if(server_state != APPROVED)
  {
    printf("server rejected the transaction \n");
    return;
  }
  
  server_error = saveTransaction(&transData);
  
  if(server_error != Server_OK)
  {
    printf("server cancelled the transaction \n");
    return;
  }
  
  printf("Please take your money ;) \n");
  
}
