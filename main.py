from flask import Flask , request, jsonify,json
from flask_pymongo import PyMongo
from flask_cors import CORS
from marshmallow import Schema , fields , ValidationError
from bson.json_util import dumps
from json import loads
from datetime import datetime

# For Launch
app = Flask (__name__)
CORS(app)

# For Connection to Mongo
app.config ["MONGO_URI"] = "mongodb+srv://CBeharie99:project@cluster0.otczh.mongodb.net/NIGM?ssl=true&ssl_cert_reqs=CERT_NONE"
mongo = PyMongo(app)




class ReadingsSchema(Schema):
    reading = fields.String(required=True)
    patient_id = fields.Integer(required = True)
   


#############################################################################
# routes for NIGM 

@app.route("/home")
def home ():
    return "Welcome to Glu-Clever"

@app.route("/home/history")
def get_history ():
    readings = mongo.db.readings.find()
    return jsonify(loads(dumps(readings)))

@app.route ("/home/history", methods = ["POST"])
def add_Reading ():
    try:
        newReading = ReadingsSchema().load(request.json)
        Readings_id = mongo.db.readings.insert_one(newReading).inserted_id
        readings = mongo.db.readings.find_one(Readings_id)
        return loads(dumps(readings))
    except ValidationError as ve:
         return ve.messages, 400

@app.route ("/home/history/<ObjectId:id>", methods = ["PATCH"])
def update_record(id):
    mongo.db.readings.update_one({"_id":id}, {"$set": request.json})
    readings = mongo.db.readings.find_one(id)
    return loads(dumps(readings))

@app.route ("/home/history/<ObjectId:id>", methods = ["DELETE"])
def delete_record(id):
    result = mongo.db.readings.delete_one({"_id": id})
    if result.deleted_count == 1:
       return {
           "Reading Deleted": True
        }
    else:
        return {
               "Reading Deleted": False
            }, 400





if __name__ =="__main__" :
    app.run (port=5000, debug = True )