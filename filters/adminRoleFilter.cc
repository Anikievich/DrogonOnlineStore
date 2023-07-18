/**
 *
 *  adminRoleFilter.cc
 *
 */

#include "adminRoleFilter.h"

using namespace drogon;

void adminRoleFilter::doFilter(const HttpRequestPtr &req,
                         FilterCallback &&fcb,
                         FilterChainCallback &&fccb)
{
    auto userRole = jwtService::getCurrentUserRoleFromRequest(req);
    // LOG_DEBUG<<userId.value();
    //LOG_DEBUG<<std::chrono::system_clock::now();
    LOG_DEBUG<<"userID.has_value :"<<userRole.id.has_value();    //Edit your logic here
    if (userRole.id.has_value()&&userRole.role == "ADMIN")
    {
        //Passed
        fccb();
        return;
    }
    //Check failed
    else if (!userRole.id.has_value()) {
        fcb(ErrorHandlingMiddleware::errorReturn(ApiError::unauthorised("Not authorized")));
    }else if (userRole.role != "ADMIN") {
        fcb(ErrorHandlingMiddleware::errorReturn(ApiError::forbidden("No access")));
    }
    //Check failed
    auto res = drogon::HttpResponse::newHttpResponse();
    res->setStatusCode(k500InternalServerError);
    fcb(res);
}
