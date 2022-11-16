//
//  card.h
//  C play ground
//
//  Created by Mohamed Khalil on 17.09.22.
//

#ifndef card_h
#define card_h

#include <stdio.h>
#include <string.h>


typedef struct ST_cardData_t
{
  uint8_t cardHolderName[25];
  uint8_t primaryAccountNumber[20];
  uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
  OK,
  WRONG_NAME,
  WRONG_EXP_DATE,
  WRONG_PAN
}EN_cardError_t;

EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);

#endif /* card_h */
