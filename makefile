$(BUILD)
	g++
	-g
	-lstdc++
	-std=c++17
	-o
	Binary/app
	src/data_reader.cpp
	src/cluster.cpp
	src/k_fold.cpp
	src/k_means.cpp
	src/main.cpp

$(RUN)
	Binary/app.exe

$(CLEAN)
	del Binary/app.exe,src/pch.hpp.gch

$(PCH)
	g++ -std=c++17 src/pch.hpp