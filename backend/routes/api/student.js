const express = require("express");
const connection = require("../../configs/DBConnection");
const router = express.Router();
const fs = require("fs");
const { v4: uuidv4 } = require("uuid");
const path = require("path");

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

router.post("/upload", (req, res) => {
  let { filePath, usn } = req.body;
  const fileExt = "" + path.extname(filePath);
  const fileName = uuidv4();
  const destPath = `./uploads/${fileName}.${fileExt}`;
  usn = `"${usn}"`;

  fs.copyFile(`${filePath}`, destPath, (err) => {
    if (err) {
      res.status(500).json({ text: "File couldn't be uploaded" });
    } else {
      const value = `"${destPath}"`;
      const sql = `Update student Set assignment = ${value} Where usn =${usn}`;

      connection.query(sql, (err, result) => {
        if (err) {
          console.error(err);
          res.status(500).json({ text: "File couldn't be uploaded" });
        }
        res.status(200).json({ text: "Upload Successful!" });

        //Save to database
      });
    }
  });
});

router.get("/score/:usn", (req, res) => {
  usn = `"${req.params.usn}"`;

  const sql = `Select score from student where usn=${usn}`;

  connection.query(sql, (err, data) => {
    if (err) {
      console.log(err);
    } else {
      res.status(200).send(data[0].score);
    }
  });
});
module.exports = router;
