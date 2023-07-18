//
// Created by aniki on 7/16/23.
//

#ifndef ONLINESTORE_DEVICEUPDATEDECORATOR_H
#define ONLINESTORE_DEVICEUPDATEDECORATOR_H

#include <iostream>
#include <string>
#include "../entity/Device.h"
#include <optional>

class DeviceUpdateDecorator{

private:
class Component {
public:

    virtual ~Component() {}

    virtual std::string Operation(bool fl) const = 0;
    // virtual std::string Operation() const = 0;
};


class BrandDecorator : public Component {
private:
    std::optional<int> brand;
public:
    BrandDecorator(std::optional<int> brand) {
        this->brand = brand;
    };

    std::string Operation(bool flg) const override {

        if (this->brand !=std::nullopt) {
            if (flg) return ", brand = '" + std::to_string( brand.value()) + "'";
            else {
                flg = true;
                return "brand = '" + std::to_string( brand.value()) + "'";
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

    /**
     * Декоратор делегирует всю работу обёрнутому компоненту.
     */
    std::string Operation(bool flg) const override {
        return this->component_->Operation(flg);
    }
};

/**
 * Конкретные Декораторы вызывают обёрнутый объект и изменяют его результат
 * некоторым образом.
 */
    class TypeDecorator : public Decorator {

    private:
      std::optional<int> type;
    public:

    TypeDecorator(Component *component, std::optional<int> type) : Decorator(component) {
        this->type = type;
    }

    std::string Operation(bool flg) const override {
        if (type !=std::nullopt) {

                if (flg) return ", type = '" + std::to_string(type.value()) + "'" + Decorator::Operation(flg) + "";

                else {
                    flg = true;
                    return "type = '" + std::to_string(type.value()) + "'" + Decorator::Operation(flg) + "";
                }
                }
            return "" + Decorator::Operation(flg) + "";
        }
    };


    class ImgDecorator : public Decorator {

    private:
         std::optional<std::string> img;
    public:

        ImgDecorator(Component *component, std::optional<std::string> img) : Decorator(component) {
            this->img = img;
        }

        std::string Operation(bool flg) const override {
            if (img !=std::nullopt) {

                if (flg) return ", img = '" + (img.value()) + "'" + Decorator::Operation(flg) + "";

                else {
                    flg = true;
                    return "img = '" + (img.value()) + "'" + Decorator::Operation(flg) + "";
                }
            }
            return "" + Decorator::Operation(flg) + "";
        };
    };


    class PriceDecorator : public Decorator {

    private:
        std::optional<float> price;
    public:

        PriceDecorator(Component *component,  std::optional<float> price) : Decorator(component) {
            this->price = price;
        }

        std::string Operation(bool flg) const override {
            if (price !=std::nullopt) {

                if (flg) return ", price = '" + std::to_string(price.value()) + "'" + Decorator::Operation(flg) + "";

                else {
                    flg = true;
                    return "price = '" + std::to_string(price.value()) + "'" + Decorator::Operation(flg) + "";
                }
            }
            return "" + Decorator::Operation(flg) + "";
        };
    };

    class NameDecorator : public Decorator {

    private:
        std::optional<std::string> name;
    public:

        NameDecorator(Component *component,  std::optional<std::string> name) : Decorator(component) {
            this->name = name;
        }

        std::string Operation(bool flg) const override {
            if (name !=std::nullopt) {

                if (flg) return ", name = '" + (name.value()) + "'" + Decorator::Operation(flg) + "";

                else {
                    flg = true;
                    return "name = '" + (name.value()) + "'" + Decorator::Operation(flg) + "";
                }
            }
            return "" + Decorator::Operation(flg) + "";
        };
    };

static std::string ClientCode(Component *component, int id, bool flg = false) {
    // ...
    return "UPDATE device SET " + component->Operation(flg) + " WHERE id = " + std::to_string(id);
    // ...
}


    public:

    static std::string UpdateDevice(Device::UpdateDTO const &device) {

      Component *brand = new BrandDecorator(device.brandID);
      Component *type = new TypeDecorator(brand, device.typeID );
      Component *img = new ImgDecorator(type, device.image );
      Component *price = new PriceDecorator(img, device.price );
      Component *name = new NameDecorator(price, device.name );

      return ClientCode(name, device.id);

    };
};
#endif //ONLINESTORE_DEVICEUPDATEDECORATOR_H
