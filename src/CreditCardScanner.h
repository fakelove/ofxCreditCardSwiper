//
//  CreditCardScanner.h
//  CreditCardScannerApp
//
//  Created by Justin Maurer on 1/5/15.
//
//  Card
//


#pragma once
#include "CreditCard.h"
#include "ofRectangle.h"
#include "ofMain.h"
#include "ofEvents.h"
#include <string>



class CreditCardScanner {
    
    public:
        enum Status
        {
            WAITING = 0,
            PROCESSING,
            VALID,
            INVALID,
            UNKNOWN
        };
    
        CreditCardScanner();
       // ~CreditCardScanner();
    
        void                                    setup();
        void                                    update();
        void                                    draw();
        void                                    keyDown( int aKey );
        void                                    keyPressed(ofKeyEventArgs & key);
        void                                    keyReleased(ofKeyEventArgs & key);


        std::string                             convertKeytoStr( int aKey );
        void                                    extractData();
        void                                    parseAllCapturedData();
        void                                    resetCapturedDataFlags();
        bool                                    hasAllDataBeenCaptured();
        bool                                    areErrorsDetected();
    
        void                                    fireStatusChangeEvent( const CreditCardScanner::Status& aStatus );
        Status                                  getStatus();
        std::string                             getTextStatus();
        static std::string                      getTextStatus( const CreditCardScanner::Status& aStatus );
    
        void                                    toggleDebugMode();
        void                                    enableDebugMode();
        void                                    disableDebugMode();
    
        ofEvent<CreditCardScanner::Status>      onStatusChange;
        ofEvent<std::string>                    onSuccessfulSwipe;

    private:
        static  const   char    kDelimeter          = '^';
        static  const   char    kStartSentinel      = '%';
        static  const   char    kEndSentinel        = '?';
        
        CreditCard                             mCreditCard;
        CreditCardScanner::Status              mStatus;
        std::string                            mCapturedCCData;
        std::string                            mLastUIDScanned;
        bool                                   mDebugEnabled;
        
        float                                  mStartScanTime;
        
        bool                                   mPerformTest;
        bool                                   mStartSentinelDetected;
        bool                                   mEndSentinelDetected;
        bool                                   mAckKeydowns;
        bool                                   mIgnoreKeydowns;
        bool                                   mShouldFireWaitingEventInUpdate;
        ofRectangle                            mTestButton;
        
        // Credit card data error checking functions
        bool                                   isCreditCardDataThresholdInvalid();
        bool                                   isCreditCardDataCharsInvalid();
        
    
};
