#include "../include/PolarUnit2.h"
#include "../include/Sensor.h"
ECOM::Components::PolarUnit2::PolarUnit2(Sensor *pComponent,int interfaceID,std::string interfaceName,std::string serviceName,std::string interfaceType,std::string interfaceModifier){
	this->pComponent = pComponent;
	this->interfaceID = interfaceID;
	this->interfaceName = interfaceName;
	this->serviceName = serviceName;
	this->interfaceType = interfaceType;
	this->interfaceModifier = interfaceModifier;

	this->participant = this->pComponent->participant;
	connext::RequesterParams requester_params(this->participant);
	requester_params.service_name(serviceName);
	requester_params.qos_profile("RequestReplyExampleProfiles","RequesterExampleProfile");
	try{
	this->requester = new connext::Requester<add_params,add_ret>(requester_params);
	} catch(const connext::RuntimeException& ex) {
		std::cout<<"Exception while loading replier:"<<ex.what()<<std::endl;
	}
}
double ECOM::Components::PolarUnit2::add(HelloWorld &a)
{
	connext::WriteSample<add_params> request;
	request.data().a.msg = DDS_String_dup(a.msg);
	double result;
	this->requester->send_request(request);

	/*Receive replies */
	const DDS::Duration_t MAX_WAIT = {4,0};
	connext::Sample<add_ret> reply;
	bool received = this->requester->receive_reply(reply,MAX_WAIT);
	if (received) {
		if(reply.info().valid_data) {
			result = reply.data().result;
			a = reply.data().a;
		} else {
		}
	} else {
		std::cout <<"Reply not received"<< std::endl;
	}
	return result;

}

