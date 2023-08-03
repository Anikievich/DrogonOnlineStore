//
// Created by aniki on 7/15/23.
//

#ifndef ONLINESTORE_UPDATEDECORATORS_H
#define ONLINESTORE_UPDATEDECORATORS_H
#include <iostream>
#include <string>
#include "../entity/User.h"
#include <optional>
#include <bcrypt/BCrypt.hpp>

class UpdateDecorator {

private:
    class Component {
    public:

        virtual ~Component() {}

        virtual std::string Operation(bool fl) const = 0;
        // virtual std::string Operation() const = 0;
    };


    class ConcreteComponent : public Component {
    private:
        std::optional<std::string> email;
    public:
        ConcreteComponent(std::optional<std::string> email) {
            this->email = email;
        };

        std::string Operation(bool flg) const override {

            if (this->email !=std::nullopt) {
                if (flg) return ", email = '" + email.value() + "'";
                else {
                    flg = true;
                    return "email = '" + email.value() + "'";
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


    class ConcreteDecoratorA : public Decorator {

    private:
        std::optional<std::string> password;
    public:

        ConcreteDecoratorA(Component *component, std::optional<std::string> password) : Decorator(component) {
            this->password = password;
        }

        std::string Operation(bool flg) const override {
            if (password !=std::nullopt) {
                auto hashPassword = BCrypt::generateHash(password.value());
                if (flg) return ", password = '" + hashPassword + "'" + Decorator::Operation(flg) + "";

                else {
                    flg = true;
                    return "password = '" + hashPassword + "'" + Decorator::Operation(flg) + "";
                }
            }
            return "" + Decorator::Operation(flg) + "";
        }
    };


    static std::string ClientCode(Component *component, int id, bool flg = false) {
        // ...
        return "UPDATE user_ SET " + component->Operation(flg) + " WHERE id = " + std::to_string(id);
        // ...
    }


public:

    static std::string UpdateUser(User::UpdateDTO const &user_) {

        Component *emailDec = new ConcreteComponent(user_.email);
        Component *decorator1 = new ConcreteDecoratorA(emailDec, user_.password);

        auto str = ClientCode(decorator1, user_.id);

        delete emailDec;
        delete decorator1;
        return str;

    };
};

#endif //ONLINESTORE_UPDATEDECORATORS_H
