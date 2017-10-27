import controllerInteractive as robot


if __name__ == "__main__":

    print(robot.rotate(degrees = -90,
                 power = 50,
                 spinDirection = "CW"))

    print(robot.move(direction = "N",
               power = 50,
               time = 1))
