#include<iostream>
#include <Winsock2.h>
#include <string>
#pragma comment(lib,"WS2_32")
using namespace std;

void main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return;
	}

	if (LOBYTE(wsaData.wVersion) != 1 ||
		HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup();
		return;
	}
	SOCKET fd;//服务器套接字  
	struct sockaddr_in addr;
	char buf[100] = "0012host:transport-any";

	//创建套接字
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == fd)
	{
		cout << "socket failed!" << endl;
		WSACleanup();//释放套接字资源  
		return;
	}

	//设置服务器地址
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(5037);

	//连接服务器
	int retVal = connect(fd, (sockaddr *)&addr, sizeof(addr));
	if (SOCKET_ERROR == retVal)
	{
		cout << "connect failed!" << endl;
		closesocket(fd);//关闭套接字  
		WSACleanup(); //释放套接字资源  
		return;
	}
	//向服务器发送数据
	send(fd, buf, 100, 0);
	Sleep(1000);
	ZeroMemory(buf, 100);
	recv(fd, buf, 100, 0);
	//cout << buf << endl;

	char buf_device[100] = "000Agetdevice:";
	//向服务器发送数据
	send(fd, buf_device, 100, 0);
	ZeroMemory(buf_device, 100);
	Sleep(1000);
	recv(fd, buf_device, 100, 0);// 接收服务器端的数据， 只接收100个字符  

	std::string sdevice = buf_device;
	sdevice.replace(0,4,"");
	cout << "型号:" + sdevice << endl;
	
	closesocket(fd);//关闭套接字  
	WSACleanup(); //释放套接字资源  

	system("pause");
}