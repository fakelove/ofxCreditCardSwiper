
#ifndef _CREDITCARDSCANNERUTILS_H
#define _CREDITCARDSCANNERUTILS_H
#pragma once
#include "ofLog.h"

namespace ccsaparams
{
    int     windowHeight    =   768;
    int     windowWidth     =   1024;
}

/*namespace ccsalogging
{
    const   std::string kLogFilename  =   "App.log";
    
    void writeToLogFile( const std::string& aMessage, ofLogLevel aLogLevel )
    {
        ofSetLogLevel(aLogLevel);
        ofLog() << aMessage;
        ofLogToFile( kLogFilename, true );
        ofLogToConsole();
    }
    
    void writeToLogFile( const std::string& aMessage )
    {
        ofSetLogLevel(OF_LOG_NOTICE);
        ofLog() << aMessage;
        ofLogToFile( kLogFilename, true );
        ofLogToConsole();
    }
}*/

#endif
