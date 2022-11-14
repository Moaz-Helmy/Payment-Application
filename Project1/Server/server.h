/******************************************************************************
 *
 * Module: Server Module
 *
 * File Name: server.h
 *
 * Description: Header file for Server Module
 *
 * Author: Moaz Mohamed
 *
 *******************************************************************************/

#ifndef SERVER_H_
#define SERVER_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "famous_types.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/*
 * Description:
 * 1- Macro to print the Transaction State in the listSavedTransactions() function.
 */
#define PRINT_TRANS_STATE(STATE) {\
		switch(STATE)\
		{\
		case APPROVED:\
		printf("Transaction State: %s\n","APPROVED");\
		break;\
		case DECLINED_INSUFFECIENT_FUND:\
		printf("Transaction State: %s\n","DECLINED_INSUFFICIENT_FUND");\
		break;\
		case DECLINED_STOLEN_CARD:\
		printf("Transaction State: %s\n","DECLINED_STOLEN_CARD");\
		break;\
		case FRAUD_CARD:\
		printf("Transaction State: %s\n","FRAUD_CARD");\
		break;\
		case INTERNAL_SERVER_ERROR:\
		printf("Transaction State: %s\n","INTERNAL_SERVER_ERROR");\
		break;\
		}\
}

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32_t transactionSequenceNumber;
}ST_transaction_t;

typedef enum EN_serverError_t
{
	SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t ;

typedef enum EN_accountState_t
{
	RUNNING,BLOCKED
}EN_accountState_t;

typedef struct ST_accountsDB_t
{
	float balance;
	EN_accountState_t state;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * 1- This function will take all transaction data and validate its data,
 *    it contains all server logic.
 * 2- It checks the account details and amount availability.
 * 3- If the account does not exist return FRAUD_CARD, if the amount is not
 *    available will return DECLINED_INSUFFECIENT_FUND, if the account is blocked will
 *    return DECLINED_STOLEN_CARD, if a transaction can't be saved will return
 *    INTERNAL_SERVER_ERROR , else returns APPROVED.
 * 4- It will update the database with the new balance.
 */
EN_transState_t recieveTransactionData(ST_transaction_t *transData);

/*
 * Description :
 * 1- This function will take card data and validate if the account related to this
 *    card exists or not.
 * 2- It checks if the PAN exists or not in the server's database (searches for the
 *    card PAN in the DB).
 * 3- If the PAN doesn't exist will return ACCOUNT_NOT_FOUND and the account reference
 *    will be NULL, else will return SERVER_OK and return a reference to this account
 *    in the DB.
 */
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence);

/*
 * Description :
 * 1- This function takes a reference to the account into the database and verifies if it is
 *    blocked or not.
 * 2- If the account is running it will return SERVER_OK, else if the account is blocked it
 *    will return BLOCKED_ACCOUNT.
 */
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence);

/*
 * Description :
 * 1- This function will take terminal data and a reference to the account in the database
 *    and check if the account has a sufficient amount to withdraw or not.
 * 2- It checks if the transaction's amount is available or not.
 * 3- If the transaction amount is greater than the balance in the database will return
 *    LOW_BALANCE, else will return SERVER_OK.
 */
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence);

/*
 * Description :
 * 1- This function will store all transaction data in the transactions database.
 * 2- It gives a sequence number to a transaction, this number is incremented once a transaction
 *    is processed into the server, you must check the last sequence number in the server to give
 *    the new transaction a new sequence number.
 * 3- It saves any type of transaction, APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD,
 *    FRAUD_CARD, INTERNAL_SERVER_ERROR.
 * 4- It will list all saved transactions using the listSavedTransactions function.
 * 5- Assuming that the connection between the terminal and server is always connected, then it will
 *    return SERVER_OK.
 */
EN_serverError_t saveTransaction(ST_transaction_t *transData);

/*
 * Description :
 * 1- This function prints all transactions found in the transactions DB.
 * 2- Please follow the following format for only one transaction data:
 * 		#########################
 * 		Transaction Sequence Number:
 * 		Transaction Date:
 * 		Transaction Amount:
 * 		Transaction State:
 * 		Terminal Max Amount:
 * 		Cardholder Name:
 * 		PAN:
 * 		Card Expiration Date:
 * 		#########################
 */
void listSavedTransactions(void);


#endif /* SERVER_H_ */
