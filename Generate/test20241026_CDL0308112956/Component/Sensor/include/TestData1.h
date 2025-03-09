#pragma  once
			#include "BaseSer.h"
			#include "../../../include/test20241026.h"
			#include <stdarg.h>
			#include <boost/thread/mutex.hpp>
			namespace ECOM {
			namespace Components {
			class Sensor;
		class TestData1 : public ECOM::Port::MyData::Publish::MyData,ECOM::Base::PortPublish,ECOM::Base::Port
		{
		private:
			boost::mutex mLock;
		public:
			TestData1(Sensor *pComponent, int portID, std::string portName, std::string portType, std::string portModifier);
			Sensor *pComponent;
			DDS_ReturnCode_t Publish();
			void TestData1SendMegs();
			void SetMessage(PostData& Megs);
		};

	}
}