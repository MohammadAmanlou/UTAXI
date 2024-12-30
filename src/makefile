CC = g++ --std=c++11
all: utaxi.out

utaxi.out: main.o utaxi.o app_manager.o user.o passenger.o driver.o trip.o location.o response.o request.o utilities.o server.o route.o handlers.o bad_request_err.o not_found_err.o permission_denied_err.o
	$(CC) main.o utaxi.o app_manager.o user.o passenger.o driver.o trip.o location.o response.o request.o utilities.o server.o route.o handlers.o bad_request_err.o not_found_err.o permission_denied_err.o -o utaxi.out

main.o: main.cpp app_manager.hpp
	$(CC) -c main.cpp -o main.o

app_manager.o: app_manager.cpp app_manager.hpp utaxi.hpp define.hpp
	$(CC) -c app_manager.cpp -o app_manager.o

utaxi.o: utaxi.cpp utaxi.hpp utaxi.hpp trip.hpp define.hpp passenger.hpp driver.hpp user.hpp location.hpp
	$(CC) -c utaxi.cpp -o utaxi.o

user.o: user.cpp user.hpp define.hpp
	$(CC) -c user.cpp -o user.o

passenger.o: passenger.cpp passenger.hpp user.hpp
	$(CC) -c passenger.cpp -o passenger.o

driver.o: driver.cpp driver.hpp user.hpp 
	$(CC) -c driver.cpp -o driver.o

trip.o: trip.cpp trip.hpp define.hpp
	$(CC) -c trip.cpp -o trip.o

location.o: location.cpp location.hpp define.hpp
	$(CC) -c location.cpp -o location.o

response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) -c utils/response.cpp -o response.o

request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) -c utils/request.cpp -o request.o

utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) -c utils/utilities.cpp -o utilities.o

server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) -c server/server.cpp -o server.o

route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) -c server/route.cpp -o route.o

handlers.o: handlers.cpp handlers.hpp 
	$(CC) -c handlers.cpp -o handlers.o

bad_request_err.o: bad_request_err.cpp bad_request_err.hpp
	$(CC) -c bad_request_err.cpp -o bad_request_err.o

not_found_err.o: not_found_err.cpp not_found_err.hpp
	$(CC) -c not_found_err.cpp -o not_found_err.o

permission_denied_err.o: permission_denied_err.cpp permission_denied_err.hpp
	$(CC) -c permission_denied_err.cpp -o permission_denied_err.o

.PHONY: clean
clean:
		rm -r *.o *.out