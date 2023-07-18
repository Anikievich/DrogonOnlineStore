//
// Created by aniki on 6/27/23.
//

#include "imgUpload.h"



imgUpload::imgUpload(const HttpRequestPtr& req) {
   MultiPartParser fileUpload;
    // Uploading multiple files at once is not allowed
    fileUpload.parse(req);
  //  //|| fileUpload.getFiles().size() != 1
    LOG_ERROR<<"img";
   //if (fileUpload.parse(req) != 0 ) {

   //   throw ForbiddenException (ErrorHandlingMiddleware::errorReturn(ApiError::forbidden("Must be one file")));

 // }
    LOG_ERROR<<"img1";
    auto &file = fileUpload.getFiles()[0];
    auto a = fileUpload.getFilesMap();
auto &b = a.at("12");
    auto v = a;
    LOG_ERROR<<"img2";
    //fileExt = file.getFileExtension();
    LOG_ERROR<<"img3";
    //if (fileExt == "gif") {

     //   throw ForbiddenException (ErrorHandlingMiddleware::errorReturn(ApiError::forbidden("GIF is not allowed")));

    //}
    // Checks the file extension to see if the file is an image
   // if (file.getFileType() != FileType::FT_IMAGE) {

   //     throw ForbiddenException (ErrorHandlingMiddleware::errorReturn(ApiError::forbidden("Must be an image")));

  //  }
    LOG_ERROR<<"img4";
    // Format a query for uploading a file to the database
    //md5 = file.getMd5();
    fileUuid = drogon::utils::getUuid();
    file.saveAs(fileUuid);
    //b.saveAs(fileUuid);
    LOG_ERROR<<"img5";
    ret["status"] = 200;
    ret["md5"] = md5;
    ret["message"] = "Successful upload";
    ret["id"] = fileUuid;

}

std::string imgUpload::getMd5() {
    return md5;
}

std::string imgUpload::getFileUuid() {
    return fileUuid;
}

std::string_view imgUpload::getFileExt() {
    return fileExt;
}

Json::Value imgUpload::getJsonResp() {
    return ret;
}
