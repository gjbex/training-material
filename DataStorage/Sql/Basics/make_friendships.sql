DROP TABLE IF EXISTS friends;

CREATE TABLE friends (
    person_id integer,
    friend_id integer,
    FOREIGN KEY(person_id) REFERENCES persons(person_id),
    FOREIGN KEY(friend_id) REFERENCES persons(person_id),
    UNIQUE(person_id, friend_id)
);

INSERT INTO friends (person_id, friend_id) VALUES (2, 3);
INSERT INTO friends (person_id, friend_id) VALUES (2, 4);
INSERT INTO friends (person_id, friend_id) VALUES (3, 6);
INSERT INTO friends (person_id, friend_id) VALUES (1, 5);
