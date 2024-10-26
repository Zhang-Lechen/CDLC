#include "djifadjf.h"

void ECOM::Components::OriginData2::ReceiveMegs() {
    HelloWorldDataReader *HelloWorld_reader = NULL;
    DDS_SampleInfoSeq info_seq;
    HelloWorldSeq data_seq;
    DDS_ReturnCode_t retcode;
    
    HelloWorld_reader = HelloWorldDataReader::narrow(this->reader);
    if (HelloWorld_reader == NULL) {
        //fprintf(stderr, "DataReader narrow error");
        return;
    }

    if (this->portType == "event") {
        // 事件型端口逻辑
        while (1) {
            retcode = HelloWorld_reader->take(data_seq, info_seq, DDS_LENGTH_UNLIMITED,
                                              DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);
            if (retcode == DDS_RETCODE_OK) {
                for (int i = 0; i < data_seq.length(); ++i) {
                    if (info_seq[i].valid_data) {
                        ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData *pPortThread = 
                            new ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData;
                        pPortThread->pPort = this;
                        pPortThread->instance = data_seq[i];

                        boost::thread *pThread;
                        pThread = new boost::thread(boost::bind(&ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData::invoke, pPortThread));
                    }
                }
            }
            HelloWorld_reader->return_loan(data_seq, info_seq);
        }
    } else if (this->portType == "periodic") {
        // 周期型端口逻辑
        if (this->portModifier == "queue") {
            // 消息队列方式，处理消息队列长度
            std::queue<HelloWorld> messageQueue;

            while (1) {
                retcode = HelloWorld_reader->take(data_seq, info_seq, DDS_LENGTH_UNLIMITED,
                                                  DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);
                if (retcode == DDS_RETCODE_OK) {
                    for (int i = 0; i < data_seq.length(); ++i) {
                        if (info_seq[i].valid_data) {
                            if (messageQueue.size() >= this->queueLength) {
                                messageQueue.pop(); // 如果队列已满，丢弃旧消息
                            }
                            messageQueue.push(data_seq[i]);
                        }
                    }
                }
                HelloWorld_reader->return_loan(data_seq, info_seq);

                // 处理队列中的消息
                while (!messageQueue.empty()) {
                    HelloWorld instance = messageQueue.front();
                    messageQueue.pop();
                    ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData *pPortThread =
                        new ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData;
                    pPortThread->pPort = this;
                    pPortThread->instance = instance;

                    boost::thread *pThread;
                    pThread = new boost::thread(boost::bind(&ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData::invoke, pPortThread));
                }
            }
        } else if (this->portModifier == "sampling") {
            // 采样方式，基于给定的采样周期
            while (1) {
                // 睡眠指定的采样周期
                boost::this_thread::sleep(boost::posix_time::seconds(this->samplePeriod.sec));

                retcode = HelloWorld_reader->take(data_seq, info_seq, 1,  // 只取一个最新的样本
                                                  DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);
                if (retcode == DDS_RETCODE_OK) {
                    if (info_seq[0].valid_data) {
                        ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData *pPortThread =
                            new ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData;
                        pPortThread->pPort = this;
                        pPortThread->instance = data_seq[0];

                        boost::thread *pThread;
                        pThread = new boost::thread(boost::bind(&ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData::invoke, pPortThread));
                    }
                }
                HelloWorld_reader->return_loan(data_seq, info_seq);
            }
        }
    }
}
void ECOM::Components::OriginData2::ReceiveMegs() {
    HelloWorldDataReader *HelloWorld_reader = NULL;
    DDS_SampleInfoSeq info_seq;
    HelloWorldSeq data_seq;
    DDS_ReturnCode_t retcode;
    
    HelloWorld_reader = HelloWorldDataReader::narrow(this->reader);
    if (HelloWorld_reader == NULL) {
        //fprintf(stderr, "DataReader narrow error");
        return;
    }

    if (this->portType == "event") {
        // 事件型端口逻辑
        while (1) {
            retcode = HelloWorld_reader->take(data_seq, info_seq, DDS_LENGTH_UNLIMITED,
                                              DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);
            if (retcode == DDS_RETCODE_OK) {
                for (int i = 0; i < data_seq.length(); ++i) {
                    if (info_seq[i].valid_data) {
                        ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData *pPortThread = 
                            new ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData;
                        pPortThread->pPort = this;
                        pPortThread->instance = data_seq[i];

                        boost::thread *pThread;
                        pThread = new boost::thread(boost::bind(&ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData::invoke, pPortThread));
                    }
                }
            }
            HelloWorld_reader->return_loan(data_seq, info_seq);
        }
    } else if (this->portType == "periodic") {
        // 周期型端口逻辑
        if (this->portModifier == "queue") {
            // 消息队列方式，处理消息队列长度
            std::queue<HelloWorld> messageQueue;

            while (1) {
                retcode = HelloWorld_reader->take(data_seq, info_seq, DDS_LENGTH_UNLIMITED,
                                                  DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);
                if (retcode == DDS_RETCODE_OK) {
                    for (int i = 0; i < data_seq.length(); ++i) {
                        if (info_seq[i].valid_data) {
                            if (messageQueue.size() >= this->queueLength) {
                                messageQueue.pop(); // 如果队列已满，丢弃旧消息
                            }
                            messageQueue.push(data_seq[i]);
                        }
                    }
                }
                HelloWorld_reader->return_loan(data_seq, info_seq);

                // 处理队列中的消息
                while (!messageQueue.empty()) {
                    HelloWorld instance = messageQueue.front();
                    messageQueue.pop();
                    ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData *pPortThread =
                        new ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData;
                    pPortThread->pPort = this;
                    pPortThread->instance = instance;

                    boost::thread *pThread;
                    pThread = new boost::thread(boost::bind(&ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData::invoke, pPortThread));
                }
            }
        } else if (this->portModifier == "sampling") {
            // 采样方式，基于给定的采样周期
            while (1) {
                // 睡眠指定的采样周期
                boost::this_thread::sleep(boost::posix_time::seconds(this->samplePeriod.sec));

                retcode = HelloWorld_reader->take(data_seq, info_seq, 1,  // 只取一个最新的样本
                                                  DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);
                if (retcode == DDS_RETCODE_OK) {
                    if (info_seq[0].valid_data) {
                        ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData *pPortThread =
                            new ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData;
                        pPortThread->pPort = this;
                        pPortThread->instance = data_seq[0];

                        boost::thread *pThread;
                        pThread = new boost::thread(boost::bind(&ECOM::Port::OriginalData::Consume::ThreadForConsumePortOriginalData::invoke, pPortThread));
                    }
                }
                HelloWorld_reader->return_loan(data_seq, info_seq);
            }
        }
    }
}
