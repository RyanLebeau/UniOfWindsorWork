#Ryan Lebeau
#Turtle Project (Fullscreen)
#05/11/2015
#v1.7.4

import turtle
import random

#creates the pen
t = turtle.Pen()

#---Class Creations---
class Line():
    """Class that will create a line.
    Also, this is the main parent class"""
    def __init__(self, colour):
        """Constructor that changes the pen colour."""
        t.pencolor(colour)
    def __str__(self):
        """Description of the used class and it's methods."""
        return "This class creates a line. The four methods found within are goto, draw, rotate right and left."
    def goto(self, x, y):
        """This allows a position to be set for the line."""
        t.up()
        t.goto(x,y)
        t.down()
    def draw(self, length):
        """Draws the line."""
        t.forward(length)
    def rotate_left(self, angle):
        """rotate_left allows the shell to turn left."""
        t.left(angle)
    def rotate_right(self, angle):
        """rotate_right allows the shell to turn right."""
        t.right(angle)

class Square(Line):
    """Class that will create a square.
    Is the child class of Line"""
    def __str__(self):
        """Description of the used class and it's methods."""
        return "This class creates a Square. The four methods found within are goto, draw, rotate right and left."
    def draw(self, length):
        """Draws the square."""
        for i in range(4):
            t.forward(length)
            t.left(90)

class Rectangle(Line):
    """Class that will create a rectangle.
    Is the child class of Line"""
    def __str__(self):
        """Description of the used class and it's methods."""
        return "This class creates a Rectangle. The four methods found within are goto, draw, rotate right and left."
    def draw(self, length, width):
        """Draws the rectangle."""
        t.begin_fill()
        for i in range(12):
            t.forward(length)
            t.left(90)
            t.forward(width)
            t.left(90)
        t.end_fill()
        
class Circle(Line):
    """Class that will create a circle.
    Is the child class of Line"""
    def __str__(self):
        """Description of the used class and it's methods."""
        return "This class creates a Circle. The four methods found within are goto, draw, rotate right and left."   
    def draw(self, radius):
        """Draws the circle."""
        t.circle(radius)

class Triangle(Line):
    """Class that will create a triangle.
    Is the child class of Line"""
    def __str__(self):
        """Description of the used class and it's methods."""
        return "This class creates a Triangle. The four methods found within are goto, draw, rotate right and left."
    def draw(self, length):
        """Draws the triangle."""
        for i in range(3):
            t.left(120)
            t.forward(length)

class Snow_person():
    """This class creates three circles for the snow man/woman stencil.
    There is a goto method to set the position, and three parameters
    within the draw function for unique sizes."""
    def __init__(self, colour):
        """The constructor hides the turtle and sets the colour."""
        t.hideturtle()
        self.colour = colour
        self.x = 0
        self.y = 0
    def goto(self, x, y):
        """Makes it able to set a position for the bottom of the snow person."""
        self.x = x
        self.y = y
        t.up()
        t.goto(self.x, self.y)
        t.down()
    def draw(self, pen):
        """Creates a snow person with three independant circle sizes.
        The circles are offset if the previous goto method is called.
        """
        t.pensize(pen)
        circle_base = Circle(self.colour)
        circle_base.draw(80)
        circle_middle = Circle(self.colour)
        circle_middle.goto(self.x, self.y + 160)
        circle_middle.draw(60)
        circle_top = Circle(self.colour)
        circle_top.goto(self.x, self.y + 160 + 120)
        circle_top.draw(35)

