# Wind River Workbench generated Makefile.
# Do not edit!!!
#
# The file ".wrmakefile" is the template used by the Wind River Workbench to
# generate the makefiles of this project. Add user-specific build targets and
# make rules only(!) in this project's ".wrmakefile" file. These will then be
# automatically dumped into the makefiles.

WIND_HOME := $(subst \,/,$(WIND_HOME))
WIND_BASE := $(subst \,/,$(WIND_BASE))
WIND_USR := $(subst \,/,$(WIND_USR))
WRVX_COMPBASE := $(subst \,/,$(WRVX_COMPBASE))

all : pre_build main_all post_build

_clean ::
	@echo "make: removing targets and objects of `pwd`"

TRACE=0
TRACEON=$(TRACE:0=@)
TRACE_FLAG=$(TRACEON:1=)

MAKEFILE := Makefile

FLEXIBLE_BUILD := 1

BUILD_SPEC = PPC32e500v2diab_SMP
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
WS_ROOT_DIR := C:/WindRiver/workspace2
PRJ_ROOT_DIR := E:/0_RT_Lab_WorkBench/20201216MainForceControl/demo_7700_v2_1



#Global Build Macros
PROJECT_TYPE = DKM
DEFINES = 
EXPAND_DBG = 0


#BuildSpec specific Build Macros
VX_CPU_FAMILY = ppc
CPU = PPC32
TOOL_FAMILY = diab
TOOL = e500v2diab
TOOL_PATH = 
CC_ARCH_SPEC = -tPPCE500V2FH:vxworks69
VSB_DIR = $(WIND_BASE)/target/lib_smp
VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 

IDE_LIBRARIES = 

IDE_DEFINES = -DCPU=_VX_$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_WRS_VX_SMP -D_WRS_CONFIG_SMP -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\"   -DIP_PORT_VXWORKS=69 



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
DEBUGFLAGS_C++-Compiler = -g
DEBUGFLAGS_Linker = -g
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_C-Compiler =  -XO -Xsize-opt 
DEBUGFLAGS_C++-Compiler =  -XO -Xsize-opt 
DEBUGFLAGS_Linker =  -XO -Xsize-opt 
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler =  -XO -Xsize-opt 
endif


#Project Targets
PROJECT_TARGETS = demo_7700_cps11_v1/$(MODE_DIR)/demo_7700_cps11_v1.out


#Rules

# demo_7700_cps11_v1
ifeq ($(DEBUG_MODE),1)
demo_7700_cps11_v1/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
demo_7700_cps11_v1/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
demo_7700_cps11_v1/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
demo_7700_cps11_v1/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
demo_7700_cps11_v1/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
demo_7700_cps11_v1/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
demo_7700_cps11_v1/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler =  -XO -Xsize-opt 
demo_7700_cps11_v1/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler =  -XO -Xsize-opt 
demo_7700_cps11_v1/$(MODE_DIR)/% : DEBUGFLAGS_Linker =  -XO -Xsize-opt 
demo_7700_cps11_v1/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
demo_7700_cps11_v1/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
demo_7700_cps11_v1/$(MODE_DIR)/% : DEBUGFLAGS_Assembler =  -XO -Xsize-opt 
endif
demo_7700_cps11_v1/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
demo_7700_cps11_v1/$(MODE_DIR)/% : IDE_LIBRARIES = 
demo_7700_cps11_v1/$(MODE_DIR)/% : IDE_DEFINES = -DCPU=_VX_$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL -D_WRS_VX_SMP -D_WRS_CONFIG_SMP -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\"   -DIP_PORT_VXWORKS=69 
demo_7700_cps11_v1/$(MODE_DIR)/% : PROJECT_TYPE = DKM
demo_7700_cps11_v1/$(MODE_DIR)/% : DEFINES = 
demo_7700_cps11_v1/$(MODE_DIR)/% : EXPAND_DBG = 0
demo_7700_cps11_v1/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
demo_7700_cps11_v1/$(MODE_DIR)/% : CPU = PPC32
demo_7700_cps11_v1/$(MODE_DIR)/% : TOOL_FAMILY = diab
demo_7700_cps11_v1/$(MODE_DIR)/% : TOOL = e500v2diab
demo_7700_cps11_v1/$(MODE_DIR)/% : TOOL_PATH = 
demo_7700_cps11_v1/$(MODE_DIR)/% : CC_ARCH_SPEC = -tPPCE500V2FH:vxworks69
demo_7700_cps11_v1/$(MODE_DIR)/% : VSB_DIR = $(WIND_BASE)/target/lib_smp
demo_7700_cps11_v1/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
demo_7700_cps11_v1/$(MODE_DIR)/% : LIBPATH = 
demo_7700_cps11_v1/$(MODE_DIR)/% : LIBS = 
demo_7700_cps11_v1/$(MODE_DIR)/% : OBJ_DIR := demo_7700_cps11_v1/$(MODE_DIR)

