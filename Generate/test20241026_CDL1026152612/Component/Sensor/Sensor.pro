#-------------------------------------------------
#
# Project created by QtCreator 2024-10-26T15:26:12
#
#-------------------------------------------------
TEMPLATE = lib
TARGET = Sensor
DESTDIR = "./Debug"
QT += core widgets gui
CONFIG += debug
DEFINES += NDDS_DLL_VARIABLE RTI_WIN32 _CONSOLE RTI_STATIC
INCLUDEPATH += "./GeneratedFiles" \
"./GeneratedFiles/$(Configuration)" \
"$(BOOST_PATH)/boost_1_58_0" \
"$(ECOM_PATH)/Release" \
"$(NDDSHOME)/include" \
"$(NDDSHOME)/include/ndds" \
"./../../IDLGenerate"
FORMS += "Sensor.ui"
LIBS += -L"$(NDDSHOME)/lib/i86Win32VS2010" \
	-L"$(BOOST_PATH)/boost_1_58_0/stage/lib" \
	-lrticonnextmsgcppd \
	-lnddscppd \
	-lnddscd \
	-lnddscored \
	-lnetapi32 \
	-ladvapi32 \
	-luser32 \
	-lWS2_32
DEPENDPATH += "."
MOC_DIR += "./GeneratedFiles/debug"
OBJECTS_DIR += debug
UI_DIR += "./GeneratedFiles"
RCC_DIR += "./GeneratedFiles"
HEADERS += "../../include/test20241026.h" \
	"./include/Sensor.h" \
	"../../IDLGenerate/test20241026IDL.h" \
	"../../IDLGenerate/test20241026IDLPlugin.h" \
	"../../IDLGenerate/test20241026IDLSupport.h" \
	"./include/PolarUnit2.h" \
	"./include/TestData1.h" \
	"./include/OriginData2.h"SOURCES += "../../sources/test20241026.cpp" \
	"./sources/Sensor.cpp" \
	"../../IDLGenerate/test20241026IDL.cxx" \
	"../../IDLGenerate/test20241026IDLPlugin.cxx" \
	"../../IDLGenerate/test20241026IDLSupport.cxx" \
	"./sources/PolarUnit2.cpp" \
	"./sources/TestData1.cpp" \
	"./sources/OriginData2.cpp" \
	"./GeneratedFiles/Debug/moc_Sensor.cpp"
