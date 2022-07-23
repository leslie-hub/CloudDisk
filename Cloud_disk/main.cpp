#include <iostream>
#include <vector>
#include <string>
#include "CCMysql.h"
#include "CCMongo.h"


using namespace std;

void splitString(const char *Src, char delim, vector<string> &vsplit)
{
    string tmp = Src;
    vsplit.clear();
    int index = 0;
    size_t last = 0;
    last = tmp.find_first_not_of(delim, last);//找到第一个不为分隔符的字符
    index = tmp.find_first_of(delim, last);//找到第一个分隔符
    while (index != string::npos)//npos代表字符串的结尾
    {
        string target = tmp.substr(last, index - last);
        vsplit.push_back(target);

        //last = index +1;
        last = tmp.find_first_not_of(delim, index);
        index = tmp.find_first_of(delim, last);

    }
    if (index == string::npos && tmp.length() > last)//到末尾了,如果整个长度大于last坐标,说明还有最后一个字符要放到vector
    {
        vsplit.push_back(tmp.substr(last));
    }
#if 0
    cout << vsplit.size() << endl;
	for (size_t i = 0; i < vsplit.size(); i++)
	{
		cout << "i=" << i << "," << vsplit[i].c_str() << endl;
	}
#endif
}

/*
- 上传 upload srcfile mongofile
- 下载 download mongofile desfile
- 查看  list
- 退出 quit
删除 delete mongofile  localfile
*/

int main(int argc,char *argv[])
{
    if (argc != 3){
        cout << "./main user passwd" << endl;
        return -1;
    }
    string line;
    vector<string> vCmd;
    CCMysql cmysql;
    CCMongo cmongo;

    if (cmysql.UserLogin(argv[1], argv[2]) < 1){
        cout << "login err" << endl;
        return -1;
    }
    while (1){//进入管理台
        cout << "ods>";
        getline(cin, line);//获取行，指令
        splitString(line.c_str(), ' ', vCmd);//拆分命令
        if (vCmd[0].compare("quit") == 0){
            //quit
            cout << "bye bye" << endl;
            break;
        }
        else if (vCmd[0].compare("upload") == 0){
            //上传
            cout << "upoload:" << vCmd[1] << "," << vCmd[2] << endl;
            //1.mysql insert
            cmysql.UploadFile(argv[1],vCmd[1].c_str(),vCmd[2].c_str());
            //2.mongo 上传文件
            myulong llsize=cmongo.UploadFile(vCmd[1].c_str(),vCmd[2].c_str());//返回上传的文件大小
            //3.mysql update
            //stat
            cmysql.UpdateFileInfo(llsize,argv[1],vCmd[1].c_str(),vCmd[2].c_str());
        }
        else if (vCmd[0].compare("download") == 0){
            //下载
            cout << "download:" << vCmd[1] << "," << vCmd[2] << endl;
            cmongo.downloadFile(vCmd[1].c_str(), vCmd[2].c_str());

        }
        else if (vCmd[0].compare("list") == 0){
            //查看
            //cout << vCmd[0] << endl;
            cmysql.ListFileInfo(argv[1]);

        }

    }
    return 0;
}
