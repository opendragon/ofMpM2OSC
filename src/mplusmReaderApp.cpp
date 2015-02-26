#include "mplusmReaderApp.h"
#include "TwoFingersInputHandler.h"
#include <mpm/M+MGeneralChannel.h>

//  #############################################################################################
//                  COMMAND LINE commands for mplusm and yarp
//                  MPLUSM Commands:
//                  mpmPortLister - Lists out the active mplusm/yarp ports
//                  mpmFindServices - Lets you search through the service by providing search criterion
//                  mpmVersion - Shows the current version of mplusm, ace and yarp
//                  mpmServiceMetrics - Displays the network traffic of a particular of all services
//                  mpmServiceLister - Descriptive information on a particular or all services
//                  mpmRequestInfo - Displays information on a one or more requests
//
//                  YARP Commands: (Passive connection)
//                  yarp conf --clean - everytime the yarp server is launched from a different ip
//                  address, its configuration needs to be clean
//                  so that other mplusm apps and services can point to new ip address.
//                  yarp name list - Lists the currently active ports
//
//
//  #############################################################################################

#define NATIVE_YARP /* */
#define DO_TWO_FINGERS /* */

/*  Sample snapshot for Leap Motion Sensor Protocol
    (((confidence 0.0) (direction (-0.771852 0.442157 -0.456882)) (wristposition (113.053436 103.811607 -34.948051)) (id 58) (palmposition (67.670517 123.755173 -52.838657)) (fingers (((tipvelocity (0.0 0.0 0.0)) (type thumb) (direction (-0.931179 0.30259 0.203334)) (bones (((distal (98.252403 95.523132 -10.749332)) (proximal (98.252403 95.523132 -10.749332)) (direction (0.0 0.0 0.0)) (length 0.0)) ((distal (53.477139 110.077187 -0.960008)) (proximal (98.252403 95.523132 -10.749332)) (direction (0.931107 -0.302653 -0.20357)) (length 48.088207)) ((distal (22.891573 120.016068 5.71871)) (proximal (53.477139 110.077187 -0.960008)) (direction (0.931179 -0.30259 -0.203334)) (length 32.846058)) ((distal (2.199805 127.079865 11.220633)) (proximal (22.891573 120.016068 5.71871)) (direction (0.917762 -0.313307 -0.244032)) (length 22.545898)))) (id 580) (length 50.206398) (extended yes) (tipposition (6.958912 125.455193 9.95519))) ((tipvelocity (0.0 0.0 0.0)) (type index) (direction (-0.89006 -0.302533 -0.340978)) (bones (((distal (38.664074 138.417252 -42.362022)) (proximal (102.0271 116.197884 -19.680176)) (direction (0.894031 -0.313508 0.320033)) (length 70.873405)) ((distal (0.288223 141.711151 -57.508072)) (proximal (38.664074 138.417252 -42.362022)) (direction (0.927224 -0.079586 0.365954)) (length 41.387901)) ((distal (-20.436472 134.666794 -65.447617)) (proximal (0.288223 141.711151 -57.508072)) (direction (0.89006 0.302533 0.340978)) (length 23.284595)) ((distal (-33.213524 125.448242 -70.209824)) (proximal (-20.436472 134.666794 -65.447617)) (direction (0.776275 0.560077 0.28933)) (length 16.459446)))) (id 581) (length 56.652321) (extended yes) (tipposition (-30.274803 127.568512 -69.114517))) ((tipvelocity (0.0 0.0 0.0)) (type middle) (direction (-0.862722 -0.215451 -0.457484)) (bones (((distal (49.424152 138.425323 -60.76619)) (proximal (105.915588 117.770111 -30.775936)) (direction (0.840507 -0.307318 0.44621)) (length 67.211121)) ((distal (9.424829 135.481644 -84.164902)) (proximal (49.424152 138.425323 -60.76619)) (direction (0.861424 0.063395 0.503914)) (length 46.433941)) ((distal (-14.208801 129.579529 -96.697327)) (proximal (9.424829 135.481644 -84.164902)) (direction (0.862722 0.215451 0.457484)) (length 27.394255)) ((distal (-29.601921 123.771011 -104.249992)) (proximal (-14.208801 129.579529 -96.697327)) (direction (0.850293 0.320854 0.417198)) (length 18.103308)))) (id 582) (length 64.550774) (extended yes) (tipposition (-26.061504 125.106972 -102.512878))) ((tipvelocity (0.0 0.0 0.0)) (type ring) (direction (-0.837531 -0.153533 -0.524375)) (bones (((distal (64.093536 133.795853 -76.427025)) (proximal (110.21769 116.251999 -41.696407)) (direction (0.764349 -0.290729 0.575541)) (length 60.344345)) ((distal (28.198427 128.872375 -99.663406)) (proximal (64.093536 133.795853 -76.427025)) (direction (0.833952 0.114387 0.539851)) (length 43.042179)) ((distal (5.847433 124.77507 -113.657295)) (proximal (28.198427 128.872375 -99.663406)) (direction (0.837531 0.153533 0.524375)) (length 26.686771)) ((distal (-9.256451 121.524368 -122.891968)) (proximal (5.847433 124.77507 -113.657295)) (direction (0.839139 0.180602 0.513058)) (length 17.999266)))) (id 583) (length 62.067291) (extended yes) (tipposition (-5.782557 122.272034 -120.76799))) ((tipvelocity (0.0 0.0 0.0)) (type pinky) (direction (-0.655466 -0.304569 -0.691087)) (bones (((distal (77.098434 124.944641 -89.769348)) (proximal (114.234085 107.806198 -51.722366)) (direction (0.664797 -0.30681 0.681111)) (length 55.860142)) ((distal (55.164188 115.597015 -114.096748)) (proximal (77.098434 124.944641 -89.769348)) (direction (0.643925 0.274419 0.714181)) (length 34.063347)) ((distal (42.813889 109.858315 -127.11821)) (proximal (55.164188 115.597015 -114.096748)) (direction (0.655466 0.30457 0.691087)) (length 18.842003)) ((distal (31.809444 104.4655 -138.32309)) (proximal (42.813889 109.858315 -127.11821)) (direction (0.662714 0.324768 0.674785)) (length 16.605106)))) (id 584) (length 48.659607) (extended yes) (tipposition (34.340466 105.705849 -135.745956))))) (arm (((direction (-0.733511 0.480762 -0.480447)) (elbowposition (303.843201 -21.237085 90.018715))))) (side right) (palmvelocity (0.0 0.0 0.0)) (palmnormal (-0.429359 -0.892474 -0.138354)))) ()
*/

