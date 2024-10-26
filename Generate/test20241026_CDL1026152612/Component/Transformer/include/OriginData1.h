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
			void OriginData1SendMegs();
			void SetMessage(HelloWorld& Megs);
		};

	}
}