CC     = gcc
FLAGS  = -g -Wall
LINK   = -lpng

TARGET = mnist-data
OBJDIR = objs

SOURCE = $(shell find src/ -name \*.c)
OBJS   = $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(SOURCE)))
BINDIR = $(dir $(OBJS))

default:
	[ -d  $(OBJDIR)  ] || mkdir -pv $(OBJDIR)
	[ -d "$(BINDIR)" ] || mkdir -pv $(BINDIR)
	make $(TARGET)

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(FLAGS) $(LINK)

$(OBJDIR)/%.o:%.c
	$(CC) -o $@ -c $<

clear:
	[ ! -d $(OBJDIR) ] || rm -rv $(OBJDIR)
	[ ! -f $(TARGET) ] || rm -v $(TARGET)

all:
	make clear default
