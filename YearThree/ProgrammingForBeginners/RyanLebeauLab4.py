'''
Ryan Lebeau
10/02/2019
Lab4RyanLebeau.py
COMP2067
'''

#inputs form user
startP = int(input("Enter the starting principal: "))
annInt = int(input("Enter the annual interest rate: "))
intComp = int(input("How many times per year is the interest compounded? "))
years = int(input("For how many years will the account earn interest "))

#calculating values
annInt /= 100
x = startP*(1+(annInt/intComp))**(intComp*years)

print("At the end of",years,"years you will have ${:,.2f}".format(x))
