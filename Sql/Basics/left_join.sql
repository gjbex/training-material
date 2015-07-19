SELECT
    p.last_name AS "Last name",
    p.first_name AS "First name",
    a.number AS "Number",
    a.street AS "Street name",
    a.city AS "City"
FROM persons AS p LEFT JOIN addresses AS a
    ON p.address_id = a.address_id;