class Snowman(Snow_person):
    """The class that adds features to the base snow_person.
    The methods found within create the top hat, eyes, nose, mouth,
    buttons and arms.
    """
    def draw(self, length, height):
        """This method creates the top hat.
        It takes in a length and height parameter which
        are used in the previously created Rectangle class.
        """
        rectangle_hat = Rectangle("black")
        rectangle_hat.draw(length,height)
    def draw_eyes(self, radius, pen):
        """This method draws two eyes.
        It takes a radius for the eye size and
        the pensize that is required."""
        t.pensize(pen)
        eye_left_outer = Circle("black")
        eye_left_outer.draw(radius)
        eye_left_inner = Circle("white")
        t.begin_fill()
        eye_left_inner.draw(radius-1)
        t.end_fill()
        eye_left_pupil = Circle("blue")
        eye_left_pupil.draw(2)
    def draw_mouth(self, radius):
        """This method draws the mouth.
        It takes in a radius parameter for the six circle mouth."""
        mouth_circle = Circle("black")
        t.begin_fill()
        mouth_circle.draw(radius)
        t.end_fill()
    def draw_nose(self, length):
        """This method draws the nose.
        It takes in a side length for the equilateral triangle."""
        nose_triangle = Triangle("orange")
        nose_triangle.draw(length)
    def draw_button(self, length, colour):
        """This method draws the three buttons.
        It takes in colour and a side length for the
        three drawn rectangles, tilted at a 45."""
        button_top = Square(colour)
        button_top.rotate_left(45)
        t.fillcolor(colour)
        t.begin_fill()
        button_top.draw(length)
        t.end_fill()
        button_top.rotate_right(45)
    def draw_arm_left(self, length, angle):
        """This method draws the left arms.
        It takes in a length and an angle to draw
        two seperate lines at varying angles."""
        t.pensize(4)
        arm_left_1 = Line("brown")
        arm_left_1.rotate_left(180)
        arm_left_1.rotate_right(angle)
        arm_left_1.draw(length)
        arm_left_2 = Line("brown")
        arm_left_2.rotate_right(20)
        arm_left_2.draw(length)
        arm_left_2.rotate_left(20+angle)
        t.pensize(1)
    def draw_arm_right(self, length, angle):
        """This method draws the right arms.
        It takes in a length and an angle to draw
        two seperate lines at varying angles."""
        t.pensize(4)
        arm_right_1 = Line("brown")
        arm_right_1.rotate_right(180)
        arm_right_1.rotate_right(angle)
        arm_right_1.draw(length)
        arm_right_2 = Line("brown")
        arm_right_2.rotate_right(20)
        arm_right_2.draw(length)
        arm_right_2.rotate_left(20+angle)
        t.pensize(1)

class Snowgirl(Snowman):
    """The class that adds features to the base snow_person.
    The methods found within create the pink hat, eyes, nose, mouth,
    coat, buttons and arms.
    """
    def draw(self, length):
        """This method dreats a triangular hat.
        It makes a pink hat using the entered
        length.""" 
        triangle_hat = Triangle("pink")
        t.fillcolor("pink")
        t.begin_fill()
        triangle_hat.draw(length)
        t.end_fill()
        t.fillcolor("black")
        t.pen(3)
        triangle_hat_outline = Triangle("black")
        triangle_hat_outline.draw(length)
        t.pen(1)
    def draw_eyes(self, radius, pen):
        """This method draws two eyes.
        It takes a radius for the eye size and
        the pensize that is required."""
        t.pensize(pen)
        eye_left_outer = Circle("black")
        eye_left_outer.draw(radius)
        eye_left_inner = Circle("white")
        t.begin_fill()
        eye_left_inner.draw(radius-1)
        t.end_fill()
        eye_left_pupil = Circle("dark green")
        eye_left_pupil.draw(2)
    def draw_coat(self, colour):
        """This method draws a coat.
        It takes in a colour parameter for the coat."""
        coat_circle = Circle(colour)
        t.fillcolor(colour)
        t.begin_fill()
        coat_circle.draw(60)
        t.end_fill()
        t.forward(-5)
        coat_centre = Rectangle("white")
        t.fillcolor("white")
        coat_centre.draw(10,120)
    def draw_buttons(self, radius):
        """This method will draw coat buttons.
        It takes in a radius for each button size."""
        button_circle = Circle("black")
        t.fillcolor("burlywood")
        t.begin_fill()
        button_circle.draw(5)
        t.end_fill()
    def draw_arm_left(self, length, angle):
        """This method draws the left arms.
        It takes in a length and an angle to draw
        two seperate lines at varying angles."""
        t.pensize(4)
        arm_left_1 = Line("brown")
        arm_left_1.rotate_left(180)
        arm_left_1.rotate_right(angle)
        arm_left_1.draw(length)
        arm_left_2 = Line("brown")
        arm_left_2.rotate_right(20)
        arm_left_2.draw(50)
        arm_left_2.rotate_left(20+angle)
        t.pensize(1)
    def draw_arm_right(self, length, angle):
        """This method draws the right arms.
        It takes in a length and an angle to draw
        two seperate lines at varying angles."""
        t.pensize(4)
        arm_right_1 = Line("brown")
        arm_right_1.rotate_left(180)
        arm_right_1.rotate_left(angle)
        arm_right_1.draw(length)
        arm_right_2 = Line("brown")
        arm_right_2.rotate_left(20)
        arm_right_2.draw(50)
        arm_right_2.rotate_left(20+angle)
        t.pensize(1)

