#include "gtest/gtest.h"

#include <unistd.h>
#include <thread>
#include "Socket.hpp"
//#include "abc.hpp"
//#include "../src/Socket.hpp"
//
//TEST(Socket, add)
//{
//    add(2,7);
//    Car carObj1;
//    carObj1.year = 321;
//    ASSERT_EQ(carObj1.getYear(), 321);
////res = add_numbers(1.0, 2.0);
//    //ASSERT_NEAR(res, 3.0, 1.0e-11);
//    ASSERT_TRUE(1);
//}

void ClientThread()
{
    Socket clientSocket;
    usleep(1000000);
    clientSocket.connect("127.0.0.1", 12345);

    for (;;)
    {
        //usleep(1000);
        char buffer[100];
        if (clientSocket.receive(buffer, 100)){
            std::cout << "received" << std::endl;
            clientSocket.send(buffer, 100);
            break;
        }
    }
}

//void ServerThread(Socket socket)
//{
//    Socket * clientSocket = socket.accept();
//}

//TEST(Socket, listen)
//{
//    Socket socket;
//    ASSERT_EQ(socket.bind("127.0.0.1", 12345), 0);
//    ASSERT_TRUE(socket.listen());
//    ASSERT_TRUE(1);
//}
//
//TEST(Socket, connect)
//{
//    Socket serverSocket;
//    ASSERT_EQ(serverSocket.bind("127.0.0.1", 12345), 0);
//    ASSERT_TRUE(serverSocket.listen());
//    std::thread clientThread (ClientThread);
//
//    clientThread.join();
//
//    //ASSERT_TRUE(clientSocket.connect("127.0.0.1", 12345));
//
//
//}
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