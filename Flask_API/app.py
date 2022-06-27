import flask
from flask import request
from flask_restful import Api, Resource
from flask_cors import CORS
import psycopg2

# DB Connections

conn = psycopg2.connect(
        host="IP_ADDRESS_OF_DB",
        database="DB_NAME",
        user="USERNAME",
        password="USER_PASSWORD")

##############################


# Starting the Flask App
app = flask.Flask(__name__)
CORS(app)
api = Api(app)
###########################

#API Class Definetions
class Hello(Resource):
   def get(self):
      try:
         return "Hello World"
      except Exception:
         return Exception

class Monitor(Resource):   
   def get(self,temp,hum,device_id):    
      try:
         cur = conn.cursor()
         query = "insert into log_master (temperature,humidity,device_id) values ("+str(temp)+","+str(hum)+","+str(device_id)+")"
         cur.execute(query)
         conn.commit()
         cur.close()
         return "success"
      except Exception:
         return Exception
###################################


# Adding Classes to API
api.add_resource(Hello,"/api/test")
api.add_resource(Monitor,"/api/temphum/<float:temp>/<float:hum>/<int:device_id>")

##########################

# Main Function
if __name__ == "__main__":
    app.run(host="IP_ADDRESS", port=5000,debug=True)
    
#####################