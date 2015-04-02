#pragma once

#include "ofMain.h"
//#include "CreditCardScannerSimulator.h"
#include "CreditCardScanner.h"


class CreditCardScannerApp : public ofBaseApp{
    
	public:
		void setup();
		void update();
		void draw();
    
        void mouseReleased(int aX, int aY, int aButton );
    
        CreditCardScanner ccScan;

    private:
        ofRectangle                     mToggleDebugBtn;
};
