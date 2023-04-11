/* eslint-disable prettier/prettier */
import io from 'socket.io-client';

// const SOCKET_URL = 'http://192.168.1.54:5000';

class WSService {
   initializeSocket = async(SOCKET_URL) => {
      try {
         this.connection = false;

         this.socket = io(SOCKET_URL, {
            transports:['websocket'],
         });

         // console.log('initializing socket', this.socket);

      } catch (error) {
         console.log('cannot initialize socket', error);
      }
   };

   emit(event, data = {}){
      this.socket.emit(event, data);
   }

   on(event, cb){
      this.socket.on(event, cb);
   }

   removeListener(listenerName){
      this.socket.removeListener(listenerName);
   }
}

const socketServices = new WSService();

export default socketServices;
