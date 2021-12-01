CC	:=	g++
CFLAGS := -g -Wall

TARGET := tp2
SRCEXT := cpp

SRCDIR := src
OBJDIR := build
INCDIR := include
PROGDIR := program

INC := -I $(INCDIR)/
MAIN := $(PROGDIR)/main.cpp

SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

compile: $(OBJECTS)
	$(CC) $(CFLAGS) $(INC) $(MAIN) $^ -o $(TARGET)

clean:
	$(RM) -r $(OBJDIR)