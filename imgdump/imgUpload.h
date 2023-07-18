//
// Created by aniki on 6/27/23.
//

#ifndef ONLINESTORE_IMGUPLOAD_H
#define ONLINESTORE_IMGUPLOAD_H
#include <drogon/HttpController.h>
#include "drogon/HttpRequest.h"
//#include "Middleware/ErrorHandlingMiddleware.h"
//#include "Exception/ForbiddenException.h"


using namespace drogon;

class imgUpload {
private:
    std::string md5;
    std::string fileUuid;
    std::string_view fileExt;
    Json::Value ret;
public:
    explicit imgUpload(const HttpRequestPtr& req);
    std::string getMd5();
    std::string getFileUuid();
    std::string_view getFileExt();
    Json::Value getJsonResp();

};


#endif //ONLINESTORE_IMGUPLOAD_H
