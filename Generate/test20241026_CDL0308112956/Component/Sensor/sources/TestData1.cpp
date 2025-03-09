#include "../include/TestData1.h"
#include "../include/Sensor.h"
ECOM::Components::TestData1::TestData1(Sensor *pComponent,int portID,std::string portName,std::string portType,std::string portModifier){
	this->pComponent = pComponent;
	this->portID = portID;
	this->portName = portName;
	this->portType = portType;
	this->portModifier = portModifier;
	this->participant = this->pComponent->participant;
	this->topic_name = "MyData";

	/* To customize publisher Qos, use participant->get_default_publisher_qos() instead */
	this->publisher = this->participant->create_publisher(DDS_PUBLISHER_QOS_DEFAULT, NULL/*listener*/, DDS_STATUS_MASK_NONE);

	/* Register type before creating topic */
	this->type_name = PostDataTypeSupport::get_type_name();

	PostDataTypeSupport::register_type(this->participant, type_name);

	/* To customize topic QoS, use participant->get_default_topic_qos() instead */
	DDS_Duration_t t = {0,10000};
	this->topic = this->participant->find_topic(this->topic_name,t);
	if(this->topic == NULL)
	{
		this->topic = this->participant->create_topic(this->topic_name,type_name, DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,DDS_STATUS_MASK_NONE);
	}
	/* To customize data writer QoS, use publisher->get_default_datawriter_qos() instead */
	this->writer = publisher->create_datawriter(topic, DDS_DATAWRITER_QOS_DEFAULT, NULL /* listener */,DDS_STATUS_MASK_NONE);
	this->PostData_writer = PostDataDataWriter::narrow(writer);

	/* Create data sample for writing */
	this->instance = PostDataTypeSupport::create_data();
	this->instance_handle = DDS_HANDLE_NIL;
}
DDS_ReturnCode_t ECOM::Components::TestData1::Publish(){
	DDS_ReturnCode_t retcode = PostData_writer->write(*instance, instance_handle);
	return retcode;
}

void ECOM::Components::TestData1::SetMessage(PostData& Megs)
{
	mLock.lock();
	PostData_copy(instance,&Megs);
	DDS_ReturnCode_t retcode = this->Publish();
	if (retcode != DDS_RETCODE_OK)
	{
		printf("write error %d\n",retcode);
	}
	mLock.unlock();
}
/***********************************************
*TestData1�˿ڵ����ݷ��ͺ��������ö˿��ڵ�Publish()����
***********************************************/
void ECOM::Components::TestData1::TestData1SendMegs()
{
	if (pComponent->status==ECOM::Base::Activated)
	{
	/***********************************************
	*TODO: put your logic business code here
	***********************************************/
	//====================添加的业务逻辑=====================//
		DDS_ReturnCode_t retcode;
		struct DDS_Duration_t send_period = {1,0};
		int a = 1;
		int b = 1;
		int arr1[3] = {1,2,3};
		int arr2[2] = {9,8};
		PostData Snappostdata;
		int num=50;
		while (num--)
		{
			Snappostdata.a=num;
			Snappostdata.b=num;
			SetMessage(Snappostdata);
			NDDSUtility::sleep(send_period);
		}
	//====================添加的业务逻辑end=====================//


	}
}

