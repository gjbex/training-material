SELECT a.city, count(p.last_name)
    FROM addresses AS a INNER JOIN persons AS p
    ON a.address_id = p.address_id
    GROUP BY a.city;
