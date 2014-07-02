# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "HAVE_NANOSLEEP=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0 -I../../Libraries -I../../Libraries/libusbx -I../../Source -I../../Libraries/dfu-util/
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt ../../Libraries/libusbx/libusb-1.0.so
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "HAVE_NANOSLEEP=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  TARGET := OwlNest
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "HAVE_NANOSLEEP=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -Os -I../../Libraries -I../../Libraries/libusbx -I../../Source -I../../Libraries/dfu-util/
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -fvisibility=hidden -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt ../../Libraries/libusbx/libusb-1.0.so
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "HAVE_NANOSLEEP=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=1.0.0" -D "JUCE_APP_VERSION_HEX=0x10000" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  TARGET := OwlNest
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/DfuseLoader_f2d40499.o \
  $(OBJDIR)/ApplicationSettingsWindow_2723744.o \
  $(OBJDIR)/DualPatchPanel_2c59bfc1.o \
  $(OBJDIR)/OwlNestGui_a87229a8.o \
  $(OBJDIR)/PatchComponent_9fa7269e.o \
  $(OBJDIR)/PatchMode_d85501ec.o \
  $(OBJDIR)/StompGui_6de188b3.o \
  $(OBJDIR)/TransportPanel_18909a64.o \
  $(OBJDIR)/StompBoxAudioProcessor_ad448c3f.o \
  $(OBJDIR)/PluginEditor_94d4fb09.o \
  $(OBJDIR)/PluginPatchProcessor_a02b7946.o \
  $(OBJDIR)/ApplicationConfiguration_4b5ea10f.o \
  $(OBJDIR)/FirmwareLoader_f0d96237.o \
  $(OBJDIR)/Main_90ebc5c2.o \
  $(OBJDIR)/OwlNestSettings_f89e5d20.o \
  $(OBJDIR)/PatchProcessor_b85b83b3.o \
  $(OBJDIR)/PatchRegistry_cb5b7186.o \
  $(OBJDIR)/SampleBuffer_5a386a13.o \
  $(OBJDIR)/SeriesDeviceCallBacks_31482262.o \
  $(OBJDIR)/dfu_ad6672eb.o \
  $(OBJDIR)/dfu_file_6fdc65a.o \
  $(OBJDIR)/dfu_load_118a6344.o \
  $(OBJDIR)/dfu_util_21303760.o \
  $(OBJDIR)/dfuse_mem_b06ad2d3.o \
  $(OBJDIR)/quirks_144d50c7.o \
  $(OBJDIR)/sysex_728d86ff.o \
  $(OBJDIR)/BinaryData_ce4232d4.o \
  $(OBJDIR)/juce_audio_basics_2442e4ea.o \
  $(OBJDIR)/juce_audio_devices_a4c8a728.o \
  $(OBJDIR)/juce_audio_formats_d349f0c8.o \
  $(OBJDIR)/juce_audio_processors_44a134a2.o \
  $(OBJDIR)/juce_audio_utils_f63b12e8.o \
  $(OBJDIR)/juce_core_aff681cc.o \
  $(OBJDIR)/juce_data_structures_bdd6d488.o \
  $(OBJDIR)/juce_events_79b2840.o \
  $(OBJDIR)/juce_graphics_c8f1e7a4.o \
  $(OBJDIR)/juce_gui_basics_a630dd20.o \
  $(OBJDIR)/juce_gui_extra_7767d6a8.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking OwlNest
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning OwlNest
	@$(CLEANCMD)

strip:
	@echo Stripping OwlNest
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/DfuseLoader_f2d40499.o: ../../Source/DfuseLoader.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling DfuseLoader.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ApplicationSettingsWindow_2723744.o: ../../Source/ApplicationSettingsWindow.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ApplicationSettingsWindow.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/DualPatchPanel_2c59bfc1.o: ../../Source/DualPatchPanel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling DualPatchPanel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/OwlNestGui_a87229a8.o: ../../Source/OwlNestGui.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling OwlNestGui.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PatchComponent_9fa7269e.o: ../../Source/PatchComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PatchComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PatchMode_d85501ec.o: ../../Source/PatchMode.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PatchMode.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/StompGui_6de188b3.o: ../../Source/StompGui.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling StompGui.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TransportPanel_18909a64.o: ../../Source/TransportPanel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TransportPanel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/StompBoxAudioProcessor_ad448c3f.o: ../../Source/StompBoxAudioProcessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling StompBoxAudioProcessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PluginEditor_94d4fb09.o: ../../Source/PluginEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PluginEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PluginPatchProcessor_a02b7946.o: ../../Source/PluginPatchProcessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PluginPatchProcessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ApplicationConfiguration_4b5ea10f.o: ../../Source/ApplicationConfiguration.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ApplicationConfiguration.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/FirmwareLoader_f0d96237.o: ../../Source/FirmwareLoader.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling FirmwareLoader.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Main_90ebc5c2.o: ../../Source/Main.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Main.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/OwlNestSettings_f89e5d20.o: ../../Source/OwlNestSettings.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling OwlNestSettings.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PatchProcessor_b85b83b3.o: ../../Source/PatchProcessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PatchProcessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PatchRegistry_cb5b7186.o: ../../Source/PatchRegistry.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PatchRegistry.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SampleBuffer_5a386a13.o: ../../Source/SampleBuffer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SampleBuffer.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SeriesDeviceCallBacks_31482262.o: ../../Source/SeriesDeviceCallBacks.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SeriesDeviceCallBacks.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/dfu_ad6672eb.o: ../../Libraries/dfu-util/dfu.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling dfu.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/dfu_file_6fdc65a.o: ../../Libraries/dfu-util/dfu_file.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling dfu_file.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/dfu_load_118a6344.o: ../../Libraries/dfu-util/dfu_load.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling dfu_load.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/dfu_util_21303760.o: ../../Libraries/dfu-util/dfu_util.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling dfu_util.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/dfuse_mem_b06ad2d3.o: ../../Libraries/dfu-util/dfuse_mem.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling dfuse_mem.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/quirks_144d50c7.o: ../../Libraries/dfu-util/quirks.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling quirks.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sysex_728d86ff.o: ../../Libraries/sysex.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sysex.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinaryData.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_2442e4ea.o: ../../JuceLibraryCode/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_devices_a4c8a728.o: ../../JuceLibraryCode/modules/juce_audio_devices/juce_audio_devices.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_formats_d349f0c8.o: ../../JuceLibraryCode/modules/juce_audio_formats/juce_audio_formats.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_processors_44a134a2.o: ../../JuceLibraryCode/modules/juce_audio_processors/juce_audio_processors.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_utils_f63b12e8.o: ../../JuceLibraryCode/modules/juce_audio_utils/juce_audio_utils.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_utils.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_aff681cc.o: ../../JuceLibraryCode/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_bdd6d488.o: ../../JuceLibraryCode/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_79b2840.o: ../../JuceLibraryCode/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_c8f1e7a4.o: ../../JuceLibraryCode/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_a630dd20.o: ../../JuceLibraryCode/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_7767d6a8.o: ../../JuceLibraryCode/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
