#include"header.h"
#include"func.h"

struct item {
	int code; //(key 1)
	char item_name[50];
	float price;
	int quantity;
	float gst;
	};
struct item ** arr;

struct bill{
	char item_name[50];
	float price;
	int quantity;
	float amount;
	float gst;
	};
struct bill ** spend;
	
struct customer {
	int user_id;	//(key for customers)
	char fname[32];
	char lname[32];
	int mobile_no ;
	int points;
	};
struct customer ** brr;
struct customer * dummy;

int main()
{

	// allocation of space
	arr = (struct item**)malloc(sizeof(struct item*)* CAPACITY);
	brr = (struct customer**)malloc(sizeof(struct customer*)* PEOPLE);
	spend = (struct bill**)malloc(sizeof(struct bill*)* PEOPLE);
		
	// Assign NULL initially
	for (int i = 0; i < CAPACITY; i++)
	{
		arr[i] = NULL;
	}
	
	for (int i = 0; i < PEOPLE; i++)
	{
		spend[i]=NULL;
		brr[i]=NULL;
	}
 
 	dummy = (struct customer*)malloc(sizeof(struct customer)); 
	dummy->user_id = -1;
	dummy->points = -1;
	dummy->mobile_no = 0.00;
	
 	
 	//Taking input from the file and storing it in the hash
 	
 	FILE * f1 = fopen("iteminput.txt","r");
 	/*if (f1 ==NULL){printf("File not opened\n");}
 	else {printf("file opened successfully\n");}
 	*/
 	int n_lines;
 	
 	char name[50];int p,q;float r,gt;
 	
 	for (int a=0;a<CAPACITY;a++)
 	{
	 	fscanf(f1,"%d %s \t%f %d %f",&p,name,&r,&q,&gt); 	//in the file input format is %d %s \t%f %d
   		insert(p,name,r,q,gt);
	} 	
	
	float revenue=0;
	int bill_num =1;
	int bill_line=0;
	int num_bag=0;
	char mode_of_payment;
	int f_score[5]={0,0,0,0,0};
	int n_feed=0;
	int n_cust=0;
	int points =0;
	int n_point=0;		//unique id for each customer
	
	
	//To display date and time
	time_t t;   // not a primitive datatype
    	time(&t);
    

//Printing the menu 

	while(1)
	{
		
		printf("\n\n----------------------------------------------------------\n\t\t WELCOME TO SHUBHI SHOPPING MALL\n\t  ********************************************\n\n1. Shop now - View the items  \n2. Display the offers going on\n3. Place the order\n4. Print the bill\n5. Summary (for the staff) \n6. Customer Review\n7. Shopping Card (Point system) \n8. Exit \n " );
		printf("\n**----------------------------------------------------------------------------------------------------------------------------------------------------------**\n \n");
		printf("Choose what you want you do : ");
		int x;
		
		scanf("%d",&x);
		switch (x){
			case  1: 
			{
				while (1)
				{
					printf("\n **-----------------------------------------------------------------------------------------------------------------------------------**\n \n");
					printf("1.Display all the items\n2.Display all the available items\n3.Show all the available items in a certain range of price\n4. Back to Home Page\n\n ");  
					printf("\n **-----------------------------------------------------------------------------------------------------------------------------------**\n \n");
					printf("Choose an option: ");
					
					// Here available items means quantity >0
					int y;
					scanf("%d",&y);
					switch(y)
					{
						case 1: 
						{
							display_all();
							break;
						}
						
						case 2: 
						{
							display_avail();
							break;
						}
						
						
						
						case 3: 
						{
							printf("Enter the price range : \n Starting price : ");
							float start,end;
							scanf ("%f",&start);
							printf("Enter the ending price: ");
							scanf ("%f",&end);
							display_custom(start, end);
							break;
						}
						
						case 4 : {break;}
						
						default : { printf("Please enter valid input \n ");}
						
					}
					if (y==4){break;}
				}
				break;	
			}
			
			case 2:
			{
				printf("\n1.If you pay using credit card we will give you 10 percent discount and if you use Online Payment, you will get 5 percent discount.\n2.For purchase of more than 1000Rs you get 5 percent discount and for more than 10000Rs you get 10 percent discount\n3.If you collect 5 points on your shopping card, you get a gift hamper.\n"); 
				break;
			}
			
			case 3: 
			{
				
				
				float money=0.00;
				while (1)
				{
					printf("\nHave you selected all items : type 'y' if you have and 'n' if you want to shop more: ");
					char shop; 
					scanf("\n%c",&shop);
						
					if (shop=='n')
					{
						printf("Enter the code of the product you want to buy : ");
						int item_code;
						scanf ("%d",&item_code);
							
						int in_prod = hash_func(item_code);	//Finding index for the given key 
						int h_quant=find_quant(item_code) ;	// Finding the quantity available
							
						if (h_quant == -1)
						{
							printf("Enter valid code \n");
							break;
						}
							
						else
						{
							
							printf("Enter the number/quantity of the product you want to buy : ");
							int num;
							scanf("%d",&num);
							if (arr[in_prod]->quantity >=num)
							{
								money = money + num * (arr[in_prod]->price) *(arr[in_prod]->gst*0.01 +1);
								arr[in_prod]->quantity  = arr[in_prod]->quantity - num;
									
								insert_bill_line (bill_line,arr[in_prod]->item_name,arr[in_prod]->price,num,arr[in_prod]->gst);							
								bill_line++;
							}
								
							else
							{
								printf("We have %d quantity left for this product. Please choose again \n", arr[in_prod]->quantity);  
							}
							
						}
							
					}
					else if (shop=='y')
					{
						
						
						printf("Do you need a polybag to carry (Extra charges Rs 10 per bag): Type the number of bags you need ");
						scanf("%d",&num_bag);
						if (num_bag<0){printf("Enter valid non negative number \n");}
						else {money += num_bag *10;}	
						printf ("Your total is %0.2f Rs.\n \n",money); 
						
						if (money >=10000){money = money *0.9;}
						else if (money >=1000){money = money *0.95;}
						
						if (money >0.00)
						{
							printf("How would you like to pay :  Cash  card or Online Payment. \n For cash enter A, for card enter B, for Online Payment enter C :");   
							scanf("\n%c",&mode_of_payment);
							
							switch (mode_of_payment)
							{
								case 'A' : {break;}
								case 'B' : {money = money * 0.95 ; break;}
								case 'C' : {money =money * 0.90;break;}
								default: { printf("Enter valid input \n");break;}
							}	
							
							
							
							printf ("Your balance after everything is %0.2f Rs.\n \n",money); 
							revenue += money;
						}
						n_cust++;points++;
						
						break;
					}
					
					else{printf("Please enten 'y' or 'n' only.");}
					
					
				}
				
				//Point services
				printf("Do you have avail mall point services. Type y for yes ");
				char card;
				scanf("\n%c",&card);
				
				if (card=='y')
				{
					printf("Enter your id: ");
					int c_id;
					scanf("%d",&c_id);
					int m=find_cust(c_id);
					
					if (m== -1)
					{printf("The given id does not avail this facility. \n To avail this facility go to option 7. Shopping Card (Point system) in the menu \n");}
					
					else 
					{
						update_point(c_id);
						m=find_cust(c_id);
						
						 if (m>=5)
						{	
							printf(" Your points are : %d\n",m);
							printf("YOU WON A GIFT HAMPER\n----------------------------------------------------------\n\n");
						}
					
						else 
						{
							printf(" Your points are : %d\n",m);
						}
					
					}
				}
				else 
				{
					printf("To avail this facility go to option 7. Shopping Card (Point system) in the menu \n");
					}
				break;
			}
			
			
			
			case 4 :	//Printing the bill
			{
				
				char f_name[32],l_name[32];
				int p_num;
				printf("Enter the first name: "); 
				scanf("%s",f_name);
				printf("Enter the last name: "); 
				scanf("%s",l_name);
				printf("Enter your phone number: "); 
				scanf("%d",&p_num);
				
				float total_bill_money=0.00,disc=0.00;
				printf ("\n---------------------------------------------------------------\n\n\t\t**SHUBHI SHOPPING MALL**\n \t  ____________________________________\n\n \t\tScetor X, Street-Y , AB Area \n\t\tCity, State - 226030 \n \t\tPh.No: XXXXX56789\n---------------------------------------------------------------\n");
				
				//Entering bill number and date and time
				printf("\n%sBill no. %d\n\n", ctime(&t),bill_num);
				
				//Entering customer details (Name and phone number)
				printf("CUSTOMER NAME: %s %s \nPHONE No: %d \n\n",f_name,l_name,p_num);
				
				printf("Product Name \t Price(in Rs)\tQuantity\tGST\tAmount\n\n");
				
				for (int m=0;m<bill_line;m++)
				{
					
					printf("  %s\t\t%0.2f\t%d\t\t%0.2f\t%0.2f\n",spend[m]->item_name,spend[m]->price,spend[m]->quantity,spend[m]->gst,spend[m]->amount);
					total_bill_money = total_bill_money + spend[m]->amount;	
				}
				
				if (num_bag >0)
				{
					printf("  Polybag\t\t10.00\t%d\t\t%0.2f\n",num_bag,num_bag*10.00);
					total_bill_money = total_bill_money + num_bag*10.00;
				}
				printf("\n---------------------------------------------------------------");
				printf("\n\t\t\t\t Total: \t %0.2f\n\n",total_bill_money);
				
				if (total_bill_money >=10000)
				{	
					disc=0.10* total_bill_money;
					total_bill_money = total_bill_money *0.90;
					printf("\t\t\tDiscount availed \t  %0.2f\n",disc);
				}
					
				
				else if (total_bill_money >=1000)
				{
					disc=0.05* total_bill_money;
					total_bill_money = total_bill_money *0.95;
					printf("\t\t\tDiscount availed \t  %0.2f\n",disc);
				}
				
				if (mode_of_payment =='A'){
				printf("\n Mode of Payment : Cash \n\t\t\tDiscount availed \t0.00");}
				
				else if (mode_of_payment =='B'){
				printf("\n Mode of Payment : Card \n\t\t\tDiscount availed \t %0.2f",total_bill_money*0.05);
				total_bill_money = total_bill_money *0.95;
				} 
				
				else if (mode_of_payment =='C'){
				printf("\n Mode of Payment : Online \n\t\t\tDiscount availed \t %0.2f Rs",total_bill_money*0.1);
				total_bill_money = total_bill_money *0.90;
				} 
				
				printf("\n\t\t\t Amount to pay: \t %0.2f\n\n",total_bill_money);
				printf ("\n\t***Thankyou for shoppping*** \n--------------------------------------------------------------\n--------------------------------------------------------------\n\n");
				
				
			
				
				
				
				//Home delivery option
				printf("Do you want to avail home delivery ? Type y for yes and any key except y for no: ");
				char del;
				scanf("\n%c",&del);
				
				if (del=='y')
				{
					printf("Please enter your address for delivery: \nEnd with a '$' if you are done writing or do not have to write more.\n");
					char ch; 
          				FILE *del_file = fopen("delivery.txt", "a+");
          				
          				if (del_file==NULL){printf("Could not open feedback file \n");}
          				else {printf("File Opened\n");}
          				
          				fprintf(del_file,"%sBill no. %d\nAddress: ", ctime(&t),bill_num);
          				ch= getc(stdin);
          				while ( ch != '$') 
            				{ 
             					 fprintf(del_file,"%c", ch); 
             					 ch= getc(stdin);
            				}
            				fprintf(del_file,"\nCUSTOMER NAME: %s %s \nPHONE No: %d \n\n",f_name,l_name,p_num);
            				fclose(del_file);
				}
				
				bill_num++;
				bill_line =0;
				
				break;
			}
			
			case 5 : {
					printf("Please enter the security key (111): ");
					int sec;
					
					
					scanf("%d",&sec);
					if (sec ==111)
					{
						printf("\nTotal revenue generated is %0.2f Rs \n Total Customers : %d\n\n",revenue,n_cust);
						if (n_feed >0)
					
					{
						float overall=(f_score[0]+2*f_score[1]+3*f_score[2]+4*f_score[3]+5*f_score[4])/n_feed;
						printf("General review of the customers : \n\t 5 stars: %d \n\t 4 starts: %d \n\t 3 stars: %d \n\t 2 stars: %d \n\t 1 star: %d \n No of feedbacks: %d \n\nOverall view %f\n",f_score[4],f_score[3],f_score[2],f_score[1],f_score[0],n_feed,overall);
						
						}
						else{ printf("No feedbacks submitted till now.\n\n");}
						
						}
					
					else {printf ("Security key does not match. Try again \n");}
					break;
					
					}
					
					
			case 6: 
			{ 
				printf("\n\t  ** CUSTOMER FEEDBACK**  \n----------------------------------------------------------\n\n"); 
				int score;
				
				while(1)
				{	
					printf("How satisfied were you from the experience today. Rate from 1 to 5: ");
					
					scanf("%d",&score);
            				
					if (score==1){f_score[0]++;n_feed++ ;break; } 
					else if (score==2){f_score[1]++; n_feed++ ; break;}
					else if (score==3){f_score[2]++;n_feed++; break;}
					else if (score==4){f_score[3]++; n_feed++;break; }
					else if (score==5){f_score[4]++;n_feed++; break;}
					else {printf("Please enter valid number");}
					
				}
				
					printf("\nAny additional feedback: (Optional) \n End with a '$' if you are done writing or do not have to write more.");
					char ch; 
          				FILE *feed_file = fopen("feedback.txt", "a+");
          				
          				if (feed_file==NULL){printf("Could not open feedback file \n");}
          				else {printf("File Opened\n");}
          				
          				ch= getc(stdin);
          				while ( ch != '$') 
            				{ 
             					 fprintf(feed_file,"%c", ch); 
             					 ch= getc(stdin);
            				}
            				 fprintf(feed_file,"\n %d star",score);
            				fclose(feed_file);
					
					f_greeting();
					break;
			}		
			
			
			
			case 7 :
			{
				
					
				//Point services
				printf("Do you have avail mall point services. Type y for yes and any other key if you don't. ");
				char card;
				scanf("\n%c",&card);
				
				if (card=='y')
				{
					printf("Enter your id: ");
					int c_id;
					scanf("%d",&c_id);
					int m=find_cust(c_id);
					
					if (m== -1)
					{printf("The given id does not avail this facility \n\n");}
					
					else 
					{
						m=find_cust(c_id);
						find_cust_detail(c_id);
						
						
						if (m>=5)
						{	
							printf(" Your points are : %d\n",m);
							printf("YOU WON A GIFT HAMPER\n----------------------------------------------------------\n\n");
						}
					
						else 
						{
							printf(" Your points are : %d\n\n",m);
						}
					
					}
					
					printf ("Do you want delete your account ? Type 0 for yes ");
					int g;
					scanf("%d",&g);
					if (g==0)
					{
						delete_cust(c_id);
					}	
				}
				
				
				else 
				{
					printf("Do you want to create an account: Type 0 for yes or press any other key to go to home page : ");
					int ans;
					scanf("%d",&ans);
				
					if (ans==0)
					{
					
						char f_name[32],l_name[32];
						int p_num;
						printf("Enter the first name: "); 
						scanf("%s",f_name);
						printf("Enter the last name: "); 
						scanf("%s",l_name);
						printf("Enter your phone number: "); 
						scanf("%d",&p_num);
						insert_cust (n_point,f_name,l_name,p_num,0);
						printf("Your id is %d.\n Please remember it for future references.\n ",n_point);
						n_point++;
					}
				}
					
				break;
			
			}
			
			case 8: {break;}
		}
		if (x==8)
		{ 
			points=0;
			printf("Have a nice day. Visit again	\n")  ;
			break;
		}		
	}
} 

