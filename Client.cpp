#include <thread>
#include <string>
#include <grpcpp/grpcpp.h>
#include "messages.grpc.pb.h"
#include "messages.pb.h"
#include "client.h"
#include "equations.h"
#include "apiclient.h"
#include <google/protobuf/message.h>
#include <iostream>
#include <string>
#include <chrono>



int main() {
	std::string input;
	std::chrono::seconds(1);
	int grpcPort = 0;

	CallHttpServer(grpcPort);

	//std::cout << "port:";
	//std::cin >> grpcPort;
	client(std::to_string(grpcPort));
	std::getline(std::cin, input);



	//CallHttpServer();
	//std::cout << " done ";


}