#pragma  once
#include "BaseSer.h"
#include "../../../include/test20241026.h"
namespace ECOM {
namespace Components {
class Transformer;
		class PolarUnit1 : public ECOM::Interface::ADD::Provide::ADD,ECOM::Base::Interface
		{
		public:
			Transformer *pComponent;
			class MyReplierListener : public connext::ReplierListener<add_params,add_ret>{
			public:
			PolarUnit1 *pInterface;

				MyReplierListener(PolarUnit1 *pPolarUnit1){
				this->pInterface = pPolarUnit1;
			}
				virtual void on_request_available(connext::Replier<add_params, add_ret> &replier);
		};
			PolarUnit1(Transformer *pComponent,int interfaceID,std::string interfaceName,std::string serviceName,std::string interfaceType,std::string interfaceModifier);

			MyReplierListener *myreplierlistener;

			double add(HelloWorld &a);
		};

	}
}