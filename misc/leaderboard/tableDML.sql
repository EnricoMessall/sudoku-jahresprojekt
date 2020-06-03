INSERT INTO users (ID, Nickname)
VALUES (NULL, "haxor");
INSERT INTO userScore (ID, UserID, Time, Difficulty, Date)
VALUES (
    NULL,
    (
      SELECT ID
      FROM users
      WHERE Nickname = "haxor"
    ),
    1589549576,
    0,
    strftime('%d-%m-%Y %H:%M:%S', 'now')
  );
SELECT Nickname,
  Time,
  Difficulty,
  Date
FROM userScore
  INNER JOIN users ON users.ID = userScore.UserID -- WHERE Difficulty = 0
ORDER BY Time ASC;