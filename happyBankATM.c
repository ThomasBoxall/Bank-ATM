#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h> //Used for modulo with floats

//Define constants
#define USERDATAROWS 50
#define TRANSACTIONSROWS 255


//Declare procedures
void exit(int status);
void openUserData();
void closeUserData();
void mainMenu();
void printBankLogo();
void openTransactions();
void closeTransactions();
void login();
void newAccount();
void progressBar();
void loggedInMenu();
void adminLogin();
void adminMenu();
void checkBalance();
void withdraw();
void deposit();
void miniStatement();
void accountsLowHigh();
void transfer();
void reactivate();
void deactivate();
void startUp();
void adminPrintAllTransactions();
void adminPrintAllAccounts();

//Declare global vairables
int currentUserId, structureLocationCurrentUserId;
int mainMenuChoice;
char date;
int sleepTime = 1;
//Declare pointer vars
int maxTransaction;
int maxUser;

//Setup array of structures to store user data in
struct users{
	int userId;
	char firstName[50];
	char lastName[50];
	float balance;
	int pin;
	int role; //1=std user, 2=admin(still has standard user atributes)
	int active; //0=inactive, 1=active
	int writeOut;
} userData[USERDATAROWS];
//Setup array of structures to store transactions in
struct transactions{
	int userId;
	int transCode;
	float amountIn;
	float amountOut;
	int writeOut;
}transactions[TRANSACTIONSROWS];

int main(){
	system("color 02");
	startUp();
	openUserData();
	openTransactions();
	sleep(1);
	mainMenu();
	closeUserData();
	closeTransactions();
}