void display_avail() 
{
	int i = 0,j=1;
	printf("Available Products are :");
	printf("\n************************** \n \n");
	for(i = 0; i<CAPACITY; i++) 
	{
		if(arr[i]->quantity != 0)
		{		
			printf("%d %s \t\t%.2fRs.\t GST is %0.1f perc \t %d pieces left   \tCode is %d \n",j,arr[i]->item_name,arr[i]->price,arr[i]->gst,arr[i]->quantity,arr[i]->code );
			j++;
		}
		if (j==1){printf("All items have been purchased. Please come back later");}
	}
	printf("\n");
}

void display_all() 
{
	int i = 0;
	printf("Products are :\n");
	printf("********************\n \n");
	for(i = 0; i<CAPACITY; i++) 
	{
		printf("%d\t%s\t\t%.2fRs.\t GST is %0.1f perc \t %d pieces left     \tCode is %d \n",i+1,arr[i]->item_name,arr[i]->price,arr[i]->gst,arr[i]->quantity,arr[i]->code );		
	}
	printf("\n");
}


void display_custom(float b, float e) 
{
	int i = 0,j=1;
	printf("\n **Available Products** : \n");
	printf("*************************\n \n");
	for(i = 0; i<CAPACITY; i++) 
	{
		if(arr[i]->quantity != 0 && arr[i]->price >=b && arr[i]->price <=e)
		{		
			printf("%d %s \t\t%.2fRs.\t GST is %0.1f perc \t %d pieces left    \tCode is %d \n",j,arr[i]->item_name,arr[i]->price,arr[i]->gst,arr[i]->quantity,arr[i]->code );
			j++;
		}
	}
	if (j==1){printf("There are no available items in the given range. Please come back later.");}	
	printf("\n");
}



