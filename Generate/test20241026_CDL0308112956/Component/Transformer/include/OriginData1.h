#pragma  once
			#include "BaseSer.h"
			#include "../../../include/test20241026.h"
			#include <stdarg.h>
			#include <boost/thread/mutex.hpp>
			namespace ECOM {
			namespace Components {
			class Transformer;
		class OriginData1 : public ECOM::Port::OriginalData::Publish::OriginalData,ECOM::Base::PortPublish,ECOM::Base::Port
		{
		private:
			boost::mutex mLock;
		public:
			OriginData1(Transformer *pComponent, int portID, std::string portName, std::string portType, std::string portModifier);
			Transformer *pComponent;
			DDS_ReturnCode_t Publish();
			// 原代码
			// void OriginData1SendMegs();
			// 原代码end
			//====================消息队列=====================//
			void OriginData1SendMegs(int send_period);
			//====================消息队列end=====================//
			void SetMessage(HelloWorld& Megs);
			

		};

	}
}