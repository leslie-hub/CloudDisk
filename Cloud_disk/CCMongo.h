//
// Created by pl on 2022/1/5.
//

#pragma once
#include <iostream>
#include <mongo/client/dbclient.h>
#include <string>
#include <mongocxx/client.hpp>
using namespace std;

typedef unsigned long long mongoulong;

class CCMongo
{
public:

    CCMongo();
    mongoulong UploadFile(const char *LocalFile, const char *MongoFile);
    int downloadFile(const char *MongoFile,const char *DesFile);
    ~CCMongo();
};