void insert_bill_line (int line,char item_name[50],float price,int quant,float gst)
{
	struct bill *temp =(struct bill *)malloc(sizeof(struct bill));
	strcpy(temp->item_name,item_name);
	temp->price=price;
	temp->quantity= quant;
	temp ->amount = temp->quantity * (temp->price)*(gst *0.01 +1) ;
	temp->gst = gst;
	spend[line] = temp;
}

void insert_cust (int id,char f_name[32],char l_name[32],int num,int points)
{
	struct customer *temp =(struct customer *)malloc(sizeof(struct customer));
	strcpy(temp->fname,f_name);
	strcpy(temp->lname,l_name);
	temp->user_id=id;
	temp->mobile_no= num;
	temp ->points = points;
	
	int hashIndex=hash_func_cust(id);
	// Finding index for the given key
	
	 while (brr[hashIndex] != NULL && brr[hashIndex]->user_id != id && brr[hashIndex]->user_id != -1) 
	 {
	        hashIndex++;
        	hashIndex %= CAPACITY;
    	}
    	//Finding next free space

	brr[hashIndex] = temp;
	
}


void insert (int code,char item_name[50],float price,int quantity,float gst)
{
	struct item *temp =(struct item *)malloc(sizeof(struct item));
	temp->code=code;
	strcpy(temp->item_name,item_name);
	temp->price=price;
	temp->quantity= quantity;
	temp->gst= gst;
	
	int hashIndex=hash_func(code);
	// Finding index for the given key
	
	 while (arr[hashIndex] != NULL && arr[hashIndex]->code != code && arr[hashIndex]->code != -1) 
	 {
	        hashIndex++;
        	hashIndex %= CAPACITY;
    	}
    	//Finding next free space

	arr[hashIndex] = temp;
}
 
 
int delete_cust(int key)
{
    // Apply hash function to find index for given key
    int hashIndex=hash_func(key);
 
    // Finding the node with given key
    while (brr[hashIndex] != NULL) 
    {
        if (brr[hashIndex]->user_id == key) {
            // Insert dummy node here for further use
            brr[hashIndex] = dummy;

 
            // Return the value of the key
            printf("Node value of key %d is deleted successfully\n",key);
            return 1;
        }
        hashIndex++;
        hashIndex %= CAPACITY;
    }
 
    // If not found return null
    printf("This account does not exists\n");
    return 0;
}
 

