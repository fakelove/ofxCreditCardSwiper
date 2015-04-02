//
//  CreditCard.cpp
//  CreditCardScannerApp
//
//  Created by Justin Maurer on 1/5/15.
//
//

#include "CreditCard.h"

CreditCard::CreditCard()
{
    mFormatCode                 =   '\0';
    mPrimaryAccountNumber       =   "";
    mName                       =   "";
    mExpirationDate             =   "";
    mServiceCode                =   "";
    mDiscretionaryData          =   "";
    mData                       =   "";
}

CreditCard::~CreditCard()
{
    
}

void CreditCard::resetAllInfo()
{
    mFormatCode                 =   '\0';
    mPrimaryAccountNumber       =   "";
    mName                       =   "";
    mExpirationDate             =   "";
    mServiceCode                =   "";
    mDiscretionaryData          =   "";
    mData                       =   "";
}