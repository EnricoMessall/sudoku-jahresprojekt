INSERT INTO users
VALUES
  (NULL, "haxor");
INSERT INTO userScore
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
    99,
    0
  );