
SET(YATE_EXT_LIB_TARTGET ilbc)

ADD_LIBRARY(${YATE_EXT_LIB_TARTGET} STATIC


		anaFilter.c 
		iCBSearch.c 
		packing.c 
        constants.c 
		gainquant.c 
		iLBC_decode.c 
		StateConstructW.c 
        createCB.c 
		getCBvec.c 
		iLBC_encode.c 
		StateSearchW.c 
		doCPLC.c 
        helpfun.c 
		syntFilter.c 
		enhancer.c 
		hpInput.c 
		LPCdecode.c 
        filter.c 
		hpOutput.c 
		LPCencode.c 
		FrameClassify.c  
		iCBConstruct.c 
		lsf.c

)


## 链接Yate库
## TARGET_LINK_LIBRARIES( ${YATE_EXT_LIB_TARTGET} yateengine )

SET_PROPERTY(TARGET ${YATE_EXT_LIB_TARTGET} PROPERTY FOLDER "libs")

