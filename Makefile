
CPP	:= g++
CPPFLAGS	:= -g -Wall -Werror

INCLUDEDIR	:= include
SRCDIR	:= src
DEPDIR	:= build/deps
OBJDIR	:= build/objs
LIBS	:= -lGL -lglut 

PROGNAME	:= out
SRCS	:= $(shell ls src)
OBJS	:= $(SRCS:.cpp=.o)
DEPS	:= $(OBJS:.o=.d)


all: $(PROGNAME)

-include $(DEPS)

$(PROGNAME): $(patsubst %,$(OBJDIR)/%, $(OBJS)) 
	$(CPP) $(CPPFLAGS) $^ $(LIBS) -o $@ 


$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CPP) $(CPPFLAGS) -I $(INCLUDEDIR) -c $< -o $@ -MMD -MF $(DEPDIR)/$(patsubst $(OBJDIR)/%.o,%.d, $@)


clean:
	$(RM) build/objs/*
	$(RM) build/deps/*



