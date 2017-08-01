#
# OMNeT++/OMNEST Makefile for vlc
#
# This file was generated with the command:
#  opp_makemake -f --deep -O out
#

# Name of target to be created (-o option)
TARGET = vlc$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I. \
    -Inets \
    -Isrc \
    -Isrc/VLCchannel \
    -Isrc/VLCnode \
    -Isrc/VLCnode/VLCdevice \
    -Isrc/VLCnode/VLCmobilityManager

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/src/VLCcommons.o \
    $O/src/VLCchannel/VLCchannel.o \
    $O/src/VLCnode/VLCdevice/VLCtransmitter.o \
    $O/src/VLCnode/VLCdevice/VLCdevice.o \
    $O/src/VLCnode/VLCmobilityManager/VLCmobilityManager.o \
    $O/src/VLCnode/VLCmobilityManager/VLClineMobilityManager.o \
    $O/src/VLCchannel/VLCchannelMsg_m.o \
    $O/src/VLCnode/VLCmobilityManager/VLCmobilityMsg_m.o

# Message files
MSGFILES = \
    src/VLCchannel/VLCchannelMsg.msg \
    src/VLCnode/VLCmobilityManager/VLCmobilityMsg.msg

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f vlc vlc.exe libvlc.so libvlc.a libvlc.dll libvlc.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f nets/*_m.cc nets/*_m.h
	$(Q)-rm -f src/*_m.cc src/*_m.h
	$(Q)-rm -f src/VLCchannel/*_m.cc src/VLCchannel/*_m.h
	$(Q)-rm -f src/VLCnode/*_m.cc src/VLCnode/*_m.h
	$(Q)-rm -f src/VLCnode/VLCdevice/*_m.cc src/VLCnode/VLCdevice/*_m.h
	$(Q)-rm -f src/VLCnode/VLCmobilityManager/*_m.cc src/VLCnode/VLCmobilityManager/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc nets/*.cc src/*.cc src/VLCchannel/*.cc src/VLCnode/*.cc src/VLCnode/VLCdevice/*.cc src/VLCnode/VLCmobilityManager/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/src/VLCcommons.o: src/VLCcommons.cc \
	src/VLCcommons.h
$O/src/VLCchannel/VLCchannel.o: src/VLCchannel/VLCchannel.cc \
	src/VLCchannel/VLCchannel.h \
	src/VLCcommons.h \
	src/VLCnode/VLCdevice/VLCdevice.h
$O/src/VLCchannel/VLCchannelMsg_m.o: src/VLCchannel/VLCchannelMsg_m.cc \
	src/VLCchannel/VLCchannelMsg_m.h
$O/src/VLCnode/VLCdevice/VLCdevice.o: src/VLCnode/VLCdevice/VLCdevice.cc \
	src/VLCchannel/VLCchannel.h \
	src/VLCcommons.h \
	src/VLCnode/VLCdevice/VLCdevice.h \
	src/VLCnode/VLCmobilityManager/VLClineMobilityManager.h \
	src/VLCnode/VLCmobilityManager/VLCmobilityManager.h \
	src/VLCnode/VLCmobilityManager/VLCmobilityMsg_m.h
$O/src/VLCnode/VLCdevice/VLCtransmitter.o: src/VLCnode/VLCdevice/VLCtransmitter.cc \
	src/VLCcommons.h \
	src/VLCnode/VLCdevice/VLCdevice.h
$O/src/VLCnode/VLCmobilityManager/VLClineMobilityManager.o: src/VLCnode/VLCmobilityManager/VLClineMobilityManager.cc \
	src/VLCcommons.h \
	src/VLCnode/VLCmobilityManager/VLClineMobilityManager.h \
	src/VLCnode/VLCmobilityManager/VLCmobilityManager.h \
	src/VLCnode/VLCmobilityManager/VLCmobilityMsg_m.h
$O/src/VLCnode/VLCmobilityManager/VLCmobilityManager.o: src/VLCnode/VLCmobilityManager/VLCmobilityManager.cc \
	src/VLCchannel/VLCchannel.h \
	src/VLCcommons.h \
	src/VLCnode/VLCmobilityManager/VLCmobilityManager.h \
	src/VLCnode/VLCmobilityManager/VLCmobilityMsg_m.h
$O/src/VLCnode/VLCmobilityManager/VLCmobilityMsg_m.o: src/VLCnode/VLCmobilityManager/VLCmobilityMsg_m.cc \
	src/VLCnode/VLCmobilityManager/VLCmobilityMsg_m.h

