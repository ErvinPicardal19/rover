var express = require('express');
var socket = require('socket.io');

const port = process.env.PORT || 5000;
const app = express();
app.use(express.static('public'));

app.get('/', (req, res) => {
    res.send("HTTPS WORKING!");
});

const server = app.listen(port, () => {
   console.log("====================================")
      console.log('\x1b[42m\x1b[30m%s\x1b[0m', `Listening on PORT ${port}...`);
      console.log("====================================")
});

const io = socket(server);

let roverId = null;

io.on('connect', (socket) => {
   console.log(`user ${socket.id} connected`);

   socket.on('rover_found', (id) => {
      console.log("RoverID: ", socket.id);
      roverId = socket.id;
   });

   socket.on('go_up',  () => {
      console.log("Going Up!");
      io.to(roverId).emit('go_up', {});
   });

   socket.on('go_left',  () => {
      console.log("Going Left!");
      io.to(roverId).emit('go_left', {});
   });

   socket.on('go_right',  () => {
      console.log("Going Right!");
      io.to(roverId).emit('go_right', {});
   });

   socket.on('go_down',  () => {
      console.log("Going Down!");
      io.to(roverId).emit('go_down', {});
   });

   socket.on('stop',  () => {
      console.log("Stopped!");
      io.to(roverId).emit('stop', {});
   });

   socket.on('claw_change', (val) => {
      console.log("New Claw Value: ", val);
      io.to(roverId).emit('claw_change', val);
   });

   socket.on('speed_change', (val) => {
      console.log("New Speed Value: ", val);
      io.to(roverId).emit('speed_change', val);
   });

   socket.on('sonar', (val) => {
      console.log("Sonar Mode: ", val);
      io.to(roverId).emit('sonar', val);
   });

   socket.on('disconnect',  () => {
       console.log(`user ${socket.id} disconnected`);
   });
});

console.log("Changed!");

