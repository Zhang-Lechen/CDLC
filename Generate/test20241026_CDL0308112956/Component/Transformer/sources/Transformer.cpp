#define WIN32_DLL

#include "../include/Transformer.h"
#include <stdlib.h>
//====================添加的业务逻辑=====================//
#include "../flagSign.h"
//====================添加的业务逻辑end=====================//

#include "../include/PolarUnit1.h"
#include "../include/PolarUnit3.h"
#include "../include/OriginData1.h"
//====================添加的业务逻辑=====================//
void sendMegs(ECOM::Components::Transformer *pCom);
//====================添加的业务逻辑end=====================//
ECOM::Components::Transformer::Transformer(SerLoad *ser)
{

	this->compId = ser->compId;
	this->compName = ser->compName;
	this->vec_Ports = ser->vec_Ports;
	this->vec_Interfaces = ser->vec_Interfaces;

this->participant = DDSDomainParticipantFactory::get_instance()->create_participant(DOMAINID,/* Domain ID */DDS_PARTICIPANT_QOS_DEFAULT,/* QoS */NULL,/* Listener */DDS_STATUS_MASK_NONE);
	/* To customize participant QoS, use DDSTheParticipantFactory->get_default_participant_qos() instead */
}

void ECOM::Components::Transformer::InitComponent()
{

	vector<ECOM::Base::Port>::iterator it1;
	for(it1 = this->vec_Ports.begin();it1 != this->vec_Ports.end();it1++)
	{
		if(it1->portName == "OriginData1")
		{
			pOriginData1 = new OriginData1(this,it1->portID,it1->portName,it1->portType,it1->portModifier);
		}
	}
	vector<ECOM::Base::Interface>::iterator it2;
	for(it2 = this->vec_Interfaces.begin();it2 != this->vec_Interfaces.end();it2++)
	{
		if(it2->interfaceName == "PolarUnit1")
		{
			pPolarUnit1 = new PolarUnit1(this,it2->interfaceID,it2->interfaceName,it2->serviceName,it2->interfaceType,it2->interfaceModifier);
		}
		if(it2->interfaceName == "PolarUnit3")
		{
			pPolarUnit3 = new PolarUnit3(this,it2->interfaceID,it2->interfaceName,it2->serviceName,it2->interfaceType,it2->interfaceModifier);
		}
	}
	this->status=ECOM::Base::Initialized;
}

void ECOM::Components::Transformer::FreeComponent()
{

	//====================添加的业务逻辑=====================//
	flagGlobal = 0;
	// flagNum1 = 0;
	flagNum2 = 0;
	//====================添加的业务逻辑=====================//
	this->status=ECOM::Base::UnLoaded;
}

void ECOM::Components::Transformer::ActivateComponent()
{

	//====================添加的业务逻辑=====================//
	if (flagGlobal == 0)
	{
		cout << "���봴���Ĺ���" << endl;
		boost::thread thrdb1(boost::bind(&sendMegs,this));
		flagGlobal = 1;
		// flagNum1=1;
	}
	else
	{
		cout << "�����޸ĵĹ���" << endl;
		flagNum2 =0;
	}
	//====================添加的业务逻辑=====================//
	this->status=ECOM::Base::Activated;
}

void ECOM::Components::Transformer::UnActivateComponent()
{

	//====================添加的业务逻辑=====================//
	flagNum2=1;
	//====================添加的业务逻辑=====================//
	this->status=ECOM::Base::UnActivated;
}

//====================添加的业务逻辑=====================//
// void sendMegs(ECOM::Components::Transformer *pCom){
// 	pCom->getPublishPortOriginData1()->OriginData1SendMegs();
// }
//====================添加的业务逻辑=====================//

//====================周期性发送=====================//
void sendMegs(ECOM::Components::Transformer *pCom){
	// 设置发送周期
	pCom->getPublishPortOriginData1()->OriginData1SendMegs(2000);
}
//====================周期性发送end=====================//

extern "C" WIN32_EXPORT SER_INSTANCE CreateComponent(SerLoad *ser)
{
	ECOM::Components::Transformer *retTransformer = new ECOM::Components::Transformer(ser);
	return retTransformer;
}