static ofxOscSender sender;

#define FILTER_FACTOR 0.9

#if defined(DO_TWO_FINGERS)
# define LEFT_FINGER_MASK    0x01
# define RIGHT_FINGER_MASK   0x02
# define LEFT_FINGER_OFFSET  1
# define RIGHT_FINGER_OFFSET 4
# define LEAP_PORT_NAME "/ECUADTwoFingersReader"
#else // ! defined(DO_TWO_FINGERS)
# define LEAP_PORT_NAME "/ECUADLeapMotionReader"
#endif // ! defined(DO_TWO_FINGERS)

#if defined(NATIVE_YARP)
yarp::os::Port * port = NULL;
# if defined(DO_TWO_FINGERS)
TwoFingersInputHandler * handler = NULL;
# endif // DO_TWO_FINGERS
#else // ! defined(NATIVE_YARP)
MplusM::Common::GeneralChannel * port = NULL;
#endif // ! defined(NATIVE_YARP)

static bool finger1DataValid = false;
static bool finger2DataValid = false;

static double oldFinger1X = 0;
static double oldFinger1Y = 0;
static double oldFinger1Z = 0;
static double oldFinger2X = 0;
static double oldFinger2Y = 0;
static double oldFinger2Z = 0;

#if defined(DO_TWO_FINGERS)
static double getNumber(yarp::os::Value & aValue)
{
	double result;

	if (aValue.isInt())
	{
		result = aValue.asInt();
	}
	else if (aValue.isDouble())
	{
		result = aValue.asDouble();
	}
	else
	{
		result = 0.0;
	}
	return result;
} // getNumber

