from sqlite3 import OperationalError

import pandas as pd
from fastapi import FastAPI, HTTPException, Depends
from http.client import HTTPException
from sqlalchemy import create_engine, select, text
from sqlalchemy.exc import SQLAlchemyError
from sqlalchemy.orm import sessionmaker, Session

import ML_loaders
import Models

app = FastAPI()
cnn_model = ML_loaders.load_tensor_model('..\..\MLAlgorithms\Project-CNN\model.h5')
rcnn_model = ML_loaders.load_tensor_model('..\..\MLAlgorithms\Project-CNN-Regresion\Rmodel.h5')
xgb_model = ML_loaders.load_joblib_model('..\..\MLAlgorithms\Project-XGB\model_xbg.pkl')
encoder = ML_loaders.load_joblib_model('..\..\MLAlgorithms\Project-CNN\encoder.pkl')
scaler = ML_loaders.load_joblib_model('..\..\MLAlgorithms\Project-CNN\scaler.pkl')
rscaler = ML_loaders.load_joblib_model('..\..\MLAlgorithms\Project-CNN-Regresion\scaler.pkl')

DATABASE_URL = "sqlite:///../Database/AgriP"
engine = create_engine(DATABASE_URL)
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)


def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()


@app.get("/ping")
def ping():
    try:
        # Attempt to execute a simple query to check database connectivity
        with engine.connect() as connection:
            connection.execute(text("SELECT 1"))
        return {"message": "Ping successful. Database connection is established."}
    except OperationalError as e:
        return {"error": f"Database connection error: {str(e)}"}


@app.post("/login")
def login(user: Models.PUser, db: Session = Depends(get_db)):
    user_db = db.query(Models.User).filter(Models.User.username == user.username).first()
    db.close()
    if user_db and user_db.password == user.password:
        return Models.LoginResponse(message="Login successful")
    raise HTTPException(status_code=401, detail="Invalid username or password")


# Endpoint for user registration
@app.post("/register")
def register(user: Models.PUser, db: Session = Depends(get_db)):
    user_db = db.execute(select(Models.User).filter(Models.User.username == user.username)).first()
    if user_db:
        db.close()
        raise HTTPException(status_code=400, detail="Username already exists")
    db.add(Models.User(**user.dict()))
    db.commit()
    db.close()
    return Models.RegisterResponse(message="Registration successful")


# Endpoint for retrieving names of a specific type
@app.get("/retrieve-names/{DDtype}")
def retrieve_names(DDtype: str, db: Session = Depends(get_db)):
    try:
        results = db.query(Models.DropDown).filter(Models.DropDown.type == DDtype).all()
        names = [result.name for result in results]  # Ensure 'name' attribute is available in the result object
        return {"names": names}
    except SQLAlchemyError as e:
        # Log the error or handle it appropriately
        return {"error": str(e)}
    finally:
        db.close()


