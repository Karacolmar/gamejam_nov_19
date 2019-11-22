# GNU Make project makefile autogenerated by Premake
ifndef config
  config=debug64
endif

ifndef verbose
  SILENT = @
endif

CC = gcc
CXX = g++
AR = ar

ifndef RESCOMP
  ifdef WINDRES
    RESCOMP = $(WINDRES)
  else
    RESCOMP = windres
  endif
endif

ifeq ($(config),debug64)
  OBJDIR     = obj/x64/Debug
  TARGETDIR  = ../../../bin
  TARGET     = $(TARGETDIR)/gamejam_nov_19d
  DEFINES   += -D__orxDEBUG__
  INCLUDES  += -I$(ORX)/include
  ALL_CPPFLAGS  += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS    += $(CFLAGS) $(ALL_CPPFLAGS) -ffast-math -g -msse2 -m64 -Wno-unused-function
  ALL_CXXFLAGS  += $(CXXFLAGS) $(ALL_CFLAGS) -fno-exceptions
  ALL_RESFLAGS  += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS   += $(LDFLAGS) -L$(ORX)/lib/dynamic -L. -static-libgcc -static-libstdc++ -m64 -L/usr/lib64 -Wl,-rpath ./ -Wl,--export-dynamic
  LIBS      += -lorxd -ldl -lm -lrt
  LDDEPS    +=
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
	@echo Running post-build commands
	cp -f $(ORX)/lib/dynamic/liborx*.so ../../../bin
  endef
endif

ifeq ($(config),profile64)
  OBJDIR     = obj/x64/Profile
  TARGETDIR  = ../../../bin
  TARGET     = $(TARGETDIR)/gamejam_nov_19p
  DEFINES   += -D__orxPROFILER__
  INCLUDES  += -I$(ORX)/include
  ALL_CPPFLAGS  += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS    += $(CFLAGS) $(ALL_CPPFLAGS) -ffast-math -g -msse2 -O2 -m64 -Wno-unused-function -fschedule-insns
  ALL_CXXFLAGS  += $(CXXFLAGS) $(ALL_CFLAGS) -fno-exceptions -fno-rtti
  ALL_RESFLAGS  += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS   += $(LDFLAGS) -L$(ORX)/lib/dynamic -L. -static-libgcc -static-libstdc++ -m64 -L/usr/lib64 -Wl,-rpath ./ -Wl,--export-dynamic
  LIBS      += -lorxp -ldl -lm -lrt
  LDDEPS    +=
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
	@echo Running post-build commands
	cp -f $(ORX)/lib/dynamic/liborx*.so ../../../bin
  endef
endif

ifeq ($(config),release64)
  OBJDIR     = obj/x64/Release
  TARGETDIR  = ../../../bin
  TARGET     = $(TARGETDIR)/gamejam_nov_19
  DEFINES   +=
  INCLUDES  += -I$(ORX)/include
  ALL_CPPFLAGS  += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS    += $(CFLAGS) $(ALL_CPPFLAGS) -ffast-math -g -msse2 -O2 -m64 -Wno-unused-function -fschedule-insns
  ALL_CXXFLAGS  += $(CXXFLAGS) $(ALL_CFLAGS) -fno-exceptions -fno-rtti
  ALL_RESFLAGS  += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS   += $(LDFLAGS) -L$(ORX)/lib/dynamic -L. -static-libgcc -static-libstdc++ -m64 -L/usr/lib64 -Wl,-rpath ./ -Wl,--export-dynamic
  LIBS      += -lorx -ldl -lm -lrt
  LDDEPS    +=
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
	@echo Running post-build commands
	cp -f $(ORX)/lib/dynamic/liborx*.so ../../../bin
  endef
endif

