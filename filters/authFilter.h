/**
 *
 *  authFilter.h
 *
 */

#ifndef ONLINESTORE_AUTHFILTER_H
#define ONLINESTORE_AUTHFILTER_H

#include <drogon/HttpFilter.h>
#include "../utils/jwtService.h"
#include "../Middleware/ErrorHandlingMiddleware.h"

using namespace drogon;


class authFilter : public HttpFilter<authFilter>
{
  public:
    authFilter() {}
    void doFilter(const HttpRequestPtr &req,
                  FilterCallback &&fcb,
                  FilterChainCallback &&fccb) override;
};

#endif //ONLINESTORE_AUTHFILTER_H