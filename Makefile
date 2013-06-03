CC=g++
SRCDIR=src
OBJDIR=obj

all: noon noont fibo

_OBJ = CPU.o Parser.o Settings.o
OBJ = $(patsubst %, $(OBJDIR)/%,$(_OBJ))

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(SRCDIR)/%.h
#$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) -c -o $@ $<

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	$(CC) -c $(SRCDIR)/main.cpp -o $(OBJDIR)/main.o

$(OBJDIR)/fibonacci.o: $(SRCDIR)/fibonacci.cpp
	$(CC) -c $(SRCDIR)/fibonacci.cpp -o $(OBJDIR)/fibonacci.o

noon: $(OBJ) $(OBJDIR)/main.o
	$(CC) $^ -o $@

noont: $(SRCDIR)/test.cpp noon
	$(CC) $< -o $@

fibo: $(OBJ) $(OBJDIR)/fibonacci.o
	$(CC) $^ -o $@

clean:
	rm $(OBJDIR)/*.o noon noont fibo

