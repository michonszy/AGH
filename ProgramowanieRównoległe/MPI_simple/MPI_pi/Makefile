# kompilator c
#CCOMP = /usr/lib64/openmpi/bin/mpicc
CCOMP = /opt/homebrew/bin/mpicc

# konsolidator
#LOADER = /usr/lib64/openmpi/bin/mpicc
LOADER = /opt/homebrew/bin/mpicc

# program uruchomieniowy MPI
#MPI_run = /usr/lib64/openmpi/bin/mpiexec
MPI_run = /opt/homebrew/bin/mpiexec
#/opt/homebrew/bin/mpicc
# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3

# pliki naglowkowe
#INC = -I../pomiar_czasu

# biblioteki
#LIB = -L../pomiar_czasu -lm

all: MPI_simple run 

run: MPI_simple
	$(MPI_run) -np 4 ./MPI_simple

# zaleznosci i komendy
MPI_simple : MPI_simple.o
	$(LOADER) $(OPT) MPI_simple.o -o MPI_simple $(LIB)

# jak uzyskac plik moj_program.o ?
MPI_simple.o: MPI_simple.c 
	$(CCOMP) -c $(OPT) MPI_simple.c

clean:
	rm -f *.o
