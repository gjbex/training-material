SELECT p1.first_name, p1.last_name, p2.first_name, p2.last_name
    FROM persons AS p1, friends AS f, persons AS p2
    WHERE p1.person_id = f.person_id AND f.friend_id = p2.person_id;
