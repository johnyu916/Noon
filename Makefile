CC=g++
SRCDIR=src
OBJDIR=obj

all: noon noont

_OBJ = CPU.o Parser.o Settings.o
OBJ = $(patsubst %, $(OBJDIR)/%,$(_OBJ))

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(SRCDIR)/%.h
#$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) -c -o $@ $<

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	$(CC) -c $(SRCDIR)/main.cpp -o $(OBJDIR)/main.o

noon: $(OBJ) $(OBJDIR)/main.o
	$(CC) $^ -o $@

noont: $(SRCDIR)/test.cpp noon
	$(CC) $< -o $@

fibo: $(SRCDIR)/fibonacci.cpp noon
	$(CC) $< -o $@

clean:
	rm $(OBJDIR)/*.o noon noont

