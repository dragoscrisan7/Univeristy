import tensorflow as tf
import joblib


def load_tensor_model(path):
    custom_objects = {'mse': tf.keras.losses.MeanSquaredError()}
    model = tf.keras.models.load_model(path, custom_objects=custom_objects)
    return model


def load_joblib_model(path):
    model = joblib.load(path)
    return model


cnn_model = load_tensor_model('..\..\MLAlgorithms\Project-CNN\model.h5')
rcnn_model = load_tensor_model('..\..\MLAlgorithms\Project-CNN-Regresion\Rmodel.h5')
xgb_model = load_joblib_model('..\..\MLAlgorithms\Project-XGB\model_xbg.pkl')
encoder = load_joblib_model('..\..\MLAlgorithms\Project-CNN\encoder.pkl')
scaler = load_joblib_model('..\..\MLAlgorithms\Project-CNN\scaler.pkl')
rscaler = load_joblib_model('..\..\MLAlgorithms\Project-CNN-Regresion\scaler.pkl')