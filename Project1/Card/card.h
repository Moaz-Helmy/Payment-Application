/******************************************************************************
 *
 * Module: Card Module
 *
 * File Name: card.h
 *
 * Description: Header file for the Card module.
 *
 * Author: Moaz Mohamed
 *
 *******************************************************************************/

#ifndef CARD_H_
#define CARD_H_

/*******************************************************************************
 *                                Includes                                     *
 *******************************************************************************/
#include "famous_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ASCII_OF_0 48
#define ASCII_OF_9 57

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
	CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * 1- This function will ask for the cardholder's name and store it into card data.
 * 2- Card holder name is 24 characters string max and 20 min.
 * 3- If the cardholder name is NULL, less than 20 characters or more than 24 will
 * 	  return WRONG_NAME error, else return CARD_OK.
 */
EN_cardError_t getCardHolderName(ST_cardData_t *cardData);

/*
 * Description :
 * 1- This function will ask for the card expiry date and store it in card data.
 * 2- Card expiry date is 5 characters string in the format "MM/YY", e.g "05/25".
 * 3- If the card expiry date is NULL, less or more than 5 characters, or has the
 * 	  wrong format will return WRONG_EXP_DATE error, else return CARD_OK.
 */
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);

/*
 * Description :
 * 1- This function will ask for the card's Primary Account Number and store it in card data.
 * 2- PAN is 20 characters numeric only string 19 character max, and 16 character min.
 * 3- If the PAN is NULL, less than 16 or more than 19 characters, will return WRONG_PAN error,
 *    else return CARD_OK.
 */
EN_cardError_t getCardPAN(ST_cardData_t *cardData);

#endif /* CARD_H_ */