static void doFingers(yarp::os::Bottle & aBottle)
{
	if (7 == aBottle.size())
	{
		yarp::os::Value & flagsVal = aBottle.get(0);

		if (flagsVal.isInt())
		{
			double xPos;
			double yPos;
			double zPos;
            double xFiltered;
            double yFiltered;
            double zFiltered;
			int    flags = flagsVal.asInt();

			if (flags & LEFT_FINGER_MASK)
			{
                ofxOscMessage     firstFinger;
				yarp::os::Value & posXVal = aBottle.get(LEFT_FINGER_OFFSET);
				yarp::os::Value & posYVal = aBottle.get(LEFT_FINGER_OFFSET + 1);
				yarp::os::Value & posZVal = aBottle.get(LEFT_FINGER_OFFSET + 2);

				xPos = getNumber(posXVal);
				yPos = getNumber(posYVal);
				zPos = getNumber(posZVal);
                if (finger1DataValid)
                {
                    xFiltered = (FILTER_FACTOR * xPos) + ((1 - FILTER_FACTOR) * oldFinger1X);
                    yFiltered = (FILTER_FACTOR * yPos) + ((1 - FILTER_FACTOR) * oldFinger1Y);
                    zFiltered = (FILTER_FACTOR * zPos) + ((1 - FILTER_FACTOR) * oldFinger1Z);
                }
                else
                {
                    xFiltered = xPos;
                    yFiltered = yPos;
                    zFiltered = zPos;
                }
                oldFinger1X = xPos;
                oldFinger1Y = yPos;
                oldFinger1Z = zPos;
                finger1DataValid = true;
                firstFinger.setAddress("/firstFinger");
                firstFinger.addFloatArg(xFiltered);
                firstFinger.addFloatArg(yFiltered);
                firstFinger.addFloatArg(zFiltered);
                sender.sendMessage(firstFinger);
			}
			if (flags & RIGHT_FINGER_MASK)
			{
                ofxOscMessage     secondFinger;
				yarp::os::Value & posXVal = aBottle.get(RIGHT_FINGER_OFFSET);
				yarp::os::Value & posYVal = aBottle.get(RIGHT_FINGER_OFFSET + 1);
				yarp::os::Value & posZVal = aBottle.get(RIGHT_FINGER_OFFSET + 2);

				xPos = getNumber(posXVal);
				yPos = getNumber(posYVal);
				zPos = getNumber(posZVal);
                if (finger2DataValid)
                {
                    xFiltered = (FILTER_FACTOR * xPos) + ((1 - FILTER_FACTOR) * oldFinger2X);
                    yFiltered = (FILTER_FACTOR * yPos) + ((1 - FILTER_FACTOR) * oldFinger2Y);
                    zFiltered = (FILTER_FACTOR * zPos) + ((1 - FILTER_FACTOR) * oldFinger2Z);
                }
                else
                {
                    xFiltered = xPos;
                    yFiltered = yPos;
                    zFiltered = zPos;
                }
                oldFinger2X = xPos;
                oldFinger2Y = yPos;
                oldFinger2Z = zPos;
                finger2DataValid = true;
                secondFinger.setAddress("/secondFinger");
                secondFinger.addFloatArg(xFiltered);
                secondFinger.addFloatArg(yFiltered);
                secondFinger.addFloatArg(zFiltered);
                sender.sendMessage(secondFinger);
			}
		}
	}
} // doFingers
#else // ! DO_TWO_FINGERS
static void dumpFingerProps(const int            fingerNumber,
                            yarp::os::Property & fingerProps)
{
    yarp::os::Value & tipPosition(fingerProps.find("tipposition"));
    
    if (tipPosition.isList())
    {
        yarp::os::Bottle * positionData = tipPosition.asList();
        
        if (positionData && (3 == positionData->size()))
        {
            double            xPos;
            double            yPos;
            double            zPos;
            double            xFiltered;
            double            yFiltered;
            double            zFiltered;
            yarp::os::Value & posX = positionData->get(0);
            yarp::os::Value & posY = positionData->get(1);
            yarp::os::Value & posZ = positionData->get(2);

            xPos = getNumber(posX);
            yPos = getNumber(posY);
            zPos = getNumber(posZ);
            if (fingerNumber == 1)
            {
                ofxOscMessage firstFinger;
                
                firstFinger.setAddress("/firstFinger");
                if (finger1DataValid)
                {
                    xFiltered = (FILTER_FACTOR * xPos) + ((1 - FILTER_FACTOR) * oldFinger1X);
                    yFiltered = (FILTER_FACTOR * yPos) + ((1 - FILTER_FACTOR) * oldFinger1Y);
                    zFiltered = (FILTER_FACTOR * zPos) + ((1 - FILTER_FACTOR) * oldFinger1Z);
                }
                else
                {
                    xFiltered = xPos;
                    yFiltered = yPos;
                    zFiltered = zPos;
                }
                oldFinger1X = xPos;
                oldFinger1Y = yPos;
                oldFinger1Z = zPos;
                finger1DataValid = true;
                firstFinger.addFloatArg(xFiltered);
                firstFinger.addFloatArg(yFiltered);
                firstFinger.addFloatArg(zFiltered);
                sender.sendMessage(firstFinger);
            }
            else if (fingerNumber == 2)
            {
                ofxOscMessage secondFinger;
                
                secondFinger.setAddress("/secondFinger");
                if (finger2DataValid)
                {
                    xFiltered = (FILTER_FACTOR * xPos) + ((1 - FILTER_FACTOR) * oldFinger2X);
                    yFiltered = (FILTER_FACTOR * yPos) + ((1 - FILTER_FACTOR) * oldFinger2Y);
                    zFiltered = (FILTER_FACTOR * zPos) + ((1 - FILTER_FACTOR) * oldFinger2Z);
                }
                else
                {
                    xFiltered = xPos;
                    yFiltered = yPos;
                    zFiltered = zPos;
                }
                oldFinger2X = xPos;
                oldFinger2Y = yPos;
                oldFinger2Z = zPos;
                finger2DataValid = true;
                firstFinger.addFloatArg(xFiltered);
                firstFinger.addFloatArg(yFiltered);
                firstFinger.addFloatArg(zFiltered);
                sender.sendMessage(secondFinger);
            }
        }
    }
} // dumpFingerProps

