#include "Periodic.h"

void periodic_joinThread(FILE *fp, int period, int flagNum)
{
	fprintf(fp, "int joinThread()\n");
	fprintf(fp, "{\n");
	fprintf(fp, "\tstruct DDS_Duration_t send_period = {%d, %d};\n", (int)(period/1E3), period%1000*1E6);
	fprintf(fp, "\tint a = 0;\n");
	fprintf(fp, "\twhile(flagNum%d)\n\t{\n", flagNum);
	fprintf(fp, "\t\ta++;\n");
	fprintf(fp, "\t\tNDDSUtility::sleep(send_period);\n");
	fprintf(fp, "\t\tcout << \"a:\" << a << endl;\n");
	fprintf(fp, "\t}\n");
	fprintf(fp, "\treturn 0;\n");
	fprintf(fp, "}\n");
}

void periodic_sendMegs(FILE *fp, const char *portName, const char *type, int flagNum)
{
	fprintf(fp, "void %sSendMegs(int period)\n", portName);
	fprintf(fp, "{\n");
	fprintf(fp, "\tif (pComponent->status==ECOM::Base::Activated)\n\t{\n");
	fprintf(fp, "\t\tDDS_ReturnCode_t retcode;\n");
	fprintf(fp, "\t\tstruct DDS_Duration_t send_period = {period/1E3, period%%1000*1E6};\n");
    // 修改为实际发送的数据类型
	fprintf(fp, "\t\t%s Snap%s;\n\n", type, type);
	fprintf(fp, "\t\twhile (true)\n\t\t{\n");
	fprintf(fp, "\t\t\twhile(flagNum%d)\n\t\t\t{\n", flagNum);
	fprintf(fp, "\t\t\t\tboost::thread thrdb2(&joinThread);\n");
	fprintf(fp, "\t\t\t\tthrdb2.join();\n\t\t\t}\n\n");
    // 添加发送的信息
    fprintf(fp, "\t\t\t/***********************************************\n");
    fprintf(fp, "\t\t\t*TODO: add your message information here\n");
    fprintf(fp, "\t\t\t***********************************************/\n");

    // 修改为实际发送的数据类型
    fprintf(fp, "\t\t\t// Snap%s.msg = \n", type);
	fprintf(fp, "\t\t\tSetMessage(Snap%s);\n\n", type);
	fprintf(fp, "\t\t\tNDDSUtility::sleep(send_period);\n");
	fprintf(fp, "\t\t\tnum++;\n\t\t}\n");
	fprintf(fp, "\t}\n");
	fprintf(fp, "}\n");
}

void periodic_freeComp(FILE *fp, const char* comp, int flagNum)
{
    fprintf(fp, "void ECOM::Components::%s::FreeComponent()\n", comp);
	fprintf(fp, "{\n");
	fprintf(fp, "\tflagGlobal = 0;\n");
	for (int i = 1; i <= flagNum; i++) {
		fprintf(fp, "\tflagNum%d = 0;\n", i);
	}
	fprintf(fp, "\tthis->status=ECOM::Base::UnLoaded;\n");
	fprintf(fp, "}\n");
}

void periodic_activateComp(FILE *fp, const char* comp, int flagNum)
{
	fprintf(fp, "void ECOM::Components::%s::ActivateComponent()\n", comp);
	fprintf(fp, "{\n");
	fprintf(fp, "\tif (flagGlobal == 0)\n\t{\n");
	fprintf(fp, "\t\tcout << \"Initializing Component\" << endl;\n");
	fprintf(fp, "\t\tboost::thread thrdb1(boost::bind(&sendMegs, this));\n");
	fprintf(fp, "\t\tflagGlobal = 1;\n");
	fprintf(fp, "\t}\n");
	fprintf(fp, "\telse\n\t{\n");
	fprintf(fp, "\t\tcout << \"Modifying Component\" << endl;\n");
	for (int i = 1; i <= flagNum; i++) {
		fprintf(fp, "\t\tflagNum%d = 0;\n", i);
	}
	fprintf(fp, "\t}\n");
	fprintf(fp, "\tthis->status = ECOM::Base::Activated;\n");
	fprintf(fp, "}\n");
}

void periodic_unactivateComp(FILE *fp, const char* comp, int flagNum)
{
	fprintf(fp, "void ECOM::Components::%s::UnActivateComponent()\n", comp);
	fprintf(fp, "{\n");
	for (int i = 1; i <= flagNum; i++) {
		fprintf(fp, "\tflagNum%d = 1;\n", i);
	}
	fprintf(fp, "\tthis->status=ECOM::Base::UnActivated;\n");
	fprintf(fp, "}\n");
}

void periodic_sendMegs(FILE *fp, const char* comp, const vector<string> publish_names)
{
	fprintf(fp, "void sendMegs(ECOM::Components::%s *pCom){\n", comp);
	for (int i = 0; i < publish_names.size(); i++) {
		string name = publish_names[i];
		int period = getPublishPeriod(name);
		if (period != 0) {
			fprintf(fp, "\npCom->getPublishPort%s()->%sSendMegs(%d);\n", name, name, period);
		}
		// else {
		// 	fprintf(fp, "\npCom->getPublishPort%s()->%sSendMegs();\n", name, name);
		// }
	}
}

