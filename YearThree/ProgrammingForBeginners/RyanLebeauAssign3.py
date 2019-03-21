'''
Ryan Lebeau
21/03/2019
RyanLebeauAssign3.py
COMP2067
'''
#sum an entire list of numbers
def sumList(nums):
    print("The sum is:",sum(nums))

#reverse a passed in string
def reverseString(strOrig):
    strRev=str()
    #loops for length of strOrig and takes last position and adds to strRev
    for i in range(len(strOrig)):
        strRev = strRev+strOrig[(len(strOrig)-1)-i]
    print("String",strOrig,"reversed is:",strRev)

#declaring lis tof nums and string
numList=[18,2,13,0,7]
string=str("abcd2er4")
#calling functions
sumList(numList)
reverseString(string)
