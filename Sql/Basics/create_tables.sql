DROP TABLE IF EXISTS addresses;

CREATE TABLE addresses (
    address_id integer not null,
    street varchar(50),
    number integer,
    city varchar(50),
    PRIMARY KEY (address_id)
);


DROP TABLE IF EXISTS persons;

CREATE TABLE persons (
    person_id integer not null,
    last_name varchar(50),
    first_name varchar(50),
    address_id integer,
    PRIMARY KEY (person_id),
    FOREIGN KEY(address_id) REFERENCES addresses(address_id)
);

