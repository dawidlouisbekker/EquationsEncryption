#pragma once
#ifndef THISGRPCLIENT
#define THISGRPCCLIENT

#include <iostream>
#include <memory>
#include <string>
#include <random>
#include <Windows.h>
#include <windows.h>
#include <stdlib.h>
#include <grpcpp/grpcpp.h>
#include "equations.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using validator::Validator;
using validator::IP;
using validator::Answer;
using validator::Variables;

class ValidatorClient {
private:
    double answer;
public:
    ValidatorClient(std::shared_ptr<Channel> channel) : stub_(Validator::NewStub(channel)) {
        answer = 0;
    }


    void EstablishConnection(const std::string& ip) {
        IP request;
        request.set_ip(ip);
        Variables reply;
        ClientContext context;

        Status status = stub_->EstablishCon(&context, request, &reply);

        if (status.ok()) {
            std::cout << "Received: a=" << reply.a()
                << ", b=" << reply.b()
                << ", c=" << reply.c()
                << ", x=" << reply.x()
                << " Equation context=" << reply.equtioncontext() << std::endl;

            Equations calc = Equations();
            
            answer = calc.CalcAnswer(reply.a(), reply.b(), reply.c(), reply.x(), reply.equtioncontext());



        }
        else {
            std::cerr << "RPC failed: " << status.error_code()
                << ": " << status.error_message() << std::endl;
        }
    }

    void SendAnswer() {
        Answer request;
        request.set_answer(answer);
        Variables reply;
        ClientContext context;

        Status status = stub_->GiveVariables(&context, request, &reply);

        if (status.ok()) {
            std::cout << "Echoed: a=" << reply.a()
                << ", b=" << reply.b()
                << ", c=" << reply.c()
                << ", x=" << reply.x() << std::endl;
                Equations calc = Equations();

                answer = calc.CalcAnswer(reply.a(), reply.b(), reply.c(), reply.x(), reply.equtioncontext());
        }
        else {
            std::cerr << "RPC failed: " << status.error_code()
                << ": " << status.error_message() << std::endl;
        }
    }

private:
    std::unique_ptr<Validator::Stub> stub_;
};

void WebHookclient(const std::string url) {
    // Open the URL in the default web browser
    std::system("start http://127.0.0.1:8080/adbfinejwnileubfjksn");

}

int client(std::string port) {

        std::string target_str = "127.0.0.1:" + port;
        std::string input;

        bool isFInished = false;
        ValidatorClient client(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
        client.EstablishConnection(target_str);
        std::cout << std::endl << "client started" << std::endl << std::endl;

        while (isFInished == false) {

            client.SendAnswer();
            std::cout << std::endl << "again(y/n):";
            std::getline(std::cin, input);
            if (input == "y") {

                continue;
            }
            else {
                isFInished = true;
            }

        }
    return 0;
}

#endif // !"THISGRPCLIENT"

