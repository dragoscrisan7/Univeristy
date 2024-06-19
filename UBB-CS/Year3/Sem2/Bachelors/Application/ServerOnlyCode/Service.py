from sqlite3 import OperationalError

import pandas as pd
import jwt
from fastapi import FastAPI, HTTPException, Depends
from sqlalchemy import select, text
from sqlalchemy.exc import SQLAlchemyError
from sqlalchemy.orm import Session

from ML_loaders import cnn_model, rcnn_model, scaler, rscaler, encoder, xgb_model
from DataAccessLayer import get_db, engine
import Models
from fastapi.responses import JSONResponse


app = FastAPI()


@app.get("/ping")
def ping():
    try:
        with engine.connect() as connection:
            connection.execute(text("SELECT 1"))
        return JSONResponse(content={"message": "Ping successful. Database connection is established."},
                            headers={"Access-Control-Allow-Origin": "*"})
    except OperationalError as e:
        return {"error": f"Database connection error: {str(e)}"}


@app.post("/login")
def login(user: Models.PUser, db: Session = Depends(get_db)):
    user_db = db.query(Models.User).filter(Models.User.username == user.username).first()
    db.close()
    if user_db and user_db.password == user.password:
        payload = {"username": user_db.username, "user_id": user_db.id}

        token = jwt.encode(payload, "your-secret-key", algorithm="HS256")

        return JSONResponse(content={"token": token}, headers={"Access-Control-Allow-Origin": "*"})
    raise HTTPException(status_code=401, detail="Invalid username or password")


@app.post("/register")
def register(user: Models.PUser, db: Session = Depends(get_db)):
    user_db = db.execute(select(Models.User).filter(Models.User.username == user.username)).first()
    if user_db:
        db.close()
        raise HTTPException(status_code=400, detail="Username already exists")
    db.add(Models.User(**user.dict()))
    db.commit()
    db.close()
    return JSONResponse(content={"message": "Registration successful"}, headers={"Access-Control-Allow-Origin": "*"})


@app.get("/retrieve-names")
def retrieve_names(db: Session = Depends(get_db)):
    try:
        results = db.query(Models.DropDown).all()

        names_by_type = {}

        for result in results:
            type_key = result.type.replace(' ', '_')
            if type_key not in names_by_type:
                names_by_type[type_key] = []
            names_by_type[type_key].append(result.name)

        return JSONResponse(content={"names_by_type": names_by_type}, headers={"Access-Control-Allow-Origin": "*"})
    except SQLAlchemyError as e:
        raise HTTPException(status_code=500, detail=str(e))
    finally:
        db.close()


@app.post('/CNN-predict')
def cnn_predict(input_data: Models.PredictYieldData):
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

        input_df = pd.DataFrame([input_dict])

        X_encoded = encoder.transform(input_df[['District', 'Crop', 'Season', 'Soil Type', 'Irrigation Method']])
        feature_names = encoder.get_feature_names_out(['District', 'Crop', 'Season', 'Soil Type', 'Irrigation Method'])
        X_categorical = pd.DataFrame(X_encoded.toarray(), columns=feature_names)

        X_numeric = input_df.drop(columns=['District', 'Crop', 'Season', 'Soil Type', 'Irrigation Method'])

        X_processed = pd.concat([X_categorical, X_numeric], axis=1)

        X_processed_scaled = scaler.transform(X_processed)

        X_reshaped = X_processed_scaled.reshape(X_processed_scaled.shape[0], X_processed_scaled.shape[1], 1)

        prediction = cnn_model.predict(X_reshaped)

        return JSONResponse(content={"prediction": prediction.tolist()}, headers={"Access-Control-Allow-Origin": "*"})
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

        X_encoded = encoder.transform(input_df[['District', 'Crop', 'Season', 'Soil Type', 'Irrigation Method']])
        feature_names = encoder.get_feature_names_out(['District', 'Crop', 'Season', 'Soil Type', 'Irrigation Method'])
        X_categorical = pd.DataFrame(X_encoded.toarray(), columns=feature_names)

        X_numeric = input_df.drop(columns=['District', 'Crop', 'Season', 'Soil Type', 'Irrigation Method'])

        X_processed = pd.concat([X_categorical, X_numeric], axis=1)

        X_processed_scaled = rscaler.transform(X_processed)

        prediction = rcnn_model.predict(X_processed_scaled)

        return JSONResponse(content={"prediction": prediction.tolist()}, headers={"Access-Control-Allow-Origin": "*"})
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

        input_df = pd.DataFrame([input_dict])

        cat_cols = ['District', 'Crop', 'Season', 'Soil Type', 'Irrigation Method']
        input_df[cat_cols] = input_df[cat_cols].astype("category")

        input_df.drop(columns=['Production (metric tons)', 'Water Consumption (liters/hectare)'], inplace=True,
                      errors='ignore')

        prediction = xgb_model.predict(input_df)

        return JSONResponse(content={"prediction": prediction.tolist()}, headers={"Access-Control-Allow-Origin": "*"})
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
