const express = require("express");
const app = express();

app.use(express.json());
app.use(
  express.urlencoded({
    extended: true,
  })
);

app.get("/", (req, res) => {
  res.status(200).json("OK");
});

app.listen("3000", () => {
  console.log("Server Started ... http://localhost:3000");
});
