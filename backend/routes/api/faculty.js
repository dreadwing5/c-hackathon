const express = require("express");
const connection = require("../../configs/DBConnection");
const router = express.Router();
const fs = require("fs");
const { v4: uuidv4 } = require("uuid");
const path = require("path");
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

router.post("/upload", (req, res) => {
  let { filePath, facultyId } = req.body;
  const fileExt = "" + path.extname(filePath);
  const fileName = uuidv4();
  const destPath = `./uploads/${fileName}.${fileExt}`;
  facultyId = `"${facultyId}"`;

  fs.copyFile(`${filePath}`, destPath, (err) => {
    if (err) {
      res.status(500).json({ text: "File couldn't be uploaded" });
    } else {
      const value = `"${destPath}"`;
      const sql = `Update faculty Set assignment = ${value} Where faculty_id =${facultyId}`;
      console.log(sql);

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

module.exports = router;