int find_quant(int key)
{
	// Apply hash function to find index for given key
	int hashIndex=hash_func(key);
 
	int s = 0;
 
	// Find the node with given key
	while (arr[hashIndex] != NULL)
	{
        	 s = 0;
        	// If counter is greater than capacity
        	if (s > CAPACITY)
		{	
			break;
			s++;
		}
	 
        	// If node found return its value
        	if (arr[hashIndex]->code == key)
		{
			//printf("Value of Key %d is %d \n",key,arr[hashIndex]->quantity);
			return arr[hashIndex]->quantity;
 		}
        	hashIndex++;
        	hashIndex %= CAPACITY;
	}
 
    // If not found return -1
    printf("Key %d does not exists \n",key);
    return -1; 
}

int find_cust(int key)
{
	// Apply hash function to find index for given key
	int hashIndex=hash_func_cust(key);
 
	int s = 0;
 
	// Find the node with given key
	while (brr[hashIndex] != NULL)
	{
        	 s = 0;
        	// If counter is greater than capacity
        	if (s > CAPACITY)
		{	
			break;
			s++;
		}
	 
        	// If node found return 1
        	if (brr[hashIndex]->user_id == key)
		{
			if (brr[hashIndex]->points >=5)
			{
			int q =brr[hashIndex]->points;
			brr[hashIndex]->points = brr[hashIndex]->points-5;
			return q;
			
			}
			
			else return brr[hashIndex]->points ;
 		}
        	hashIndex++;
        	hashIndex %= CAPACITY;
	}
 
    // If not found return -1
    return -1; 
}

