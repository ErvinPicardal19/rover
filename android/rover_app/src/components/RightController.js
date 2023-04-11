/* eslint-disable prettier/prettier */
import React, {useEffect, useState} from 'react';
import {
  View,
  StyleSheet,
  Image,
} from 'react-native';
import VerticalSlider from 'rn-vertical-slider-matyno';
import Icon from 'react-native-vector-icons/FontAwesome';
import socketServices from '../utils/socketServices';

const RightController = (props) => {
  const {isConnected, setIsConnected} = props;
  const [value, setValue] = useState(0);
  const [lastVal, setLastVal] = useState(0);


  useEffect(() => {
    console.log('Claw: ', value);
  }, [value]);

  const onChangHandler = (newVal) => {
    if (newVal !== lastVal){
      setValue(newVal);
      socketServices.emit('claw_change', newVal);
      setLastVal(newVal);
    }
  };

  return (
    <View style={styles.body}>
      <VerticalSlider
          value={value}
          disabled={isConnected ? false : true}
          min={0}
          max={180}
          onChange={(value) => onChangHandler(value)}
          width={30}
          height={250}
          step={1}
          borderRadius={5}
          showBallIndicator={false}
          minimumTrackTintColor={isConnected ? '#2B2D42' : '#2B2D4244'}
          maximumTrackTintColor={'gray'}
          ballIndicatorColor={'black'}
          ballIndicatorTextColor={'white'}
          ballIndicatorPosition={-50}
        />
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
  image: {
   width: 50,
   height: 50,
  },
});

export default RightController;
