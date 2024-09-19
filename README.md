🚨 ESP32 PIR Sensor with Temperature & Humidity Logging System 🌡️

This project demonstrates how to build and deploy a motion detection and temperature/humidity logging system using the ESP32, a PIR sensor, a DHT22 sensor, and an OLED display. Sensor data is logged to a Flask server hosted on Heroku, where it is stored in a PostgreSQL database.

The system is simulated on Wokwi before physical implementation, which significantly speeds up testing and development.
📑 Table of Contents

    Features
    Hardware Components
    Software Components
    Setup Overview
    Step-by-Step Instructions
        1. Simulating the ESP32 in Wokwi
        2. Setting up the Flask Server
        3. Hosting the Flask Server on Heroku
        4. Adding PostgreSQL for Data Logging
    Project Files
    Future Improvements
    License

🚀 Features

    Motion Detection: The system detects motion using a PIR sensor and logs the event.
    Temperature & Humidity Monitoring: The DHT22 sensor reads environmental data (temperature and humidity).
    Data Logging to PostgreSQL: Sensor data and motion events are logged to a PostgreSQL database hosted on Heroku.
    OLED Display: Real-time data is displayed on an OLED screen connected to the ESP32.
    Simulation Using Wokwi: The entire setup is simulated in the Wokwi platform before physical implementation.
    Hosted on Heroku: The Flask server is hosted on Heroku, making it accessible globally and scalable for real-world deployment.

🛠️ Hardware Components

    ESP32 Dev Kit V1: Microcontroller that manages sensors and communicates with the server.
    PIR Motion Sensor: Detects motion and triggers an event.
    DHT22 Sensor: Measures temperature and humidity.
    OLED Display (SSD1306): Displays motion, temperature, and humidity data.
    Buzzer & LED: Alerts the user upon motion detection.

💻 Software Components

    Flask: Python micro-framework to create the server for handling sensor data.
    PostgreSQL: Database to store sensor logs and motion events.
    Heroku: Cloud platform for hosting the Flask server and PostgreSQL.
    Wokwi: Online simulation platform to test ESP32 and sensor integration.

📊 Setup Overview

    Simulation in Wokwi: The ESP32 and sensor system is simulated in Wokwi, allowing you to test the sensors and firmware before deploying hardware.
    Flask Server Setup: The Flask server receives HTTP POST requests from the ESP32, logs the motion events, and saves sensor data.
    Heroku Hosting: The Flask server is hosted on Heroku, making it publicly accessible.
    PostgreSQL Database: A Heroku PostgreSQL add-on is used to store the logged data for future use.

🔧 Step-by-Step Instructions
1. Simulating the ESP32 in Wokwi

The Wokwi platform allows you to simulate your hardware setup with virtual ESP32, sensors, and displays before testing with actual hardware.
Steps:

    Go to Wokwi.
    Create a new project, adding an ESP32 Dev Kit V1, PIR Motion Sensor, DHT22 sensor, and OLED display.
    Write the ESP32 firmware that reads motion, temperature, and humidity data and displays it on the OLED.
    The firmware sends the data to the Flask server hosted on Heroku via HTTP POST requests.

This simulation allows for testing without needing physical components, significantly speeding up the development process.
2. Setting up the Flask Server

A Flask server is used to handle incoming data from the ESP32. The server logs the sensor data (motion, temperature, and humidity) to a PostgreSQL database and sends a response back to the ESP32.

The server is written in Python and is configured to receive POST requests, process the incoming data, and store it in the database.

For more details, refer to the server.py file in the repository.
3. Hosting the Flask Server on Heroku

Once the Flask server is ready, you can deploy it to Heroku to make it accessible globally. Heroku’s free tier is sufficient for basic usage and allows you to scale if needed.
Steps:

    Create a new Heroku app:

    bash

heroku create esp32-pir-server

Push your code to Heroku:

bash

git push heroku master

Set environment variables (e.g., DATABASE_URL):

bash

heroku config:set FLASK_APP=server.py

Run the app:

bash

    heroku open

Your server is now live, and the ESP32 can send data to it over the internet.
4. Adding PostgreSQL for Data Logging

Heroku provides an easy way to add a PostgreSQL database as a service. This database will store the motion, temperature, and humidity data for later use.
Steps:

    Add the PostgreSQL Add-On:

    bash

    heroku addons:create heroku-postgresql:hobby-dev

    Migrate the database: The Flask app will automatically create the necessary tables if they don’t exist. Ensure that the connection to the PostgreSQL database is set up in your environment variables via DATABASE_URL.

To view or manipulate your data, you can use tools like pgAdmin or Heroku’s built-in Postgres GUI.

For more details, check the PostgreSQL setup instructions in the Heroku documentation.
📁 Project Files

    server.py: The main Flask application that handles incoming sensor data and stores it in the PostgreSQL database.
    requirements.txt: Lists the Python packages required to run the Flask app on Heroku (e.g., Flask, SQLAlchemy, psycopg2-binary).
    Wokwi Project: The ESP32 and sensor simulation setup, which can be accessed at Wokwi.

📈 Future Improvements

    Data Visualization Dashboard: Build a front-end interface or dashboard to visualize the motion and sensor data in real-time.
    Notifications: Add functionality to send alerts (e.g., email, SMS) when motion is detected.
    Additional Sensors: Integrate more sensors like gas detectors or light sensors to make the system more comprehensive.

📜 License

This project is licensed under the MIT License - see the LICENSE file for details.
