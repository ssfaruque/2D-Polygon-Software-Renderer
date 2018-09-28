
CPP	:= g++
CPPFLAGS	:= -g -Wall -Werror

INCLUDEDIR	:= include
SRCDIR	:= src
DEPDIR	:= build/deps
OBJDIR	:= build/objs
LIBS	:= -lgl -lglut

PROGNAME	:= out
SRCS	:= $(shell ls src)
OBJS	:= $(SRCS:.cpp=.o)
DEPS	:= $(OBJS:.o=.d)


all: $(PROGNAME)

-include $(DEPS)

$(PROGNAME): $(OBJDIR)/$(OBJS)
	$(CPP) $(CPPFLAGS) -I $(INCLUDEDIR) $(LIBS) -o $@ 


$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	echo $(OBJS)
	$(CPP) $(CPPFLAGS) -c $< -o $@ -I $(INCLUDEDIR) -MMD -MF $(DEPDIR)/$(patsubst $(OBJDIR)/%.o,%.d, $@)


clean:
	$(RM) build/objs/*
	$(RM) build/deps/*



