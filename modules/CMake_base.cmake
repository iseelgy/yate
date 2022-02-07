
# JUSTSIG := server/ysigchan.yate server/analog.yate \
#	server/ciscosm.yate server/sigtransport.yate \
#	sig/isupmangler.yate sig/ss7_lnp_ansi.yate \
#	sig/camel_map.yate


# PROGS := cdrbuild.yate cdrcombine.yate cdrfile.yate regexroute.yate \
# 	tonegen.yate tonedetect.yate wavefile.yate \
# 	extmodule.yate conference.yate moh.yate pbx.yate \
# 	dumbchan.yate callfork.yate mux.yate \
# 	yrtpchan.yate ystunchan.yate \
# 	ysipchan.yate \
# 	yiaxchan.yate \
# 	yjinglechan.yate jabber/jabberserver.yate jabber/jbfeatures.yate \
# 	ysockschan.yate filetransfer.yate fileinfo.yate \
# 	gvoice.yate \
# 	javascript.yate \
# 	server/pbxassist.yate server/dbpbx.yate server/lateroute.yate \
# 	server/park.yate server/queues.yate server/queuesnotify.yate \
# 	server/regfile.yate server/accfile.yate server/register.yate \
# 	server/callcounters.yate server/cpuload.yate server/ccongestion.yate \
# 	server/dbwave.yate \
# 	server/yradius.yate \
# 	server/ysnmpagent.yate \
# 	server/monitoring.yate \
# 	server/sipfeatures.yate \
# 	sip/sip_cnam_lnp.yate \
# 	server/heartbeat.yate server/clustering.yate \
# 	server/mgcpgw.yate server/mgcpca.yate \
# 	server/mrcpspeech.yate \
# 	server/presence.yate server/subscription.yate \
# 	server/users.yate \
# 	$(JUSTSIG) \
# 	server/analogdetect.yate \
# 	server/cache.yate \
# 	server/eventlogs.yate \
# 	client/jabberclient.yate \
# 	callgen.yate analyzer.yate rmanager.yate msgsniff.yate wiresniff.yate \
# 	radio/dummyradio.yate radio/radiotest.yate


# qt4
# PROGS := $(PROGS) qt4/updater.yate qt4/customtable.yate qt4/customtext.yate \
#	qt4/customtree.yate qt4/widgetlist.yate qt4/clientarchive.yate



##==========================================================
	
ADD_LIBRARY(callfork SHARED
    callfork.cpp
)

yate_modules( callfork modules-base modules )


##==========================================================
	
ADD_LIBRARY(cdrbuild SHARED
    cdrbuild.cpp
)

yate_modules( cdrbuild modules-base modules )


##==========================================================
	
ADD_LIBRARY(cdrcombine SHARED
    cdrcombine.cpp
)

yate_modules( cdrcombine modules-base modules )

##==========================================================

ADD_LIBRARY(cdrfile SHARED
    cdrfile.cpp
)

yate_modules( cdrfile modules-base modules )


##==========================================================

ADD_LIBRARY(conference SHARED
    conference.cpp
)

yate_modules( conference modules-base modules )

##==========================================================

ADD_LIBRARY(dumbchan SHARED
    dumbchan.cpp
)

yate_modules( dumbchan modules-base modules )

##==========================================================

ADD_LIBRARY(extmodule SHARED
    extmodule.cpp
)

yate_modules( extmodule modules-base modules )


##==========================================================

ADD_LIBRARY(filetransfer SHARED
    filetransfer.cpp
)

yate_modules( filetransfer modules-base modules )

##==========================================================

ADD_LIBRARY(fileinfo SHARED
    fileinfo.cpp
)

yate_modules( fileinfo modules-base modules )

##==========================================================

ADD_LIBRARY(gvoice SHARED
    gvoice.cpp
)

yate_modules( gvoice modules-base modules )

##==========================================================

if(NOT WIN32)

ADD_LIBRARY(javascript SHARED
    javascript.cpp
)


TARGET_INCLUDE_DIRECTORIES(javascript PUBLIC ../libs/yscript ../libs/ypbx)

TARGET_LINK_LIBRARIES( javascript yscript ypbx)

yate_modules( javascript modules-base modules )

endif()

##==========================================================

if(NOT WIN32)

ADD_LIBRARY(moh SHARED
    moh.cpp
)

yate_modules( moh modules-base modules )

endif()


##==========================================================

ADD_LIBRARY(mux SHARED
    mux.cpp
)

yate_modules( mux modules-base modules )


##==========================================================

ADD_LIBRARY(pbx SHARED
    pbx.cpp
)

yate_modules( pbx modules-base modules )

##==========================================================
	
ADD_LIBRARY(msgsniff SHARED
    msgsniff.cpp
)

yate_modules( msgsniff modules-base modules )


##==========================================================
	
ADD_LIBRARY(regexroute SHARED
    regexroute.cpp
)

yate_modules( regexroute modules-base modules )


##==========================================================

ADD_LIBRARY(rmanager SHARED
    rmanager.cpp
)

yate_modules( rmanager modules-base modules )


##==========================================================

ADD_LIBRARY(tonegen SHARED
    tonegen.cpp
)

yate_modules( tonegen modules-base modules )

##==========================================================

ADD_LIBRARY(tonedetect SHARED
    tonedetect.cpp
)

yate_modules( tonedetect modules-base modules )


##==========================================================

ADD_LIBRARY(ysockschan SHARED
    ysockschan.cpp
)

yate_modules( ysockschan modules-base modules )

	
##==========================================================

ADD_LIBRARY(ystunchan SHARED
    ystunchan.cpp
)

yate_modules( ystunchan modules-base modules )

##==========================================================

ADD_LIBRARY(yrtpchan SHARED
    yrtpchan.cpp
)

TARGET_INCLUDE_DIRECTORIES(yrtpchan PUBLIC ../libs/yrtp )

TARGET_LINK_LIBRARIES( yrtpchan yrtp)

yate_modules( yrtpchan modules-base modules )

##==========================================================

ADD_LIBRARY(ysipchan SHARED
    ysipchan.cpp
)

TARGET_INCLUDE_DIRECTORIES(ysipchan PUBLIC ../libs/ysip ../libs/ysdp)

TARGET_LINK_LIBRARIES( ysipchan ysip ysdp)

yate_modules( ysipchan modules-base modules )

##==========================================================

ADD_LIBRARY(yiaxchan SHARED
    yiaxchan.cpp
)

TARGET_INCLUDE_DIRECTORIES(yiaxchan PUBLIC ../libs/yiax )

TARGET_LINK_LIBRARIES( yiaxchan yiax )

yate_modules( yiaxchan modules-base modules )


##==========================================================


##ADD_LIBRARY(yjinglechan SHARED
#    yjinglechan.cpp
#)

#TARGET_INCLUDE_DIRECTORIES(yjinglechan PUBLIC ../libs/yjabber )

#TARGET_LINK_LIBRARIES( yjinglechan yjabber )

#yate_modules( yjinglechan modules-base modules )

##==========================================================

ADD_LIBRARY(wavefile SHARED
    wavefile.cpp
)

yate_modules( wavefile modules-base modules )



##==========================================================

ADD_LIBRARY(callgen SHARED
    callgen.cpp
)

yate_modules( callgen modules-base modules )


##==========================================================

ADD_LIBRARY(analyzer SHARED
    analyzer.cpp
)

yate_modules( analyzer modules-base modules )


##==========================================================

ADD_LIBRARY(wiresniff SHARED
    wiresniff.cpp
)

yate_modules( wiresniff modules-base modules )


##==========================================================

