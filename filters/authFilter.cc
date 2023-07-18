/**
 *
 *  authFilter.cc
 *
 */

#include "authFilter.h"
#include <trantor/utils/Logger.h>
using namespace drogon;

void authFilter::doFilter(const HttpRequestPtr &req,
                         FilterCallback &&fcb,
                         FilterChainCallback &&fccb)
{
    //Edit your logic here
    auto userId = jwtService::getCurrentUserIdFromRequest(req);
   // LOG_DEBUG<<userId.value();
    //LOG_DEBUG<<std::chrono::system_clock::now();
    auto const& json = req->getJsonObject();
    LOG_DEBUG<<"userID.has_value : "<<userId.id.has_value();
    LOG_DEBUG<<"userID : " << userId.id.value();
    //Edit your logic here
    if (userId.id.has_value())
    {
        //Passed
        fccb();
        return;
    }
    //Check failed
    fcb(ErrorHandlingMiddleware::errorReturn(ApiError::unauthorised("Not authorized")));

}
