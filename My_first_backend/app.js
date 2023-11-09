const express = require("express");
const flux = express();

// partie 1
const titreSinatra = [
  "come danse",
  "All or Nothing at All",
  "Autumn in New York",
  "Blue Moon",
  "New York, New York",
  "Cheek to Cheek",
  "Embraceable You",
  "Come Fly with Me",
  "Come Rain or Come Shine",
  "Fly Me to the Moon",
  "I Get a Kick Out of You",
  "My Way",
  "I've Got the World on a String",
  "My Way",
  "In the Wee Small Hours of the Morning",
  "It Had to Be You",
  "Love and Marriage",
  "Moon River",
  "I've Got You Under My Skin",
  "My Funny Valentine",
  "New York, New York",
];

flux.get("/", (req, res) => {
  const randomSong =
    titreSinatra[Math.floor(Math.random() * titreSinatra.length)];
  res.send(randomSong);
});

// partie 2

flux.get("/birth_date", (req, res) => {
  res.send("December 12, 1915");
});

flux.get("/birth_city", (req, res) => {
  res.send("Hoboken, New Jersey");
});

flux.get("/wives", (req, res) => {
  const femmes = ["Nancy Barbato", "Ava Gardner", "Mia Farrow", "Barbara Marx"];
  res.send(femmes.join(", "));
});

flux.get("/picture", (req, res) => {
  res.redirect(
    "https://en.wikipedia.org/wiki/Frank_Sinatra#/media/File:Frank_Sinatra2,_Pal_Joey.jpg"
  );
});
// partie 3

flux.get("/public", (req, res) => {
  res.send("Everybody can see this page");
});

flux.get("/protected", (req, res) => {
  const authification = req.headers.authorization;
  if (!authification) {
    res.status(401).send("Not authorized");
    return;
  }

  const [username, password] = Buffer.from(
    authification.split(" ")[1],
    "base64"
  )
    .toString()
    .split(":");
  if (username === "admin" && password === "admin") {
    res.send("Welcome, authenticated client");
  } else {
    res.status(401).send("Not authorized");
  }
});

flux.listen(8080, "0.0.0.0", () => {
  console.log("Server is running on port 8080");
});
