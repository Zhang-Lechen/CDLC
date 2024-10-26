#include "../include/TestData2.h"
#include "../include/Navidisplay.h"
ECOM::Components::TestData2::TestData2(Navidisplay *pComponent,int portID,std::string portName,std::string portType,std::string portModifier){
	this->pComponent = pComponent;
	this->portID = portID;
	this->portName = portName;
	this->portType = portType;
	this->portModifier = portModifier;
	this->participant = this->pComponent->participant;
	this->topic_name = "MyData";

	/* Register type before creating topic */
	type_name = PostDataTypeSupport::get_type_name();

	PostDataTypeSupport::register_type(this->participant, type_name);

	/* To customize topic QoS, use participant->get_default_topic_qos() instead */
	DDS_Duration_t t = {0,10000};
	this->topic = this->participant->find_topic(this->topic_name,t);
	if(this->topic == NULL)
	{
		this->topic = this->participant->create_topic(this->topic_name,type_name, DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,DDS_STATUS_MASK_NONE);
	}
	/* To customize the subscriber QoS, use the configuration file USER_QOS_PROFILES.xml */
	subscriber = this->participant->create_subscriber(DDS_SUBSCRIBER_QOS_DEFAULT, NULL /* listener */, DDS_STATUS_MASK_NONE);

	PostDataListener *reader_listener = new PostDataListener(this);
	/* To customize the data reader QoS, use the configuration file USER_QOS_PROFILES.xml */
	this->reader = subscriber->create_datareader(topic, DDS_DATAREADER_QOS_DEFAULT, reader_listener /* listener */,DDS_STATUS_MASK_ALL);

}
ECOM::Components::TestData2::PostDataListener::PostDataListener(TestData2 *pPort) {
	this->pPort = pPort;
}

void ECOM::Components::TestData2::PostDataListener::on_data_available(DDSDataReader* reader) {
	PostDataDataReader *PostData_reader = NULL;
	DDS_SampleInfoSeq info_seq;
	PostDataSeq data_seq;
	DDS_ReturnCode_t retcode;
	PostData_reader = PostDataDataReader::narrow(reader);
	if(PostData_reader == NULL) {
		//fprintf(stderr, "DataReader narrow error");
		return;
	}

	retcode = PostData_reader->take(data_seq, info_seq, DDS_LENGTH_UNLIMITED,DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);
	if (retcode == DDS_RETCODE_OK) {
		for (int i = 0; i < data_seq.length(); ++i) {
			if (info_seq[i].valid_data) {
				this->pPort->DataProcess(&(data_seq[i]));

			}
		}
	PostData_reader->return_loan(data_seq, info_seq);
	}

}
//端口的主动查询式函数，如有需要可以调用
void ECOM::Components::TestData2::ReceiveMegs() {
	PostDataDataReader *PostData_reader = NULL;
	DDS_SampleInfoSeq info_seq;
	PostDataSeq data_seq;
	DDS_ReturnCode_t retcode;
	DDS_Duration_t receive_period = {1,0};

	PostData_reader = PostDataDataReader::narrow(this->reader);
	if(PostData_reader == NULL) {
		//fprintf(stderr, "DataReader narrow error");
		return;
	}

	while(1){

		retcode = PostData_reader->take(data_seq, info_seq, DDS_LENGTH_UNLIMITED,DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);
		if (retcode == DDS_RETCODE_OK) {
			for (int i = 0; i < data_seq.length(); ++i) {
				if (info_seq[i].valid_data) {
					ECOM::Port::MyData::Consume::ThreadForConsumePortMyData *pPortThread = new ECOM::Port::MyData::Consume::ThreadForConsumePortMyData;
					pPortThread->pPort = this;
					pPortThread->instance = data_seq[i];

					boost::thread *pThread;
					pThread = new boost::thread(boost::bind(&ECOM::Port::MyData::Consume::ThreadForConsumePortMyData::invoke,pPortThread));
				}
			}
		}

	PostData_reader->return_loan(data_seq, info_seq);
	}

}
/***********************************************
*TestData2端口的数据处理函数，用于处理接收到的数据
***********************************************/
void ECOM::Components::TestData2::DataProcess(PostData *pinstance){
	if (pComponent->status==ECOM::Base::Activated)
	{
	/***********************************************
	*TODO : put your logic to process data
	***********************************************/


	}
}

