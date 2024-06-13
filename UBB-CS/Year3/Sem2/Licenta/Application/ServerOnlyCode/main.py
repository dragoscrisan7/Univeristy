from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from Service import app

api = FastAPI()

origins = [
    "http://localhost:3000",
    "http://172.23.192.1:3000",
    "http://127.0.0.1:8000",
]

api.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["GET", "POST", "PUT", "DELETE"],
    allow_headers=["*"],
)

app.mount("/", api)

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="127.0.0.1", port=8000)

