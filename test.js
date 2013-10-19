var assert = require('assert');
var fswait = require('./build/Release/fswait');

fswait.check("./", function(result) {
  console.log('File changed: ', result);
});
