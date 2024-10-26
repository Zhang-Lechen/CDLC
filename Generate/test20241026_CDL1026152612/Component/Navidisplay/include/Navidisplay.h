#include <BaseUi.h>
#include "ui_Navidisplay.h"
#include "../../../include/test20241026.h"
#include <sstream>
#include <boost/thread.hpp>

namespace ECOM {
namespace Components {
class PolarUnit4;
class TestData2;
class Navidisplay: public QWidget, public BaseUi
{
	Q_OBJECT

public:
	explicit Navidisplay(QWidget *parent = 0,ViewLoad *view = NULL);
	~Navidisplay();

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
	PolarUnit4 *pPolarUnit4;
public:
	PolarUnit4 *getRequireInterfacePolarUnit4()
	{
		return pPolarUnit4;
	}

private:
	void PolarUnit4_send_request();
///////////////////////////////////////////////port  instance/////////////////////////////////////////////////
private:
	TestData2 *pTestData2;
public:
	TestData2 *getConsumePortTestData2()
	{
		return pTestData2;
	}


private:
	//// You can define any private variables here

	//// You can define any private variables here

private slots:
	//// You put your slots declarations here

};

}
}
