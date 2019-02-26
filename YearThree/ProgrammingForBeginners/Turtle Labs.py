#Ryan Lebeau
#Turtle Exercise
#14/10/2015
#v1.0

import turtle
import math

#Arrow
#pen code
t=turtle.Pen()
t.pencolor("red")
t.hideturtle()
#arrow code
t.left(90)
t.forward(100)
t.right(90)
t.forward(50)
t.left(135)
t.forward(100)
t.left(90)
t.forward(100)
t.left(135)
t.forward(50)
t.right(90)
t.forward(100)
t.left(90)
t.forward(42)

#Star
#pen code
t.pencolor("blue")
t.hideturtle()
t.up()
t.goto(-100,200)
t.down()
#star loop
for i in range (8):
    t.left(135)
    t.forward(100)
#clear screen
t.clear()

#Person
#pen code
t=turtle.Pen()
t.pencolor("black")
t.hideturtle()
t.speed(8)
t.pensize(8)
#circle
t.circle(80)
#directions and pen colour
t.pensize(3)
t.up()
t.pencolor("blue")
t.left(90)
t.forward(110)
t.left(90)
t.forward(33)
t.down()
t.pensize(5)
t.circle(10)
t.left(180)
t.up()
t.forward(60)
t.right(90)
t.forward(10)
t.down()
t.circle(10)
t.up()
t.forward(60)
t.right(90)
t.down()
t.pencolor("red")
t.forward(55)
t.up()
t.right(90)
t.forward(100)
t.right(90)
t.forward(15)
t.left(90)
t.forward(15)
t.down()
t.pencolor("yellow")
#hair loop
for i in range(6):
    t.forward(20)
    t.left(180)
    t.up()
    t.forward(20)
    t.left(90)
    t.forward(5)
    t.left(90)
    t.down()
#pupils
t.up()
t.goto(-30,96)
t.down()
t.pensize(4)
t.pencolor("black")
t.forward(1)
t.up()
t.right(90)
t.forward(63)
t.down()
t.forward(1)
#body
t.up()
t.goto(0,0)
t.right(90)
t.down()
t.pensize(8)
t.forward(200)
t.left(45)
t.forward(100)
t.left(180)
t.forward(100)
t.left(90)
t.forward(100)
t.left(180)
t.forward(100)
t.left(45)
t.forward(120)
t.left(90)
t.forward(80)
t.left(180)
t.forward(165)
#clear screen
t.clear()

#Shapes
user_input = input("What shape do you want? Circle, Triangle, Star, or Square.")
#pen code
t=turtle.Pen()
t.pencolor("green")
t.hideturtle()
t.hideturtle()
t.pensize(8)
if user_input.lower() == "circle":
    t.circle(50)
elif user_input.lower() == "triangle":
    t.forward(100)
    t.left(135)
    t.forward(100)
    t.left(90)
    t.forward(100)
    t.left(135)
    t.forward(50)
#star loop
elif user_input.lower() == "star":
    for i in range (8):
        t.left(135)
        t.forward(100)
elif user_input.lower() == "square":
    for i in range(4):
        t.forward(100)
        t.left(90)
#if something is spelled incorrectly
else:
    print ("That is not a vaild shape.")
#clear screen
t.clear()

#Square Wave
#pen code
t = turtle.Pen()
t.hideturtle()
t.pensize(3)
t.pencolor("orange")
#starting position
t.up()
t.goto(-200,0)
t.down()
#variable that will add to the angle
x=0
#code that draws the square wave
for i in range(14):
    t.left(45+x)
    t.forward(25)
    t.right(90)
    t.forward(25)
    x=45
#clear screen
t.clear()

#Sine Wave
#pen code
t = turtle.Pen()
t.hideturtle()
t.pensize(1)
t.pencolor("red")
#loop for sine wave
for i in range(20):
    y = math.sin(i)
    y *= 10
    t.goto(i*10,y)
#clear screen
t.clear()

#Recreating Image
#background colour
turtle.bgcolor("black")
#pen code 1
t = turtle.Pen()
t.hideturtle()
t.speed(0)
t.pensize(1)
#pen code 2
b = turtle.Pen()
b.hideturtle()
b.speed(1000000)
b.pensize(1)
#variables for angle increase
x=0
#variable for length increase
length=0
#variable for start of other images
done_1= True
done_2= True
done_3= True
done_4= True
#first pen goto
t.up()
t.goto(0,200)
t.down()
#loop for image
for i in range (10000):
    #first image
    t.right(45+x)
    t.pencolor("aquamarine")
    t.forward(length)
    t.right(91)
    t.pencolor("orange")
    t.forward(length)
    #second image
    while done_1:
        b.goto(0,-200)
        done_1 = False
    b.right(45+x)
    b.pencolor("orange")
    b.forward(length)
    b.right(91)
    b.pencolor("aquamarine")
    b.forward(length)
    length+=3
    x=45











