#include "anything.h"

// 周期型发送消息的模板函数
void ECOM::Components::OriginData1::OriginData1SendMegsPeriod()
{
	if (pComponent->status==ECOM::Base::Activated)
	{

		// 设置发送周期，第一个参数是秒，第二个参数是纳秒
		struct DDS_Duration_t send_period = {this->period/1E3,this->period%1000*1E6};
		
		while (true)
		{
  
			/***********************************************
	        * TODO: put your logic business code here
	        * ***********************************************/
			// 等待下一个周期
			// NDDSUtility::sleep(send_period);
			std::this_thread::sleep_for(std::chrono::seconds(send_period.sec) + std::chrono::nanoseconds(send_period.nanosec));
		}
	}
}

// 周期型接收消息的模板函数：使用消息队列

