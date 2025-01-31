CREATE TABLE users(
    id integer primary key autoincrement,
    first_name text not null,
    last_name text not null,
    age integer not null
);

CREATE TABLE rooms(
    id integer primary key autoincrement,
    seats_count integer not null
);