demo_7700_cps11_v1/$(MODE_DIR)/Objects/demo_7700_cps11_v1/ast7700Srio.o : $(PRJ_ROOT_DIR)/ast7700Srio.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP -Xc-new -Xdialect-c89  -Xstsw-slow -ei1518,4177,4223,4301,4550,5409,1606 -ei4193,4826,4381,4237,1573,4007,4082,4177,4223,4260,4550,5361,5828,2273,5387,5388 -ei1522,4092,4111,4152,4167,4171,4174,4186,4188,4191,4192,4223,4231,4236,4284,4375,4494,4513,5152,5457 -Xforce-declarations   -Xmake-dependency=0xd $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


demo_7700_cps11_v1/$(MODE_DIR)/Objects/demo_7700_cps11_v1/main.o : $(PRJ_ROOT_DIR)/main.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP -Xc-new -Xdialect-c89  -Xstsw-slow -ei1518,4177,4223,4301,4550,5409,1606 -ei4193,4826,4381,4237,1573,4007,4082,4177,4223,4260,4550,5361,5828,2273,5387,5388 -ei1522,4092,4111,4152,4167,4171,4174,4186,4188,4191,4192,4223,4231,4236,4284,4375,4494,4513,5152,5457 -Xforce-declarations   -Xmake-dependency=0xd $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


demo_7700_cps11_v1/$(MODE_DIR)/Objects/demo_7700_cps11_v1/subMod_DataDisplayUDP.o : $(PRJ_ROOT_DIR)/subMod_DataDisplayUDP.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP -Xc-new -Xdialect-c89  -Xstsw-slow -ei1518,4177,4223,4301,4550,5409,1606 -ei4193,4826,4381,4237,1573,4007,4082,4177,4223,4260,4550,5361,5828,2273,5387,5388 -ei1522,4092,4111,4152,4167,4171,4174,4186,4188,4191,4192,4223,4231,4236,4284,4375,4494,4513,5152,5457 -Xforce-declarations   -Xmake-dependency=0xd $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


demo_7700_cps11_v1/$(MODE_DIR)/Objects/demo_7700_cps11_v1/udp_ast7700TortlabCom.o : $(PRJ_ROOT_DIR)/udp_ast7700TortlabCom.c
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -W:c:,-Xclib-optim-off -Xansi -Xlocal-data-area-static-only  -W:c++:.CPP -Xc-new -Xdialect-c89  -Xstsw-slow -ei1518,4177,4223,4301,4550,5409,1606 -ei4193,4826,4381,4237,1573,4007,4082,4177,4223,4260,4550,5361,5828,2273,5387,5388 -ei1522,4092,4111,4152,4167,4171,4174,4186,4188,4191,4192,4223,4231,4236,4284,4375,4494,4513,5152,5457 -Xforce-declarations   -Xmake-dependency=0xd $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


