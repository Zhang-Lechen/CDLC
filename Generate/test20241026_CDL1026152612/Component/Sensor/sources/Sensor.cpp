#define PLUGIN_LIB

#include "../include/Sensor.h"
#include <stdlib.h>

#include "../include/PolarUnit2.h"
#include "../include/TestData1.h"
#include "../include/OriginData2.h"
ECOM::Components::Sensor::Sensor(QWidget *parent,ViewLoad *view):QWidget(parent)
{

	/* To customize the participant QoS, use the configuration file USER_QOS_PROFILES.xml */
	this->compId = view->pluginId;
	this->compName = view->pluginName;
	this->vec_Ports = view->vec_Ports;
	this->vec_Interfaces = view->vec_Interfaces;
	this->uix = view->x;
	this->uiy = view->y;
	uiForm = new Ui_Form;
	uiForm->setupUi(this);
	this->participant = DDSDomainParticipantFactory::get_instance()->create_participant(DOMAINID,/* Domain ID */DDS_PARTICIPANT_QOS_DEFAULT,/* QoS */NULL,/* Listener */DDS_STATUS_MASK_NONE);
}
ECOM::Components::Sensor::~Sensor()
{
	if (uiForm != NULL)
	{
		delete uiForm;
	}
}

void ECOM::Components::Sensor::InitPlugin()
{

	vector<ECOM::Base::Port>::iterator it1;
	for(it1 = this->vec_Ports.begin();it1 != this->vec_Ports.end();it1++)
	{
		if(it1->portName == "TestData1")
		{
			pTestData1 = new TestData1(this,it1->portID,it1->portName,it1->portType,it1->portModifier);
		}
		if(it1->portName == "OriginData2")
		{
			pOriginData2 = new OriginData2(this,it1->portID,it1->portName,it1->portType,it1->portModifier);
		}
	}
	vector<ECOM::Base::Interface>::iterator it2;
	for(it2 = this->vec_Interfaces.begin();it2 != this->vec_Interfaces.end();it2++)
	{
		if(it2->interfaceName == "PolarUnit2")
		{
			pPolarUnit2 = new PolarUnit2(this,it2->interfaceID,it2->interfaceName,it2->serviceName,it2->interfaceType,it2->interfaceModifier);
		}
	}
	this->status=ECOM::Base::Initialized;
}

void ECOM::Components::Sensor::FreePlugin()
{

	this->status=ECOM::Base::UnLoaded;
}

void ECOM::Components::Sensor::ActivatePlugin()
{

	this->status=ECOM::Base::Activated;
}

void ECOM::Components::Sensor::UnActivatePlugin()
{

	this->status=ECOM::Base::UnActivated;
}

void ECOM::Components::Sensor::ShowPlugin()
{	//TODO: put your logic for plugin showing
	this->show();
	this->move(uix,uiy);
}

void ECOM::Components::Sensor::HidePlugin()
{
}

/***********************************************
*TODO:PolarUnit2接口的请求发送函数，在该函数中调用接口的方法。
*用法已在方法体中注释
***********************************************/
void ECOM::Components::Sensor::PolarUnit2_send_request()
{
	if (this->status==ECOM::Base::Activated)
	{
	/***********************************************
	*TODO: put your logic business code here
	*调用接口内方法的例子
	*this->getRequireInterfacePolarUnit2->add(parameters<>)
	***********************************************/



	}
}
extern "C" QT_EXPORT UI_INSTANCE CreatePlugin(QWidget *parent,ViewLoad *view)
{
	ECOM::Components::Sensor *retSensor = new ECOM::Components::Sensor(parent,view);
	return retSensor;
}

