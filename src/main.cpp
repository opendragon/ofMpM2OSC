#include "ofMain.h"
#include "mplusmReaderApp.h"
#undef check
#include <mpm/M+MCommon.h>

//========================================================================
int main(void)
{

    // declaring yarp object for networking purpose
    yarp::os::Network yarp;
    
	ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new mplusmReaderApp());

}
