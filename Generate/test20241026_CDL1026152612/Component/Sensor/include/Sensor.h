#include <BaseUi.h>
#include "ui_Sensor.h"
#include "../../../include/test20241026.h"
#include <sstream>
#include <boost/thread.hpp>

namespace ECOM {
namespace Components {
class PolarUnit2;
class TestData1;
class OriginData2;
class Sensor: public QWidget, public BaseUi
{
	Q_OBJECT

public:
	explicit Sensor(QWidget *parent = 0,ViewLoad *view = NULL);
	~Sensor();

public:
	virtual void InitPlugin();
	virtual void FreePlugin();
	virtual void ActivatePlugin();
	virtual void UnActivatePlugin();
	virtual void ShowPlugin();
	virtual void HidePlugin();
private:
	Ui_Form *uiForm;

private:
///////////////////////////////////////////////interface  instance/////////////////////////////////////////////////
//pointer to interface & get pointer
private:
	PolarUnit2 *pPolarUnit2;
public:
	PolarUnit2 *getRequireInterfacePolarUnit2()
	{
		return pPolarUnit2;
	}

private:
	void PolarUnit2_send_request();
///////////////////////////////////////////////port  instance/////////////////////////////////////////////////
private:
	TestData1 *pTestData1;
public:
	TestData1 *getPublishPortTestData1()
	{
		return pTestData1;
	}

private:
	OriginData2 *pOriginData2;
public:
	OriginData2 *getConsumePortOriginData2()
	{
		return pOriginData2;
	}


private:
	//// You can define any private variables here

	//// You can define any private variables here

private slots:
	//// You put your slots declarations here

};

}
}
