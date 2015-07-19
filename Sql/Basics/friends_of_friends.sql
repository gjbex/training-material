WITH RECURSIVE
    all_friends(person_id) AS (
        SELECT person_id FROM persons WHERE last_name = 'Fransen'
        UNION
        SELECT friends.friend_id FROM friends, all_friends
            WHERE friends.person_id = all_friends.person_id)
SELECT persons.person_id, persons.first_name, persons.last_name
    FROM persons INNER JOIN all_friends
    ON persons.person_id = all_friends.person_id;
