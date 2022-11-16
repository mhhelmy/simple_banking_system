//
//  card.c
//  C play ground
//
//  Created by Mohamed Khalil on 17.09.22.
//

#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
  int i = 0;
  printf("Please enter card holder name as written on the card: \n");
  
  // Loop over the input to read the card holder name
  while (1)
  {
    
    // i is not allowed to reach Array size to have a place for the null terminator
    if (i == 25)
    {
      memset(cardData->cardHolderName, 0, sizeof(cardData->cardHolderName));
      return WRONG_NAME;
    }
    
    // read one charcter from the input
    
    scanf("%c", &cardData->cardHolderName[i]);
    
    // If user pressed enter we should break here and validate
    if (cardData->cardHolderName[i] == '\n')
    {
      break;
    }
    
    // move to the next index in the array
    i++;
  }
  
  printf("\n");
  
  // remove any extra space the user trailed in the name
  // Note: I is not allowed to reach 19 as this is less than the minimum length.
  
  for (; i > 19; i--)
  {
    // ignore the end of line input from the user
    if (cardData->cardHolderName[i] == '\n')
      continue;
    
    if (cardData->cardHolderName[i] != ' ' )
      break;
  }
  
  if (i < 20)
  {
    
    memset(cardData->cardHolderName, 0, sizeof(cardData->cardHolderName));
    
    return WRONG_NAME;
  }
  
  cardData->cardHolderName[i + 1] = '\0';
  
  return OK;
  
}




EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
  int i = 0;
  
  char c;
  
  printf("Please enter expiry date (MM/YY): \n");
  // Loop over the input to read the card holder name
  while (i < 6)
  {
    
    scanf("%c", &c);
    
    if (i == 0)
    {
      // this cahrcter is allowed to be only 1 or 0
      if ((c != '0') && (c!= '1'))
        return WRONG_EXP_DATE;
    }
    else if (i == 1)
    {
      
      if (cardData->cardExpirationDate[0] == '1')
      {
        if ((c < '0') || (c > '2'))
          return WRONG_EXP_DATE;
      }
      else
      {
        if ((c < '0') || (c > '9'))
          return WRONG_EXP_DATE;
      }
      
    }
    else if (i == 2)
    {
      if (c != '/')
        return WRONG_EXP_DATE;
    }
    else if (i == 3)
    {
      if ((c < '2') || (c > '9'))
        return WRONG_EXP_DATE;
    }
    else if (i == 4)
    {
      if ((c < '0') || (c > '9'))
        return WRONG_EXP_DATE;
      
    }
    else
    {
      if (c != '\n')
        return WRONG_EXP_DATE;
      
      // if we didn't return then terminate the string
      c= '\0';
    }
    
    
    // We store now the date as numircal number in the array
    cardData->cardExpirationDate[i] = c;
    i++;
    
  }
  
  printf("\n");
  return OK;
}



EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
  int i = 0;
  printf("Please enter PAN as written on the card: \n");
  
  // Loop over the input to read the PAN
  while (1)
  {
    
    // i is not allowed to reach to have a place for the null terminator
    if (i == 20)
    {
      memset(cardData->primaryAccountNumber, 0, sizeof(cardData->primaryAccountNumber));
      return WRONG_PAN;
    }
    
    // read one charcter from the input
    
    scanf("%c", &cardData->primaryAccountNumber[i]);
    
    // If user pressed enter we should break here and validate
    if (cardData->primaryAccountNumber[i] == '\n')
    {
      break;
    }
    
    // move to the next index in the array
    i++;
  }
  
  printf("\n");
  // remove any extra space the user trailed in the name
  // Note: I is not allowed to reach 19 as this is less than the minimum length.
  
  for (; i > 15; i--)
  {
    // ignore the end of line input from the user
    if (cardData->primaryAccountNumber[i] == '\n')
      continue;
    
    if (cardData->primaryAccountNumber[i] != ' ' )
      break;
  }
  
  if (i < 16)
  {
    
    memset(cardData->primaryAccountNumber, 0, sizeof(cardData->primaryAccountNumber));
    
    return WRONG_PAN;
  }
  
  cardData->primaryAccountNumber[i + 1] = '\0';
  
  return OK;
  
}
