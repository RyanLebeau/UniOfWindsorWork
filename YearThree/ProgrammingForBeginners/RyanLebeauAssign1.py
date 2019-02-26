'''
Ryan Lebeau
01/29/2019
RyanLebeauAssign1.py
COMP2067
'''
#---Q1
#gathering input and declaring variables
inches = int(input("Enter number of inches: "))
feet = 0
finch = 0
#if there is not a remainder divide evenly
if (inches%12 == 0):
    feet = inches/12
    print(inches,"inches equals",feet,"feet.")
#if there is a remainder divide by 12 then mod12 for inches
else:
    #convert to int to force floor rounding
    feet = int(inches/12)
    finch = inches%12
    print(inches,"inches equals",feet,"feet and",finch,"inches.")
print("")

#---Q2
#declaring variables and constants
food=0
tax=0
tip=0
total=0
TAX_RATE = 0.07
TIP_RATE = 0.18
#input and calculating tax,tip,total
food = float(input("Enter the charge for food: "))
tip = food*TIP_RATE
tax = food*TAX_RATE
total = tax+tip+food
#printing out values
print("Tip: $",format(tip,'.2f'))
print("Tax: $",format(tax,'.2f'))
print("Total: $",format(total,'.2f'))