#---Function Definitions---    
def complete_snowman():
    """This draws the complete snowman using the Snowman class."""
    #one body is drawn filled in white
    snow_person_1 = Snow_person("black")
    snow_person_1.goto(-180,-200)
    t.fillcolor("white")
    t.begin_fill()
    snow_person_1.draw(4)
    t.end_fill()
    #two rectangles are used for the hat
    snow_man = Snowman("black")
    snow_man.goto(-230,145)
    t.fillcolor("black")
    snow_man.draw(100,30)
    snow_man.goto(-205,175)
    snow_man.draw(50,40)
    #two eyes
    snow_man.goto(-195,120)
    snow_man.draw_eyes(5, 2)
    snow_man.goto(-165,120)
    snow_man.draw_eyes(5, 2)
    #six circle mouth
    snow_man.goto(-197,100)
    snow_man.draw_mouth(2)
    snow_man.goto(-190,95)
    snow_man.draw_mouth(2)
    snow_man.goto(-183,92)
    snow_man.draw_mouth(2)
    snow_man.goto(-176,92)
    snow_man.draw_mouth(2)
    snow_man.goto(-169,95)
    snow_man.draw_mouth(2)
    snow_man.goto(-162,100)
    snow_man.draw_mouth(2)
    #carrot nose
    snow_man.goto(-177,110)
    t.fillcolor("orange")
    t.begin_fill()
    snow_man.draw_nose(7)
    t.end_fill()
    #three coloured buttons
    snow_man.goto(-180, 45)
    snow_man.draw_button(10, "dark green")
    snow_man.goto(-180, 15)
    snow_man.draw_button(10, "blue2")
    snow_man.goto(-180, -15)
    snow_man.draw_button(10, "red")
    #two wooden arms
    snow_man.goto(-220,20)
    snow_man.draw_arm_left(50,25)
    snow_man.goto(-140,20)
    snow_man.draw_arm_right(50,25)

def complete_snowgirl():
    """This draws the complete snowgirl using the Snowgirl class."""
    #one body is drawn filled in white
    snow_person_2 = Snow_person("black")
    snow_person_2.goto(180,-200)
    t.fillcolor("white")
    t.begin_fill()
    snow_person_2.draw(4)
    t.end_fill()
    t.pensize(2)
    #two triangular hats a re-drawn for a black outline
    snowgirl = Snowgirl("black")
    snowgirl.goto(229,139)
    snowgirl.draw(100)
    #two eyes
    snowgirl.goto(165,120)
    snowgirl.draw_eyes(5, 2)
    snowgirl.goto(196,120)
    snowgirl.draw_eyes(5, 2)
    #six circle mouth
    snowgirl.goto(163,100)
    snowgirl.draw_mouth(2)
    snowgirl.goto(170,95)
    snowgirl.draw_mouth(2)
    snowgirl.goto(177,92)
    snowgirl.draw_mouth(2)
    snowgirl.goto(184,92)
    snowgirl.draw_mouth(2)
    snowgirl.goto(191,95)
    snowgirl.draw_mouth(2)
    snowgirl.goto(198,100)
    snowgirl.draw_mouth(2)
    #carrot nose
    snowgirl.goto(184,110)
    t.fillcolor("orange")
    t.begin_fill()
    snowgirl.draw_nose(7)
    t.end_fill()
    #purple overcoat
    snowgirl.goto(180,-40)
    snowgirl.draw_coat("purple")
    #ten wooden buttons on the coat
    snowgirl.goto(165,55)
    snowgirl.draw_buttons(7)
    snowgirl.goto(195,55)
    snowgirl.draw_buttons(7)
    snowgirl.goto(165,35)
    snowgirl.draw_buttons(7)
    snowgirl.goto(195,35)
    snowgirl.draw_buttons(7)
    snowgirl.goto(165,15)
    snowgirl.draw_buttons(7)
    snowgirl.goto(195,15)
    snowgirl.draw_buttons(7)
    snowgirl.goto(165,-5)
    snowgirl.draw_buttons(7)
    snowgirl.goto(195,-5)
    snowgirl.draw_buttons(7)
    snowgirl.goto(165,-25)
    snowgirl.draw_buttons(7)
    snowgirl.goto(195,-25)
    snowgirl.draw_buttons(7)
    #two wooden arms
    snowgirl.goto(120,20)
    snowgirl.draw_arm_left(20,25)
    snowgirl.goto(240,20)
    snowgirl.draw_arm_right(20,25)

