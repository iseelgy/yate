
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

ADD_LIBRARY(extmodule SHARED
    extmodule.cpp
)

yate_modules( extmodule modules-engine modules )


##==========================================================
	
ADD_LIBRARY(msgsniff SHARED
    msgsniff.cpp
)

yate_modules( msgsniff modules-engine modules )


##==========================================================

ADD_LIBRARY(rmanager SHARED
    rmanager.cpp
)

yate_modules( rmanager modules-engine modules )


##==========================================================

ADD_LIBRARY(ysockschan SHARED
    ysockschan.cpp
)

yate_modules( ysockschan modules-engine modules )

	
##==========================================================

ADD_LIBRARY(ystunchan SHARED
    ystunchan.cpp
)

yate_modules( ystunchan modules-engine modules )

##==========================================================

ADD_LIBRARY(wiresniff SHARED
    wiresniff.cpp
)

yate_modules( wiresniff modules-engine modules )



