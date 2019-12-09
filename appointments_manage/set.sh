g++ -c -g -std=c++11 -Wall -Werror  task_management_tool.cpp -o task_management_tool.o
g++ -c -g -std=c++11 -Wall -Werror  app.cpp -o app.o
g++ -g -std=c++11 -Wall -Werror task_management_tool.o app.o -o app
./app
