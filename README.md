# Unscented Kalman Filter(EKF)
## Estimate State of an object with noisy sensor measurements.

---

[//]: # (Image References)

[image1]: ./support/SimulatorStartup.png "Simulator Startup Window"
[image2]: ./support/EKFRunning.png " Simulator Results"
[image3]: ./support/TuningGraphs.png " Tuning Results"
[image4]: ./support/LaserNIS_Graph.png " Dataset 1 Results"
[image5]: ./support/RadarNIS_Graph.png " Dataset 2 Results"


## Overview
Implementation of an Unscented Kalman filter in C++, which tracks a vehicles position and velocity by fusing simulated Radar and Laser measurement data. 

* EKF takes a mean and approximates to produce a Gaussian distribution in order to predict the future point.
* UKF takes a mean plus a number of weighted points taken from the distribution, approximates using all these points to produce a more accurate gaussian distribution, which then allows a more accurate prediction of the future point.

The basic process of the UKF is:

1. Initialise Variables 
2. Prediction - Generate Sigma Points; Predict Sigma Points; Predict Mean and Covariance 
3. Update - Prediction Measurement; Update State 


The simulated data is provided over WebSocket from the Udacity Term 2 Simulator. The code fuses this received data and predicts the path of the vehicle using an Unscented Kalman Filter. The prediction is passed back to the simulator and displayed with the sensor measurements.

---

## Installation steps

To run this code the following downloads are required:

1. Make a project directory `mkdir project_udacity && cd project_udacity`
2. Clone this repository into the project_udacity directory. `git clone https://github.com/nutmas/CarND-Unscented-Kalman-Filter-Project.git`
3. Setup environment. `cd CarND-Unscented-Kalman-Filter-Project\` and launch the script to install uWebSocketIO `./install-mac.sh`. Alternatively for Ubuntu installs launch `./install-ubuntu.sh`. The environment will be installed with these scripts.
4. Download Term 2 Simulator: 
      * Download from here: [Udacity Simulator](https://github.com/udacity/self-driving-car-sim/releases).
      * Place the extracted folder into the project_UKF directory. 
      * Within the folder run simulator `term2_sim`; if successful the following window should appear:
      ![alt text][image1]

---

## Other Important Dependencies

* cmake >= 3.5
* make >= 4.1 
* gcc/g++ >= 5.4

---

## Build the code

1. From the project_udacity folder change to folder created from cloning `cd CarND-Unscented-Kalman-Filter-Project`
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make` 

---

## Usage

After running the script, confirming the operation of the simulator and building the code the UKF program is ready to be run.

1. From terminal window; change to build folder of project `cd ~/project_udacity/CarND-Unscented-Kalman-Filter-Project/build/`
2. Run UKF: `./UnscentedKF `
3. Message appears `Listening to port 4567` the UKF is now running and waiting for connection from the simulator
4. Run the simulator `term2_sim`
5. Press 'Select' in the simulator window.
6. In the UKF terminal window `Connected!!!` will now appear.
7. The UKF is now fully operational.

        * Select the dataset 1 or 2
        * Press Start

The Animation will start and the vehicle can be seen moving around the screen.

![alt text][image2]

* Red markers are Laser measurements
* Blue markers are Radar measurements
* Green markers are UKF predictions

---

## Results

From the Simulator window the RMSE can be seen to evaluate the performance of the UKF for the selected dataset. 

The output positions px, py, vx and vy RMSE should be <= [.09, .10, .40, .30].

To achieve the required result longitudinal and yaw acceleration noises were tested to understand which values produced the best results. The Covariance Matrix P initialisation values were also modified to achieve the result.

Table 1: Noise Parameter Tuning

Tables show the Longitudinal and Yaw Acceleration noise parameters.
The first column of position values are results for dataset1 and next set are for dataset2.

![alt text][image3]

---

## Conclusion

Almost all of the experiments on dataset 1 would have met the RMSE target requirement. 
Evaluating the performance against dataset 2 did not meet the criteria. Further tuning was carried out tuning the value of P Matrix at initialisation.

Tuning the parameters to std_a = 1.0, std_yawdd = 0.5 and setting P matrix to ([identity] * 2) produced the best results.

To validate the tuned parameters I performed a consistency check on the filter; This helps to understand if the filter is under estimating or over estimating uncertainty. 

The consistency check used is called Normal Innovation Squared (NIS).
This check is the difference between the predicted measurement and actual measurement, normalised to produce a scalar result. This result is then evaluated against a chi-squared distribution.

A large amount of values above this threshold would indicate predicted values are outside the covariance area and under-estimating the uncertainty. If the majority of values are small, then this would indicate the estimations are consistently close to the mean and over estimating the uncertainty in the system.

Laser is 2 degrees of freedom, 95% chi-squared = 5.991
The graphs below shows the results for both datasets.

![alt text][image4]

Radar is 3 degrees of freedom, 95% chi-squared = 7.815
The graphs below shows the results for both datasets.

![alt text][image5]

For both laser and radar the consistency check results appear to be good. They are not above the chi-squared value and do not gather near the 0 axis.


---

## License

For License information please see the [LICENSE](./LICENSE) file for details

---

