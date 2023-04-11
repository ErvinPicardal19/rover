import React, {useState} from 'react';
import {StyleSheet, View} from 'react-native';
import {GestureHandlerRootView} from 'react-native-gesture-handler';

import ServerController from './components/ServerController';
import LeftController from './components/LeftController';
import RightController from './components/RightController';

const App = () => {
  const [isConnected, setIsConnected] = useState(false);

  return (
    <GestureHandlerRootView style={styles.body}>
      <LeftController
        isConnected={isConnected}
        setIsConnected={setIsConnected}
      />
      <ServerController
        isConnected={isConnected}
        setIsConnected={setIsConnected}
      />
      <RightController
        isConnected={isConnected}
        setIsConnected={setIsConnected}
      />
    </GestureHandlerRootView>
  );
};

const styles = StyleSheet.create({
  body: {
    flex: 1,
    flexDirection: 'row',
    backgroundColor: '#2B2D42',
    alignItems: 'stretch',
    justifyContent: 'center',
  },
  segment: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
    backgroundColor: '#EDF2F4',
  },
});

export default App;
