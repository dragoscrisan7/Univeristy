import tensorflow as tf
import joblib


def load_tensor_model(path):
    custom_objects = {'mse': tf.keras.losses.MeanSquaredError()}
    model = tf.keras.models.load_model(path, custom_objects=custom_objects)
    return model


def load_joblib_model(path):
    model = joblib.load(path)
    return model
