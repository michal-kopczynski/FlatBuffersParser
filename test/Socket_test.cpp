#include "gtest/gtest.h"

#include <unistd.h>
#include <thread>
#include "Socket.hpp"

void ClientThread()
{
    Socket clientSocket;
    usleep(1000000);
    clientSocket.connect("127.0.0.1", 12345);

    for (;;)
    {
        char buffer[100];
        if (clientSocket.receive(buffer, 100)){
            std::cout << "received" << std::endl;
            clientSocket.send(buffer, 100);
            break;
        }
    }
}

TEST(Socket, send_receive)
{
    Socket serverSocket;
    ASSERT_EQ(serverSocket.bind("127.0.0.1", 12345), 0);
    ASSERT_TRUE(serverSocket.listen());

    std::thread clientThread (ClientThread);
    std::shared_ptr<Socket> clientSocket = serverSocket.accept();
    std::cout << "client accepted" << std::endl;
    std::string testMessage("test message");

    clientSocket->send(testMessage.c_str(), testMessage.length());
    char rcvBuffer[100];
    clientSocket->receive(rcvBuffer, sizeof(rcvBuffer));
    std::string receivedMessage(rcvBuffer);
    ASSERT_EQ(receivedMessage, testMessage);

    clientThread.join();
}