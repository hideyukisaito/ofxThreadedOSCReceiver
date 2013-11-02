#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class ofxThreadedOSCReceiver : public ofThread
{
public:
    
    ~ofxThreadedOSCReceiver()
    {
        if (isThreadRunning()) stopThread();
    }
    
    void setup(int port)
    {
        receiver.setup(port);
    }
    
    void start()
    {
        startThread(true, false);
    }
    
    void stop()
    {
        stopThread();
    }
    
    void threadedFunction()
    {
        while (isThreadRunning())
        {
            if (lock())
            {
                while (receiver.hasWaitingMessages())
                {
                    if (receiver.getNextMessage(&msg))
                    {
                        ofxOscMessage m = msg;
                        ofNotifyEvent(messageReceived, m, this);
                    }
                    
                }
            }
            unlock();
        }
    }
    
    ofEvent<ofxOscMessage> messageReceived;
    
private:
    
    ofxOscReceiver receiver;
    ofxOscMessage msg;
    
};