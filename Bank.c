#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char* name;
	char gender;
	int age;
	int account_num;
	int balance;
}Bank_user;

typedef struct {
    Bank_user** user_list;         
    char* bank_name;	
	int user_num;	
	int interest_rate;	
	int ID_num;    	
}Bank;

Bank* make_bank(int people_num, char * name, int interest_rate);
Bank_user* make_bankUser(Bank* bank);
Bank_user** make_bankUser_list(int people_num);
char* get_name(char* question);
int get_string_length(char* string);
int get_int(char* question);
char get_char(char* question);
char* make_char_array(int string_length);
void copy_string(char* copy, char* original);
void make_account(Bank* bank);
int return_balance(Bank* bank, int user_ID);
int deposit(Bank* bank);
int withdraw(Bank* bank);
void free_all(Bank** bank_arr, int len);
void free_bank(Bank* bank);
void print_userinfo(Bank* bank, int user_ID, int balance);
void find_user_ID(Bank* bank, char* name);
int return_user_ID(Bank* bank, char* find_name);
int is_same_string(char* str1, char* str2);
void show_bank_list(Bank** bank_arr, int len);
void set_balance(int plus, int amount, Bank* bank, int user_ID);
int get_user_ID(Bank* bank);

int main(void) {
	
	int run_program = 1, choice = 0, num, user_ID;  
	char* name;

	Bank* bank_arr[] = {make_bank(50,"NH Bank",2), make_bank(60,"HN Bank",3), make_bank(40,"IBK Bank",4), make_bank(50,"KB bank",3),make_bank(70,"SH bank",5)};
	int len = (sizeof(bank_arr) / sizeof(Bank*));
	
	while(run_program){				
		
		show_bank_list(bank_arr,len);
		num = get_int("Select a bank to Process : ") - 1;
		
		if( !(0 <= num && num < len) ) {
			break;
		}
		
		printf("\n\n1. Create account\n");
		printf("2. Check balance\n");
		printf("3. Deposit\n");
		printf("4. Withdraw\n");
		printf("5. Find user's ID\n\n\n");

		choice = get_int("Enter the number: ");
	
		switch(choice) {//1. print , 2. 계좌 ID찾기 
			case 1: //계좌개설
				make_account(bank_arr[num]);
				break;
			case 2: //계좌잔액확인
				user_ID = get_user_ID(bank_arr[num]);
				print_userinfo(bank_arr[num], user_ID, return_balance(bank_arr[num], user_ID));
				break;
			case 3: //입금
				user_ID = deposit(bank_arr[num]); 
				print_userinfo(bank_arr[num], user_ID, return_balance(bank_arr[num], user_ID));
				break;
			case 4: //출금
				user_ID = withdraw(bank_arr[num]);
				print_userinfo(bank_arr[num], user_ID, return_balance(bank_arr[num], user_ID));
				break;
			case 5: //아이디찾기
				find_user_ID(bank_arr[num], get_name("Enter the user's name: ")); 
				break;
			default:
				run_program = 0;
				break;
		}
	}
    
	free_all(bank_arr,len);
	
	return 0;
}

Bank* make_bank(int people_num, char * name, int interest_rate){
	Bank* bank = (Bank*)malloc(sizeof(Bank));  
	bank -> bank_name = name;
	bank -> user_num = people_num;
	bank -> ID_num = 0;
	bank -> user_list = make_bankUser_list(people_num);
	bank -> interest_rate = interest_rate;
	return bank;
}

Bank_user* make_bankUser(Bank* bank){
	Bank_user* new_user = (Bank_user*)malloc(sizeof(Bank_user)*1);
	new_user -> name = get_name("Enter the user name: ");
	getchar();
	new_user -> gender = get_char("Enter the gender: ");
	new_user -> age = get_int("Enter the age: ");
	new_user -> account_num = bank->ID_num;
	new_user -> balance = 0;
	return new_user;
}

Bank_user** make_bankUser_list(int people_num) {
	Bank_user** user_list = (Bank_user**)malloc(sizeof(Bank_user*) * people_num);
	return user_list;
}

char* get_name(char* question) {
	char tempname[100];
	printf("%s",question);
	scanf("%s",tempname);
	char* name = make_char_array(get_string_length(tempname));
	copy_string(name, tempname);
	return name;
}

int get_string_length(char* string) { 
	int len = 0;
	for(int i=0; *(string + i)!= '\0'; i++) {
		len++;
	}
	return len;
}

