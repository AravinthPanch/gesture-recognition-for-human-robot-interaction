__author__ = 'Aravinth Panchadcharam'
__email__ = "me@aravinth.info"
__project__ = 'Gesture Recognition For Human-Robot Interaction'
__date__ = '09/06/15'

from naoqi import ALProxy


class RobotAngle():
    def __init__(self, host_name, port):
        self.motionProxy = ALProxy("ALMotion", host_name, port)

        self.head_joints = ["HeadPitch", "HeadYaw"]
        self.hand_joints = ["LShoulderRoll", "LShoulderPitch", "LElbowRoll", "LElbowYaw", "RShoulderRoll",
                            "RShoulderPitch",
                            "RElbowRoll",
                            "RElbowYaw"]

    def get_head_angles(self):
        sensor_angles = self.motionProxy.getAngles(self.head_joints, True)
        print "Head Pitch and Yaw:"
        print str(sensor_angles)

    def get_hand_angles(self):
        sensor_angles = self.motionProxy.getAngles(self.hand_joints, True)
        print "Shoulder and Elbow:"
        print str(sensor_angles)


if __name__ == "__main__":
    robotAngle = RobotAngle("127.0.0.1", 52102)
    robotAngle.get_hand_angles()
