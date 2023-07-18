//
// Created by aniki on 5/9/23.
//

#ifndef ONLINESTORE_APIERROR_H
#define ONLINESTORE_APIERROR_H


#include <iostream>
#include <string>
#include <drogon/HttpResponse.h>
class ApiError
{
public:
    int status{};
    std::string massage;
    //drogon::HttpStatusCode code() ;
public:
    ApiError(int status, std::string massage) ;

    //ApiError(const ApiError& other);
//ApiError( ApiError&& other) noexcept{
// this->status = status;
// this->massage = massage;
//}
    static ApiError badRequest(std::string massage);
    static ApiError forbidden(std::string massage);
    static ApiError internal(std::string massage);
    static ApiError unauthorised(std::string massage);
    ~ApiError();
    //{
     //   std::cout << "ApiError DESTRUCTOR "<< this << std::endl;
    //}

};


#endif //ONLINESTORE_APIERROR_H
