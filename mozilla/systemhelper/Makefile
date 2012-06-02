CPP = g++
CPPFLAGS += -fno-rtti -fno-exceptions -shared
GECKO_SDK_PATH = /usr/lib/xulrunner-devel-1.9.2.8/
XPIDL = $(GECKO_SDK_PATH)/bin/xpidl
CPPHEADER = -m header
TYPELIB = -m typelib
REGDIR = /usr/lib/xulrunner-1.9.2.8/
OUTDIR = $(REGDIR)/components
GECKO_CONFIG_INCLUDE = -include xpcom-config.h
GECKO_DEFINES  = -DMOZILLA_INTERNAL_API
GECKO_INCLUDES = -I$(GECKO_SDK_PATH)/include -I/usr/include/nspr

GECKO_LDFLAGS =  $(GECKO_SDK_PATH)/lib/libxpcomglue_s.a \
    -L$(GECKO_SDK_PATH)/lib -L$(GECKO_SDK_PATH)/bin -lmozjs -lxul -lxpcom -L/usr/lib/nspr -lnspr4

GECKO_IDL = -I$(GECKO_SDK_PATH)/idl

build: idl nsCcoss.o nsCcossModule.o
	$(CPP) $(CPPFLAGS) -o libccoss.so $(GECKO_DEFINES) \
	nsCcoss.o nsCcossModule.o $(GECKO_LDFLAGS)

idl: nsICcoss.idl
	$(XPIDL) $(GECKO_IDL) $(CPPHEADER) nsICcoss.idl
	$(XPIDL) $(GECKO_IDL) $(TYPELIB) nsICcoss.idl

nsCcoss.o: nsCcoss.cpp
	$(CPP) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) \
	$(GECKO_INCLUDES) -c nsCcoss.cpp -o nsCcoss.o

nsCcossModule.o: nsCcossModule.cpp
	$(CPP) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) \
	$(GECKO_INCLUDES) -c nsCcossModule.cpp -o nsCcossModule.o

install:
	cp nsICcoss.xpt $(OUTDIR)/
	cp libccoss.so $(OUTDIR)/

clean: 
	rm -frv *.o
	rm -frv *.so
	rm -frv *.*~
	rm -frv *~
	rm -frv *.xpt
