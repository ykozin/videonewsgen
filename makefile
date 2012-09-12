TARGET=videonewsgen
ROOT=`pwd`
OBJDIR=$(ROOT)/obj
BINDIR=$(ROOT)/bin
LOGDIR=$(ROOT)/log
SRCDIR=$(ROOT)/src
CC=g++
CFLAGS=-O3  `pkg-config --cflags gstreamer-0.10`
LDFLAGS=`pkg-config --libs gstreamer-0.10`

$(TARGET) : createdirs core
	$(CC) $(LDFLAGS) -o $(BINDIR)/$(TARGET) \
	$(OBJDIR)/core.o

core : 
	$(CC) $(CFLAGS) -c $(SRCDIR)/core.cpp -o $(OBJDIR)/core.o
	
createdirs :
	if [ ! -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi
	if [ ! -d $(BINDIR) ]; then mkdir $(BINDIR); fi
	if [ ! -d $(LOGDIR) ]; then mkdir $(LOGDIR); fi
	
clean :
	rm -rf $(OBJDIR)/*.o
