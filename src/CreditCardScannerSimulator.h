//
//  SampleCreditCardData.h
//  CreditCardScannerApp
//
//  Created by Justin Maurer on 1/6/15.
//
//

//  ***** Word of caution ****
//  This class needs some work. It currently doesn't work simulating multiple swipes well
//  Or even a single swipe well for that matter. Will investigate later if have time
//  Class that adds sample credit card data and functions to simulate the scanning of users

#pragma once
#include "ofEvents.h"

class CreditCardScannerSimulator {

public:

    void setup()
    {
        mTimeSinceLastCardSwipeSimulation = -1.0f;
        mSampleDataArrIdx = 0;
        // Original Data
        // %B4847350318294483^YOU/A GIFT FOR^20101211000000998000000?;4847350318294483=201012110000998?
        
        // Actual Data
        // 5b48473503182944836you/a gift for620101211000000998000000/;4847350318294483=201012110000998/
        mSampleCardDatas.push_back("%B1111111111111111^YOU/A GIFT FOR^20101211000000998000000?;4847350318294483=201012110000998?");
        mSampleCardDatas.push_back("%B2222222222222222^YOU/A GIFT FOR^20101211000000998000000?;4847350318294483=201012110000998?");
        mSampleCardDatas.push_back("%B3333333333333333^YOU/A GIFT FOR^20101211000000998000000?;4847350318294483=201012110000998?");
        
        mSampleCardDatasArr[0] = "%B1111111111111111^YOU/A GIFT FOR^20101211000000998000000?;4847350318294483=201012110000998?";
        mSampleCardDatasArr[1] = "%B2222222222222222^YOU/A GIFT FOR^20101211000000998000000?;4847350318294483=201012110000998?";
        mSampleCardDatasArr[2] = "%B3333333333333333^YOU/A GIFT FOR^20101211000000998000000?;4847350318294483=201012110000998?";
        
    }
    
    void update()
    {

    }
    
    void simulateMultipleCardSwipes()
    {
        int numElements = sizeof(mSampleCardDatasArr)/sizeof(std::string);

        if ( mSampleDataArrIdx == (numElements - 1) ){
            mSampleDataArrIdx = 0;
        }
        
        simulateCardSwipe( mSampleCardDatasArr[mSampleDataArrIdx] );

        mSampleDataArrIdx++;
       /* cout << ofGetElapsedTimef() << std::endl;
        if ( ofGetElapsedTimef() - mTimeSinceLastCardSwipeSimulation ){
            
        }
        // Just performing KeyUp/Released events for now
        for ( auto iter = mSampleCardDatas.begin(); iter != mSampleCardDatas.end(); iter++ )
        {
            simulateCardSwipe( *iter );
            usleep( 3000 );
        }*/
    }
                              
    void simulateCardSwipe( const std::string& aCardData )
    {
        for ( auto iter = aCardData.begin(); iter != aCardData.end(); iter++ )
        {
            dispatchCardData( *iter );
            usleep( 10 );
        }
    }
    
    void dispatchCardData( int aKey )
    {
        ofKeyEventArgs keyEvent;
        keyEvent.key = aKey;
        ofNotifyKeyPressed(keyEvent.key);
    }

private:
    int                         mSampleDataArrIdx;
    float                       mTimeSinceLastCardSwipeSimulation;
    std::string                 mSampleCardDatasArr[3];
    std::vector<std::string>    mSampleCardDatas;
    
    
    
};
