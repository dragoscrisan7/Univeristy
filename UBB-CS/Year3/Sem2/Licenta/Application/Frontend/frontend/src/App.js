import React, { useEffect } from 'react';
import { BrowserRouter as Router, Route, NavLink, Routes } from 'react-router-dom';
import HomePage from './pages/HomePage'; 
import ChemicalComponentPage from './pages/ChemicalComponentPage';
import CropYieldPage from './pages/CropYieldPage';

function App() {
  useEffect(() => {
    localStorage.removeItem('token');
  }, []);

  return (
    <Router>
      <Routes>
        <Route path="/" element={<HomePage />} />
        <Route path="/crop-yield" element={<CropYieldPage />} /> 
        <Route path="/chemical-component" element={<ChemicalComponentPage />} /> 
      </Routes>
    </Router>
  );
}

export default App;
