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

//====================消息队列=====================//
// void ECOM::Components::OriginData2::setBufferSize(int queue_length) {
// 	this->bufferSize = queue_length;
// }
//====================消息队列end=====================//

// 原代码
// void ECOM::Components::OriginData2::HelloWorldListener::on_data_available(DDSDataReader* reader) {
// 	HelloWorldDataReader *HelloWorld_reader = NULL;
// 	DDS_SampleInfoSeq info_seq;
// 	HelloWorldSeq data_seq;
// 	DDS_ReturnCode_t retcode;
// 	HelloWorld_reader = HelloWorldDataReader::narrow(reader);
// 	if(HelloWorld_reader == NULL) {
// 		//fprintf(stderr, "DataReader narrow error");
// 		return;
// 	}

// 	retcode = HelloWorld_reader->take(data_seq, info_seq, DDS_LENGTH_UNLIMITED,DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);
// 	if (retcode == DDS_RETCODE_OK) {
// 		for (int i = 0; i < data_seq.length(); ++i) {
// 			if (info_seq[i].valid_data) {
// 				//====================消息队列=====================//
// 				if (this->pPort->msgQueue.size() < this->pPort->bufferSize) {
// 					// HelloWorld *pinstance = new HelloWorld;
// 					// HelloWorld_copy(pinstance,&(data_seq[i]));
// 					this->pPort->msgQueue.push(data_seq[i]);
// 				}
// 				//====================消息队列end=====================//
// 				// 原代码
// 				// this->pPort->DataProcess(&(data_seq[i]));
// 				// 原代码end

// 			}
// 		}
// 	HelloWorld_reader->return_loan(data_seq, info_seq);
// 	}

// }
// 原代码end

//====================采样端口=====================//
void ECOM::Components::OriginData2::ReceiveMegs(int period) {
	HelloWorldDataReader *HelloWorld_reader = NULL;
	DDS_SampleInfoSeq info_seq;
	HelloWorldSeq data_seq;
	DDS_ReturnCode_t retcode;
	// 设置接收周期，第一个参数是秒，第二个参数是纳秒
	DDS_Duration_t receive_period = {period/1E3,period%1000*1E6};

	HelloWorld_reader = HelloWorldDataReader::narrow(this->reader);
	if(HelloWorld_reader == NULL) {
		return;
	}

	while(true)
	{
		retcode = HelloWorld_reader->take(data_seq, info_seq, DDS_LENGTH_UNLIMITED,DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);
		if (retcode == DDS_RETCODE_OK) {
			for (int i = 0; i < data_seq.length(); ++i) {
				if (info_seq[i].valid_data) {
					DataProcess(&(data_seq[i]));
					ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData *pPortThread = new ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData;
					pPortThread->pPort = this;
					pPortThread->instance = data_seq[i];

					boost::thread *pThread;
					pThread = new boost::thread(boost::bind(&ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData::invoke,pPortThread));
				}
			}
			HelloWorld_reader->return_loan(data_seq, info_seq);
		}

		
		NDDSUtility::sleep(receive_period);
	}

}
//====================采样端口end=====================//

//====================消息队列=====================//
// void ECOM::Components::OriginData2::ReceiveMegs(int period)
// {
// 	DDS_Duration_t receive_period = {period/1E3,period%1000*1E6};
// 	while (true)
// 	{
// 		if (this->msgQueue.size() > 0)
// 		{
// 			HelloWorld pinstance = this->msgQueue.front();
// 			this->msgQueue.pop();
// 			this->DataProcess(&pinstance);
// 			ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData *pPortThread = new ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData;
// 			pPortThread->pPort = this;
// 			pPortThread->instance = pinstance;

// 			boost::thread *pThread;
// 			pThread = new boost::thread(boost::bind(&ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData::invoke,pPortThread));
// 		}
// 		NDDSUtility::sleep(receive_period);
// 	}
// }
//====================消息队列end=====================//
//====================原代码=======================//
// void ECOM::Components::OriginData2::ReceiveMegs() {
// 	HelloWorldDataReader *HelloWorld_reader = NULL;
// 	DDS_SampleInfoSeq info_seq;
// 	HelloWorldSeq data_seq;
// 	DDS_ReturnCode_t retcode;
// 	DDS_Duration_t receive_period = {1,0};

// 	HelloWorld_reader = HelloWorldDataReader::narrow(this->reader);
// 	if(HelloWorld_reader == NULL) {
// 		//fprintf(stderr, "DataReader narrow error");
// 		return;
// 	}

// 	while(1){

// 		retcode = HelloWorld_reader->take(data_seq, info_seq, DDS_LENGTH_UNLIMITED,DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);
// 		if (retcode == DDS_RETCODE_OK) {
// 			for (int i = 0; i < data_seq.length(); ++i) {
// 				if (info_seq[i].valid_data) {
// 					ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData *pPortThread = new ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData;
// 					pPortThread->pPort = this;
// 					pPortThread->instance = data_seq[i];

// 					boost::thread *pThread;
// 					pThread = new boost::thread(boost::bind(&ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData::invoke,pPortThread));
// 				}
// 			}
// 		}

// 	HelloWorld_reader->return_loan(data_seq, info_seq);
// 	}

// }
//====================原代码end=======================//

/***********************************************
*OriginData2�˿ڵ����ݴ������������ڴ������յ�������
***********************************************/
void ECOM::Components::OriginData2::DataProcess(HelloWorld *pinstance){
	if (pComponent->status==ECOM::Base::Activated)
	{
	/***********************************************
	*TODO : put your logic to process data
	***********************************************/
	//====================添加的业务逻辑=====================//
		QString str = "Sensor receive msg: ";
		str += QString(QLatin1String(pinstance -> msg));
		this->pComponent->getUiForm()->lineEdit_4->setText(str);
	//====================添加的业务逻辑end=====================//

	}
}

