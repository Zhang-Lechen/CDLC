#pragma  once
#include "BaseSer.h"
#include "../../../include/test20241026.h"
namespace ECOM {
namespace Components {
class Sensor;
		class PolarUnit2 : public ECOM::Interface::ADD::Require::ADD,ECOM::Base::Interface
		{
		public:
			Sensor *pComponent;
			PolarUnit2(Sensor *pComponent,int interfaceID,std::string interfaceName,std::string serviceName,std::string interfaceType,std::string interfaceModifier);

			double add(HelloWorld &a);
		};
	}
}