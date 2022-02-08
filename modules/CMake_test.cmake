


##==========================================================

ADD_LIBRARY(msgdelay SHARED
    test/msgdelay.cpp
)

yate_modules( msgdelay modules-test modules )

##==========================================================

ADD_LIBRARY(nettest SHARED
    test/nettest.cpp
)

yate_modules( nettest modules-test modules )

