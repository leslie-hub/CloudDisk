//
// Created by pl on 2022/1/5.
//
#include <stdlib.h>
#include "CCMongo.h"

using namespace mongo;
DBClientConnection *conn = NULL;//全局conn

/**
 * 构造 连接mongodb
 */
CCMongo::CCMongo()
{
    //到时候来改写
    conn = new DBClientConnection(false, 0, 3);
    std::string errmsg;
    if (!conn->connect("localhost", errmsg)){
        cout << "connect to mongo err:" << errmsg << endl;
        exit(1);
    }
}

/**
 * 上传
 * @param LocalFile
 * @param MongoFile
 * @return
 */
mongoulong CCMongo::UploadFile(const char *LocalFile, const char *MongoFile)
{
    //构造 GridFS对象

    mongo::GridFS gfs(*conn, "ods");
    //上传文件
    mongo::BSONObj obj = gfs.storeFile(LocalFile, MongoFile);

    //GridFile findFile( BSONObj query ) const;
    return gfs.findFile(obj).getContentLength();//返回文件大小
    //return 0;


}

/**
 * 下载
 * @param MongoFile
 * @param DesFile
 * @return
 */
int CCMongo::downloadFile(const char *MongoFile, const char *DesFile)
{
    //通过gridfs 查找文件获得 gridfile 对象，write 就ok了
    //构造 GridFS对象
    mongo::GridFS gfs(*conn, "ods");
    gfs.findFile(MongoFile).write(DesFile);
    return 0;
}

/**
 * 关闭conn
 */
CCMongo::~CCMongo()
{
    if (conn){
        delete conn;
        conn = NULL;
    }
}

//**************************************************************mongocxx版本******************************

/**
 * 构造 连接mongodb
 *//*

CCMongo::CCMongo()
{
    //到时候来改写
    conn = new DBClientConnection(false, 0, 3);
    std::string errmsg;
    if (!conn->connect("localhost", errmsg)){
        cout << "connect to mongo err:" << errmsg << endl;
        exit(1);
    }
    // 数据库
    mongocxx::database db = client["fs"];
    // 集合
    mongocxx::collection coll = db["file"];
    mongocxx::
}

*/
/**
 * 上传
 * @param LocalFile
 * @param MongoFile
 * @return
 *//*

mongoulong CCMongo::UploadFile(const char *LocalFile, const char *MongoFile)
{
    //构造 GridFS对象
    mongo::GridFS gfs(*conn, "ods");
    //上传文件
    mongo::BSONObj obj = gfs.storeFile(LocalFile, MongoFile);

    //GridFile findFile( BSONObj query ) const;
    return gfs.findFile(obj).getContentLength();//返回文件大小
    //return 0;

}

*/
/**
 * 下载
 * @param MongoFile
 * @param DesFile
 * @return
 *//*

int CCMongo::downloadFile(const char *MongoFile, const char *DesFile)
{
    //通过gridfs 查找文件获得 gridfile 对象，write 就ok了
    //构造 GridFS对象
    mongo::GridFS gfs(*conn, "ods");
    gfs.findFile(MongoFile).write(DesFile);
    return 0;
}

*/
/**
 * 关闭conn
 *//*

CCMongo::~CCMongo()
{
    if (conn){
        delete conn;
        conn = NULL;
    }
}
*/


//**************************************************************mongocxx版本******************************