int get_int(char* question) {
	int val;
	printf("%s",question);
	scanf("%d",&val);
	return val;
}

char get_char(char* question) {
	char gender;
	printf("%s", question);
	scanf("%c", &gender);
	return gender;
}

char* make_char_array(int string_length) {
	char* arr = (char*)malloc((string_length+2)*1);
	*(arr) = string_length;
	*(arr+string_length+1) = '\0';
	return arr+1;
}

void copy_string(char* copy, char* original) {
	for(int i = 0; i<get_string_length(original); i++){
		*(copy + i) = *(original + i);
	}
}

void make_account(Bank* bank) {
	if((bank->ID_num) <= (bank->user_num)) {
		*((bank-> user_list) + (bank->ID_num)) = make_bankUser(bank);
		printf("Account number %d has been created.\n", bank->ID_num);
		(bank-> ID_num)++;
	}
}

int return_balance(Bank* bank, int user_ID) {
	if(user_ID == -1) {
		return 0;
	}
	return bank ->user_list[user_ID] -> balance;
}

void free_bank(Bank* bank) {
	
	for(int i=0; bank->user_list[i] != NULL; i++) {
		free((bank->user_list[i]->name)-1);
	}
	
	for(int i=0; bank->user_list[i] != NULL; i++) {
		free(bank->user_list[i]);
	}

	free(bank->user_list);
	
	if( (*(bank->bank_name-1)) == get_string_length(bank->bank_name) ){
		free((bank->bank_name)-1);
	}
	free(bank);
}

void free_all(Bank** bank_arr, int len) {
	for(int i = 0; i< len; i++) {
		free_bank(*(bank_arr+i));
	}
}

int get_user_ID(Bank* bank){
	int user_ID = get_int("Enter the user ID number: "); 
	if(bank->user_list[user_ID] == NULL) {	
		return -1;
	}
	return user_ID;
}

void print_userinfo(Bank* bank, int user_ID, int balance) {
	if(user_ID<0) {
		printf("There is no information for the user you are looking for.\n");
		return;
	}
	printf("User ID: %d ,Balance: %d \n",user_ID, balance);
}

void find_user_ID(Bank* bank, char* name) {
	int exist_ID = return_user_ID(bank, name); //
	if(exist_ID != -1) {
		printf("The user's ID is %d.\n " , exist_ID);
	}
	else {
		printf("There is no information for the user you are looking for.\n");
	}
}

int return_user_ID(Bank* bank, char* name) {
	for(int i=0; bank->user_list[i] != NULL; i++) {
		if(is_same_string(name, bank->user_list[i]->name) == 1) {
			return bank->user_list[i] -> account_num;
		}
	}
	return -1;
}

int is_same_string(char* str1, char* str2) {   
	if(get_string_length(str1) != get_string_length(str2)){
		return -1;
	}
	for(int i = 0; (*(str1+i) != '\0'); i++){
		if((*(str1+i)) != (*(str2+i))) { 
			return -1;
		}
	}
	return 1;
}

void show_bank_list(Bank** bank_arr, int len) {
	printf("\n\n");
	for( int i = 0; i < len; i++){
		printf("%d. %s\n",i+1,(bank_arr[i]->bank_name));
	}
}

void set_balance(int plus, int amount, Bank* bank, int user_ID) {
	if(plus == 1){
		((*((bank ->user_list) + user_ID)) -> balance) += amount;
	}
	else {
		if(amount > return_balance(bank, user_ID)) { 
			printf("The balance is insufficient.\n");
			return;
    	}
		((*((bank ->user_list) + user_ID)) -> balance) -= amount;
	}
}

int deposit(Bank* bank) {
	int user_ID = get_user_ID(bank); 
	if(user_ID == -1) {
		return user_ID;
	}
	int amount = get_int("Enter the amount to deposit: ");
	set_balance(1, amount, bank, user_ID);
	printf("%d has been deposited into account number %d. \n", amount, user_ID);
	
	return user_ID;
}

int withdraw(Bank* bank) {
	int user_ID = get_user_ID(bank);
	if(user_ID == -1) {
		return user_ID;
	}
	int amount = get_int("Enter the amount to withdraw: ");
	set_balance(0, amount, bank, user_ID);
	printf("%d was withdrawn from account number %d. \n", amount, user_ID);
	
	return user_ID;
}
