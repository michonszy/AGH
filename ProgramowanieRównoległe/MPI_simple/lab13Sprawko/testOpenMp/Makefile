CPP = /usr/local/opt/llvm/bin/clang
CPPFLAGS = -I/usr/local/opt/llvm/include -fopenmp
LDFLAGS = -L/usr/local/opt/llvm/lib

calka_omp: calka_omp.c
     $(CPP) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)
