#include "../include/OriginData1.h"
#include "../include/Transformer.h"
//====================添加的业务逻辑=====================//
#include <string>
#include <iostream>
#include <sstream>

// ================可能用不到的原代码=============//
// extern int flagNum1;
// ================可能用不到的原代码end=============//
extern int flagNum2;
// extern int flagNum3;
//====================添加的业务逻辑end=====================//

ECOM::Components::OriginData1::OriginData1(Transformer *pComponent,int portID,std::string portName,std::string portType,std::string portModifier){
	this->pComponent = pComponent;
	this->portID = portID;
	this->portName = portName;
	this->portType = portType;
	this->portModifier = portModifier;
	this->participant = this->pComponent->participant;
	this->topic_name = "OriginalData";

	/* To customize publisher Qos, use participant->get_default_publisher_qos() instead */
	this->publisher = this->participant->create_publisher(DDS_PUBLISHER_QOS_DEFAULT, NULL/*listener*/, DDS_STATUS_MASK_NONE);

	/* Register type before creating topic */
	this->type_name = HelloWorldTypeSupport::get_type_name();

	HelloWorldTypeSupport::register_type(this->participant, type_name);

	/* To customize topic QoS, use participant->get_default_topic_qos() instead */
	DDS_Duration_t t = {0,10000};
	this->topic = this->participant->find_topic(this->topic_name,t);
	if(this->topic == NULL)
	{
		this->topic = this->participant->create_topic(this->topic_name,type_name, DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,DDS_STATUS_MASK_NONE);
	}
	/* To customize data writer QoS, use publisher->get_default_datawriter_qos() instead */
	this->writer = publisher->create_datawriter(topic, DDS_DATAWRITER_QOS_DEFAULT, NULL /* listener */,DDS_STATUS_MASK_NONE);
	this->HelloWorld_writer = HelloWorldDataWriter::narrow(writer);

	/* Create data sample for writing */
	this->instance = HelloWorldTypeSupport::create_data();
	this->instance_handle = DDS_HANDLE_NIL;
}
DDS_ReturnCode_t ECOM::Components::OriginData1::Publish(){
	DDS_ReturnCode_t retcode = HelloWorld_writer->write(*instance, instance_handle);
	return retcode;
}

void ECOM::Components::OriginData1::SetMessage(HelloWorld& Megs)
{
	mLock.lock();
	HelloWorld_copy(instance,&Megs);
	DDS_ReturnCode_t retcode = this->Publish();
	if (retcode != DDS_RETCODE_OK)
	{
		printf("write error %d\n",retcode);
	}
	mLock.unlock();
}


//====================周期性发送=====================//
int period = 2000;
int joinThread()
{
	struct DDS_Duration_t send_period = {period/1E3, period%1000*1E6};
	int a=0;
	while(flagNum2)
	{
		a++;
		NDDSUtility::sleep(send_period);
		cout << "a:" <<a<< endl;
	}
	return 0;
}
//====================周期性发送end=====================//

/***********************************************
*OriginData1�˿ڵ����ݷ��ͺ��������ö˿��ڵ�Publish()����
***********************************************/
// 原代码
// void ECOM::Components::OriginData1::OriginData1SendMegs()
// 原代码end
//====================周期性发送=====================//
void ECOM::Components::OriginData1::OriginData1SendMegs(int period)
//====================周期性发送end=====================//
{
	if (pComponent->status==ECOM::Base::Activated)
	{
	/***********************************************
	*TODO: put your logic business code here
	***********************************************/
	//====================添加的业务逻辑=====================//
	// DDS_ReturnCode_t retcode;
	// struct DDS_Duration_t send_period = {1,0};
	// int num = 0;
	// HelloWorld SnapHello;

	// while (flagNum1)
	// {
	// 	//sprintf(this->instance->msg,"Hello World! <%d>", num);
	// 	//pCom->getPublishPortOriginData1()->instance->msg = "Hello World";
	// 	while(flagNum2)
	// 	{
	// 		boost::thread thrdb2(&joinThread);
	// 		thrdb2.join();
	// 		cout << "���߳̽���" << endl;
	// 	}
	// 	string a;
	// 	stringstream str;
	// 	str << num;
	// 	str >> a;    //��int���͵�numת��string���͵�a
	// 	string Megs = "Hello World!" + a;
	// 	cout << Megs <<endl;
	// 	SnapHello.msg=(char *)Megs.c_str();
	// 	SetMessage(SnapHello);    
	// 	printf("wht happened%d\n",num);
	// 	NDDSUtility::sleep(send_period);//��ʱ
	// 	num++;
	// }
	//====================添加的业务逻辑end=====================//
	//====================周期性发送端口=====================//
	DDS_ReturnCode_t retcode;
	// 设置发送周期，第一个参数是秒，第二个参数是纳秒
	struct DDS_Duration_t send_period = {period/1E3,period%1000*1E6};
	int num = 0;
	HelloWorld SnapHello;

	while (true)
	{
		// 内部循环，处理事件
		while(flagNum2)
		{
			boost::thread thrdb2(&joinThread);
			thrdb2.join();
		}
		// 生成并发送消息
		string a;
		stringstream str;
		str << num;
		str >> a;
		string Megs = "Hello World!" + a;
		cout << Megs <<endl;
		SnapHello.msg=(char *)Megs.c_str();
		SetMessage(SnapHello);    
		
		// 等待下一个周期
		NDDSUtility::sleep(send_period);
		// std::this_thread::sleep_for(std::chrono::seconds(send_period.sec) + std::chrono::nanoseconds(send_period.nanosec));
		num++;
	}
	//====================周期性发送端口end=====================//

	}
}