OBJECTS_demo_7700_cps11_v1 = demo_7700_cps11_v1/$(MODE_DIR)/Objects/demo_7700_cps11_v1/ast7700Srio.o \
	 demo_7700_cps11_v1/$(MODE_DIR)/Objects/demo_7700_cps11_v1/main.o \
	 demo_7700_cps11_v1/$(MODE_DIR)/Objects/demo_7700_cps11_v1/subMod_DataDisplayUDP.o \
	 demo_7700_cps11_v1/$(MODE_DIR)/Objects/demo_7700_cps11_v1/udp_ast7700TortlabCom.o

demo_7700_cps11_v1/$(MODE_DIR)/demo_7700_cps11_v1.out : $(OBJECTS_demo_7700_cps11_v1)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";ddump -Ng $(OBJECTS_demo_7700_cps11_v1) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c ppc -tags $(VSB_DIR)/tags/ppc/PPC32/e500v2common/dkm.tags > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)dcc $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -Xdollar-in-ident -ei1518,4177,4223,4301,4550,5409,1606 -ei4193,4826,4381,4237,1573,4007,4082,4177,4223,4260,4550,5361,5828,2273,5387,5388 -ei1522,4092,4111,4152,4167,4171,4174,4186,4188,4191,4192,4223,4231,4236,4284,4375,4494,4513,5152,5457 -Xforce-declarations  $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES)  $(IDE_DEFINES) $(DEFINES) -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)dld -tPPCE500V2FH:vxworks69 -X -r5 -r4 -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_demo_7700_cps11_v1) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

demo_7700_cps11_v1/$(MODE_DIR)/demo_7700_cps11_v1_compile_file : $(FILE) ;

_clean :: demo_7700_cps11_v1/$(MODE_DIR)/demo_7700_cps11_v1_clean

demo_7700_cps11_v1/$(MODE_DIR)/demo_7700_cps11_v1_clean : 
	$(TRACE_FLAG)if [ -d "demo_7700_cps11_v1" ]; then cd "demo_7700_cps11_v1"; rm -rf $(MODE_DIR); fi

DEP_FILES := demo_7700_cps11_v1/$(MODE_DIR)/Objects/demo_7700_cps11_v1/ast7700Srio.d demo_7700_cps11_v1/$(MODE_DIR)/Objects/demo_7700_cps11_v1/main.d demo_7700_cps11_v1/$(MODE_DIR)/Objects/demo_7700_cps11_v1/subMod_DataDisplayUDP.d \
	 demo_7700_cps11_v1/$(MODE_DIR)/Objects/demo_7700_cps11_v1/udp_ast7700TortlabCom.d
-include $(DEP_FILES)


WIND_SCOPETOOLS_BASE := $(subst \,/,$(WIND_SCOPETOOLS_BASE))

clean_scopetools :
	$(TRACE_FLAG)rm -rf $(PRJ_ROOT_DIR)/.coveragescope/db

CLEAN_STEP := clean_scopetools


-include $(PRJ_ROOT_DIR)/*.makefile

-include *.makefile

JOBS?=1
ifeq ($(JOBS),1)
main_all : external_build  $(PROJECT_TARGETS)
	@echo "make: built targets of `pwd`"
else
main_all : external_build 
	@$(MAKE) -f $(MAKEFILE) --jobs $(JOBS) $(MFLAGS) $(PROJECT_TARGETS);\
	echo "make: built targets of `pwd`"
endif 

# entry point for extending the build
external_build ::
	@echo ""

# main entry point for pre processing prior to the build
pre_build :: $(PRE_BUILD_STEP) generate_sources
	@echo ""

# entry point for generating sources prior to the build
generate_sources ::
	@echo ""

# main entry point for post processing after the build
post_build :: $(POST_BUILD_STEP) deploy_output
	@echo ""

# entry point for deploying output after the build
deploy_output ::
	@echo ""

clean :: external_clean $(CLEAN_STEP) _clean

# entry point for extending the build clean
external_clean ::
	@echo ""
