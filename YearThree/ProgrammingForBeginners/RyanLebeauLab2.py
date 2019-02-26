'''
Ryan Lebeau
01/24/2019
Lab2RyanLebeau.py
COMP2067
'''

stockSym = "CS2067"
#contains all provided data about stocks
sharesInfo = [5000, 1.13, 3567, 1.59, 1.80]
#calculations for profits
priceDec1 = sharesInfo[0]*sharesInfo[1]
valueJan1 = sharesInfo[2]*sharesInfo[3]
sharesLeft = sharesInfo[0]-sharesInfo[2]
valueJan21 = sharesLeft*sharesInfo[4]

#print the values to the user rounding to 2 decimal places if necessary
print("The Trading symbol for the company is: ",stockSym)
print("Price of shares purchased on Dec1 2018: ",round(priceDec1,2)," dollars")
print("Value of shares sold on Jan1 2019: ",round(valueJan1,2)," dollars")
#calculation for profit off jan1 shares done in print
print("The amount of profit made on Jan1: ",
          round((valueJan1-(sharesInfo[2]*sharesInfo[1])),2)," dollars")
print("Value of shares sold on Jan21: ",round(valueJan21,2)," dollars")
#calculation for profit off jan21 shares done in print
print("Profit for Jan21 trade is: ",
          round((valueJan21-(sharesLeft*sharesInfo[1])),2)," dollars")
#since total profit is only used once, do calculation in print
print("Total profit by trading the stock was:",
          round((valueJan1+valueJan21-priceDec1),2)," dollars")