void find_cust_detail(int key)
{
	// Apply hash function to find index for given key
	int hashIndex=hash_func_cust(key);
 
	int s = 0;
 
	// Find the node with given key
	while (brr[hashIndex] != NULL)
	{
        	 s = 0;
        	// If counter is greater than capacity
        	if (s > CAPACITY)
		{	
			break;
			s++;
		}
	 
        	// If node found return 1
        	if (brr[hashIndex]->user_id == key)
		{
			printf("\n Name: %s %s \n Phone num : %d \n\n",brr[hashIndex]->fname,brr[hashIndex]->lname,brr[hashIndex]->mobile_no);
			
			
 		}
        	hashIndex++;
        	hashIndex %= CAPACITY;
	}
 
   
}

int update_point(int key)
{
	// Apply hash function to find index for given key
	int hashIndex=hash_func_cust(key);
 
	int s = 0;
 
	// Find the node with given key
	while (brr[hashIndex] != NULL)
	{
        	 s = 0;
        	// If counter is greater than capacity
        	if (s > CAPACITY)
		{	
			break;
			s++;
		}
	 
        	// If node found return 1
        	if (brr[hashIndex]->user_id == key)
		{
			
			brr[hashIndex]->points = brr[hashIndex]->points+1;
			return brr[hashIndex]->points ;
 		}
        	hashIndex++;
        	hashIndex %= CAPACITY;
	}
 
    // If not found return -1
    return -1; 
}	



				
			
 


