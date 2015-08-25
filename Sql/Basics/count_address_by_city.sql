SELECT city, count(*)
    FROM addresses
    GROUP BY city
    ORDER BY count(*) DESC;
