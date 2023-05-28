Commands for compiling and running the sfml code
g++ -c main.cpp
g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app



g++ -IC:\SFML-2.5.1\include -c main.cpp 
g++ -LC:\SFML-2.5.1\lib .\main.o -o app.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows
./app


