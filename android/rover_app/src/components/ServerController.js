/* eslint-disable react-native/no-inline-styles */
/* eslint-disable no-shadow */
/* eslint-disable prettier/prettier */
import React, {useEffect, useState} from 'react';
import {View, StyleSheet, Modal, TextInput, Text, TouchableOpacity} from 'react-native';
import {Slider} from '@miblanchard/react-native-slider';

import socketServices from '../utils/socketServices';

const ServerController = (props) => {
  const {isConnected, setIsConnected} = props;

   const [ip, setIp] = useState('');
   const [showWarning, setShowWarning] = useState(false);
   const [isValid, setIsValid] = useState(false);
  //  const [isConnected, setIsConnected] = useState(false);
   const [value, setValue] = useState(0);
   const [lastVal, setLastVal] = useState(0);

   const validateIP = (value) => {
      var re = /^((25[0-5]|(2[0-4]|1[0-9]|[1-9]|)[0-9])(\.(?!$)|$)){4}$/;
      if (!re.test(value)){
         setIsValid(false);
      } else {
         setIsValid(true);
      }
    };

    const onChangHandler = (newVal) => {
        setValue(newVal);
    };

    const setSpeedHandler = (val) => {
      socketServices.emit('speed_change', value);
    };

   const handleServerConnect = async() => {
      const SOCKET_URL = `http://${ip}:5000`;
      console.log(`SOCKET_URL: ${SOCKET_URL}`);
      // dispatch(connectSocket({URL: SOCKET_URL}));
      await socketServices.initializeSocket(SOCKET_URL);

      socketServices.on('connect', (data) => {
        console.log('=== socket connected ===');
        console.log(socketServices.socket.connected);
        setIsConnected(socketServices.socket.connected);
     });
     socketServices.on('disconnect', (data) => {
        console.log('=== socket disconnect ===');
        console.log(socketServices.socket.connected);
        setIsConnected(socketServices.socket.connected);
     });
     socketServices.on('error', (data) => {
        console.log('socket error', data);
     });
   };

   const handleServerDisconnect = () => {
      socketServices.socket.disconnect();
   };

   return (
      <View style={styles.body}>
         <Modal
         visible={showWarning}
         onRequestClose={() => setShowWarning(false)}
         transparent>
         <View style={styles.center_view}>
            <View style={styles.warning_modal}>
               <View style={styles.modal_title}>
               <Text style={styles.warning_title}>WARNING!</Text>
               </View>
               <View style={styles.modal_body}>
               <Text>Name length must exceed 2 characters.</Text>
               </View>
            </View>
         </View>
         </Modal>
         <View>
            <Text style={styles.text}>Server IP</Text>
            <TextInput
            style={styles.input}
            placeholder="e.g 192.168.1.1"
            onChangeText={value => {
               validateIP(value);
               setIp(value);
            }}
            />
            <View style={styles.button_container}>
               {/* <Button title={'Connect'} onPress={handleServerConnect} disabled={isValid ? false : true}/> */}
               <TouchableOpacity
                onPress={handleServerConnect}
                disabled={(isValid || !isConnected) ? false : true}
                style={{alignSelf: 'baseline'}}>
                  <Text style={{color: (isValid) ? '#00FF00' : '#00FF0044'}}>CONNECT</Text>
               </TouchableOpacity>
               {/* <Button title={'Disconnect'} onPress={handleServerDisconnect}/> */}
               <TouchableOpacity
                onPress={handleServerDisconnect}
                disabled={(isConnected) ? false : true}
                style={{alignSelf: 'baseline'}}>
                  <Text style={{color: (isConnected) ? '#FF0000' : '#FF000044'}}>DISCONNECT</Text>
               </TouchableOpacity>
            </View>
            <View style={styles.info_container}>
              <Text style={styles.text}>Status: {isConnected ? 'Connected' : 'Disconnected'}</Text>
              <View style={{backgroundColor: '#8D99AE', padding: 10, borderRadius: 15, marginTop: 15}}>
                <Slider
                  value={value}
                  onValueChange={value => onChangHandler(Math.floor(value))}
                  minimumValue={0}
                  maximumValue={255}
                  thumbTintColor="#fff"
                  minimumTrackTintColor="#EF233C"
                  disabled={isConnected ? false : true}
                />
                <Text style={styles.text2}>Speed: {Math.floor(value / 255 * 100)}%</Text>
                <TouchableOpacity
                onPress={setSpeedHandler}
                disabled={isConnected ? false : true}
                style={{alignSelf: 'flex-end'}}>
                  <Text style={{color: '#FCFAFA'}}>SET</Text>
               </TouchableOpacity>
              </View>
            </View>

         </View>
      </View>
   );
};

const styles = StyleSheet.create({
  body: {
   flex: 1,
   backgroundColor: 'transparent',
   alignItems: 'center',
   justifyContent: 'flex-start',
   paddingTop: 10,
  },
  text: {
    color: '#8D99AE',
    fontSize: 12,
    fontFamily: 'Roboto-Regular',
  },
  text2: {
    color: '#EDF2F4',
    fontSize: 12,
    fontFamily: 'Roboto-Regular',
  },
  input: {
    width: 200,
    height: 40,
    borderWidth: 1,
    backgroundColor: '#8D99AE',
    borderColor: '#6C7585',
    borderRadius: 5,
    textAlign: 'center',
    fontSize: 12,
  },
  center_view: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
    backgroundColor: '#00000099',
  },
  warning_modal: {
    width: 300,
    height: 300,
    backgroundColor: '#ffffff',
    borderWidth: 1,
    borderRadius: 20,
  },
  modal_title: {
    height: 50,
    backgroundColor: 'red',
    alignItems: 'center',
    justifyContent: 'center',
    borderTopLeftRadius: 20,
    borderTopRightRadius: 20,
  },
  warning_title: {
    color: 'white',
    fontSize: 20,
  },
  modal_body: {
    height: 200,
    alignItems: 'center',
    justifyContent: 'center',
  },
  button_container: {
    flexDirection: 'row',
    alignItems: 'center',
    justifyContent: 'space-evenly',
  },
  info_container: {
    margin: 10,
  },
});

export default ServerController;
