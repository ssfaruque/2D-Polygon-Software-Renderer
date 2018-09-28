
CPP	:= g++
CPPFLAGS	:= -g -Wall -Werror

INCLUDEDIR	:= include
SRCDIR	:= src
DEPDIR	:= build/deps
OBJDIR	:= build/objs

PROGNAME	:= out
SRCS	:= $(shell ls src)
OBJS	:= $(SRCS:.cpp=.o)
DEPS	:= $(OBJS:.o=.d)

all: $(PROGNAME)

$(PROGNAME): OBJS



clean:
	$(RM) build/objs/*
	$(RM) build/deps/*



