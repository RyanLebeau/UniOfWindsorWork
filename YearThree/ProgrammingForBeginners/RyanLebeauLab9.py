'''
Ryan Lebeau
21/03/2019
RyanLebeauLab9.py
COMP2067
'''
#function to find max of 3 entered numbers
def maxNums(nums):
    #trys to find max and cast numbers to integers
    #catches valueError if characters were entered
    #catches indexError if less than three numbers were entered
    try:
        maxN=max(int(nums[0]), int(nums[1]), int(nums[2]))
    except ValueError:
        print("Please enter only numbers")
    except IndexError:
        print("Please enter three numbers total seperated\nby a space between each number.")
    else:
        print("The max of the three numbers entered is:",maxN)
#input from user then split string
inS=str(input("Enter three numbers seperated by a space: "))
nums=inS.split();
maxNums(nums);
