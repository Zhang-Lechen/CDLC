#pragma  once
			#include "BaseSer.h"
			#include "../../../include/test20241026.h"
			namespace ECOM {
			namespace Components {
			class Navidisplay;
		class PolarUnit4 : public ECOM::Interface::MINUS::Require::MINUS,ECOM::Base::Interface
		{
		public:
			Navidisplay *pComponent;
			PolarUnit4(Navidisplay *pComponent,int interfaceID,std::string interfaceName,std::string serviceName,std::string interfaceType,std::string interfaceModifier);

			double minus(const double a, double &b);
		};
	}
}