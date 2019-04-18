var express = require('express');
var bodyParser = require('body-parser');

var app = express();

app.use(bodyParser.json())
app.use(bodyParser.urlencoded({extended: true}));

var fs = require('fs')
var child_process = require('child_process');

app.post('/', function(req, res) {
  var def = req.body.def;
  console.log(def);

  var response = "";

  var child = child_process.execFile('../proboc', ['--streams', '--stage=1'],
    function(err, stdout, stderr) {
      if (err) {
        res.sendStatus(400);
        res.end(stderr);
        throw err;
      }
      res.end(stdout); 
    }
  );

  child.stdin.write(def);
  child.stdin.end();
});

app.listen(8081, function() {
  console.log('Example app listening on port 8081');
});
