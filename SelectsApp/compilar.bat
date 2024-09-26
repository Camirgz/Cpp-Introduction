cls

g++ -I"include" -c src/model.cpp -o bin/model.o
g++ -I"include" -c src/controller.cpp -o bin/controller.o
g++ -I"include" bin/model.o bin/controller.o src/selects.cpp -o bin/selects
::bin\selects.exe

g++ -c tests/tests.cpp -o bin/tests.o
g++ -I"include" bin/tests.o bin/model.o bin/controller.o tests/principalTests.cpp -o bin/tests
bin\tests.exe
