'''
Ryan Lebeau
16/03/2019
RyanLebeauLab8.py
COMP2067
'''
#---Q60
#getting user input for investment value
invest = int(input("Enter investment amount: "))
print("Simple Interest\tCompund Interest")
simp=invest
comp=invest
#for loop with 4 iterations
for i in range (0,4):
    #calculating interest at 5%
    simp+=invest*0.05
    comp+=comp*0.05
    #printing interest
    print(i+1," ${:,.2f}".format(simp),"\t${:,.2f}".format(comp))

#---Q64
#getting user input for car value
value = int(input("\nEnter cars value at purcahse: "))
#for loop with 4 iterations
for i in range(0,4):
    #calculate depreciation
    value-=value*0.15
    print(i+1,"\t${:,.2f}".format(value))
