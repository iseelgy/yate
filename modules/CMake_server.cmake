


##==========================================================

ADD_LIBRARY(ysnmpagent SHARED
    server/ysnmpagent.cpp
)

TARGET_INCLUDE_DIRECTORIES(ysnmpagent PUBLIC ../libs/ysnmp ../libs/yasn)

TARGET_LINK_LIBRARIES( ysnmpagent ysnmp yasn)

yate_modules( ysnmpagent modules-server modules/server )


