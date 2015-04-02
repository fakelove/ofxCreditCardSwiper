#include "ofMain.h"
#include "CreditCardScannerApp.h"
#include "CreditCardScannerUtils.h"

//========================================================================
int main( ){

	ofSetupOpenGL(ccsaparams::windowWidth, ccsaparams::windowHeight,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new CreditCardScannerApp());

}
