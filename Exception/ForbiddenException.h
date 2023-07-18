//
// Created by aniki on 6/27/23.
//

#ifndef ONLINESTORE_FORBIDDENEXCEPTION_H
#define ONLINESTORE_FORBIDDENEXCEPTION_H
#include <drogon/HttpResponse.h>

class ForbiddenException {
private:
    drogon::HttpResponsePtr res;
public:
     explicit ForbiddenException(drogon::HttpResponsePtr res);

     drogon::HttpResponsePtr getRespons();
};


#endif //ONLINESTORE_FORBIDDENEXCEPTION_H