void openUserData(){
	//Open userData file and read in to structure
	FILE *fp;
	fp = fopen("enter location of user data file here \\userData.txt", "r");
	
	char holdingString[USERDATAROWS][255], *pch;
	int currentPositionInStruct=0, switchContoller;
	float trimmed;
	while((fgets(holdingString[currentPositionInStruct], USERDATAROWS, fp) != NULL) && (currentPositionInStruct<=255)){
		switchContoller = 1;
		//puts(holdingString[currentPositionInStruct]); //Print entire row

		pch = strtok(holdingString[currentPositionInStruct], " ");
		
		while(pch != NULL){
			switch(switchContoller){
				case 1:
					//userID
					userData[currentPositionInStruct].userId = atoi(pch);
					break;
				case 2:
					//firstName
					strcpy(userData[currentPositionInStruct].firstName, pch);
					break;
				case 3:
					//lastName
					strcpy(userData[currentPositionInStruct].lastName, pch);
					break;
				case 4:
					//balance
					trimmed = ("%.2f", atof(pch));
					userData[currentPositionInStruct].balance = trimmed;
					break;
				case 5:
					//pin
					userData[currentPositionInStruct].pin = atoi(pch);
					break;
				case 6:
					//role
					userData[currentPositionInStruct].role = atoi(pch);
					break;
				case 7:
					//active
					userData[currentPositionInStruct].active = atoi(pch);
					break;
				case 8:
					//Writeout
					userData[currentPositionInStruct].writeOut = atoi(pch);
					break;
			}//End of switch
			
			switchContoller++;
			pch = strtok(NULL, " "); //Find the next chunk of text
				
		} //End of inner while
	currentPositionInStruct++;
	} //End of eitire file while loop	
	fclose(fp);
	maxUser = currentPositionInStruct;
}//End of openUserData()
void closeUserData(){
	FILE *fp;
	fp = fopen("enter location of user data file here \\userData.txt", "w");
	int rowCount;
	for(rowCount=0; rowCount<USERDATAROWS; rowCount++){
		if (userData[rowCount+1].writeOut == 1){
			fprintf(fp, "%d ", userData[rowCount].userId);
			fprintf(fp, "%s ", userData[rowCount].firstName);
			fprintf(fp, "%s ", userData[rowCount].lastName);
			fprintf(fp, "%.2f ", userData[rowCount].balance);
			fprintf(fp, "%d ", userData[rowCount].pin);
			fprintf(fp, "%d ", userData[rowCount].role);
			fprintf(fp, "%d ", userData[rowCount].active);
			fprintf(fp, "%d\n", userData[rowCount].writeOut);	
		}else if (userData[rowCount].writeOut == 1){
			fprintf(fp, "%d ", userData[rowCount].userId);
			fprintf(fp, "%s ", userData[rowCount].firstName);
			fprintf(fp, "%s ", userData[rowCount].lastName);
			fprintf(fp, "%.2f ", userData[rowCount].balance);
			fprintf(fp, "%d ", userData[rowCount].pin);
			fprintf(fp, "%d ", userData[rowCount].role);
			fprintf(fp, "%d ", userData[rowCount].active);
			fprintf(fp, "%d", userData[rowCount].writeOut);
		}
		
	}
	fclose(fp);
}//End of closeUserData()
void mainMenu(){
	system("cls");
	progressBar();
	printBankLogo();
	puts("\nPlease select one of the options below");
	puts("1. Login");
	puts("2. Create account");
	puts("3. Administrator login");
	printf("Enter choice here: ");
	fflush(stdin);
	scanf("%d", &mainMenuChoice);
	
	switch(mainMenuChoice){
		case 1:
			login();
			break;
		case 2:
			newAccount();
			//Create new account
			break;
		case 3:
			adminLogin();
			break;
		default:
			printf("That wasn't valid");
			sleep(sleepTime);
			mainMenu();
			break;
	}
}
void printBankLogo(){
	puts("*********************************************************************");
	puts("****                                                             ****");
	puts("****                     HAPPY BANK ATM                          ****");
	puts("****                                                             ****");
	puts("**** Build:17/12/2020                                       V0.0 ****");	
	puts("*********************************************************************");
}
void openTransactions(){
	FILE *fp;
	fp = fopen("enter location of transactions file here \\transactions.txt", "r");
	char holdingString[TRANSACTIONSROWS][255], *pch;
	int currentPositionInStruct=0, switchContoller;
	
	while((fgets(holdingString[currentPositionInStruct], USERDATAROWS, fp) != NULL) && (currentPositionInStruct<=255)){
		switchContoller = 1;

		pch = strtok(holdingString[currentPositionInStruct], " ");
		
		while(pch != NULL){
			switch(switchContoller){
				case 1:
					//userId
					transactions[currentPositionInStruct].userId = atoi(pch);
					break;
				case 2:
					//transCode
					transactions[currentPositionInStruct].transCode = atoi(pch);
					break;
				case 3:
					//amount in
					transactions[currentPositionInStruct].amountIn = atof(pch); 
					break;
				case 4:
					//Amount out
					transactions[currentPositionInStruct].amountOut = atof(pch); 
					break;
				case 5:
					//writeout
					transactions[currentPositionInStruct].writeOut = atoi(pch);
					break;
			}
			switchContoller++;
			pch = strtok(NULL, " ");
		}
	currentPositionInStruct++;
	}
	fclose(fp);
	maxTransaction = currentPositionInStruct;
}
void closeTransactions(){
	FILE *fp;
	fp = fopen("enter location of transactions file here \\transactions.txt", "w");
	int rowCount;
	for(rowCount=0; rowCount<TRANSACTIONSROWS; rowCount++){
		if(transactions[rowCount+1].writeOut == 1){
			fprintf(fp, "%d ", transactions[rowCount].userId);
			fprintf(fp, "%d ", transactions[rowCount].transCode);
			fprintf(fp, "%.2f ", transactions[rowCount].amountIn);
			fprintf(fp, "%.2f ", transactions[rowCount].amountOut);
			fprintf(fp, "%d\n", transactions[rowCount].writeOut);
		}else if(transactions[rowCount].writeOut == 1){
			fprintf(fp, "%d ", transactions[rowCount].userId);
			fprintf(fp, "%d ", transactions[rowCount].transCode);
			fprintf(fp, "%.2f ", transactions[rowCount].amountIn);
			fprintf(fp, "%.2f ", transactions[rowCount].amountOut);
			fprintf(fp, "%d", transactions[rowCount].writeOut);
		}
	}
}
void login(){
	int userId, pin;
	system("cls");
	printBankLogo();
	puts("Please enter your user ID and pin below");
	printf("User ID: ");
	fflush(stdin);
	scanf("%d", &userId);
	printf("Pin: ");
	fflush(stdin);
	scanf("%d", &pin);
	
	//Now validate the login
	int x, incorrect = 0;
	for(x=0; x<maxUser; x++){
		if((userData[x].userId == userId)&&(userData[x].pin == pin) && (userData[x].active == 1)){
			//Correct user
			incorrect == 0;
			structureLocationCurrentUserId = x;
			printf("UserID and pin accepted...\nLogging in");
			sleep(sleepTime);
			loggedInMenu();
			break;	
		} else if((userData[x].userId == userId)&&(userData[x].pin == pin) && (userData[x].active == 0)){
			printf("Your account is closed. Please contact an administrator if you think this is a mistake.");
			sleep(sleepTime);
			mainMenu();
		}
		incorrect++;
	}
	if(incorrect>0){
		//the details are incorrect
		printf("Those details are incorrect. Please try again");
		sleep(sleepTime);
		login();
	}
}
void newAccount(){
	char firstName[50], lastName[50], yesNo, tempSave[10];
	int pin = 0, userId = 0;
	float balance = 0.00;
	//first generate userId
	userId = userData[maxUser-1].userId + 1;

	system("cls");
	printBankLogo();
	printf("Please enter your details below when requested");
	printf("\nFirst name: ");
	fflush(stdin);
	gets(firstName);
	printf("\nLast name: ");
	fflush(stdin);
	gets(lastName);
	printf("\nPin(no leading 0s): ");
	fflush(stdin);
	gets(tempSave);
	pin = atoi(tempSave);
	
	progressBar();
	
	printBankLogo();
	printf("Please confirm your details below (you can add balance later)");
	printf("\nUSER ID: %d", userId);
	printf("\nFIRST NAME: %s", firstName);
	printf("\nLAST NAME: %s", lastName);
	printf("\nBALANCE: %.2f", balance);
	printf("\nPIN: %d", pin);
	printf("\n\nAre you happy with this(y), or do you wish to start again(n): ");
	fflush(stdin);
	scanf("%c", &yesNo);
	
	switch(yesNo){
		case 'y':
		case 'Y':
			//Save to userData Struct then close file
			userData[maxUser].userId = userId;
			strcpy(userData[maxUser].firstName, firstName);
			strcpy(userData[maxUser].lastName, lastName);
			userData[maxUser].balance = balance;
			userData[maxUser].pin = pin;
			userData[maxUser].role = 1;
			userData[maxUser].active = 1;
			userData[maxUser].writeOut = 1;
			maxUser++;
			closeUserData();
			mainMenu();
			break;
		default:
		case 'n':
		case 'N':
			newAccount();
			break;
	}	
}
void progressBar(){
	//Adapted from Geeksforgeeks
	
	// Print initial loading bar 
	system("cls");
	int i;
	printf("\n\n\t\t\t          LOADING   ");
	printf("\n\n\t\t\t");

	for (i = 0; i < 26; i++){
		printf("%c", 177);
	}
		 
	// Set the cursor starting point back to start
	printf("\r"); 
	
	printf("\t\t\t");
	// Print loading bar progress 
	for (i = 0; i < 26; i++) { 
		printf("%c", 219); 

		// Sleep for 0.1 second 
		Sleep(10); 
	}
	system("cls");
}
void loggedInMenu(){
	int userChoice;
	progressBar();
	printBankLogo();
	puts("Please select one of the following");
	puts("1. Check balance");
	puts("2. Withdraw cash");
	puts("3. Deposit cash");
	puts("4. Transfer money");
	puts("5. Onscreen mini-statement");
	puts("6. Close account");
	puts("9. Logout");
	printf("Enter selection here: ");
	fflush(stdin);
	scanf("%d", &userChoice);
	switch(userChoice){
		case 1:
			//Check balance
			checkBalance();
			break;
		case 2:
			//Withdraw cash
			withdraw();
			break;
		case 3:
			//Deposit cash
			deposit();
			break;
		case 4:
			//Transfer money
			transfer();
			break;
		case 5:
			//Onscreen mini-statement
			miniStatement();
			break;
		case 6:
			//Close account
			userData[structureLocationCurrentUserId].active = 0;
			break;
		case 9:
			//logout
			mainMenu();
			break;
		default:
			//Invalid option
			puts("Invalid option. Please re-select");
			sleep(sleepTime);
			loggedInMenu();
			break;
	}
	
	
}
void adminLogin(){
	int userId, pin;
	system("cls");
	printBankLogo();
	puts("Please enter your user ID and pin below");
	printf("User ID: ");
	fflush(stdin);
	scanf("%d", &userId);
	printf("Pin: ");
	fflush(stdin);
	scanf("%d", &pin);
	
	//Now validate the login
	int x, incorrect = 0;
	for(x=0; x<maxUser; x++){
		if((userData[x].userId == userId)&&(userData[x].pin == pin) && (userData[x].active == 1) && (userData[x].role == 2)){
			//Correct user
			incorrect == 0;
			structureLocationCurrentUserId = x;
			printf("UserID and pin accepted...\nLogging in to admin console");
			sleep(sleepTime);
			adminMenu();
			break;	
		}
		incorrect++;
	}
	if(incorrect>0){
		//the details are incorrect
		printf("Those details are incorrect. Please try again");
		sleep(sleepTime);
		adminLogin();
	}
}
void adminMenu(){
	int userChoice;
	system("cls");
	progressBar();
	printBankLogo();
	
	puts("0. Shutdown system");
	puts("1. Display balance of accounts");
	puts("2. Reactivate account");
	puts("3. Deactivate account");
	puts("4. Display all transactions for all users");
	puts("5. Display all account information");
	puts("9. Logout");
	printf("Enter choice here: ");
	fflush(stdin);
	scanf("%d", &userChoice);
	
	switch(userChoice){
		case 0:
			closeUserData();
			closeTransactions();
			printf("System shutting down.\nPlease wait");
			sleep(sleepTime);
			exit(0);
			break;
		case 1:
			accountsLowHigh();
			break;
		case 2:
			reactivate();
			break;
		case 3:
			deactivate();
			break;
		case 4:
			adminPrintAllTransactions();
			break;
		case 5:
			adminPrintAllAccounts();
			break;
		case 9:
			mainMenu();
			break;
		default:
			puts("That wasn't valid, please try again");
			sleep(sleepTime);
			adminMenu();
			break;
	}
}
void checkBalance(){
	progressBar();
	printBankLogo();
	puts("BALANCE CHECKER");
	printf("\nNAME: %s %s", userData[structureLocationCurrentUserId].firstName, userData[structureLocationCurrentUserId].lastName);
	printf("\nCURRENT BALANCE: %.2f", userData[structureLocationCurrentUserId].balance);
	puts("\n---\nPress enter to return to the main menu");
	system("pause");
	loggedInMenu();
}
void withdraw(){
	int invalid = 0;
	float amount;
	char amountChar[10];
	progressBar();
	printBankLogo();
	puts("WITHDRAW");
	printf("\nPlease enter the amount you wish to withdraw: ");
	fflush(stdin);
	gets(amountChar);
	amount = atof(amountChar); //Will return 0 if amountChar contains non-numerical characters
	//Check that the amount they want to withdraw is less than or equal to everything in their account
	if((amount<=userData[structureLocationCurrentUserId].balance) && (amount != 0)){
		//It is
		//Now check if the number is divisible by 5
		if(fmod(amount, 5) == 0){
			//Amount is divisible by 5 so it can be deducted from account.
			userData[structureLocationCurrentUserId].balance = userData[structureLocationCurrentUserId].balance - amount;
			closeUserData();
			//Now write entry into transaction
			transactions[maxTransaction].userId = userData[structureLocationCurrentUserId].userId;
			transactions[maxTransaction].transCode = 1;
			transactions[maxTransaction].amountIn = 0.00;
			transactions[maxTransaction].amountOut = amount;
			transactions[maxTransaction].writeOut = 1;
			closeTransactions();
			puts("\n---\nTransaction complete.\nReturning to main menu.");
			sleep(sleepTime);
			maxTransaction++;
			loggedInMenu();
		} else{
			invalid++;
		}
	}else{
		invalid++;
	}
	
	if(invalid>0){
		invalid = 0;
		printf("Invalid amount. You can only withdraw multiples of 5.\nYou have %.2f in your account.\nPlease try again.", userData[structureLocationCurrentUserId].balance);
		sleep(sleepTime);
		withdraw();	
	}
}
void deposit(){
	int invalid = 0;
	float amount;
	char amountChar[10];
	progressBar();
	printBankLogo();
	puts("DEPOSIT");
	printf("\nPlease enter the amount you wish to DEPOSIT: ");
	fflush(stdin);
	gets(amountChar);
	amount = atof(amountChar); //Will return 0 if amountChar contains non-numerical characters
	
	//Now check that amount is a multiple of 5 so bank notes can be accepted
	if((fmod(amount, 5) == 0) && (amount != 0)){
		//Amount is a multiple of 5 so deposit can be added to account
		userData[structureLocationCurrentUserId].balance = userData[structureLocationCurrentUserId].balance + amount;
		
		//Now write entry into transaction
		transactions[maxTransaction].userId = userData[structureLocationCurrentUserId].userId;
		transactions[maxTransaction].transCode = 2;
		transactions[maxTransaction].amountIn = amount;
		transactions[maxTransaction].amountOut = 0.00;
		transactions[maxTransaction].writeOut = 1;
		closeUserData();
		closeTransactions();
		puts("\n---\nTransaction complete.\nReturning to main menu.");
		sleep(sleepTime);
		maxTransaction++;
		loggedInMenu();
	}else{
		invalid++;
	}
	if(invalid>0){
		invalid = 0;
		printf("Invalid amount. Your deposit must be a multiple of 5.\nPlease try again.");
		sleep(sleepTime);
		deposit();	
	}
}
void miniStatement(){
	int accountNumber, loopCount, correctCount[maxTransaction], arrayCount=0, arrayCountTransfer, actAboveFive;
	accountNumber = userData[structureLocationCurrentUserId].userId;
	
	//Loop through transaction array of structures and if current matches, add to counting array
	for(loopCount=0; loopCount<maxTransaction; loopCount++){
		if(accountNumber == transactions[loopCount].userId){
			correctCount[arrayCount] = loopCount;
			arrayCount++;
		}
	}
	if(arrayCount != 0){
		//Now loop backwards thorough the arrays and print the first five
		arrayCount--; //So it is the same as when was last used for correctCount
		arrayCountTransfer = arrayCount;
		//Print header
		printf("\n|-------------------------------------|");
		printf("\n| TRANS CODE | AMOUNT IN | AMOUNT OUT |");
		printf("\n|-------------------------------------|");
		loopCount = arrayCount;
		actAboveFive = arrayCountTransfer - 5;
		while((loopCount>actAboveFive) && (loopCount > -1)){
			printf("\n| %10d | %9.2f | %10.2f |", transactions[correctCount[arrayCount]].transCode, transactions[correctCount[arrayCount]].amountIn, transactions[correctCount[arrayCount]].amountOut);
			arrayCount--;
			loopCount--;
		}
		//Print footer to table
		printf("\n|-------------------------------------|\n");
	} else{
		puts("\n---\nThere is no data to show\n---");
	}

	system("pause");
	loggedInMenu();
}
void accountsLowHigh(){
	//First loop through all index positions of userData struct and if that is NOT admin and NOT closed then add that index position to temp holding array.
	//Then bubble sort the holding array by balance
	//Then print out to screen.
	progressBar();
	printBankLogo();
	int accountsToSort[maxUser], transferForCount, toSortCount=0, loopCount, temp, checkCount, anotherCount;
	
	//Loop through all items in the userData struct
	for(transferForCount=0; transferForCount<maxUser; transferForCount++){
		if((userData[transferForCount].active == 1) && (userData[transferForCount].role == 1)){
			//Needs to be transfered onto the accountsToSort
			accountsToSort[toSortCount] = transferForCount;
			toSortCount++;
		}
	}

	for(loopCount=0; loopCount < toSortCount; loopCount++){
		for(anotherCount=0; anotherCount < toSortCount-loopCount-1; anotherCount++){
			if(userData[accountsToSort[anotherCount]].balance > userData[accountsToSort[anotherCount+1]].balance){
				//Swap
				temp = accountsToSort[anotherCount + 1];
				accountsToSort[anotherCount+1] = accountsToSort[anotherCount];
				accountsToSort[anotherCount] = temp;
			}
		}
	}
	//Now we have a sorted array of index positions
	//Now to print out
	
	
	//First we need to print the header
	printf("\n|-------------------------------------------------------------|");
	printf("\n|               CURRENT BALANCES (LOW TO HIGH)                |");
	printf("\n|-------------------------------------------------------------|");
	printf("\n| ACCOUNT ID |   FIRST NAME   |    LAST NAME    |   BALANCE   |");
	printf("\n|-------------------------------------------------------------|");
		
	int printCount;
	for(printCount=0; printCount<toSortCount; printCount++){
		printf("\n| %10d | %-14s | %-15s | %11.2f |",userData[accountsToSort[printCount]].userId, userData[accountsToSort[printCount]].firstName, userData[accountsToSort[printCount]].lastName, userData[accountsToSort[printCount]].balance);
	}
	printf("\n|-------------------------------------------------------------|\n\n");
	system("pause");
	
	adminMenu();


}
void transfer(){
	progressBar();
	printBankLogo();
	puts("ACCOUNT TO ACCOUNT TRANSFER");
	//This in theory is a withdraw then a deposit into a different account
	
	//Withdraw section
	int accountToTransferTo, valid=0, accountToTransferToPos;
	char holdingChar[10];
	float transferAmount;
	
	while(valid == 0){
		printf("Please enter what account you wish to transfer the money to: ");
		fflush(stdin);
		gets(holdingChar);
		accountToTransferTo = atoi(holdingChar);
		printf("\nPlease enter what amount of money you wish to transfer the money to: ");
		fflush(stdin);
		gets(holdingChar);
		transferAmount = atof(holdingChar);
		
		if((transferAmount <= userData[structureLocationCurrentUserId].balance) && (transferAmount != 0) && (userData[structureLocationCurrentUserId].active = 1)){
			//Valid transfer. Need to check account
			int x, loopIncrement=0;
			for(x=0; x<maxUser; x++){
				if(accountToTransferTo == userData[x].userId){
					//Valid transfer to account
					accountToTransferToPos = x;
					accountToTransferTo == userData[x].userId;
					valid = 1;;
					break;
				}else {
					valid = 0;
				}
				loopIncrement = loopIncrement + 1;
			}
		}else{
			valid = 0;
		}
		if(valid==0){
			printf("That wasn't valid. Please re-enter");
			valid = 0;
			sleep(sleepTime);
			system("cls");
			printBankLogo();
		}		
	} //End of while
	
	//Now we have a valid amount to transfer into a valid account
	//First update userData
	userData[structureLocationCurrentUserId].balance = userData[structureLocationCurrentUserId].balance - transferAmount;
	userData[accountToTransferToPos].balance = userData[accountToTransferToPos].balance + transferAmount;
	closeUserData();

	//Now write entry into transaction
	//First withdrawal from account
	transactions[maxTransaction].userId = userData[structureLocationCurrentUserId].userId;
	transactions[maxTransaction].transCode = 3;
	transactions[maxTransaction].amountIn = 0.00;
	transactions[maxTransaction].amountOut = transferAmount;
	transactions[maxTransaction].writeOut = 1;
	maxTransaction++;

	//Deposit into account
	transactions[maxTransaction].userId = userData[accountToTransferToPos].userId;
	transactions[maxTransaction].transCode = 4;
	transactions[maxTransaction].amountIn = transferAmount;
	transactions[maxTransaction].amountOut = 0.00;
	transactions[maxTransaction].writeOut = 1;
	maxTransaction++;
	closeTransactions();
	
	puts("---\nTransaction complete. Returning to main menu");
	sleep(sleepTime);
	loggedInMenu();
}
void reactivate(){
	progressBar();
	printBankLogo();
	//Account can be reactivated by an admin user
	int accountToReactivate, locationInStruct, faliure;
	char holdingChar[10];
	puts("REACTIVATE ACCOUNT");
	printf("\nPlease enter the user ID of the account to be reactivated: ");
	fflush(stdin);
	gets(holdingChar);
	accountToReactivate = atoi(holdingChar);
	
	//Now check if it is an active user
	int loopCount;
	for(loopCount=0; loopCount<maxUser; loopCount++){
		if(userData[loopCount].userId == accountToReactivate){
			//Reactivate this one
			faliure = 0;
			userData[loopCount].active = 1;
			closeUserData();
			puts("Account reactivated sucsessfully");
			break;
		}else{
			faliure++;
		}
	}
	if(faliure > 0 ){
		//User not found
		puts("That user wasn't found");
		puts("Please re-enter");
		sleep(sleepTime);
		reactivate();
	}
	system("pause");
	adminMenu();
}
void deactivate(){
	progressBar();
	printBankLogo();
	//Account can be deactivated by an admin user
	int accountToReactivate, locationInStruct, faliure;
	char holdingChar[10];
	puts("DEACTIVATE ACCOUNT");
	printf("\nPlease enter the user ID of the account to be deactivated: ");
	fflush(stdin);
	gets(holdingChar);
	accountToReactivate = atoi(holdingChar);
	
	//Now check if it is an active user
	int loopCount;
	for(loopCount=0; loopCount<maxUser; loopCount++){
		if(userData[loopCount].userId == accountToReactivate){
			//Deactivate this one
			faliure = 0;
			userData[loopCount].active = 0;
			closeUserData();
			puts("Account deactivated sucsessfully");
			break;
		}else{
			faliure++;
		}
	}
	if(faliure == maxUser-1){
		//User not found
		puts("That user wasn't found");
		puts("Please re-enter");
		sleep(sleepTime);
		reactivate();
	}
	system("pause");
	adminMenu();
}
void startUp(){
	//Progress Bar adapted from Geeksforgeeks
	
	puts("\t  _    _                           ____              _     ");
	puts("\t | |  | |                         |  _ \\            | |    ");
	puts("\t | |__| | __ _ _ __  _ __  _   _  | |_) | __ _ _ __ | | __ ");
	puts("\t |  __  |/ _` | '_ \\| '_ \\| | | | |  _ < / _` | '_ \\| |/ / ");
	puts("\t | |  | | (_| | |_) | |_) | |_| | | |_) | (_| | | | |   <  ");
	puts("\t |_|  |_|\\__,_| .__/| .__/ \\__, | |____/ \\__,_|_| |_|_|\\_\\ ");
	puts("\t              | |   | |     __/ |                          ");
	puts("\t              |_|   |_|    |___/                           ");
	
	
	printf("\n\t\tAS-LEVEL COMPUTER SCIENCE PROGRAMMING CHALLENGE");
	
	// Print initial loading bar 

	int i;
	printf("\n\n\t\t\t    SYSTEM STARTING UP   ");
	printf("\n\n\t  ");

	for (i = 0; i < 55; i++){
		printf("%c", 177);
	}
		 
	// Set the cursor starting point back to start
	printf("\r"); 
	
	printf("\t  ");
	// Print loading bar progress 
	for (i = 0; i < 55; i++) { 
		printf("%c", 219); 

		// Sleep for 0.1 second 
		Sleep(100); 
	}
}
void adminPrintAllTransactions(){
	//Gives the admin user a way to see all transactions in bank
	int loopCount;
	char transCodeString[14];
	
	printf("\n|----------------------------------------------------|");
	printf("\n|               OVERVIEW OF TRANSACTIONS             |");
	printf("\n|----------------------------------------------------|");
	printf("\n| UserID | Transaction Code | Amount In | Amount Out |");
	printf("\n|----------------------------------------------------|");
	for(loopCount=0; loopCount<maxTransaction; loopCount++){
		switch(transactions[loopCount].transCode){
			case 1:
				strcpy(transCodeString, "Withdrawal");
				break;
			case 2:
				strcpy(transCodeString, "Deposit");
				break;
			case 3:
				strcpy(transCodeString, "Transfer Out");
				break;
			case 4:
				strcpy(transCodeString, "Transfer In");
				break;
			default:
				strcpy(transCodeString, "Unknown code");
				break;
		}
		
		printf("\n| %6d | %16s | %9.2f | %10.2f |", transactions[loopCount].userId, transCodeString, transactions[loopCount].amountIn, transactions[loopCount].amountOut);
	}
		printf("\n|----------------------------------------------------|\n");
	system("pause");
	adminMenu();
}
void adminPrintAllAccounts(){
	//Print all account info for all accounts
	int loopCount;
	char activeHolding[10], roleHolding[15];
	puts("|------------------------------------------------------------------------------------------------|");
	puts("|                                     ALL ACCOUNT INFORMATION                                    |");
	puts("|------------------------------------------------------------------------------------------------|");
	puts("| USER ID |  FIRST NAME  |  LAST NAME   |   BALANCE  |  PIN   |      ROLE       | ACCOUNT STATUS |");
	puts("|------------------------------------------------------------------------------------------------|");
	
	
	for(loopCount=0; loopCount<maxUser; loopCount++){
		switch(userData[loopCount].active){
			case 0:
				strcpy(activeHolding, "Inactive");
				break;
			case 1:
				strcpy(activeHolding, "Active");
				break;
			default:
				strcpy(activeHolding, "Unknown");
				break;
		}
		switch(userData[loopCount].role){
			case 1:
				strcpy(roleHolding, "Standard");
				break;
			case 2:
				strcpy(roleHolding, "Administrator");
				break;
			default:
				strcpy(roleHolding, "Unknown");
		}
		
		printf("| %7d | %12s | %12s | %10.2f | %6d | %15s | %14s |\n", userData[loopCount].userId, userData[loopCount].firstName, userData[loopCount].lastName, userData[loopCount].balance, userData[loopCount].pin, roleHolding, activeHolding);
	}
	printf("|------------------------------------------------------------------------------------------------|\n");
	system("pause");
	adminMenu();
}


