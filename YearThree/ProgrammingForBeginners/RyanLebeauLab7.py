'''
Ryan Lebeau
04/03/2019
RyanLebeauLab7.py
COMP2067
'''

#---Q1
'''
-A
*
**
***
****

-B
  *  
 *** 
*****
 *** 
  *  
'''

#---Q2
N=0
F=2
#user input to be greater than one
N=int(input("Enter a number greater than 1: "))
while(1):
    if(N<=1):
        N=int(input("That number is not greater than 1.\nEnter a number greater than 1: "))
    else:
        break
#main loop
while(1):
    #exit if factor is one or below
    if(N<=1):
        break
    else:
        #if N does not divide F evenly increment F
        if N%F != 0:
            F+=1
        #if N does divide F evenly print out the factor and divide N
        else:
            print(F, end=" ")
            N = N/F

