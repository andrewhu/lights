from flask import Flask
import pickle

app = Flask(__name__)

@app.route("/")
def get_brightness():
    brightness = pickle.load(open("brightness.pickle", "rb"))
    return str(brightness)

@app.route("/set_brightness/<int:brightness>/<string:token>")
def set_brightness(brightness, token):
    if token != "":
        return 403
    pickle.dump(brightness, open("brightness.pickle", "wb"))
    return 200


