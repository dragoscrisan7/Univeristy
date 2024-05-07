import React from 'react';
import { BrowserRouter as Router, Route, Switch } from 'react-router-dom'; // Import BrowserRouter and other necessary components from 'react-router-dom'
import HomePage from './components/HomePage'; // Import the HomePage component

function App() {
  return (
    <Router>
      <Switch>
        <Route path="/" exact component={HomePage} /> {/* Define a route for the HomePage component */}
        {/* Add more routes here for other components/pages */}
      </Switch>
    </Router>
  );
}

export default App;