ifeq ($(config),debug32)
  OBJDIR     = obj/x32/Debug
  TARGETDIR  = ../../../bin
  TARGET     = $(TARGETDIR)/gamejam_nov_19d
  DEFINES   += -D__orxDEBUG__
  INCLUDES  += -I$(ORX)/include
  ALL_CPPFLAGS  += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS    += $(CFLAGS) $(ALL_CPPFLAGS) -ffast-math -g -msse2 -m32 -Wno-unused-function
  ALL_CXXFLAGS  += $(CXXFLAGS) $(ALL_CFLAGS) -fno-exceptions
  ALL_RESFLAGS  += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS   += $(LDFLAGS) -L$(ORX)/lib/dynamic -L. -static-libgcc -static-libstdc++ -m32 -L/usr/lib32 -Wl,-rpath ./ -Wl,--export-dynamic
  LIBS      += -lorxd -ldl -lm -lrt
  LDDEPS    +=
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
	@echo Running post-build commands
	cp -f $(ORX)/lib/dynamic/liborx*.so ../../../bin
  endef
endif

ifeq ($(config),profile32)
  OBJDIR     = obj/x32/Profile
  TARGETDIR  = ../../../bin
  TARGET     = $(TARGETDIR)/gamejam_nov_19p
  DEFINES   += -D__orxPROFILER__
  INCLUDES  += -I$(ORX)/include
  ALL_CPPFLAGS  += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS    += $(CFLAGS) $(ALL_CPPFLAGS) -ffast-math -g -msse2 -O2 -m32 -Wno-unused-function -fschedule-insns
  ALL_CXXFLAGS  += $(CXXFLAGS) $(ALL_CFLAGS) -fno-exceptions -fno-rtti
  ALL_RESFLAGS  += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS   += $(LDFLAGS) -L$(ORX)/lib/dynamic -L. -static-libgcc -static-libstdc++ -m32 -L/usr/lib32 -Wl,-rpath ./ -Wl,--export-dynamic
  LIBS      += -lorxp -ldl -lm -lrt
  LDDEPS    +=
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
	@echo Running post-build commands
	cp -f $(ORX)/lib/dynamic/liborx*.so ../../../bin
  endef
endif

ifeq ($(config),release32)
  OBJDIR     = obj/x32/Release
  TARGETDIR  = ../../../bin
  TARGET     = $(TARGETDIR)/gamejam_nov_19
  DEFINES   +=
  INCLUDES  += -I$(ORX)/include
  ALL_CPPFLAGS  += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS    += $(CFLAGS) $(ALL_CPPFLAGS) -ffast-math -g -msse2 -O2 -m32 -Wno-unused-function -fschedule-insns
  ALL_CXXFLAGS  += $(CXXFLAGS) $(ALL_CFLAGS) -fno-exceptions -fno-rtti
  ALL_RESFLAGS  += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  ALL_LDFLAGS   += $(LDFLAGS) -L$(ORX)/lib/dynamic -L. -static-libgcc -static-libstdc++ -m32 -L/usr/lib32 -Wl,-rpath ./ -Wl,--export-dynamic
  LIBS      += -lorx -ldl -lm -lrt
  LDDEPS    +=
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
	@echo Running post-build commands
	cp -f $(ORX)/lib/dynamic/liborx*.so ../../../bin
  endef
endif

OBJECTS := \
	$(OBJDIR)/gamejam_nov_19.o \

RESOURCES := \

SHELLTYPE := msdos
ifeq (,$(ComSpec)$(COMSPEC))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  SHELLTYPE := posix
endif

.PHONY: clean prebuild prelink

all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

$(TARGET): $(GCH) $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking gamejam_nov_19
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning gamejam_nov_19
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
.NOTPARALLEL: $(GCH) $(PCH)
$(GCH): $(PCH)
	@echo $(notdir $<)
	$(SILENT) $(CXX) -x c++-header $(ALL_CXXFLAGS) -MMD -MP $(DEFINES) $(INCLUDES) -o "$@" -MF "$(@:%.gch=%.d)" -c "$<"
endif

$(OBJDIR)/gamejam_nov_19.o: ../../../src/gamejam_nov_19.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(OBJDIR)/$(notdir $(PCH)).d
endif
