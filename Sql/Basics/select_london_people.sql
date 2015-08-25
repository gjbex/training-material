SELECT
    p.first_name AS "First name",
    p.last_name AS "Last name",
    a.city AS "City"
FROM persons AS p INNER JOIN addresses AS a
    ON p.address_id = a.address_id
WHERE a.city = "London";
