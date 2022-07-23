//
// Created by pl on 2022/1/4.
//

#include "CCMysql.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>


/**
 * 构造 也就是构造mysql句柄
 */
CCMysql::CCMysql()
{
    mysql = mysql_init(NULL);
    if (mysql == NULL){
        printf("mysql init err");
        exit(1);
    }
    mysql = mysql_real_connect(mysql, "localhost", "root", "123", "ods", 0, NULL, 0);
    if (mysql == NULL){
        printf("mysql connect err");
        exit(1);
    }

}

/**
 * 登录
 * @param User
 * @param Passwd
 * @return
 */
int CCMysql::UserLogin(const char *User, const char *Passwd)
{
    //用户名和密码匹配
    //执行该sql：select * from t_user_info where user_id='yekai' and pass_word='123';
    //如果有结果集，代表匹配
    if (strstr(Passwd, " or ")){
        printf("zhe yang bu hao!\n");
        return 0;
    }
    char rSql[512] = { 0 };

    sprintf(rSql, "select user_id from t_user_info where user_id='%s' and pass_word='%s'", User, Passwd);
    printf("%s\n", rSql);
    if (mysql_query(mysql, rSql)){
        printf("mysql exe err:%s\n", rSql);
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(mysql);//取结果集
    if (result != NULL){//该指针为空并非代表准确，有结果集，但结果集没有记录
        return (int)result->row_count;
    }
    return 0;// 代表结果不匹配

}

/**
 * 查看
 * @param User
 * @return
 */
int CCMysql::ListFileInfo(const char *User)
{
    //select * from t_file_info where user_id='yekai';
    //执行上面的sql，显示结果集
    char rSql[512] = { 0 };
    sprintf(rSql, "select * from t_file_info where user_id='%s'",User);
    if (mysql_query(mysql, rSql)){
        printf("query err:%s\n", rSql);
        return -1;
    }
    MYSQL_RES *result = mysql_store_result(mysql);//取结果集
    if (result != NULL)
    {//该指针为空并非代表准确，有结果集，但结果集没有记录
        MYSQL_ROW row;
        unsigned int num_fields;
        unsigned int i;

        num_fields = mysql_num_fields(result);
        while ((row = mysql_fetch_row(result)))
        {
            unsigned long *lengths;
            lengths = mysql_fetch_lengths(result);
            for (i = 0; i < num_fields; i++)
            {
                printf("%s\t",  row[i] ? row[i] : "NULL");
            }
            printf("\n");
        }
    }
    return 0;
}

/**
 * 上传 --- 初始化文件上传状态
 * @param User
 * @param LocalFile
 * @param MongoFile
 * @return
 */
int CCMysql::UploadFile(const char *User, const char *LocalFile, const char *MongoFile)
{
   // mysql> insert into t_file_info(local_file_name,mongo_file_name,file_size,user_id,status,remark) values('xxx.11','yyy.11',1024,'yekai','0','uploading');
   // 在mysql端 对于上传的工作其实就是insert信息到 t_file_info
    //需要执行上述insert语句，代表上传文件状态  刚开始肯定正在上传状态咯  status 为 0
    char rSql[512] = { 0 };
    sprintf(rSql, "insert into t_file_info(local_file_name, mongo_file_name, file_size, user_id,status, remark)"
                  "values('%s', '%s', 0, '%s', '0','uploading')", LocalFile, MongoFile, User);

    if (mysql_query(mysql, rSql)){
        printf("run upload err:%s\n", rSql);
        return -1;
    }
    return 0;
}

/**
 * 更新 上传文件状态
 * @param FileSize
 * @param User
 * @param LocalFile
 * @param MongoFile
 * @return
 */
int CCMysql::UpdateFileInfo(myulong FileSize, const char *User, const char *LocalFile, const char *MongoFile)
{
    //update t_file_info set file_size=1011,status='1',remark='upload sucess'
    //where user_id='yekai' and local_file_name='xxx.11' and mongo_file_name='yyy.11';
    char rSql[512] = { 0 };
    sprintf(rSql, "update t_file_info set file_size=%lld,status='1',remark='upload sucess'"
                  "where user_id='%s' and local_file_name='%s' and mongo_file_name='%s'", FileSize, User, LocalFile, MongoFile);
    if (mysql_query(mysql, rSql)){
        printf("run update err:%s\n", rSql);
        return -1;
    }
    return 0;
}


/**
 * 析构 关闭mysql句柄
 */
CCMysql::~CCMysql()
{
    if (mysql){
        mysql_close(mysql);
    }
}