static void dumpHandData(const int            fingerNumber,
						 yarp::os::Property & handData)
{
    yarp::os::Value & fingerValue(handData.find("fingers"));
    
    if (fingerValue.isList())
    {
        yarp::os::Bottle * fingers = fingerValue.asList();
        
        if (fingers)
        {
            int fingerCount = fingers->size();
            
            if (1 <= fingerCount)
            {
                yarp::os::Value & finger1 = fingers->get(0);
                
                if (finger1.isDict())
                {
                    yarp::os::Property * fingerProps = finger1.asDict();
                    
                    if (fingerProps)
                    {
                        dumpFingerProps(fingerNumber, *fingerProps);
                    }
                }
                else if (finger1.isList())
                {
                    yarp::os::Bottle * fingerList = finger1.asList();
                    
                    if (fingerList)
                    {
                        yarp::os::Property fingerProps;
                        
                        if (MplusM::ListIsReallyDictionary(*fingerList, fingerProps))
                        {
                            dumpFingerProps(fingerNumber, fingerProps);
                        }
                    }
                }
            }
        }
    }
} // dumpHandData

static void processLeapData(const yarp::os::Bottle & inData)
{
    if (2 == inData.size())
    {
        yarp::os::Value & firstTopValue = inData.get(0);
        
        if (firstTopValue.isList())
        {
            yarp::os::Bottle * handList = firstTopValue.asList();
            
            if (handList)
            {
                int handCount = handList->size();
                
                if (1 < handCount)
                {
                    yarp::os::Value & hand1Value = handList->get(0);
					yarp::os::Value & hand2Value = handList->get(1);
                    
                    if (hand1Value.isDict())
                    {
                        yarp::os::Property * handData = hand1Value.asDict();
                        
                        if (handData)
                        {
                            dumpHandData(1, *handData);
                        }
                    }
                    else if (hand1Value.isList())
                    {
                        yarp::os::Bottle * asList = hand1Value.asList();
                        
                        if (asList)
                        {
                            yarp::os::Property handData;
                            
                            if (MplusM::ListIsReallyDictionary(*asList, handData))
                            {
                                dumpHandData(1, handData);
                            }
                        }
                    }
                    if (hand2Value.isDict())
                    {
                        yarp::os::Property * handData = hand2Value.asDict();
                        
                        if (handData)
                        {
                            dumpHandData(2, *handData);
                        }
                    }
                    else if (hand2Value.isList())
                    {
                        yarp::os::Bottle * asList = hand2Value.asList();
                        
                        if (asList)
                        {
                            yarp::os::Property handData;
                            
                            if (MplusM::ListIsReallyDictionary(*asList, handData))
                            {
                                dumpHandData(2, handData);
                            }
                        }
                    }
                }
            }
        }
    }
} // processLeapData
#endif // ! defined(DO_TWO_FINGERS)

