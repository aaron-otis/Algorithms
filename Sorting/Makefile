CC = gcc
CFLAGS = -Wall -Werror -O3
TFLAGS = -g
CFILES = MergeSort.c SelectionSort.c RandomListGenerator.c
TARGET = RuntimeAnalysis
TEST = test
RM = /bin/rm
RFILES = *.log *.aux *~ *.gnuplot *.table
LATEX = /usr/bin/pdflatex
LFLAGS = -shell-escape
LFILES = Assignment1.tex

all: $(TARGET)

$(TARGET): $(TARGET).c $(CFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(CFILES)

test: $(CFILES) $(TEST).c
	$(CC) $(CFLAGS) $(TFLAGS) -o $(TEST) $(TEST).c $(CFILES)

latex: $(LFILES)
	$(LATEX) $(LFLAGS) $(LFILES)
	$(LATEX) $(LFLAGS) $(LFILES)

clean:
	$(RM) $(TARGET) $(TEST) $(RFILES)
