DEPS =  headers/avm.h ../phaseD/instructions.h
obj = avm.o avm_utilities.o avm_table.o avm_dispatchers.o avm_execute.o avm_execute_table.o avm_execute_function.o avm_execute_jump.o avm_libfuncs.o avm_load.o
FLAGS = -std=c++11 -g
CC = g++

%.o: %.cpp $(DEPS)
	$(CC) -c $(FLAGS) $< -o $@ 

../avm: $(obj) $(DEPS)
	$(CC) $(FLAGS) $^ -o $@ -g

clean:
	rm ../avm 
	rm *.o 
