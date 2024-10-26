#include "BaseSer.h"
#include "../../../include/test20241026.h"
#include <sstream>
#include <boost/thread.hpp>

namespace ECOM {
namespace Components {
class PolarUnit1;
class PolarUnit3;
class OriginData1;
class Transformer: public BaseSer
{
public:
	Transformer(SerLoad *ser);
	~Transformer(void) {}

public:
	virtual void InitComponent();
	virtual void FreeComponent();
	virtual void ActivateComponent();
	virtual void UnActivateComponent();
private:
///////////////////////////////////////////////interface  instance/////////////////////////////////////////////////
//pointer to interface & get pointer
private:
	PolarUnit1 *pPolarUnit1;
public:
	PolarUnit1 *getProvideInterfacePolarUnit1()
	{
		return pPolarUnit1;
	}

//pointer to interface & get pointer
private:
	PolarUnit3 *pPolarUnit3;
public:
	PolarUnit3 *getProvideInterfacePolarUnit3()
	{
		return pPolarUnit3;
	}

///////////////////////////////////////////////port  instance/////////////////////////////////////////////////
private:
	OriginData1 *pOriginData1;
public:
	OriginData1 *getPublishPortOriginData1()
	{
		return pOriginData1;
	}

};

}
}
