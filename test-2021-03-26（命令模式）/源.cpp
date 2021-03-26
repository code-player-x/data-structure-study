#define CRT SECURE NO WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue> //queue的头文件
#include<Windows.h>
using namespace std;
//发送协议类
class HandleClientProtocol
{
public:
	//处理增加金币
	void Addmoney()
	{
		cout << "给玩家增加金币!" << endl;
	}
	//处理增加钻石
	void AddDiamond()
	{
		cout << "给玩家增加钻石!" << endl;
	}
	//处理玩家装备
	void AddEquipment()
	{
		cout << "给玩家穿装备!" << endl;
	}
	//处理玩家等级
	void addLevel() {
		cout << "给玩家增加等级!" << endl;
	}
};
//////////////////////////////////////////////////////////////////////////////////
// 命令接口
class AbstractCommand
{
public:
	virtual void  handle() = 0;//处理客户端请求的接口
};
//处理增加金币请求
class AddMoneyCommand :public AbstractCommand
{
public:
	HandleClientProtocol* pProtocal;
public:
	AddMoneyCommand(HandleClientProtocol* pProtocal)
	{
		this->pProtocal = pProtocal;
	}
	virtual void  handle()
	{
		this->pProtocal->Addmoney();
	}
};
//处理增加钻石的请求
class AddDiamondCommand :public AbstractCommand {
public:
	AddDiamondCommand(HandleClientProtocol* pProtocol) {
		this->pProtocol = pProtocol;
	}
	virtual void handle() {
		this->pProtocol->AddDiamond();
	}
public:
	HandleClientProtocol* pProtocol;
};
//处理增加装备的请求
class AddEquipmentCommand : public AbstractCommand {
public:
	HandleClientProtocol* pProtocol;
public:
	AddEquipmentCommand(HandleClientProtocol* pProtocol) {
		this->pProtocol = pProtocol;
	}
	virtual void handle() {
		this->pProtocol->AddEquipment();
	}
};
//处理玩家升级的请求
class AddLevelCommand :public AbstractCommand {
public:
	HandleClientProtocol* pProtocol;
public:
	AddLevelCommand(HandleClientProtocol* pProtocol) {
		this->pProtocol = pProtocol;
	}
	virtual void handle() {
		this->pProtocol->addLevel();
	}
};
//////////////////////////////////////////////////////////////////////////////////
//服务器程序
class Server {
public:
	queue<AbstractCommand*> mCommands;
public:
	void startHandle()
	{
		while (!mCommands.empty())
			//查看是否为空范例 M.empty()是的话返回1，不是返回0;
		{
			Sleep(2000);
			AbstractCommand* command = mCommands.front();//显示第一个元素M.front()
			command->handle();
			mCommands.pop();//清除第一个元素 M.pop()
		}
	}
	void addRequest(AbstractCommand* command)
	{
		mCommands.push(command);//从已有元素后面增加元素   M.push()
	}
};
void test01()
{
	HandleClientProtocol* pProtocal = new HandleClientProtocol;
	//客户端增加金市的请求
	AbstractCommand* addmoney = new AddMoneyCommand(pProtocal);
	//客户端增加钻石的请求
	AbstractCommand* adddiamond = new AddDiamondCommand(pProtocal);
	//客户端穿装备的请求
	AbstractCommand* addequpment = new AddEquipmentCommand(pProtocal);
	//客户端升级请求
	AbstractCommand* addlevel = new AddLevelCommand(pProtocal);
	Server* server = new Server;
	//将客户端请求加入到处理的队列中

	server->addRequest(addmoney);
	server->addRequest(adddiamond);
	server->addRequest(addequpment);
	server->addRequest(addlevel);
	//服务器开始处理请求
	server->startHandle();
}
int main()
{
	test01();
	return 0;
}