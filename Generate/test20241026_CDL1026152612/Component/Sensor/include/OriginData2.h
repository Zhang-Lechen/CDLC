#pragma  once
#include "BaseSer.h"
#include "../../../include/test20241026.h"
#include <stdarg.h>
#include <boost/thread/mutex.hpp>
namespace ECOM {
namespace Components {
class Sensor;
		class OriginData2 : public ECOM::Base::PortConsume,public ECOM::Base::Port,public ECOM::Port::OriginalData::Consume::OriginalData
		{
		public:
			OriginData2(Sensor *pComponent,int portID,std::string portName, std::string portType, std::string portModifier);
			Sensor *pComponent;
			void ReceiveMegs();
			class HelloWorldListener : public DDSDataReaderListener{
			public:
				OriginData2 *pPort;
				HelloWorldListener(OriginData2 *pPort);
				virtual void on_data_available(DDSDataReader* reader);
			};

		private:
			void DataProcess(HelloWorld *pinstance);
		};

	}
}