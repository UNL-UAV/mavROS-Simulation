# mavROS-Simulation

### Information

Repository for getting the simulation up and running. This is using ros and gazebo simulation software.

### Prerequisite

The enviroment you need for the simulation software needs to be ubuntu, any version later than 18.04 should work. The list of things that need to be installed before you can begin using the simulation is in the list below:

1.	ROS
2.	mavROS
3.	geographicLib
4.	gazebo
5.	px4 firmware
6.	GSTREAMER 1

If you have not used ROS before then I would suggest reading through and doing the tutorials. Once you have a basic understanding you should come back and begin using the simulation. 
A small preview of how this simulation works is in the diagram below:
![mavROS simulation layout](https://dev.px4.io/v1.9.0/assets/simulation/px4_sitl_overview.png)

### Directions for Installation

-	First you should install ROS, you can use any version that you want to. This tutorial was written using ubuntu 20.04 and the newest realease of ROS, Noetic.
-	You can find the instructions to install [ROS](http://wiki.ros.org/noetic/Installation)
-	The next things that you need to install will be [mavROS](https://dev.px4.io/v1.9.0/en/ros/mavros_installation.html).
-	You will need to install mavROS by using the commands below
```
sudo apt-get install ros-version-mavros ros-version-mavros-extras
```
-	Replace version above with your version of mavros. for example if you are using noetic, use *ros-version-mavros*
-	Next you are going to need to get the geagraphic lib, you need this for mavros so that you can send long/lat. The command is below:
```
wget https://raw.githubusercontent.com/mavlink/mavros/master/mavros/scripts/install_geographiclib_datasets.sh
sudo chmod +x install_geographiclib_datasets.sh
sudo ./install_geographiclib_datasets.sh
```
-	You do not need to explicitly install gazebo unless you did not install the full desktop version of ROS
-	The px4 firmware is what is need to simulate the flight controller, and ROS is what is going to be controlling the simulated flight controller.
-	To install the px4 firmware you can fork the repository from our github page or just pull it if you aren't planning on messing with the firmware code, the command is below:
```
git clone git@github.com:UNL-UAV/Firmware.git
cd Firmware
```
-	next you are going to have to install some package dependencies so that you can make the simulation px4 flight controller, please run the commands below to be able to build.
```
sudo apt-get install libprotobuf-dev libprotoc-dev protobuf-compiler libeigen3-dev libxml2-utils python-rospkg python-jinja2
sudo apt-get install libgstreamer-plugins-base1.0-dev gstreamer1.0-plugins-bad gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-ugly -y
```
-	Now you can run the simulation by using the command below (be sure you're in the Firmware directory that was pulled from Github). It is going to take a really long time to build the first time but afterwards it shouldn't take super long.
-   Also there might be errors that come up because of some other dependencies that weren't included in the installation process, they should all be explicit instructions to install a certain dependency, you should be able to follow the error and resolve it.
```
make px4_sitl gazebo
```

### Directions for Running

To understand how to run, it is best to understand the logic of how the simulation is running. Look at the diagram above one more time to try and understand it.
Theres three different things that need to be running for the simulation to work. First you need to run the gazebo simulation and also connect it to the sitl px4 controller. Then you need to run ROS to create the connection and control the pixhawk. Then you need to run ROS nodes to populate certain topics to control the simulation.

-   Run the gazebo simulation and run the sitl pixhawk.
-   This needs to be done from the Firmware repository directory as all the make files for this command are there.
```
make px4_sitl gazebo
```
-   To run the ROS simulation you need to launch ROS and connect it to your computer, or you can connect it two whichever computer is running the px4 simulation.
```
roslaunch mavros px4.launch fcu_url:="udp://:14540@127.0.0.1:14557"
```
-   Then you can run nodes to control your drone. At thsis point all the information between ROS and the sitl pixhawk should be working. This means that you can not run nodes to populate topics to control the drone. If you have not already built nodes, there is an example takeoff already supplied in the repository.
-   To run the takeoff node you have to move to this repository, ..../mavROS-Simulation then run the commands below.
-   If for some reason the code does not compile after catkin_make, check the CMakeLists.txt to make sure the right version of everything is included.
```
catkin_make
source devel/setup.bash
rosrun examples takeoff_example
```