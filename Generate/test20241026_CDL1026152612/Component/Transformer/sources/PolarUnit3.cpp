#include "../include/PolarUnit3.h"
#include "../include/Transformer.h"
ECOM::Components::PolarUnit3::PolarUnit3(Transformer *pComponent,int interfaceID,std::string interfaceName,std::string serviceName,std::string interfaceType,std::string interfaceModifier){
	this->pComponent = pComponent;
	this->interfaceID = interfaceID;
	this->interfaceName = interfaceName;
	this->serviceName = serviceName;
	this->interfaceType = interfaceType;
	this->interfaceModifier = interfaceModifier;

	this->participant = this->pComponent->participant;
	this->myreplierlistener = new MyReplierListener(this);

	connext::ReplierParams<minus_params,minus_ret>replier_params(this->participant);
	replier_params.service_name(serviceName);
	replier_params.qos_profile("RequestReplyExampleProfiles", "ReplierExampleProfile");

	replier_params.replier_listener(*myreplierlistener);
	try{
		this->replier = new connext::Replier<minus_params,minus_ret>(replier_params);
	} catch(const connext::RuntimeException& ex) {
		std::cout<<"Exception while loading replier:"<<ex.what()<<std::endl;
	}
}
void ECOM::Components::PolarUnit3::MyReplierListener::on_request_available(connext::Replier<minus_params,minus_ret> &replier){
	connext::LoanedSamples<minus_params> requests = replier.take_requests(DDS_LENGTH_UNLIMITED);
	typedef connext::LoanedSamples<minus_params>::iterator iterator;
	for (iterator it = requests.begin();it != requests.end(); ++it) {
		if (it->info().valid_data) {

			double result = this->pInterface->minus(it->data().a, it->data().b);

			/*Send reply indicating error */
			connext::WriteSample<minus_ret> reply;
			reply.data().result = result;
			reply.data().b = it->data().b;
			replier.send_reply(reply, it->identity());
		}
	}
}

double ECOM::Components::PolarUnit3::minus(const double a, double &b)
{
	if (pComponent->status==ECOM::Base::Activated)	{
		//TODO : Add your business logic here


	}
	return 0;
}

