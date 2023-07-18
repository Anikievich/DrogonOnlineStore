/**
 *
 *  adminRoleFilter.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
#include "../utils/jwtService.h"
#include "../Middleware/ErrorHandlingMiddleware.h"

using namespace drogon;


class adminRoleFilter : public HttpFilter<adminRoleFilter>
{
  public:
    adminRoleFilter() {}
    void doFilter(const HttpRequestPtr &req,
                  FilterCallback &&fcb,
                  FilterChainCallback &&fccb) override;
};

