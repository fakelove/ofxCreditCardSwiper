//
//  CreditCardScanner.cpp
//  CreditCardScannerApp
//
//  Created by Justin Maurer on 1/5/15.
//
//

#include "CreditCardScanner.h"
#include "ofUtils.h"
#include "Poco/RegularExpression.h"
#include <map>

const   int     kCCDataErrorThresholdLength     =   16;     //  Invalid CC data length
const   float   kScanThresholdTime              =   1.0f;   //  In Seconds
const   float   kVerticalTextDebugSpacing       =   15.0f;  //  In Pixels
const   float   kBottomMargin                   =   10.0f;  //  In pixels

CreditCardScanner::CreditCardScanner()
{
    ofRegisterKeyEvents(this);
    
    mCreditCard = CreditCard();

    mStatus                             =       CreditCardScanner::WAITING;
    mCapturedCCData                     =       "";
    mLastUIDScanned                     =       "";
    mPerformTest                        =       false;
    mStartSentinelDetected              =       false;
    mEndSentinelDetected                =       false;
    mIgnoreKeydowns                     =       false;
    mShouldFireWaitingEventInUpdate     =       true;
    mStartScanTime                      =       -1;
}

/*CreditCardScanner::~CreditCardScanner()
{
    ofUnregisterKeyEvents(this);
}*/

void CreditCardScanner::setup()
{
    // Fires waiting status upon creation of app
    //fireStatusChangeEvent(CreditCardScanner::WAITING);
}

void CreditCardScanner::update()
{
    if ( ofGetElapsedTimef() - mStartScanTime > kScanThresholdTime ){

        
        // Acknowledge keydowns after threshold since first scan time has passed
        mIgnoreKeydowns     =   false;
        mStatus             =   CreditCardScanner::WAITING;
        mCapturedCCData     =   "";
        fireStatusChangeEvent(CreditCardScanner::WAITING);
        
    }
}

void CreditCardScanner::draw()
{
    if ( mDebugEnabled ){
        ofSetColor(0.0f, 0.0f, 0.0f);
        ofDrawBitmapString("Last ID Detected: " + mLastUIDScanned, 10, ofGetWindowHeight() - kBottomMargin - kVerticalTextDebugSpacing*2 );
        ofDrawBitmapString("Captured Credit Card Data: " + mCapturedCCData, 10, ofGetWindowHeight() - kBottomMargin - kVerticalTextDebugSpacing );
        ofDrawBitmapString("Credit Card Status: " + getTextStatus(), 10, ofGetWindowHeight() - kBottomMargin );
    }
}

void CreditCardScanner::toggleDebugMode()
{
    mDebugEnabled = !mDebugEnabled;
}

void CreditCardScanner::enableDebugMode()
{
    mDebugEnabled = true;
}

void CreditCardScanner::disableDebugMode()
{
    mDebugEnabled = false;
}

void CreditCardScanner::fireStatusChangeEvent( const CreditCardScanner::Status& aStatus )
{
    // Fire status change event
    CreditCardScanner::Status status = aStatus;
    ofNotifyEvent( onStatusChange, status );
}

std::string CreditCardScanner::getTextStatus()
{
    std::string status;
    switch( mStatus )
    {
    case CreditCardScanner::WAITING:        status = "Waiting";         break;
    case CreditCardScanner::PROCESSING:     status = "Processing";      break;
    case CreditCardScanner::VALID:          status = "Valid";           break;
    case CreditCardScanner::INVALID:        status = "Invalid";         break;
    case CreditCardScanner::UNKNOWN:        status = "Unknown";         break;
    default: status = "Unknown:blank";
    }
  
    return status;
}

std::string  CreditCardScanner::getTextStatus( const CreditCardScanner::Status& aStatus )
{
    std::string status;
    switch( aStatus )
    {
        case CreditCardScanner::WAITING:        status = "waiting";         break;
        case CreditCardScanner::PROCESSING:     status = "processing";      break;
        case CreditCardScanner::VALID:          status = "valid";           break;
        case CreditCardScanner::INVALID:        status = "invalid";         break;
        case CreditCardScanner::UNKNOWN:        status = "unknown";         break;
        default: status = "unknown:blank";
    }
    
    return status;
}

void CreditCardScanner::resetCapturedDataFlags()
{
    mStartSentinelDetected  =   false;
    mEndSentinelDetected    =   false;
}