def ground():
    """Creates a snowy ground drawn by one large rectangle."""
    ground_snow = Rectangle("white")
    ground_snow.goto(1000,-500)
    t.fillcolor("white")
    t.begin_fill()
    ground_snow.draw(300,2000)
    t.end_fill()

def snow():
    """Creates randomized snowflakes on the screen."""
    t.pensize(5)
    snowflake = Line("white")
    #draws 250 snowflakes at random places on the screen
    for i in range(250):
        snowflake.goto(random.randrange(-1000,1000),random.randrange(-200,800))
        snowflake.draw(2)
    t.pensize(1)

def background_rectangles():
    """Creates two background rectangles for the snow people.
    This is done to draw over any snow flakes that are
    positioned within the snow people.
    """
    #creating the first rectangle
    bg_rectangle = Rectangle("grey85")
    bg_rectangle.goto(-310,-200)
    t.fillcolor("grey85")
    t.begin_fill()
    #draws the rectangle
    bg_rectangle.draw(255,428)
    t.end_fill()
    #creating the second rectangle
    bg_rectangle_2 = Rectangle("grey85")
    bg_rectangle.goto(50,-200)
    t.begin_fill()
    #draws the rectangle
    bg_rectangle_2.draw(255,428)
    t.end_fill()

def tree_left():
    """This function creates a tree.
    This is the tree on the left of the snow people."""
    #rotate turtle right
    t.right(90)
    t.up()
    #goto the starting position of the tree stump
    t.goto(-615,-200)
    t.down()
    #changes the colour of fill to tree brown
    t.fillcolor("brown")
    #creates the tree stump rectangle
    base_log = Rectangle("brown")
    t.begin_fill()
    base_log.draw(25,50)
    t.end_fill()
    t.fillcolor("dark green")
    #variable that changes the x
    x_offset=0
    #variable that changes the y
    y_offset=0
    #variable that changes the size of triangle
    size_change=0
    #for loop creating 5 triangles
    for i in range(5):
        #creates tree triangle
        tree_base = Triangle("dark green")
        t.up()
        #sets position of beginning triangle and the offsets
        t.goto(-400-x_offset,-150+y_offset)
        t.down()
        #draws and fills the tree green
        t.begin_fill()
        tree_base.draw(400-size_change)
        t.end_fill()
        #adds to all the offset variables
        x_offset+=30
        y_offset+=100
        size_change+=60

def tree_right():
    """This function creates a tree.
    This is the tree on the left of the snow people."""
    t.up()
    #goto the starting position of the tree stump
    t.goto(595,-200)
    t.down()
    #changes the colour of fill to tree brown
    t.fillcolor("brown")
    #creates the tree stump rectangle
    base_log = Rectangle("brown")
    t.begin_fill()
    base_log.draw(25,50)
    t.end_fill()
    t.fillcolor("dark green")
    #variable that changes the x
    x_offset=0
    #variable that changes the y
    y_offset=0
    #variable that changes the size of triangle
    size_change=0
    #for loop creating 5 triangles
    for i in range(5):
        #creates tree triangle
        tree_base = Triangle("dark green")
        t.up()
        #sets position of beginning triangle and the offsets
        t.goto(800-x_offset,-150+y_offset)
        t.down()
        #draws and fills the tree green
        t.begin_fill()
        tree_base.draw(400-size_change)
        t.end_fill()
        #adds to all the offset variables
        x_offset+=30
        y_offset+=100
        size_change+=60
        

#sets the background colour
turtle.bgcolor("grey85")
#hides the turtle shell
t.hideturtle()
#sets the speed for turtle
t.speed(0)
#calls the snow function
snow()
#calls the back ground rectangles
background_rectangles()
#draws the snowman
complete_snowman()
#draws the snowgirl
complete_snowgirl()
#creates the snowy ground
ground()
#draws the left and right trees
tree_left()
tree_right()
#grey drop shadow for Merry Christmas!
t.up()
t.goto(-190,-310)
t.down()
t.pencolor("grey85")
t.write("Merry Christmas!", font=("Century", 30, "italic"))
#black base text for Merry Christmas!
t.up()
t.goto(-195,-300)
t.down()
t.pencolor("black")
t.write("Merry Christmas!", font=("Century", 30, "italic"))
#grey drop shadow for From Ryan Lebeau
t.up()
t.goto(-190,-410)
t.down()
t.pencolor("grey85")
t.write("From Ryan Lebeau", font=("Century", 30, "italic"))
#black base text for From Ryan Lebeau
t.up()
t.goto(-195,-400)
t.down()
t.pencolor("black")
t.write("From Ryan Lebeau", font=("Century", 30, "italic"))




