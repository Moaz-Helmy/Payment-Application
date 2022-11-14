/******************************************************************************
 *
 * Module: Terminal Module
 *
 * File Name: terminal.h
 *
 * Description: Header file for Terminal module
 *
 * Author: Moaz Mohamed
 *
 *******************************************************************************/

#ifndef TERMINAL_H_
#define TERMINAL_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "famous_types.h"
#include "../Card/card.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef struct ST_terminalData_t
{
	float transAmount;
	float maxTransAmount;
	uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
	TERMINAL_OK,WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t ;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * 1- This function will ask for the transaction data and store it in terminal data.
 * 2- Transaction date is 10 characters string in the format DD/MM/YYYY, e.g 25/06/2022.
 * 3- If the transaction date is NULL, less than 10 characters or wrong format will return
 *    WRONG_DATE error, else return TERMINAL_OK.
 */
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);

/*
 * Description :
 * 1- This function compares the card expiry date with the transaction date.
 * 2- If the card expiration date is before the transaction date will return EXPIRED_CARD,
 *    else return TERMINAL_OK.
 */
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData);

/*
 * Description :
 * 1- This function checks if the PAN is a Luhn number or not.
 * 2- If PAN is not a Luhn number will return INVALID_CARD, else return OK.
 */
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData);

/*
 * Description :
 * 1- This function asks for the transaction amount and saves it into terminal data.
 * 2- If the transaction amount is less than or equal to 0 will return INVALID_AMOUNT,
 *    else return TERMINAL_OK.
 */
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);

/*
 * Description :
 * 1- This function compares the transaction amount with the terminal max amount.
 * 2- If the transaction amount is larger than the terminal max amount will return
 *    EXCEED_MAX_AMOUNT, else return TERMINAL_OK.
 */
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);

/*
 * Description :
 * 1- This function takes the maximum allowed amount and stores it into terminal data.
 * 2- Transaction max amount is a float number.
 * 3- If transaction max amount less than or equal to 0 will return the INVALID_MAX_AMOUNT
 *    error, else return TERMINAL_OK.
 */
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount);

#endif /* TERMINAL_H_ */
