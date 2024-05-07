import React from 'react';
import { Link } from 'react-router-dom';

const HomePage = () => {
  return (
    <div className="home-page">
      <h1>Agriculture App</h1>
      <div className="button-container">
        <Link to="/register">
          <button className="register-button">Register</button>
        </Link>
        <Link to="/login">
          <button className="login-button">Login</button>
        </Link>
        <button className="chemical-prediction-button">Chemical Prediction</button>
        <button className="crop-yield-prediction-button">Crop Yield Prediction</button>
      </div>
    </div>
  );
}

export default HomePage;
