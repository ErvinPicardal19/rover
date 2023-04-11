/* eslint-disable prettier/prettier */
import React, {useEffect, useState} from 'react';
import {View, StyleSheet} from 'react-native';
import { BaseButton } from 'react-native-gesture-handler';

import Icon from 'react-native-vector-icons/FontAwesome';

import socketServices from '../utils/socketServices';


const LeftController = (props) => {
   const {isConnected, setIsConnected} = props;

   return (
      <View style={styles.body}>
         <View>
         <BaseButton style={{...styles.arrow_pad, backgroundColor: isConnected ? '#2B2D42' : '#2B2D4244'}} rippleColor={'#f00'} enabled={isConnected ? true : false} onActiveStateChange={(isActive) => {
            if (isActive){
               socketServices.emit('go_up');
               console.log('Going Up!');
            } else {
               socketServices.emit('stop');
               console.log('Stopped!');
            }
         }}>
               <Icon
                  name="angle-up"
                  color="#fff"
                  size={30}

               />
            </BaseButton>
         </View>
         <View style={styles.horizonetal_pads}>
            <View>
            <BaseButton style={{...styles.arrow_pad, backgroundColor: isConnected ? '#2B2D42' : '#2B2D4244'}} rippleColor={'#f00'} enabled={isConnected ? true : false} onActiveStateChange={(isActive) => {
               if (isActive){
                  socketServices.emit('go_left');
                  console.log('Going Left!');
               } else {
                  socketServices.emit('stop');
                  console.log('Stopped!');
               }
            }}>
                  <Icon
                     name="angle-left"
                     color="#fff"
                     size={30}

                  />
               </BaseButton>
            </View>
            <View>
            <BaseButton style={{...styles.arrow_pad, backgroundColor: isConnected ? '#2B2D42' : '#2B2D4244'}} rippleColor={'#f00'} enabled={isConnected ? true : false} onActiveStateChange={(isActive) => {
               if (isActive){
                  socketServices.emit('go_right');
                  console.log('Going Right!');
               } else {
                  socketServices.emit('stop');
                  console.log('Stopped!');
               }
            }}>
                  <Icon
                     name="angle-right"
                     color="#fff"
                     size={30}

                  />
               </BaseButton>
            </View>
         </View>
         <View>
         <BaseButton style={{...styles.arrow_pad, backgroundColor: isConnected ? '#2B2D42' : '#2B2D4244'}} rippleColor={'#f00'} enabled={isConnected ? true : false} onActiveStateChange={(isActive) => {
            if (isActive){
               socketServices.emit('go_down');
               console.log('Going Down!');
            } else {
               socketServices.emit('stop');
               console.log('Stopped!');
            }
         }}>
               <Icon
                  name="angle-down"
                  color="#fff"
                  size={30}

               />
            </BaseButton>
         </View>
      </View>
   );
};

const styles = StyleSheet.create({
   body: {
      flex: 1,
      alignItems: 'center',
      justifyContent: 'center',
      backgroundColor: '#EDF2F4',
    },
    horizonetal_pads: {
      width: '100%',
      flexDirection: 'row',
      alignItems: 'center',
      justifyContent: 'space-evenly',
      marginHorizontal: 10,
    },
    arrow_pad: {
      height: 50,
      width: 50,
      borderRadius: 5,
      alignItems: 'center',
      justifyContent: 'center',
    },
});

export default LeftController;
