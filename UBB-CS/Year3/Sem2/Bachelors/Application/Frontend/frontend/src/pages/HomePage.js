import React, { useState, useEffect } from 'react';
import './HomePage.css'; 
import { useNavigate } from 'react-router-dom';

const HomePage = () => {
  const [isRegistering, setIsRegistering] = useState(false);
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const navigate = useNavigate();

  useEffect(() => {
    const timer = setTimeout(() => {
      const token = localStorage.getItem('token');
      if (token) {
        const buttonContainer = document.querySelector('.button-container');
        buttonContainer.classList.add('set-opacity');
      }
      else {
        const loginBox = document.querySelector('.login-box');
        loginBox.classList.add('set-opacity');
      }
    }, 10);
    return () => clearTimeout(timer);
  }, []);

  const toggleMode = () => {
    setIsRegistering(!isRegistering);
  };

  const handleFormSubmit = async (event) => {
    event.preventDefault(); 

    if (!username || !password) {
      alert("Please enter both username and password");
      return;
    }

    if (isRegistering) {
      try {
        const response = await fetch('http://127.0.0.1:8000/register', {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json'
          },
          body: JSON.stringify({ username, password })
        });

        if (response.ok) {
          alert("Registration successful");
        } else {
          const data = await response.json();
          alert(data.detail); 
        }
      } catch (error) {
        console.error('Error:', error);
        alert("An error occurred during registration");
      }
    } else {
      try {
        const response = await fetch('http://127.0.0.1:8000/login', {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json'
          },
          body: JSON.stringify({ username, password })
        });
  
        if (response.ok) {
          const data = await response.json();
          localStorage.setItem('token', data.token);
          const loginBox = document.querySelector('.login-box');
          loginBox.classList.add('fade-out');
          const buttonContainer = document.querySelector('.button-container');
          buttonContainer.classList.add('fade-in');
        } else {
          const data = await response.json();
          alert(data.detail);
        }
      } catch (error) {
        console.error('Error:', error);
        alert("An error occurred during login");
      }
    }
  };

  const goToCropYieldPage = () => {
    navigate('/crop-yield'); 
  };

  const goToChemicalComponentPage = () => {
    navigate('/chemical-component'); 
  };

  return (
    <div className="home-page">
      <h1 className="title">AgriP</h1>
      {
        <div className="login-box">
          <h2 className="login-title"> {isRegistering ? 'Register' : 'Login'}</h2>
          <form onSubmit={handleFormSubmit}>
            <div className="input-group">
              <input 
                type="text" 
                id="username" 
                name="username" 
                placeholder="Enter your username"  
                value={username} 
                onChange={(e) => setUsername(e.target.value)}   
              />
            </div>
            <div className="input-group">
              <input 
                type="password" 
                id="password" 
                name="password" 
                placeholder="Enter your password" 
                value={password} 
                onChange={(e) => setPassword(e.target.value)}  
              />
            </div>
            <button className="login-button" type="submit">{isRegistering ? 'Register' : 'Login'}</button>
          </form>
          <p>
            <a href="#" onClick={toggleMode}>{isRegistering ? 'Login' : 'Register'}</a>
          </p>
        </div>
      }
      {
        <div className="button-container">
          <button className="bottom-left-button" onClick={goToChemicalComponentPage}></button>
          <button className="bottom-right-button" onClick={goToCropYieldPage}></button>
        </div>
      }
    </div>
  );
}

export default HomePage;