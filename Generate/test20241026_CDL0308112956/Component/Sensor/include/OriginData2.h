#pragma  once
#include "BaseSer.h"
#include "../../../include/test20241026.h"
#include <stdarg.h>
#include <boost/thread/mutex.hpp>

//====================消息队列&采样端口=====================//
#include <queue>
//====================消息队列&采样端口end=====================//

namespace ECOM {
namespace Components {
	class Sensor;
	class OriginData2 : public ECOM::Base::PortConsume,public ECOM::Base::Port,public ECOM::Port::OriginalData::Consume::OriginalData
	{
	public:
		OriginData2(Sensor *pComponent,int portID,std::string portName, std::string portType, std::string portModifier);
		Sensor *pComponent;

		//====================修改的原代码=====================//
		// void ReceiveMegs();
		//====================修改的原代码end=====================//		
		
		//====================消息队列&采样端口=====================//
		void ReceiveMegs(int period);
		//====================消息队列&采样端口end=====================//

		//====================消息队列=====================//
		// void setBufferSize(int size);
		//====================消息队列end=====================//
		class HelloWorldListener : public DDSDataReaderListener{
		public:
			OriginData2 *pPort;
			HelloWorldListener(OriginData2 *pPort);
			// 原代码&消息队列
			// virtual void on_data_available(DDSDataReader* reader);
			// 原代码&消息队列
		};

	private:
		void DataProcess(HelloWorld *pinstance);

		//====================消息队列=====================//
		// std::queue<HelloWorld> msgQueue;
		// int bufferSize;
		//====================消息队列end=====================//		
	};

	}
}