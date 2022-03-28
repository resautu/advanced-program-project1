poject01:Administrator.o calculator.o Datefunction.o main.o main_menu.o sundry_function.o User.o \
Administrator.h calculator.h Datebase.h Item.h MainMenu.h \
sundry.h User.h
	g++ Administrator.o calculator.o Datefunction.o main.o main_menu.o sundry_function.o User.o \
Administrator.h calculator.h Datebase.h Item.h MainMenu.h \
sundry.h User.h -o project01
main.o:main.cpp
	g++ -c main.cpp -o main.o
Administrator.o:Administrator.cpp
	g++ -c Administrator.cpp -o Administrator.o
calculator.o:calculator.cpp
	g++ -c calculator.cpp -o calculator.o
Datefunction.o:Datefunction.cpp
	g++ -c Datefunction.cpp -o Datefunction.o
main_menu.o:main_menu.cpp
	g++ -c main_menu.cpp -o main_menu.o
sundry_function.o:sundry_function.cpp
	g++ -c sundry_function.cpp -o sundry_function.o
User.o:User.cpp
	g++ -c User.cpp -o User.o

clean:
	rm *.o
	rm main