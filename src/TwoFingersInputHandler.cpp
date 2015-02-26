#include "TwoFingersInputHandler.h"
//#include <mpm/M+MBaseChannel.h>

//#include <odl/ODEnableLogging.h>
#include <odl/ODLogging.h>

using namespace MplusM;
using namespace MplusM::Common;

TwoFingersInputHandler::TwoFingersInputHandler(HandlerFunction theHandler) :
    inherited(), _theHandler(theHandler)
{
    OD_LOG_ENTER(); //####
    OD_LOG_EXIT_P(this); //####
} // TwoFingersInputHandler::TwoFingersInputHandler

TwoFingersInputHandler::~TwoFingersInputHandler(void)
{
    OD_LOG_OBJENTER(); //####
    OD_LOG_OBJEXIT(); //####
} // TwoFingersInputHandler::~TwoFingersInputHandler

bool TwoFingersInputHandler::read(yarp::os::ConnectionReader & connection)
{
    OD_LOG_OBJENTER(); //####
    OD_LOG_P1("connection = ", &connection); //####
    bool result = true;
    
    try
    {
		yarp::os::Bottle aBottle;
            
        if (aBottle.read(connection))
        {
			if (_theHandler)
			{
				(*_theHandler) (aBottle);
			}
        }
    }
    catch (...)
    {
        OD_LOG("Exception caught"); //####
        throw;
    }
    OD_LOG_OBJEXIT_B(result); //####
    return result;
} // TwoFingersInputHandler::read
