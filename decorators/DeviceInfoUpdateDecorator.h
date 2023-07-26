//
// Created by aniki on 7/20/23.
//

#ifndef ONLINESTORE_DEVICEINFOUPDATEDECORATOR_H
#define ONLINESTORE_DEVICEINFOUPDATEDECORATOR_H

#include <iostream>
#include <string>
#include "../entity/DeviceInfo.h"
#include <optional>

class DeviceInfoUpdateDecorator{

private:
    class Component {
    public:

        virtual ~Component() {}

        virtual std::string Operation(bool fl) const = 0;
        // virtual std::string Operation() const = 0;
    };


    class DeviceIdDecorator : public Component {
    private:
        std::optional<int> deviceID;
    public:
        DeviceIdDecorator(std::optional<int> deviceID) {
            this->deviceID = deviceID;
        };

        std::string Operation(bool flg) const override {

            if (this->deviceID !=std::nullopt) {
                if (flg) return ", device_id = '" + std::to_string( deviceID.value()) + "'";
                else {
                    flg = true;
                    return "device_id = '" + std::to_string( deviceID.value()) + "'";
                }
            }
            return "";
        }
    };


    class Decorator : public Component {
    protected:
        Component *component_;

    public:
        Decorator(Component *component) : component_(component) {
        }


        std::string Operation(bool flg) const override {
            return this->component_->Operation(flg);
        }
    };


    class TitleDecorator : public Decorator {

    private:
        std::optional<std::string> title;
    public:

        TitleDecorator(Component *component, std::optional<std::string> title) : Decorator(component) {
            this->title = title;
        }

        std::string Operation(bool flg) const override {
            if (title !=std::nullopt) {

                if (flg) return ", title = '" + (title.value()) + "'" + Decorator::Operation(flg) + "";

                else {
                    flg = true;
                    return "title = '" + (title.value()) + "'" + Decorator::Operation(flg) + "";
                }
            }
            return "" + Decorator::Operation(flg) + "";
        }
    };


    class DescriptionDecorator : public Decorator {

    private:
        std::optional<std::string> description;
    public:

        DescriptionDecorator(Component *component, std::optional<std::string> description) : Decorator(component) {
            this->description = description;
        }

        std::string Operation(bool flg) const override {
            if (description !=std::nullopt) {

                if (flg) return ", description = '" + (description.value()) + "'" + Decorator::Operation(flg) + "";

                else {
                    flg = true;
                    return "description = '" + (description.value()) + "'" + Decorator::Operation(flg) + "";
                }
            }
            return "" + Decorator::Operation(flg) + "";
        };
    };




    static std::string ClientCode(Component *component, int id, bool flg = false) {
        // ...
        return "UPDATE device_info SET " + component->Operation(flg) + " WHERE id = " + std::to_string(id);
        // ...
    }


public:

    static std::string UpdateDevice(DeviceInfo::UpdateDTO const &deviceInfo) {

        Component *deviceId = new DeviceIdDecorator(deviceInfo.deviceID);
        Component *title = new TitleDecorator(deviceId, deviceInfo.title );
        Component *description = new DescriptionDecorator(title, deviceInfo.description );

        return ClientCode(description, deviceInfo.id);

    };
};




#endif //ONLINESTORE_DEVICEINFOUPDATEDECORATOR_H
