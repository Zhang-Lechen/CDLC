#pragma  once
#include "BaseSer.h"
#include "../../../include/test20241026.h"
namespace ECOM {
namespace Components {
class Transformer;
		class PolarUnit3 : public ECOM::Interface::MINUS::Provide::MINUS,ECOM::Base::Interface
		{
		public:
			Transformer *pComponent;
			class MyReplierListener : public connext::ReplierListener<minus_params,minus_ret>{
			public:
			PolarUnit3 *pInterface;

				MyReplierListener(PolarUnit3 *pPolarUnit3){
				this->pInterface = pPolarUnit3;
			}
				virtual void on_request_available(connext::Replier<minus_params, minus_ret> &replier);
		};
			PolarUnit3(Transformer *pComponent,int interfaceID,std::string interfaceName,std::string serviceName,std::string interfaceType,std::string interfaceModifier);

			MyReplierListener *myreplierlistener;

			double minus(const double a, double &b);
		};

	}
}