from pydantic import BaseModel
from typing import List
from sqlalchemy import Column, Integer, String
import sqlalchemy

Base = sqlalchemy.orm.declarative_base()


class PredictYieldData(BaseModel):
    District: str
    Crop: str
    Season: str
    Area_hectares: float
    Soil_Type: str
    pH_Level: float
    Organic_Matter: float
    Nitrogen_Content: float
    Phosphorus_Content: float
    Potassium_Content: float
    Irrigation_Method: str
    Water_Availability: float


class PredictChemicalData(BaseModel):
    District: str
    Crop: str
    Season: str
    Soil_Type: str
    pH_Level: float
    Organic_Matter: float
    Irrigation_Method: str
    Water_Availability: float
    Productivity: float


class User(Base):
    __tablename__ = 'User'

    id = Column(Integer, primary_key=True, index=True)
    username = Column(String, unique=True, index=True)
    password = Column(String)


class PUser(BaseModel):
    username: str
    password: str


class DropDown(Base):
    __tablename__ = 'DropDowns'

    id = Column(Integer, primary_key=True, index=True)
    name = Column(String, index=True)
    type = Column(String)


class PDropDown(BaseModel):
    type: str


class LoginResponse(BaseModel):
    message: str


class RegisterResponse(BaseModel):
    message: str


class RetrieveNamesResponse(BaseModel):
    names: List[str]
