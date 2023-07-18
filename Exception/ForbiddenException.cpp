//
// Created by aniki on 6/27/23.
//

#include "ForbiddenException.h"
#include <utility>

    ForbiddenException::ForbiddenException(drogon::HttpResponsePtr res) {
        this->res = std::move(res);
    }

    drogon::HttpResponsePtr ForbiddenException::getRespons() {
        return res;
    }
