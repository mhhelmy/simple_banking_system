//
//  main.c
//  C play ground
//
//  Created by Mohamed Khalil on 08.08.22.
//

#include <stdio.h>
#include "./Card/card.h"
#include "./Terminal/terminal.h"
#include "./Server/server.h"
#include "./Application/app.h"

extern ST_transaction bank_transaction_DB [TRANSACTION_DB_SIZE];

int main(int argc, const char * argv[])
{

  
  memset (bank_transaction_DB, 0 , sizeof(bank_transaction_DB));
  
  while (1)
  {
  	// This is needed to do a clean-up for the input buffer.
    fflush(stdin);

    appStart();
  }
}

