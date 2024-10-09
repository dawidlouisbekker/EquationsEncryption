#include <iostream>
#include <memory>
#include <string>
#include <random>
#include <set>
#include <thread>
#include <grpcpp/grpcpp.h>
#include <google/protobuf/message.h>
#include "messages.grpc.pb.h"
#include "messages.pb.h"
#include "equations.h"
#include <Windows.h>
#include "ClientWebEntry.h"
#include "grpcServer.h"



int main(int argc, char** argv) {
       
  /*  
    
    int grpcPort = 0;

    
    std::cout << "This " << grpcPort;*/
    int port;
    bool isFinished = false;
    bool isConsoleFinished = false;

    port = StartHttpServer(isFinished);

    std::string input = "";

    RunServer(std::to_string(port));

    while (input != "exit") {
        
        std::getline(std::cin, input);
        if (input == "exit") {
            isConsoleFinished = true;
        }
    }

 /*   std::string server_port;
    std::thread server_thread(RunServer, 5, std::ref(server_port));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    server_thread.join();*/
    return 0;
}


   