@app.post('/CNN-predict')
def cnn_predict(input_data: Models.PredictYieldData):
    try:
        input_dict = input_data.dict()

        # Define mapping dictionary for column names
        column_mapping = {
            'Area_hectares': 'Area (hectares)',
            'Soil_Type': 'Soil Type',
            'pH_Level': 'pH Level',
            'Organic_Matter': 'Organic Matter (%)',
            'Nitrogen_Content': 'Nitrogen Content (kg/ha)',
            'Phosphorus_Content': 'Phosphorus Content (kg/ha)',
            'Potassium_Content': 'Potassium Content (kg/ha)',
            'Water_Availability': 'Water Availability (liters/hectare)',
            'Irrigation_Method': 'Irrigation Method'
        }

        # Rename keys to match the column names used in the model
        input_dict = {column_mapping.get(key, key): value for key, value in input_dict.items()}

        # Create a DataFrame with a single row containing the input data
        input_df = pd.DataFrame([input_dict])

        # Encode categorical columns using the pre-trained encoder
        X_encoded = encoder.transform(input_df[['District', 'Crop', 'Season', 'Soil Type', 'Irrigation Method']])
        feature_names = encoder.get_feature_names_out(['District', 'Crop', 'Season', 'Soil Type', 'Irrigation Method'])
        X_categorical = pd.DataFrame(X_encoded.toarray(), columns=feature_names)

        # Drop categorical columns from the input DataFrame
        X_numeric = input_df.drop(columns=['District', 'Crop', 'Season', 'Soil Type', 'Irrigation Method'])

        # Scale numerical columns using the pre-trained scaler
        X_processed = pd.concat([X_categorical, X_numeric], axis=1)

        # Combine the encoded categorical columns and the scaled numerical columns
        X_processed_scaled = scaler.transform(X_processed)

        # Reshape the input data to match the expected shape of the model input
        X_reshaped = X_processed_scaled.reshape(X_processed_scaled.shape[0], X_processed_scaled.shape[1], 1)

        # Make predictions using the loaded model
        prediction = cnn_model.predict(X_reshaped)

        return {'prediction': prediction.tolist()}
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@app.post('/RCNN-predict')
def rcnn_predict(input_data: Models.PredictChemicalData):
    try:
        input_dict = input_data.dict()

        column_mapping = {
            'Soil_Type': 'Soil Type',
            'pH_Level': 'pH Level',
            'Organic_Matter': 'Organic Matter (%)',
            'Water_Availability': 'Water Availability (liters/hectare)',
            'Irrigation_Method': 'Irrigation Method'
        }

        input_dict = {column_mapping.get(key, key): value for key, value in input_dict.items()}

        input_df = pd.DataFrame([input_dict])

        # Encode categorical columns using the pre-trained encoder
        X_encoded = encoder.transform(input_df[['District', 'Crop', 'Season', 'Soil Type', 'Irrigation Method']])
        feature_names = encoder.get_feature_names_out(['District', 'Crop', 'Season', 'Soil Type', 'Irrigation Method'])
        X_categorical = pd.DataFrame(X_encoded.toarray(), columns=feature_names)

        # Drop categorical columns from the input DataFrame
        X_numeric = input_df.drop(columns=['District', 'Crop', 'Season', 'Soil Type', 'Irrigation Method'])

        # Combine the encoded categorical columns and the numerical columns
        X_processed = pd.concat([X_categorical, X_numeric], axis=1)

        # Scale numerical columns using the pre-trained scaler
        X_processed_scaled = rscaler.transform(X_processed)

        # Make predictions using the loaded model
        predictions = rcnn_model.predict(X_processed_scaled)

        return {'predictions': predictions.tolist()}
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@app.post('/XGB-predict')
def xgb_predict(input_data: Models.PredictYieldData):
    try:
        input_dict = input_data.dict()

        column_mapping = {
            'Area_hectares': 'Area (hectares)',
            'Soil_Type': 'Soil Type',
            'pH_Level': 'pH Level',
            'Organic_Matter': 'Organic Matter (%)',
            'Nitrogen_Content': 'Nitrogen Content (kg/ha)',
            'Phosphorus_Content': 'Phosphorus Content (kg/ha)',
            'Potassium_Content': 'Potassium Content (kg/ha)',
            'Water_Availability': 'Water Availability (liters/hectare)',
            'Irrigation_Method': 'Irrigation Method'
        }

        input_dict = {column_mapping.get(key, key): value for key, value in input_dict.items()}

        # Create a DataFrame with a single row using the input data
        input_df = pd.DataFrame([input_dict])

        # Transform categorical columns to category data type
        cat_cols = ['District', 'Crop', 'Season', 'Soil Type', 'Irrigation Method']
        input_df[cat_cols] = input_df[cat_cols].astype("category")

        # Drop any unnecessary columns (if needed)
        input_df.drop(columns=['Production (metric tons)', 'Water Consumption (liters/hectare)'], inplace=True,
                      errors='ignore')

        # Predict using the XGBoost model
        prediction = xgb_model.predict(input_df)

        return {'predicted_yield': prediction.tolist()}
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
