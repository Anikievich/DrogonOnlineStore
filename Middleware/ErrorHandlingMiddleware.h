//
// Created by aniki on 5/9/23.
//

#ifndef ONLINESTORE_ERRORHANDLINGMIDDLEWARE_H
#define ONLINESTORE_ERRORHANDLINGMIDDLEWARE_H

#include <drogon/HttpResponse.h>
#include "../error/ApiError.h"
using namespace drogon;

class ErrorHandlingMiddleware {
private:

public:
     ErrorHandlingMiddleware() {
        std::cout << "MIDDLEWARE DESTRUCTOR" << std::endl;

    }

    static auto errorReturn(const ApiError &err)->HttpResponsePtr ;
};


#endif //ONLINESTORE_ERRORHANDLINGMIDDLEWARE_H
