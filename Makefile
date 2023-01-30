INCLDIR	:= include
OBJDIR	:= obj
SRCDIR	:= src
BINDIR	:= bin
LIBDIR  := lib
LIBRARIES   := SDL SDL_image SDL_ttf

CXX       := g++
VPATH	  :=
LDFLAGS   := $(foreach librayrydir,$(LIBDIR),-L$(librayrydir))
LDLIBS    := $(foreach library,$(LIBRARIES),-l$(library))
CPPFLAGS  := -g -Wall $(foreach includedir,$(INCLDIR),-I$(includedir)) $(LDFLAGS)

#Source and object files (automatic)
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(subst $(SRCDIR)/,$(OBJDIR)/, $(subst .cpp,.o, $(SRCS)))

# Define here your main source files separated by spaces (without suffix!)
EXEC = main

#Phony = do not represent a file
#.PHONY: all
all : makedir $(EXEC)

# For multiple binaries
$(EXEC) : %: %.cpp $(OBJS)
	$(CXX) $(CPPFLAGS) -o $(BINDIR)/$@ $^ $(LDLIBS)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $^

#Clean: delete every binaries and object files
.PHONY: clean
clean :
	rm -rf $(OBJDIR)/*
	rm -rf $(BINDIR)/*
	rm $(SRCDIR)/*~
	rm $(INCLDIR)/*~


#Building folders (-p : no error if folder do not exist)
.PHONY: makedir
makedir :
	mkdir -p $(BINDIR)
	mkdir -p $(OBJDIR)

#For some debug
.PHONY: print
print :
	echo $(SRCS)
	echo $(OBJS)

#Remarks:
# $@ : filename representing the target
# $< : filename of the first prerequisite
# $^ : filenames of all prerequisites, separated by spaces. Dupplicated are removed.
# $? : names of all prerequisites that are newer than the target, separated by spaces
# $+ : similar to $^ but include dupplicates
# $* : stem of target file (filename without suffix)
