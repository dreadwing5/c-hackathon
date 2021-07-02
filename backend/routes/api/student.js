const express = require("express");
const connection = require("../../configs/DBConnection");
const router = express.Router();

router.post("/", (req, res) => {
  console.log(req.body);
  const { usn, name, mailid, password, password2, department } = req.body;

  if (!name || !mailid || !password || !password2 || !usn || !department) {
    res.status(400).json({ text: "Please fill in all fields" });
  }

  //Check Passwords match
  if (password !== password2) {
    res.status(400).json({ text: "Password do not match" });
  }

  connection.query(
    "SELECT usn FROM student WHERE usn = ?",
    [usn],
    (error, data) => {
      if (data.length > 0) {
        res.status(400).json({ text: "USN already exists" });
      } else {
        connection.query(
          "INSERT INTO student SET ? ",
          {
            name: name,
            mailid: mailid,
            password: password,
            usn: usn,
            department: department,
          },
          (error, data) => {
            if (!error) {
              console.log("User Added Successfully");
              res.status(200).json({
                text: "Registration Successful!",
              });
            } else {
              console.error(error);
              res.status(500).json({ text: "Server Error" });
            }
          }
        );
      }
    }
  );
});

router.post("/login", (req, res) => {
  const { usn, password } = req.body;
  if (!usn || !password) {
    res.status(400).json({ text: "Please fill in all fields" });
  }
  connection.query("SELECT * FROM student WHERE usn= ?", [usn], (err, data) => {
    if (err) {
      console.err(err);
      res.status(500).json({ text: "Server Error" });
    }
    if (!data.length) {
      res.status(400).json({ text: "That Usn is not registered" });
    }
    const dbPassword = data[0].password;

    if (!(dbPassword === password)) {
      res.status(400).json({ text: "Password Incorrect!" });
    } else {
      console.log("Login Successful");
      res.status(200).json({ text: "Login Successful!" });
    }
  });
});
module.exports = router;
