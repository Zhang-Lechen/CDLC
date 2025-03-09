#pragma  once
			#include "BaseSer.h"
			#include "../../../include/test20241026.h"
			#include <stdarg.h>
			#include <boost/thread/mutex.hpp>
			namespace ECOM {
			namespace Components {
			class Navidisplay;
		class TestData2 : public ECOM::Base::PortConsume,public ECOM::Base::Port,public ECOM::Port::MyData::Consume::MyData
		{
		public:
			TestData2(Navidisplay *pComponent,int portID,std::string portName, std::string portType, std::string portModifier);
			Navidisplay *pComponent;
			void ReceiveMegs();
			class PostDataListener : public DDSDataReaderListener{
			public:
				TestData2 *pPort;
				PostDataListener(TestData2 *pPort);
				virtual void on_data_available(DDSDataReader* reader);
			};

		private:
			void DataProcess(PostData *pinstance);
		};

	}
}