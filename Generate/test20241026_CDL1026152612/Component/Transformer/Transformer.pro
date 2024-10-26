#-------------------------------------------------
#
# Project created by QtCreator 2024-10-26T15:26:12
#
#-------------------------------------------------
TEMPLATE = lib
TARGET = Transformer
DESTDIR = "./Debug"
QT += core
CONFIG += debug
DEFINES += NDDS_DLL_VARIABLE RTI_WIN32 _CONSOLE RTI_STATIC
INCLUDEPATH += "./GeneratedFiles" \
"./GeneratedFiles/$(Configuration)" \
"$(BOOST_PATH)/boost_1_58_0" \
"$(ECOM_PATH)/Release" \
"$(NDDSHOME)/include" \
"$(NDDSHOME)/include/ndds" \
"./../../IDLGenerate"
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
RCC_DIR += "./GeneratedFiles"
HEADERS += "../../include/test20241026.h" \
	"./include/Transformer.h" \
	"../../IDLGenerate/test20241026IDL.h" \
	"../../IDLGenerate/test20241026IDLPlugin.h" \
	"../../IDLGenerate/test20241026IDLSupport.h" \
	"./include/PolarUnit1.h" \
	"./include/PolarUnit3.h" \
	"./include/OriginData1.h"SOURCES += "../../sources/test20241026.cpp" \
	"./sources/Transformer.cpp" \
	"../../IDLGenerate/test20241026IDL.cxx" \
	"../../IDLGenerate/test20241026IDLPlugin.cxx" \
	"../../IDLGenerate/test20241026IDLSupport.cxx" \
	"./sources/PolarUnit1.cpp" \
	"./sources/PolarUnit3.cpp" \
	"./sources/OriginData1.cpp" \
	"./GeneratedFiles/Debug/moc_Transformer.cpp"
