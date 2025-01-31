# How to Use

## Install sqlite3 on Linux

Use this [link](https://www.tutorialspoint.com/sqlite/sqlite_installation.htm#install-sqlite-on-linux:~:text=Install%20SQLite%20on%20Linux,verify%20as%20explained%20above.).

## Create Database

```shell
sqlite3 db.sqlite < tables.sql
```

## Compile

```shell
g++ main.cpp -std=c++20 -lsqlite3
```

## Run

```shell
./a.out
```

You can either use the `sqlite3` shell to check the database, or use `DataGrip`.
