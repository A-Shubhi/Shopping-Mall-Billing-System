#define CAPACITY 40 		
# define PEOPLE 40

void display_all();
void display_avail();
void display_custom(float b, float e);
void find_cust_detail(int key);
int hash_func_cust(int key);	
int hash_func(int key);		
void insert (int code,char item_name[50],float price,int quantity,float gst);
void insert_cust (int id,char f_name[32],char l_name[32],int num,int points);
void insert_bill_line (int line,char item_name[50],float price,int quant,float gst);
int delete_cust(int key);
int find_cust(int key);
int update_point(int key);
int find_quant(int key);
void f_greeting();
