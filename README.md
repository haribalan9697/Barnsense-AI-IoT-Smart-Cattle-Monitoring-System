
# BarnSense: AI & IoT Smart Cattle Monitoring System

BarnSense is an innovative project that harnesses the power of AI and IoT to monitor the health of livestock, with potential applications in wildlife monitoring. This repository contains the complete working code behind the device.In this Project i have trained a model which takes live data from the sensors attached on cattles and use the data to predict wheather the cattle is healthy or not. The model i have used is gaussian naive bayes which is trained using 1000 previous data of cattles and made for classification. I have deployed the model using flask framework by creating a webapp which tracks live data and also predicts the health of the cattle using the data. When the model predicts that the cattle is unhealthy then it will alert the farmer about the need for imediate action by sending a alert notification.

## Overview

BarnSense aims to provide a comprehensive solution for monitoring the health of cattle by combining artificial intelligence and Internet of Things technologies. By analyzing various parameters, it can detect potential health issues early, allowing for timely intervention and improved animal welfare.

## Getting Started

To get started with BarnSense, follow these steps:

1. Clone this repository to your local machine.
2. Install the necessary dependencies by running:

   ```bash
   pip install -r requirements.txt
   ```

3. Create an account on Twilio and obtain your credentials.
4. Replace the Twilio credentials in the code to enable alert notifications.

## Usage

Before running the code, ensure you have set up the Twilio credentials as mentioned above. Once configured, you can run the main script to start monitoring livestock health. Make sure to keep the `doc.html` file in a separate folder named `templates` for proper functioning.

## Folder Structure

- `/src`: Contains the source code files.
- `/templates`: Holds the HTML template files (keep `doc.html` here).

## Contributing

Contributions to BarnSense are welcome! If you have ideas for improvements, new features, or bug fixes, please submit a pull request. Be sure to follow our contribution guidelines.

## Contact

For any questions or support, feel free to contact us at [haribalan9697@gmail.com](mailto:harihb9697@gmail.com).

---

Feel free to customize this template further to fit your project's specific details and requirements. Let me know if you need any further assistance!
