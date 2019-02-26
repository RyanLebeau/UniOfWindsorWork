'''
Ryan Lebeau
23/02/2019
RyanLebeauAssign2.py
COMP2067
'''

#------Q1
'''
Input A:
purple

Input B:
Error: The two colors you entered are the same.

Input C:
orange

Input D:
Error: The second color you entered is invalid.
'''

#------Q2
#get user input as int
secs = int(input("Enter the number of second: "))
#print the base seconds amount
print(secs,"seconds are equal to:")

#each statement will determine seconds,mins,hours then print
#first if is in case seconds can not be converted to minutes
if secs < 60:
    print(secs,"seconds.")
#second is if there are not enough seconds to convert to hour
elif secs >= 60 and secs < 3600:
    mins = int(secs/60)
    secsM = secs % 60
    print(mins,"full minute(s) and",secsM,"seconds.")
#for both minutes an hour conversion
elif secs >= 3600:
    mins = int(secs/60)
    secsM = secs % 60
    print(mins,"full minute(s) and",secsM,"seconds.")
    hours = int(secs/3600)
    secsH = secs % 3600
    print(hours,"full hour(s) and",secsH,"seconds.")

