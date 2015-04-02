//
//  CreditCard.h
//  CreditCardScannerApp
//
//  Created by Justin Maurer on 1/5/15.
//
//

#pragma once
#include <string>
#include <vector>

class CreditCard {
    
    public:
        CreditCard();
        ~CreditCard();
    
        void setFields();
    
        // Credit Card accessor functions
        char                getFormatCode(){ return mFormatCode; }
        std::string         getPrimaryAccountNumber(){ return mPrimaryAccountNumber; }
        std::string         getName(){ return mName; }
        std::string         getExpirationDate(){ return mExpirationDate; }
        std::string         getServiceCode(){ return mServiceCode; }
        std::string         getDiscretionaryData(){ return mDiscretionaryData; }
    
        void                setFormatCode( char aFormatCode ){ mFormatCode = aFormatCode; }
        void                setPrimaryAccountNumber( const std::string& aPrimaryAccountNumber ){ mPrimaryAccountNumber = aPrimaryAccountNumber; }
        void                setName( const std::string& aName ){ mName = aName; }
        void                setExpirationDate( const std::string& aExpirationDate ){ mExpirationDate = aExpirationDate; }
        void                setServiceCode( const std::string& aServiceCode ){ mServiceCode = aServiceCode; }
        void                setDistretionaryData( const std::string aDiscretionaryData ){ mDiscretionaryData = aDiscretionaryData; }
        void                setData( const std::string& aData ){ mData = aData; }
    
        void                resetAllInfo();
    
        std::string                     removeDataSentinels();
        std::vector<std::string>        splitDataString();
    
    private:
    
        char                mFormatCode;
        std::string         mPrimaryAccountNumber;
        std::string         mName;
        std::string         mExpirationDate;
        std::string         mServiceCode;
        std::string         mDiscretionaryData;
        std::string         mData;
    
    
};