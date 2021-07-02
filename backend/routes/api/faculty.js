const express = require("express");
const connection = require("../../configs/DBConnection");
const router = express.Router();
router.post("/", (req, res) => {
  console.log(req.body);
  let { facultyId, name, mailId, password, password2, department } = req.body;

  if (
    !name ||
    !mailId ||
    !password ||
    !password2 ||
    !facultyId ||
    !department
  ) {
    res.status(400).json({ text: "Please fill in all fields" });
  }

  //Check Passwords match
  if (password !== password2) {
    res.status(400).json({ text: "Password do not match" });
  }

  connection.query(
    "SELECT faculty_id FROM faculty WHERE faculty_id = ?",
    [facultyId],
    (error, data) => {
      if (data.length > 0) {
        res.status(400).json({ text: `${data.name} already exists` });
      } else {
        connection.query(
          "INSERT INTO faculty SET ? ",
          {
            name,
            password,
            department,
            mailid: mailId,
            faculty_id: facultyId,
          },
          (error, data) => {
            if (!error) {
              console.log("User Added Successfully");
              res.status(200).json({ text: "OK" });
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
  const { facultyId, password } = req.body;
  if (!facultyId || !password) {
    res.status(400).json({ text: "Please fill in all fields" });
  }
  connection.query(
    "SELECT * FROM faculty WHERE faculty_id= ?",
    [facultyId],
    (err, data) => {
      if (err) {
        console.err(err);
        res.status(500).json({ text: "Server Error" });
      }
      if (!data.length) {
        res.status(400).json({ text: "That Id is not registered" });
      }
      const dbPassword = data[0].password;

      if (!(dbPassword === password)) {
        res.status(400).json({ text: "Password Incorrect!" });
      } else {
        console.log("Login Successful");
        res.status(200).json({ text: "Login Successful!" });
      }
    }
  );
});
module.exports = router;
