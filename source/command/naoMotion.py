__author__ = 'Aravinth Panchadcharam'
__email__ = "me@aravinth.info"
__project__ = 'Gesture Recognition For Human-Robot Interaction'
__date__ = '09/06/15'

import time
from naoqi import ALProxy


class NaoMotion():
    def __init__(self, host_name, port):
        self.motionProxy = ALProxy("ALMotion", host_name, port)
        self.postureProxy = ALProxy("ALRobotPosture", host_name, port)
        self.ttsProxy = ALProxy("ALTextToSpeech", host_name, port)

        # self.disable_smart_stiffness()

        # Head Motion
        self.head_joints = ["HeadPitch", "HeadYaw"]
        self.head_angles = []

        # Hand Motion
        self.hand_joints = ["LShoulderRoll", "LShoulderPitch", "LElbowRoll", "LElbowYaw",
                            "RShoulderRoll",
                            "RShoulderPitch",
                            "RElbowRoll",
                            "RElbowYaw"]
        self.hand_angles = []
        self.hand_speed = 0.2

        # Body Motion
        self.head_angles = []
        self.forward_direction = 0
        self.sideward_diretion = 0
        self.rotation = 0
        self.step_frequency = 1.0
        self.walk_duration = 5
        self.turn_duration = 4

        # Is the robot sleeping?
        self.wake_up()

    # If robot is sleeping, wake it up
    def wake_up(self):
        if self.motionProxy.robotIsWakeUp() is False:
            self.motionProxy.wakeUp()
            # time.sleep(3)
            # self.postureProxy.goToPosture("Stand", 0.5)
            time.sleep(3)
            self.set_head()
        else:
            self.set_head()

    # Set the head to look at the user
    def set_head(self):
        self.head_angles = [-0.3145120143890381, -0.013848066329956055]
        self.motionProxy.setAngles(self.head_joints, self.head_angles, 0.1)
        time.sleep(2)

    # Reset the head
    def reset_head(self):
        self.head_angles = [0.06438612937927246, -4.1961669921875e-05]
        self.motionProxy.setAngles(self.head_joints, self.head_angles, 0.1)
        time.sleep(2)

    # Reset the hand
    def reset_hand(self):
        self.hand_angles = [0.2638061046600342, 1.4097040891647339, -1.0123980045318604,
                            -1.3806419372558594, -0.2623560428619385, 1.418992042541504,
                            1.0170841217041016, 1.3774900436401367]
        self.motionProxy.setAngles(self.hand_joints, self.hand_angles, self.hand_speed)

    # Wake up using click gesture
    def click_wake_up(self):
        if self.motionProxy.robotIsWakeUp() is False:
            self.motionProxy.wakeUp()
            self.set_head()
        else:
            self.set_head()

    # Set the robot to sleep
    def sleep_robot(self):
        self.motionProxy.rest()

    def get_smart_stiffness(self):
        print self.motionProxy.getSmartStiffnessEnabled()

    def disable_smart_stiffness(self):
        self.motionProxy.setSmartStiffnessEnabled(False)

    # Motion based on given Gesture
    def gesture_to_motion(self, sign):
        if sign == "Walk":
            self.reset_head()
            self.forward_direction = 1.0
            self.sideward_diretion = 0.0
            self.rotation = 0.0
            self.motionProxy.moveToward(self.forward_direction, self.sideward_diretion,
                                        self.rotation,
                                        [["Frequency", self.step_frequency]])

            time.sleep(self.walk_duration)
            self.motionProxy.stopMove()
            time.sleep(2)

            self.set_head()

        elif sign == "Turn Right":
            self.reset_head()
            self.forward_direction = 0.0
            self.sideward_diretion = 0.0
            self.rotation = 1.0
            self.motionProxy.moveToward(self.forward_direction, self.sideward_diretion,
                                        self.rotation,
                                        [["Frequency", self.step_frequency]])

            time.sleep(self.turn_duration)
            self.motionProxy.stopMove()
            time.sleep(2)

            self.set_head()

        elif sign == "Turn Left":
            self.reset_head()
            self.forward_direction = 0.0
            self.sideward_diretion = 0.0
            self.rotation = -1.0
            self.motionProxy.moveToward(self.forward_direction, self.sideward_diretion,
                                        self.rotation,
                                        [["Frequency", self.step_frequency]])

            time.sleep(self.turn_duration)
            self.motionProxy.stopMove()
            time.sleep(2)

            self.set_head()

        elif sign == "Move Right":
            self.reset_head()
            self.forward_direction = 0.0
            self.sideward_diretion = 0.0
            self.rotation = 1.0
            self.motionProxy.moveToward(self.forward_direction, self.sideward_diretion,
                                        self.rotation,
                                        [["Frequency", self.step_frequency]])

            time.sleep(self.turn_duration)
            self.motionProxy.stopMove()
            time.sleep(2)

            self.forward_direction = 1.0
            self.sideward_diretion = 0.0
            self.rotation = 0
            self.motionProxy.moveToward(self.forward_direction, self.sideward_diretion,
                                        self.rotation,
                                        [["Frequency", self.step_frequency]])

            time.sleep(self.walk_duration)
            self.motionProxy.stopMove()
            time.sleep(2)

            self.set_head()

        elif sign == "Move Left":
            self.reset_head()
            self.forward_direction = 0.0
            self.sideward_diretion = 0.0
            self.rotation = -1.0
            self.motionProxy.moveToward(self.forward_direction, self.sideward_diretion,
                                        self.rotation,
                                        [["Frequency", self.step_frequency]])

            time.sleep(self.turn_duration)
            self.motionProxy.stopMove()
            time.sleep(2)

            self.forward_direction = 1.0
            self.sideward_diretion = 0.0
            self.rotation = 0
            self.motionProxy.moveToward(self.forward_direction, self.sideward_diretion,
                                        self.rotation,
                                        [["Frequency", self.step_frequency]])

            time.sleep(self.walk_duration)
            self.motionProxy.stopMove()
            time.sleep(2)

            self.set_head()

    # Hand gesture based on gesture
    def gesture_to_gesture(self, sign):
        if sign == "Walk":
            self.hand_angles = [1.061486005783081, -1.2839999198913574, -1.2256240844726562,
                                -0.2546858787536621,
                                -1.1029877662658691,
                                -1.2486340999603271, 1.2241740226745605, 0.26534008979797363]
            self.motionProxy.setAngles(self.hand_joints, self.hand_angles, self.hand_speed)

        elif sign == "Turn Left":
            self.hand_angles = [1.061486005783081, -1.5417118072509766, -1.0031940937042236,
                                -0.02151799201965332,
                                -1.1137261390686035,
                                0.24088001251220703, 0.05066394805908203, 0.19477605819702148]
            self.motionProxy.setAngles(self.hand_joints, self.hand_angles, self.hand_speed)

        elif sign == "Turn Right":
            self.hand_angles = [1.1443220376968384, -0.127363920211792, -0.10120201110839844,
                                -0.02151799201965332,
                                -1.1029877662658691,
                                -1.2486340999603271, 1.2241740226745605, 0.26534008979797363]
            self.motionProxy.setAngles(self.hand_joints, self.hand_angles, self.hand_speed)

        elif sign == "Move Right":
            self.hand_angles = [1.1136419773101807, -0.09361600875854492, -0.1349501609802246,
                                -0.01691603660583496,
                                -0.4939899444580078, 1.6690340042114258, 0.36513400077819824,
                                0.13648414611816406]
            self.motionProxy.setAngles(self.hand_joints, self.hand_angles, self.hand_speed)

        elif sign == "Move Left":
            self.hand_angles = [0.5061781406402588, 1.5247540473937988, -0.35584592819213867,
                                -0.023051977157592773,
                                -1.0845799446105957, 0.27309393882751465, 0.07367396354675293,
                                0.19170808792114258]
            self.motionProxy.setAngles(self.hand_joints, self.hand_angles, self.hand_speed)

    # Hand gesture based on gesture
    def gesture_to_speech(self, sign):
        self.ttsProxy.say(sign)


if __name__ == "__main__":
    # Test
    localhost = "127.0.0.1"
    localPort = 54351
    remoteNao = "nao5.local"
    remotePort = 9559
    # naoMotion = NaoMotion(localhost, localPort)
    naoMotion = NaoMotion(remoteNao, remotePort)

    # naoMotion.get_smart_stiffness()

    # sign = "Walk"
    # sign = "Turn Right"
    # sign = "Turn Left"
    # sign = "Move Right"
    # sign = "Move Left"

    # naoMotion.gesture_to_speech(sign)
    # naoMotion.gesture_to_motion(sign)
    # naoMotion.gesture_to_gesture(sign)

    # naoMotion.reset_hand()
    # naoMotion.reset_head()
    naoMotion.sleep_robot()
