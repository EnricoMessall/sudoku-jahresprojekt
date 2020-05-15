CREATE TABLE IF NOT EXISTS users(
  ID INTEGER PRIMARY KEY AUTOINCREMENT,
  Nickname VARCHAR(16) NOT NULL,
  UNIQUE (Nickname)
);
-- NOTE: For the constraint to work properly, set: PRAGMA foreign_keys = ON
-- see https://stackoverflow.com/a/52226336 for more information
-- NOTE: ON CONFLICT REPLACE deletes the row and adds a new row, thus incrementing the ID of the userScore row.
CREATE TABLE IF NOT EXISTS userScore(
  ID INTEGER PRIMARY KEY AUTOINCREMENT,
  UserID INTEGER NOT NULL,
  Time INTEGER NOT NULL,
  Difficulty INTEGER NOT NULL,
  UNIQUE (UserID, Difficulty) ON CONFLICT REPLACE CONSTRAINT users_userScore FOREIGN KEY(UserID) REFERENCES users(ID) ON UPDATE CASCADE ON DELETE CASCADE
);