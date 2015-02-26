#if (! defined(TwoFingersInputHandler_H_))
# define TwoFingersInputHandler_H_ /* Header guard */

# include <mpm/M+MCommon.h>

typedef void (* HandlerFunction) (yarp::os::Bottle & data);

/*! @brief A handler for partially-structured input data. */
class TwoFingersInputHandler : public yarp::os::PortReader
{
public :

	/*! @brief The constructor. */
	TwoFingersInputHandler(HandlerFunction theHandler = NULL);

	/*! @brief The destructor. */
	virtual ~TwoFingersInputHandler(void);

protected :

private :

	COPY_AND_ASSIGNMENT_(TwoFingersInputHandler);

	/*! @brief Read an object from the input stream.
	@param connection The input stream that is to be read from.
	@returns @c true if the object was successfully read and @c false otherwise. */
	virtual bool read(yarp::os::ConnectionReader & connection);

public :

protected :

private :

	/*! @brief The class that this class is derived from. */
	typedef yarp::os::PortReader inherited;

	HandlerFunction _theHandler;

}; // TwoFingersInputHandler
        
#endif // ! defined(TwoFingersInputHandler_H_)