void periodic_recvMegs(FILE *fp, const char* comp, const vector<string> consume_names)
{
	fprintf(fp, "void recvMegs(ECOM::Components::%s *pCom){\n", comp);
	for (int i = 0; i < consume_names.size(); i++) {
		string name = consume_names[i];
		int period = getRecvPeriod(name);
		if (period != 0) {
			fprintf(fp, "\npCom->getConsumePort%s()->%sReceiveMegs(%d);\n", name, name, period);
		}
		// else {
		// 	fprintf(fp, "\npCom->getPublishPort%s()->%sSendMegs();\n", name, name);
		// }
	}
}

void set_on_data_available(FILE *fp, ComponentPortDesc *pPort, int recvType)
{
	fprintf(fp,"void ECOM::Components::%s::%sListener::on_data_available(DDSDataReader* reader) {\n", pPort->getName().c_str(), pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
	fprintf(fp,"\t%sDataReader *%s_reader = NULL;\n",pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str(),
		pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
	fprintf(fp,"\tDDS_SampleInfoSeq info_seq;\n");
	fprintf(fp,"\t%sSeq data_seq;\n",pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
	fprintf(fp,"\tDDS_ReturnCode_t retcode;\n");

	fprintf(fp,"\t%s_reader = %sDataReader::narrow(reader);\n",pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str(),
		pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
	fprintf(fp,"\tif(%s_reader == NULL) {\n",pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
	fprintf(fp,"\t\t//fprintf(stderr, \"DataReader narrow error\");\n");
	fprintf(fp,"\t\treturn;\n");
	fprintf(fp,"\t}\n\n");

	fprintf(fp,"\tretcode = %s_reader->take(data_seq, info_seq, DDS_LENGTH_UNLIMITED,DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);\n",
		pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
	fprintf(fp,"\tif (retcode == DDS_RETCODE_OK) {\n");
	fprintf(fp,"\t\tfor (int i = 0; i < data_seq.length(); ++i) {\n");
	fprintf(fp,"\t\t\tif (info_seq[i].valid_data) {\n");
	// 不同的处理方式
	if (recvType == RECV_EVENT)
		fprintf(fp,"\t\t\t\tthis->pPort->DataProcess(&(data_seq[i]));\n\n");
	else {
		fprintf(fp,"\t\t\t\tif (this->pPort->msgQueue.size() < this->pPort->bufferSize) {\n");
		fprintf(fp, "\t\t\t\t\tthis->pPort->msgQueue.push(data_seq[i]);\n");
		fprintf(fp,"\t\t\t\t}\n");
	}
	fprintf(fp,"\t\t\t}\n");
	fprintf(fp,"\t\t}\n");
	fprintf(fp,"\t%s_reader->return_loan(data_seq, info_seq);\n",pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());

	fprintf(fp,"\t}\n\n");
	fprintf(fp,"}\n");
}

void set_recvMegs_event(FILE *fp, ComponentPortDesc *pPort)
{
	fprintf(fp,"//端口的主动查询式函数，如有需要可以调用\n");
	fprintf(fp,"void ECOM::Components::%s::ReceiveMegs() {\n",pPort->getName().c_str());
	fprintf(fp,"\t%sDataReader *%s_reader = NULL;\n",pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str(),
			pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
	fprintf(fp,"\tDDS_SampleInfoSeq info_seq;\n");
	fprintf(fp,"\t%sSeq data_seq;\n",pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
	fprintf(fp,"\tDDS_ReturnCode_t retcode;\n");
	fprintf(fp,"\tDDS_Duration_t receive_period = {1,0};\n\n");
	fprintf(fp,"\t%s_reader = %sDataReader::narrow(this->reader);\n",pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str(),
			pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
	fprintf(fp,"\tif(%s_reader == NULL) {\n",pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
	fprintf(fp,"\t\t//fprintf(stderr, \"DataReader narrow error\");\n");
	fprintf(fp,"\t\treturn;\n");
	fprintf(fp,"\t}\n\n");
	fprintf(fp,"\twhile(1){\n\n");
	fprintf(fp,"\t\tretcode = %s_reader->take(data_seq, info_seq, DDS_LENGTH_UNLIMITED,DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);\n",
			pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
	fprintf(fp,"\t\tif (retcode == DDS_RETCODE_OK) {\n");
	fprintf(fp,"\t\t\tfor (int i = 0; i < data_seq.length(); ++i) {\n");
	fprintf(fp,"\t\t\t\tif (info_seq[i].valid_data) {\n");
	fprintf(fp,"\t\t\t\t\tECOM::Port::%s::Consume::ThreadForConsumePort%s *pPortThread = new ECOM::Port::%s::Consume::ThreadForConsumePort%s;\n",
			pPort->getPortEntity()->getName().c_str(),pPort->getPortEntity()->getName().c_str(),pPort->getPortEntity()->getName().c_str(),
			pPort->getPortEntity()->getName().c_str());
	fprintf(fp,"\t\t\t\t\tpPortThread->pPort = this;\n");
	fprintf(fp,"\t\t\t\t\tpPortThread->instance = data_seq[i];\n\n");
	fprintf(fp,"\t\t\t\t\tboost::thread *pThread;\n");
	fprintf(fp,"\t\t\t\t\tpThread = new boost::thread(boost::bind(&ECOM::Port::%s::Consume::ThreadForConsumePort%s::invoke,pPortThread));\n",
			pPort->getPortEntity()->getName().c_str(),pPort->getPortEntity()->getName().c_str());
	fprintf(fp,"\t\t\t\t}\n");
	fprintf(fp,"\t\t\t}\n");
	fprintf(fp,"\t\t}\n\n");
	fprintf(fp,"\t%s_reader->return_loan(data_seq, info_seq);\n",pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str());
	fprintf(fp,"\t}\n\n");
	fprintf(fp,"}\n");
}

void set_recvMegs_msgqueue(FILE *fp, ComponentPortDesc *pPort)
{
	string type = pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str();
	fprintf(fp, "void %sReceiveMegs(int period)\n", pPort->getName());
	fprintf(fp, "{\n");
	fprintf(fp, "\tDDS_Duration_t receive_period = {period/1E3, period%%1000*1E6};\n");
	fprintf(fp, "\twhile (true)\n\t{\n");
	fprintf(fp, "\t\tif (this->msgQueue.size() > 0)\n\t\t{\n");
	fprintf(fp, "\t\t\t%s pinstance = this->msgQueue.front();\n", type);
	fprintf(fp, "\t\t\tthis->msgQueue.pop();\n");
	fprintf(fp, "\t\t\tthis->DataProcess(&pinstance);\n");
	fprintf(fp, "\t\t\tECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData *pPortThread = new ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData;\n");
	fprintf(fp, "\t\t\tpPortThread->pPort = this;\n");
	fprintf(fp, "\t\t\tpPortThread->instance = pinstance;\n");
	fprintf(fp, "\t\t\tboost::thread *pThread;\n");
	fprintf(fp, "\t\t\tpThread = new boost::thread(boost::bind(&ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData::invoke, pPortThread));\n");
	fprintf(fp, "\t\t}\n");
	fprintf(fp, "\t\tNDDSUtility::sleep(receive_period);\n");
	fprintf(fp, "\t}\n");
	fprintf(fp, "}\n");
}

void set_recvMegs_sample(FILE *fp, ComponentPortDesc *pPort)
{
	string type = pPort->getPortEntity()->getTypeIndex()->m_pTypeDesc->getName().c_str();
	fprintf(fp, "void ECOM::Components::%s::ReceiveMegs(int period)\n", pPort->getName().c_str());
	fprintf(fp, "{\n");
	fprintf(fp, "\t%sDataReader *%s_reader = NULL;\n", type, type);
	fprintf(fp, "\tDDS_SampleInfoSeq info_seq;\n");
	fprintf(fp, "\t%sSeq data_seq;\n", type);
	fprintf(fp, "\tDDS_ReturnCode_t retcode;\n");
	fprintf(fp, "\tDDS_Duration_t receive_period = {period/1E3, period%%1000*1E6};\n\n");
	fprintf(fp, "\t%s_reader = %sDataReader::narrow(this->reader);\n", type, type);
	fprintf(fp, "\tif (%s_reader == NULL) { return; }\n\n", type);
	fprintf(fp, "\twhile (true)\n\t{\n");
	fprintf(fp, "\t\tretcode = %s_reader->take(data_seq, info_seq, DDS_LENGTH_UNLIMITED, DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);\n", type);
	fprintf(fp, "\t\tif (retcode == DDS_RETCODE_OK)\n\t\t{\n");
	fprintf(fp, "\t\t\tfor (int i = 0; i < data_seq.length(); ++i)\n\t\t\t{\n");
	fprintf(fp, "\t\t\t\tif (info_seq[i].valid_data)\n\t\t\t\t{\n");
	fprintf(fp, "\t\t\t\t\tDataProcess(&(data_seq[i]));\n");
	fprintf(fp, "\t\t\t\t\tboost::thread *pThread = new boost::thread(boost::bind(&ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData::invoke, new ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData{this, data_seq[i]}));\n");
	fprintf(fp, "\t\t\t\t}\n\t\t\t}\n");
	fprintf(fp, "\t\t\t%s_reader->return_loan(data_seq, info_seq);\n\t\t}\n\t\tNDDSUtility::sleep(receive_period);\n\t}\n}");
}

void set_receive_Megs(FILE *fp, ComponentPortDesc *pPort, int recvType)
{
	switch (recvType) {
		case RECV_EVENT:
			set_recvMegs_event(fp, pPort);
			break;
		case RECV_SAMPLING:
			set_recvMegs_sample(fp, pPort);
			break;
		case RECV_MSGQUEUE:
			set_recvMegs_msgqueue(fp, pPort);
			break;
		default:
			break;
	}
}
