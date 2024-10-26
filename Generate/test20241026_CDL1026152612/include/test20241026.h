#ifndef test20241026_HEADER
#define test20241026_HEADER

#include "../IDLGenerate/test20241026IDL.h"
#include "../IDLGenerate/test20241026IDLSupport.h"
#include "ndds/ndds_requestreply_cpp.h"

namespace ECOM{
namespace Port{
namespace MyData{
namespace Publish{
class MyData
{
public:
 	PostDataDataWriter *PostData_writer;
	PostData *instance;
public:
	MyData() {};
};//END class MyData
}//END namespace Publish

namespace Consume{
class MyData
{
public:
	virtual void DataProcess(PostData *pinstance) = 0;
};

class ThreadForConsumePortMyData
{
public:
	ECOM::Port::MyData::Consume::MyData *pPort;
	PostData instance;
	PostData *pinstance;
public:
	ThreadForConsumePortMyData(){
		pinstance = &instance;
	}

	void invoke()
	{
		pPort->DataProcess(pinstance);
	}

};
}//END namespace Consume
}//END namespace MyData
}//END Port
}//END ECOM

namespace ECOM{
namespace Port{
namespace OriginalData{
namespace Publish{
class OriginalData
{
public:
 	HelloWorldDataWriter *HelloWorld_writer;
	HelloWorld *instance;
public:
	OriginalData() {};
};//END class OriginalData
}//END namespace Publish

namespace Consume{
class OriginalData
{
public:
	virtual void DataProcess(HelloWorld *pinstance) = 0;
};

class ThreadForConsumePortOriginalData
{
public:
	ECOM::Port::OriginalData::Consume::OriginalData *pPort;
	HelloWorld instance;
	HelloWorld *pinstance;
public:
	ThreadForConsumePortOriginalData(){
		pinstance = &instance;
	}

	void invoke()
	{
		pPort->DataProcess(pinstance);
	}

};
}//END namespace Consume
}//END namespace OriginalData
}//END Port
}//END ECOM

namespace ECOM{
namespace Interface{
namespace ADD{
namespace Provide{
class ADD{
public:
	connext::Replier<add_params,add_ret> *replier;

	virtual double add(HelloWorld &a) = 0;

};
}//END namespace Provide

namespace Require {
class ADD {
public:
	connext::Requester<add_params,add_ret> *requester;

	virtual double add(HelloWorld &a) = 0;
};

}//END namespace Require
}//END namespace TransformParam
}//END interface
}//END ECOM

namespace ECOM{
namespace Interface{
namespace MINUS{
namespace Provide{
class MINUS{
public:
	connext::Replier<minus_params,minus_ret> *replier;

	virtual double minus(const double a, double &b) = 0;

};
}//END namespace Provide

namespace Require {
class MINUS {
public:
	connext::Requester<minus_params,minus_ret> *requester;

	virtual double minus(const double a, double &b) = 0;
};

}//END namespace Require
}//END namespace TransformParam
}//END interface
}//END ECOM

#endif