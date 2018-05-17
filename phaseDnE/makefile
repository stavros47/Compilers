all: avm al

al:
	cd phaseD && make

avm:
	cd phaseE/avm && make

clean:
	rm al avm
	cd phaseD && make clean
	cd phaseE/avm && make clean
	rm *.txt
