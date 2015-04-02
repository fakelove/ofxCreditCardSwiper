#include "CreditCardScannerApp.h"


// Margin constants
const float kLeftMargin                 =       100.0f;
const float kTopMargin                  =       100.0f;

// Spacing Constants
const float kVerticalBtnSpacing         =       30.0f;
const float kTextToBtnSpacing           =       5.0f;

// Sizing Constants
ofVec2f     kBtnSize                    =       ofVec2f( 100.0f, 50.0f );

// Color Constants
ofColor     kBtnColor                   =       ofColor( 206.0f, 32.0f, 41.0f );

void CreditCardScannerApp::setup()
{

    mToggleDebugBtn = ofRectangle( kLeftMargin, kTopMargin, kBtnSize.x, kBtnSize.y );
}

void CreditCardScannerApp::update(){
    ccScan.update();
}

void CreditCardScannerApp::draw(){

    ofClear( ofColor::white );
    
    // Credit Card Scanner Debug
    //mCreditCardScanner.draw();
    
    // Debug Button
    ofSetColor( kBtnColor );
    ofRect( mToggleDebugBtn );
    
    ofSetColor( ofColor::black );
    ofDrawBitmapString("Toggle Debug", mToggleDebugBtn.getLeft(), mToggleDebugBtn.getTop() - kTextToBtnSpacing);
    
    ofSetColor( ofColor::black );
    
    ccScan.draw();

    
}

void CreditCardScannerApp::mouseReleased(int aX, int aY, int aButton )
{
    if ( mToggleDebugBtn.inside( aX, aY ) ){
        ccScan.toggleDebugMode();
    }
    
}




