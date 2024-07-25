all: CalcCoreLib clean

CalcCoreLib:
	mkdir -p Build
	mkdir -p include
	cd Build && Cmake ../src && make
	mv Build/libCalcCore* include/

clean:
	rm -rf Build
