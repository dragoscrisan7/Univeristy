import React, { useState, useEffect } from 'react';
import { useNavigate } from 'react-router-dom';
import './ChemicalComponentPage.css';

const ChemicalComponentPage = () => {
  const navigate = useNavigate();
  const [isLoading, setIsLoading] = useState(false);
  const [dropdownOptions, setDropdownOptions] = useState({
    District: [],
    Crop: [],
    Season: [],
    Soil_Type: [],
    Irrigation_Method: []
  });

  const [formData, setFormData] = useState({
    District: '',
    Crop: '',
    Season: '',
    Productivity: '',
    Soil_Type: '',
    pH_Level: '',
    Organic_Matter: '',
    Nitrogen_Content: '',
    Phosphorus_Content: '',
    Potassium_Content: '',
    Irrigation_Method: '',
    Water_Availability: ''
  });

  const handleInputChange = (event) => {
    const { name, value, tagName} = event.target;

    if (tagName === 'SELECT') {
      setFormData({
        ...formData,
        [name]: value
      });
    } else {
      const sanitizedValue = value.replace(/[^0-9.]/g, '').replace(/(\..*)\./g, '$1');
  
      setFormData({
        ...formData,
        [name]: sanitizedValue
      });
    }
  };

  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await fetch('http://127.0.0.1:8000/retrieve-names', {
          method: 'GET',
          headers: {
            'Content-Type': 'application/json'
          }
        });
        
        if (response.ok) {
          const data = await response.json();
          setDropdownOptions(data.names_by_type);
          setIsLoading(true);

          setFormData({
            ...formData,
            District: data.names_by_type.District[0], 
            Crop: data.names_by_type.Crop[0], 
            Season: data.names_by_type.Season[0],
            Soil_Type: data.names_by_type.Soil_Type[0], 
            Irrigation_Method: data.names_by_type.Irrigation_Method[0] 
          });
        } else {
          console.error('Failed to fetch dropdown options');
        }
      } catch (error) {
        console.error('Error:', error);
      }
    };

    fetchData();
  }, []);

  const goToHomePage = () => {
    navigate('/');
  };

  const handleSubmit = async (event) => {
    event.preventDefault();
    const allFieldsCompleted = Object.keys(formData)
      .filter(key => !['Phosphorus_Content', 'Nitrogen_Content', 'Potassium_Content'].includes(key))
      .every(key => formData[key] !== '');
    if (!allFieldsCompleted) {
      alert('Please complete all fields.');
      return;
    }


    try {
      const response = await fetch('http://127.0.0.1:8000/RCNN-predict', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify(formData)
      });

      if (response.ok) {
        const data = await response.json();
        const [nitrogen, phosphorus, potassium] = data.prediction[0];
        setFormData({
          ...formData,
          Nitrogen_Content: nitrogen,
          Phosphorus_Content: phosphorus,
          Potassium_Content: potassium
        });
      } else {
        console.error('Failed to fetch prediction');
      }
    } catch (error) {
      console.error('Error:', error);
    }
  };

  return (
    <div className="chem-predict-page">
      <div className="back-button-container-brown">
        <button className="bottom-right-back-button" onClick={goToHomePage}></button>
      </div>
      {!isLoading ? ( // Conditional rendering based on loading state
        <div>Loading...</div>
      ) : (
        <div className="form-container-chem">
          <form className="chem-pred-form">
            {dropdownOptions && ( // Check if dropdownOptions is not null
              <>
                <label htmlFor="District">District:</label>
                <select name="District" value={formData.District} onChange={handleInputChange}>
                  {dropdownOptions.District.map((district) => (
                    <option key={district} value={district}>{district}</option>
                  ))}
                </select>
                <label htmlFor="Crop">Crop:</label>
                <select name="Crop" value={formData.Crop} onChange={handleInputChange}>
                  {dropdownOptions.Crop.map((crop) => (
                    <option key={crop} value={crop}>{crop}</option>
                  ))}
                </select>
                <label htmlFor="Season">Season:</label>
                <select name="Season" value={formData.Season} onChange={handleInputChange}>
                  {dropdownOptions.Season.map((season) => (
                    <option key={season} value={season}>{season}</option>
                  ))}
                </select>
                <label htmlFor="Soil_Type">Soil Type:</label>
                <select name="Soil_Type" value={formData.Soil_Type} onChange={handleInputChange}>
                  {dropdownOptions.Soil_Type.map((soilType) => (
                    <option key={soilType} value={soilType}>{soilType}</option>
                  ))}
                </select>
                <label htmlFor="Irrigation_Method">Irrigation Method:</label>
                <select name="Irrigation_Method" value={formData.Irrigation_Method} onChange={handleInputChange}>
                  {dropdownOptions.Irrigation_Method.map((irrigationMethod) => (
                    <option key={irrigationMethod} value={irrigationMethod}>{irrigationMethod}</option>
                  ))}
                </select>
              </>
            )}
            <label htmlFor="pH_Level">pH Level:</label>
            <input type="text" name="pH_Level" value={formData.pH_Level} onChange={handleInputChange} />
            <label htmlFor="Organic_Matter">Organic Matter:</label>
            <input type="text" name="Organic_Matter" value={formData.Organic_Matter} onChange={handleInputChange} />
            <label htmlFor="Water_Availability">Water Availability:</label>
            <input type="text" name="Water_Availability" value={formData.Water_Availability} onChange={handleInputChange} />
            <label htmlFor="Productivity">Production/Area:</label>
            <input type="text" name="Productivity" value={formData.Productivity} onChange={handleInputChange} />

            <label htmlFor="Predicted_Phosphorus_Content" style={{ fontWeight: 'bold' }}>Predicted_Phosphorus Content:</label>
            <input type="text" name="Predicted_Phosphorus_Content" value={formData.Phosphorus_Content} readOnly  />
            <label htmlFor="Predicted_Potassium_Content" style={{ fontWeight: 'bold' }}>Predicted_Potassium Content:</label>
            <input type="text" name="Predicted_Potassium_Content" value={formData.Potassium_Content} readOnly  />
            <label htmlFor="Predicted_Nitrogen_Content" style={{ fontWeight: 'bold' }}>Predicted_Nitrogen Content:</label>
            <input type="text" name="Predicted_Nitrogen_Content" value={formData.Nitrogen_Content} readOnly  />

          </form>
        </div> 
      )}
      <button className='chem-submit-button' onClick={handleSubmit}></button>
    </div>
  );
}

export default ChemicalComponentPage;
