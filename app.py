from flask import Flask, render_template, request
import joblib
from twilio.rest import Client

app = Flask(__name__)


with open('cattle.pkl', 'rb') as file:
    model = joblib.load(file)


healthy_pulse_threshold = 40
unhealthy_pulse_threshold = 90


account_sid = ""#enter your account sid from twilio here 
auth_token ="" #enter your authentication token from twilio here    
twilio_phone_number ="" #give your twilio phone number here                


client = Client(account_sid, auth_token)


def send_notification(status, temperature, pulse, accelerometer, latitude, longitude):
    try:
        message = client.messages.create(
            body=f"Notification: {status}\nTemperature: {temperature}\nPulse: {pulse}\nAccelerometer: {accelerometer}\nLatitude: {latitude}\nLongitude: {longitude}",
            from_=twilio_phone_number,
            to="+91" # give the number you want to recieve alert notification from here"  
        )
        print("Notification sent successfully:", message.sid)
        return True
    except Exception as e:
        print("Error sending notification:", e)
        return False

@app.route('/')
def home():
    return render_template('doc.html')

@app.route('/predict', methods=['POST'])
def predict():
 
    temperature = float(request.form['temperature'])
    pulse = float(request.form['pulse'])
    accelerometer = float(request.form['accelerometer'])
    latitude = float(request.form['latitude'])
    longitude = float(request.form['longitude'])

  
    prediction = model.predict([[temperature, pulse, accelerometer, latitude, longitude]])

    
    if pulse <= healthy_pulse_threshold or pulse >= unhealthy_pulse_threshold:
        status = 'Pulse is critical cattle needs immediate attention.'
    elif prediction == 1:
        status = 'Not Healthy'
    else:
        status = 'cattle is Healthy'

    
    notification_sent = False
    if status != 'cattle is Healthy':
        notification_sent = send_notification(status, temperature, pulse, accelerometer, latitude, longitude)

    return render_template('doc.html', status=status, notification_sent=notification_sent)

if __name__ == '__main__':
    app.run()
