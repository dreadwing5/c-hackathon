const express = require("express");
const app = express();

const connection = require("./configs/DBConnection");

app.use(express.json());
app.use(
  express.urlencoded({
    extended: true,
  })
);

app.get("/", (req, res) => {
  res.status(200).json({ text: "Hello From The Server!" });
});

app.get("/uploads/:id", function (req, res) {
  const file = `${__dirname}/uploads/${req.params.id}`;
  res.download(file); // Set disposition and send it.
});

// //Define Routes
app.use("/api/faculty", require("./routes/api/faculty"));
app.use("/api/student", require("./routes/api/student"));

app.listen("3000", () => {
  console.log("Server Started ... http://localhost:3000");
});
