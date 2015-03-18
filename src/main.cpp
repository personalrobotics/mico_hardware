#include <MicoRobot.h>
#include <iostream>
#include "std_msgs/String.h"
#include <sstream>

int main(int argc, char* argv[])
{
    ROS_INFO_STREAM("MICO HARDWARE starting");
  ros::init(argc, argv, "mico_hardware");
  ros::NodeHandle nh;

  MicoRobot robot(nh);
  controller_manager::ControllerManager cm(&robot);

  ros::AsyncSpinner spinner(1);
  spinner.start();


  double delta = 0;

  while (ros::ok())
  {
     robot.read();
      if (robot.eff_stall == true){
            cm.update(robot.get_time(), robot.get_period(), true);
            sleep(1);
      }
      else{
          cm.update(robot.get_time(), robot.get_period());
      }

     robot.write();
     usleep(10000);
  }

  return 0;
}
