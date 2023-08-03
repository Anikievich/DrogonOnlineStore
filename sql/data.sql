CREATE TABLE user_ (id BIGSERIAL NOT NULL PRIMARY KEY,
                    email VARCHAR(50) NOT NULL UNIQUE,
                    password TEXT NOT NULL,
                    role VARCHAR(50) DEFAULT 'USER' NOT NULL
                   );
CREATE TABLE basket (id BIGSERIAL NOT NULL PRIMARY KEY,
                     user_id BIGINT REFERENCES user_ (id) UNIQUE ON DELETE CASCADE ON UPDATE CASCADE NOT NULL
                    );
CREATE TABLE type (id BIGSERIAL NOT NULL PRIMARY KEY,
                   name VARCHAR(100) NOT NULL UNIQUE
                  );
CREATE TABLE brand (id BIGSERIAL NOT NULL PRIMARY KEY,
                    name VARCHAR(100) NOT NULL UNIQUE
                   );
CREATE TABLE type_brand (type_id BIGINT REFERENCES brand(id) ON DELETE CASCADE ON UPDATE CASCADE,
                         brand_id BIGINT REFERENCES type(id) ON DELETE CASCADE ON UPDATE CASCADE,
                         CONSTRAINT type_brand_pkey PRIMARY KEY (type_id, brand_id)
                        );
CREATE TABLE device( id BIGSERIAL NOT NULL PRIMARY KEY,
                     name VARCHAR(50) NOT NULL UNIQUE,
                     price NUMERIC(19, 2) NOT NULL,
                     rating INTEGER DEFAULT 0,
                     img TEXT NOT NULL,
                     type BIGINT REFERENCES type (id) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL,
                     brand BIGINT REFERENCES brand (id) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL
                   );
CREATE TABLE basket_device(id BIGSERIAL NOT NULL PRIMARY KEY,
                           device_id BIGINT REFERENCES device (id) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL UNIQUE,
                           basket_id BIGINT REFERENCES basket (id) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL
                          );
CREATE TABLE rating (id BIGSERIAL PRIMARY KEY NOT NULL,
                     user_id BIGINT REFERENCES user_ (id) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL,
                     device_id BIGINT REFERENCES device (id) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL,
                     rate INTEGER NOT NULL
                    );
CREATE TABLE device_info (id BIGSERIAL NOT NULL PRIMARY KEY,
                          device_id BIGINT REFERENCES device (id) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL,
                          title VARCHAR(100) NOT NULL,
                          description TEXT NOT NULL);