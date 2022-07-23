//
// Created by pl on 2022/1/4.
//
#pragma once
#include <mysql/mysql.h>
typedef unsigned long long myulong;

class CCMysql
{
public:
    MYSQL *mysql;
    CCMysql();
    int UserLogin(const char *User,const char *Passwd);
    int ListFileInfo(const char *User);
    int UploadFile(const char *User,const char *LocalFile,const char *MongoFile);
    int UpdateFileInfo(myulong FileSize, const char *User, const char *LocalFile, const char *MongoFile);
    ~CCMysql();
};