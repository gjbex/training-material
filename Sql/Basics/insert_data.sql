INSERT INTO addresses (address_id, street, number, city)
    VALUES (1, "Fifth Avenue", 1343, "New York");
INSERT INTO addresses (address_id, street, number, city)
    VALUES (2, "Downing Street", 10, "London");
INSERT INTO addresses (address_id, street, number, city)
    VALUES (3, "Avenue Louise", 203, "Brussels");
INSERT INTO addresses (address_id, street, number, city)
    VALUES (4, "Oxford Street", 212, "London"); 
INSERT INTO addresses (address_id, street, number, city)
    VALUES (5, "Cantersteen", 43, "Brussels");


INSERT INTO persons (person_id, last_name, first_name, address_id)
    VALUES (1, "Jansen", "Jan", 1);
INSERT INTO persons (person_id, last_name, first_name, address_id)
    VALUES (2, "Fransen", "Frans", 2);
INSERT INTO persons (person_id, last_name, first_name, address_id)
    VALUES (3, "Nellis", "Nele", 2);
INSERT INTO persons (person_id, last_name, first_name, address_id)
    VALUES (4, "Malone", "Molly", 3);
INSERT INTO persons (person_id, last_name, first_name, address_id)
    VALUES (5, "Michaels", "Micky", NULL);
INSERT INTO persons (person_id, last_name, first_name, address_id)
    VALUES (6, "Patricks", "Pat", NULL);
