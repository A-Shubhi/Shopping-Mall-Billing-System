# Shopping-Mall-Billing-System
It is billing system which allows the user to select the items they want to buy, print the bill and avail different services given by the store.
This is a menu driven made with makefile for easy working and user friendly instructions are provided. In this project , I have used hash data structures .

This shopping mall billing system is made to cater to the needs of both customers and well as the mall owner. 

The customers can view the ongoing offers in the shopping mall, the items available and their details.They can specify their mode of payment, number of polybags required and avail facilties like home delivery and give their valuable feedback. There is an optional points based card system in which the user gets certain discounts upon collection of a fixed number of points. The users can anytime view their card details and delete their aaccount.

The mart owner can view the details of all the earnings, the number of customers visited and the overall feedback given to the mall. The written feedback file and the home delivery files are also maintained which stores information about the items to be delivered and the customer. 


**THE INPUT FILE: iteminput.txt**
contains input for the items in the mall. 
The format is S.No Item_Name tab price_per_piece quantity_available GST
Initially 40 items are taken but can be customized based on requirement.

**The menu driven program**
 Menu :
			
	1) Display the list of all the items or show items less than a particular amount.	
		Display all items
		Display all available items ( quantity > 0 )
		Display items in a specified price range
	
	2) Display the offers  
	
	3) Place the order
		the user will give the code of the product and the quantity the user want to buy 
		the user will be asked the number of polybags needed
		the mode of payment will be asked and accordingly discount will be provided
		if the user avail the point card will be asked and in case he has it the number of points he has will be shown 
		 
	4) Print the bill
		the user will be asked if he wants to avail home delivery (free of charge)
		in case of positive response, the user's address will be stored in a different file named delivery.txt
		
			The bill consists of : 
			1. Mall name and mall address
			2. Bill Number
			3. Current Date and time of printing the bill
			4. All products name- their price-their gst
			5. Total 
			6. Disount availed 
			7. Mode of payment used
			8. Customer Details
				1) Name 
				2) Phone no. 
			9.Greeting
		
	5) Summary for the staff (owner) is given
		Total number of customers, total revenue generated is given
		Total number of feedbacks and overall rating of the mall is given and number of each star given 
	
	6) Ask if the customer has the shopping mall point system card 
		ask the user if he wants to create an account
		give points and give hamper on 5 points
		ask if you want to register in it or deregister from it
		the user can see his account and his points
		Points will be added only when user gives his customer id while the totaling is done while placing the order
		
	7) Feedback
		the user will be asked to rate the mall from 1 to 5
		the user can write additional information which will be stored in a file named feedback.txt
	
	8) Display the exit and the greeting messages.

 
