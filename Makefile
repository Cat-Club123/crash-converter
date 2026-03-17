include $(DEVKITPRO)/wups/share/wups_rules

TARGET      := CrashCombo
SOURCES     := src
INCLUDES    := include

CFLAGS      := -Wall -O2 $(MACHDEP)
CXXFLAGS    := $(CFLAGS)
LDFLAGS     := $(WUPS_LDFLAGS)
LIBS        := -lvpad -lwups -lcoreinit
