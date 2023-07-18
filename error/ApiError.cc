//
// Created by aniki on 5/9/23.
//

#include "ApiError.h"

//#include <utility>


ApiError::ApiError( int status, std::string massage) {
     std::cout << "ApiError CONSTRUCTOR " << this << std::endl;
    this->status = status;
    this->massage = std::move(massage);
}


//ApiError( ApiError&& other) noexcept{
// this->status = status;
// this->massage = massage;
//}
ApiError::~ApiError()
{
 std::cout << "ApiError DESTRUCTOR "<< this << std::endl;
}
    ApiError ApiError::unauthorised(std::string massage) {
        return {401, std::move(massage)};
    }
    ApiError ApiError::badRequest(std::string massage) {
        return {404, std::move(massage)};
    }

    ApiError ApiError::forbidden(std::string massage) {
        return {403, std::move(massage)};
    };
    ApiError ApiError::internal(std::string massage) {
        return {500, std::move(massage)};
    }