//--------------------------------------------------------------
void mplusmReaderApp::setup()
{
    // open an outgoing connection to HOST:PORT
    sender.setup(HOST, PORT);
    
#if defined(NATIVE_YARP)
    //open a port for communication purpose
	port = new yarp::os::Port();
    //port->setWriteOnly();
    port->setReadOnly();
    //name for the port
# if defined(DO_TWO_FINGERS)
	handler = new TwoFingersInputHandler(doFingers);
# endif // DO_TWO_FINGERS
	port->setReader(*handler);
    port->open(LEAP_PORT_NAME);
#else // ! defined(NATIVE_YARP)
    // boolean paramter suggests if the port is output or not
    port = new MplusM::Common::GeneralChannel(true);
    port->openWithRetries(LEAP_PORT_NAME, STANDARD_WAIT_TIME);
#endif // ! defined(NATIVE_YARP)
} // setup

//--------------------------------------------------------------
void mplusmReaderApp::update()
{
#if (! defined(DO_TWO_FINGERS))
    yarp::os::Bottle message;
    
    // Read from the port
#if defined(NATIVE_YARP)
    port->read(message);
#else // ! defined(NATIVE_YARP)
    port->read(message);
#endif // ! defined(NATIVE_YARP)

    processLeapData(message);
//    printf("size check: %d\n", message.find("id").asInt());
    
#endif // ! defined(DO_TWO_FINGERS)
    yarp::os::Time::delay(0.1);
} // update

//--------------------------------------------------------------
void mplusmReaderApp::exit()
{
    port->close();
    delete port;
} // exit

//--------------------------------------------------------------
void mplusmReaderApp::draw()
{
} // draw

//--------------------------------------------------------------
void mplusmReaderApp::keyPressed(int key)
{
} // keyPressed

//--------------------------------------------------------------
void mplusmReaderApp::keyReleased(int key)
{
} // keyReleased

//--------------------------------------------------------------
void mplusmReaderApp::mouseMoved(int x,
                                 int y)
{
} // mouseMoved

//--------------------------------------------------------------
void mplusmReaderApp::mouseDragged(int x,
                                   int y,
                                   int button)
{
} // mouseDragged

//--------------------------------------------------------------
void mplusmReaderApp::mousePressed(int x,
                                   int y,
                                   int button)
{
} // mousePressed

//--------------------------------------------------------------
void mplusmReaderApp::mouseReleased(int x,
                                    int y,
                                    int button)
{
} // mouseReleased

//--------------------------------------------------------------
void mplusmReaderApp::windowResized(int w,
                                    int h)
{
} // windowResized

//--------------------------------------------------------------
void mplusmReaderApp::gotMessage(ofMessage msg)
{
} // gotMessage

//--------------------------------------------------------------
void mplusmReaderApp::dragEvent(ofDragInfo dragInfo)
{
} // dragEvent
