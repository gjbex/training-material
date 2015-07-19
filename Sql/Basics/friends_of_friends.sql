WITH RECURSIVE
    all_friends(person_id) AS (
        VALUES(2)
        UNION
        SELECT friends.friend_id FROM friends, all_friends
            WHERE friends.person_id = all_friends.person_id)
SELECT persons.person_id, persons.first_name, persons.last_name
    FROM persons INNER JOIN all_friends
    ON persons.person_id = all_friends.person_id;
