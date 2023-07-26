#pragma once

#include <drogon/HttpController.h>
#include "../entity/DeviceInfo.h"
#include "../database/DataBaseHelper.h"
#include "../Middleware/ErrorHandlingMiddleware.h"
#include "../decorators/DeviceInfoUpdateDecorator.h"

using namespace drogon;

namespace api
{
class deviceInfoController : public drogon::HttpController<deviceInfoController>
{
public:
    METHOD_LIST_BEGIN
        // use METHOD_ADD to add your custom processing function here;
        // METHOD_ADD(deviceController::get, "/{2}/{1}", Get); // path is /deviceController/{arg2}/{arg1}
        // METHOD_ADD(deviceController::your_method_name, "/{1}/{2}/list", Get); // path is /deviceController/{arg1}/{arg2}/list
        // ADD_METHOD_TO(deviceController::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list
        METHOD_ADD(deviceInfoController::create, "/", Post, "adminRoleFilter");
        METHOD_ADD(deviceInfoController::getAll, "/", Get);
        METHOD_ADD(deviceInfoController::getOne, "/id={1}", Get);
        METHOD_ADD(deviceInfoController::remove, "/id={1}", Delete, "adminRoleFilter");
        METHOD_ADD(deviceInfoController::update, "/", Put, "adminRoleFilter");
    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;
    void create(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, DeviceInfo::CreateDTO &&pNewDevice);
    void getAll(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, DeviceInfo::GetAllDTO &&pNewDevice);
    void getOne(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int id);
    void remove(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int id);
    void update(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, DeviceInfo::UpdateDTO &&pNewDevice);
};
}
