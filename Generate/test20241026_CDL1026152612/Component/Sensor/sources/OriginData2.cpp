#include "../include/OriginData2.h"
#include "../include/Sensor.h"
ECOM::Components::OriginData2::OriginData2(Sensor *pComponent,int portID,std::string portName,std::string portType,std::string portModifier){
	this->pComponent = pComponent;
	this->portID = portID;
	this->portName = portName;
	this->portType = portType;
	this->portModifier = portModifier;
	this->participant = this->pComponent->participant;
	this->topic_name = "OriginalData";

	/* Register type before creating topic */
	type_name = HelloWorldTypeSupport::get_type_name();

	HelloWorldTypeSupport::register_type(this->participant, type_name);

	/* To customize topic QoS, use participant->get_default_topic_qos() instead */
	DDS_Duration_t t = {0,10000};
	this->topic = this->participant->find_topic(this->topic_name,t);
	if(this->topic == NULL)
	{
		this->topic = this->participant->create_topic(this->topic_name,type_name, DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,DDS_STATUS_MASK_NONE);
	}
	/* To customize the subscriber QoS, use the configuration file USER_QOS_PROFILES.xml */
	subscriber = this->participant->create_subscriber(DDS_SUBSCRIBER_QOS_DEFAULT, NULL /* listener */, DDS_STATUS_MASK_NONE);

	HelloWorldListener *reader_listener = new HelloWorldListener(this);
	/* To customize the data reader QoS, use the configuration file USER_QOS_PROFILES.xml */
	this->reader = subscriber->create_datareader(topic, DDS_DATAREADER_QOS_DEFAULT, reader_listener /* listener */,DDS_STATUS_MASK_ALL);

}
ECOM::Components::OriginData2::HelloWorldListener::HelloWorldListener(OriginData2 *pPort) {
	this->pPort = pPort;
}

void ECOM::Components::OriginData2::HelloWorldListener::on_data_available(DDSDataReader* reader) {
	HelloWorldDataReader *HelloWorld_reader = NULL;
	DDS_SampleInfoSeq info_seq;
	HelloWorldSeq data_seq;
	DDS_ReturnCode_t retcode;
	HelloWorld_reader = HelloWorldDataReader::narrow(reader);
	if(HelloWorld_reader == NULL) {
		//fprintf(stderr, "DataReader narrow error");
		return;
	}

	retcode = HelloWorld_reader->take(data_seq, info_seq, DDS_LENGTH_UNLIMITED,DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);
	if (retcode == DDS_RETCODE_OK) {
		for (int i = 0; i < data_seq.length(); ++i) {
			if (info_seq[i].valid_data) {
				this->pPort->DataProcess(&(data_seq[i]));

			}
		}
	HelloWorld_reader->return_loan(data_seq, info_seq);
	}

}
//端口的主动查询式函数，如有需要可以调用
void ECOM::Components::OriginData2::ReceiveMegs() {
	HelloWorldDataReader *HelloWorld_reader = NULL;
	DDS_SampleInfoSeq info_seq;
	HelloWorldSeq data_seq;
	DDS_ReturnCode_t retcode;
	DDS_Duration_t receive_period = {1,0};

	HelloWorld_reader = HelloWorldDataReader::narrow(this->reader);
	if(HelloWorld_reader == NULL) {
		//fprintf(stderr, "DataReader narrow error");
		return;
	}

	while(1){

		retcode = HelloWorld_reader->take(data_seq, info_seq, DDS_LENGTH_UNLIMITED,DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);
		if (retcode == DDS_RETCODE_OK) {
			for (int i = 0; i < data_seq.length(); ++i) {
				if (info_seq[i].valid_data) {
					ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData *pPortThread = new ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData;
					pPortThread->pPort = this;
					pPortThread->instance = data_seq[i];

					boost::thread *pThread;
					pThread = new boost::thread(boost::bind(&ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData::invoke,pPortThread));
				}
			}
		}

	HelloWorld_reader->return_loan(data_seq, info_seq);
	}

}
/***********************************************
*OriginData2端口的数据处理函数，用于处理接收到的数据
***********************************************/
void ECOM::Components::OriginData2::DataProcess(HelloWorld *pinstance){
	if (pComponent->status==ECOM::Base::Activated)
	{
	/***********************************************
	*TODO : put your logic to process data
	***********************************************/


	}
}

