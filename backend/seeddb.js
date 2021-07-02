const mysql = require("mysql2");

let seeddb = async () => {
  let db = mysql.createConnection({
    host: "localhost",
    user: "root",
    password: "",
  });

  let promise = new Promise((resolve, reject) => {
    let sql = "Create Database cpp_db";
    db.query(sql, (err, result) => {
      if (err) throw err;
      console.log("DataBase Created Successfully");
      resolve("done");
    });
  });
  let res = await promise;

  promise = new Promise((resolve, reject) => {
    let db = mysql.createConnection({
      host: "localhost",
      user: "root",
      password: "",
      database: "cpp_db",
    });
    resolve(db);
  });
  db = await promise;

  sql =
    "Create Table faculty(faculty_id varchar(255) NOT NULL PRIMARY KEY, password varchar(255), name varchar(255), department varchar(255), mailId varchar(255), assignment varchar(255), upload_date Date)";

  db.query(sql, (err, result) => {
    if (err) throw err;
    console.log("Faculty Table created successfully");
  });

  sql =
    "Create Table student(usn varchar(255) NOT NULL PRIMARY KEY, password varchar(255), name varchar(255), department varchar(255), mailId varchar(255), assignment varchar(255), submission_date Date)";
  db.query(sql, (err, result) => {
    if (err) throw err;
    console.log("Student Table created successfully");
  });
};

seeddb();
