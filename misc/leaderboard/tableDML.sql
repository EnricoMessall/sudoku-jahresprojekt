INSERT INTO users (ID, Nickname)
VALUES
  (NULL, "haxor");
INSERT INTO userScore (ID, UserID, Time, Difficulty)
VALUES
  (
    NULL,
    (
      SELECT
        ID
      FROM users
      WHERE
        Nickname = "haxor"
    ),
    1589549576,
    0
  );
SELECT
  Nickname,
  Time,
  Difficulty
FROM userScore
INNER JOIN users ON users.ID = userScore.UserID
WHERE
  Difficulty = 1
ORDER BY
  Time ASC;