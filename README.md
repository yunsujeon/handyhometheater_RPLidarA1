# handyhometheater_RPLidarA1
#### What is this?
This is a kind of speaker. surround speaker needs many speakers.  
3.1ch : 3speakers & 1upper speaker  
5.1ch : 5speakers & 1upper speaker  
and it must have fixed location. This robot make their location with mapping.  
Mapping is executed with rplidar A1 [hector mapping](https://github.com/NickL77/RPLidar_Hector_SLAM/tree/master/rplidar_ros)  
When they recognize their location, they'll go their location with three motors and omni wheels.  
#### Hardware Components
6 robots  
PC, Beaglebone Blue, RPLidar A1, omni wheels, motors with encoders, bluetooth speaker, PSD, 18650batteries  

## RPLIDAR ROS package
ROS node and test application for RPLIDAR:  
[rplidar roswiki](http://wiki.ros.org/rplidar)  
[rplidar HomePage](http://www.slamtec.com/en/Lidar)  
[rplidar Tutorial](https://github.com/robopeak/rplidar_ros/wiki)  

#### How to build rplidar ros package 
1) clone this project to your catkin's workspace src folder  
2) Running catkin_make to build rplidarNode and rplidarNodeClient  

#### How to run rplidar ros package
roslaunch rplidar_ros view_rplidar.launch  

## RPLidar Hector SLAM
Using Hector SLAM without odometry data on a ROS system with the RPLidar A1.  
1. Install ROS full desktop version (Kinetic)  
2. Create a catkin workspace  
3. Clone hector_slam  
4. In your catkin workspace run source /devel/setup.bash  
5. Run chmod 666 /dev/ttyUSB0 or the serial path to your lidar  
6. Run roslaunch rplidar_ros rplidar.launch  
7. Run roslaunch hector_slam_launch tutorial.launch  
8. RVIZ should open up with SLAM data  

#### Sources
[RPLidar](https://github.com/robopeak/rplidar_ros)  
[Hector_SLAM](https://github.com/tu-darmstadt-ros-pkg/hector_slam)  

## Map conversion
After hector_slam, you've got an image file. To active robots, we'll conversion this image file to text file.  
I conversion like this :  
contourlines - 2 / white places - 0 / else - 1  
You can complie this c file wite gcc complier.  

## Active
Finally we are ready to active 6 robots. Complie this c file and active robots  
#### ssh communication
Before active you will connect 6 robots to PC with ssh communication.  
BeagleBone Blue have wifi. On PC you will connect 6 BeagleBone Blue manually.