bool CreditCardScanner::hasAllDataBeenCaptured()
{
    // Using this site as a reference: http://stackoverflow.com/questions/2121881/parse-credit-card-input-from-magnetic-stripe
    // Valid card needs to have 1 start sentinel % -- will assume that is beginning of card data
    // has 1 format code B following
    // Has a Primary Account Number (PAN) following, upto 19 chars
    // Contains a field seperator, generally ^
    // Contains a name field
    // Contains a field seperator, generally ^
    // Contains an Expiration Data
    // Contains discrentionary data
    // Contains End sentinel

    // Unforunately the data in an example card using, a Vanilla gift visa card, does not completely abide by this format
    // Consequently, we're using the following method below:
    
    int startSentinelPos = mCapturedCCData.find("%");
    
    if ( startSentinelPos > -1 ){
        mStartSentinelDetected = true;
    }
    
    // In this Credit card there are currently two end-sentinels that are being detected
    // If 2 sentinels are detected let's assume that all data for that the end of the card is captured
    int secondSentinelCount = std::count( mCapturedCCData.begin(), mCapturedCCData.end(), '?');
    if ( secondSentinelCount == 2 ){
        mEndSentinelDetected = true;
    }
    
    if ( mStartSentinelDetected && mEndSentinelDetected ){
        mCreditCard.setData( mCapturedCCData );
        return true;
    }
    
    return false;
}

bool CreditCardScanner::areErrorsDetected()
{
    if ( isCreditCardDataThresholdInvalid() || isCreditCardDataCharsInvalid() )
    {
        return true;
    }
    
    return false;
}

bool CreditCardScanner::isCreditCardDataThresholdInvalid()
{
    if ( mCapturedCCData.length() <= kCCDataErrorThresholdLength ){
        return true;
    }
    
    return false;
}


bool CreditCardScanner::isCreditCardDataCharsInvalid()
{
    // Regex detects letters or any special characters
    std::string pattern = "^[a-zA-Z!@#$%^&*()_+\-=\[\]{};':\"\\|,.<>\/?]*$";
    
    Poco::RegularExpression regex( pattern );
    
    if ( regex.match(mCapturedCCData) ){
        return true;
    }

    return false;
}

void CreditCardScanner::parseAllCapturedData()
{
    // Parse CreditCard.mData <==> UID for Credit Cards
    // Getting credit card data <==> uid
    int startIdPos = mCapturedCCData.find( "B" ) + 1;
    int endIdPos = mCapturedCCData.find("^");

    int idLength = endIdPos - startIdPos;
    std::string uid = mCapturedCCData.substr( startIdPos, idLength );
    mCreditCard.setPrimaryAccountNumber( uid );

}

void CreditCardScanner::keyPressed(ofKeyEventArgs & args )
{
    if ( mIgnoreKeydowns ){
        return;
    }
    
    if ( mStatus == CreditCardScanner::WAITING ){
        mStatus = CreditCardScanner::PROCESSING;
        fireStatusChangeEvent(CreditCardScanner::PROCESSING);
        mStartScanTime = ofGetElapsedTimef();
    }
    
    // Look for illegal characters regardless if all data has been captured
    if ( isCreditCardDataCharsInvalid() ){
        mStatus = CreditCardScanner::INVALID;
        fireStatusChangeEvent( CreditCardScanner::INVALID );
        return;
    }
    
    // Detect any errors
    if ( hasAllDataBeenCaptured() && areErrorsDetected() ){
        mStatus = CreditCardScanner::INVALID;
        
        // Fire status change event
        fireStatusChangeEvent( CreditCardScanner::INVALID );
        
        // Reset flags and credit card info
        resetCapturedDataFlags();
        mCreditCard.resetAllInfo();
        
        // Extra keys will keep coming through we want to not allow this
        // until time threshold since scan started is up
        mIgnoreKeydowns = true;
        return;
    }
    
    if ( hasAllDataBeenCaptured() ){
        
        parseAllCapturedData();
        
        // Send event
        std::string uid = mCreditCard.getPrimaryAccountNumber();
        ofNotifyEvent( onSuccessfulSwipe, uid );
        mStatus  = CreditCardScanner::VALID;
        
        // Fire status change event
        fireStatusChangeEvent( CreditCardScanner::VALID );
        
        // Save last scanned ID for debug display
        mLastUIDScanned = mCreditCard.getPrimaryAccountNumber();
        
        // Reset flags and credit card info
        resetCapturedDataFlags();
        mCreditCard.resetAllInfo();
        
        // Extra keys will keep coming through we want to not allow this
        // until time threshold since scan started is up
        mIgnoreKeydowns = true;
    }
    
    // Append string to full CC data string
    mCapturedCCData += convertKeytoStr( args.key );
    
}

void CreditCardScanner::keyReleased(ofKeyEventArgs & args )
{
    
}

std::string CreditCardScanner::convertKeytoStr( int aKey )
{
    // Convert ascii key to char
    char charTyped = static_cast<char>( aKey );
    
    // Convert char to string
    stringstream ss;
    string stringTyped;
    
    ss << charTyped;
    ss >> stringTyped;
 
    return stringTyped;
}