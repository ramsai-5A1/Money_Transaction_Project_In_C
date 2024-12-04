
# include <stdio.h>
# include <string.h>
# include "userBox.c"
# include "authFunctions.c"

void printOuterMenu() {
    printf("\n\n\n*********************MENU************************");
    printf("\n1 - Register");
    printf("\n2 - Login");
    printf("\n3 - Exit");
    printf("\n4 - To print all customer Details");
    printf("\n*********************************************");
}

int compareTwoMobileNumbers(char mobile1[], char mobile2[]) {
    for (int index = 0; index < 10; index++) {
        if (mobile1[index] != mobile2[index]) {
            return 0;
        }
    }
    return 1;
}

void printAllUsersDetails() {
    FILE *ptr = fopen("userObjects.bin", "rb");
    if (ptr == NULL) {
        printf("\nSomething went wrong");
        return;
    }
    printf("\n\nAll users details are listed below:\n");
    struct UserBox currObj;
    while (fread(&currObj, sizeof(struct UserBox), 1, ptr) == 1) {
        printf("\nFirst name is: %s", currObj.firstName);
        printf("\nLast name is: %s", currObj.lastName);
        printf("\nEmail-id is: %s", currObj.email);
        printf("\nMobile number is: %s", currObj.mobileNumber);
        printf("\n\n");
    }
    fclose(ptr);
    printf("\nThe End of all users data\n");
}

int isMobileNumberPresentInDatabase(char mobileNumber[]) {
    FILE *ptr = fopen("userObjects.bin", "rb");
    if (ptr == NULL) {
        printf("\nSomething went wrong");
        return 0;
    }

    struct UserBox object;
    while (fread(&object, sizeof(struct UserBox), 1, ptr) == 1) {
        if (compareTwoMobileNumbers(object.mobileNumber, mobileNumber) == 1) {
            return 1;
        }
    }

    fclose(ptr);
    return 0;
}

int writeUserDataIntoFile(struct UserBox object) {
    FILE *ptr = fopen("userObjects.bin", "ab");
    if (ptr == NULL) {
        printf("\nSomething went wrong");
        return 0;
    }

    fwrite(&object, sizeof(struct UserBox), 1, ptr);
    fclose(ptr);
    return 1;
}

void collectDetailsFromUserAndStoreInDatabase(char mobileNumber[]) {
    char firstName[50];
    char lastName[50];
    int pin;
    int confirmPin;
    char email[50];

    printf("\nEnter your first-name: ");
    scanf("%[^\n]s", firstName);
    getchar();

    printf("\nEnter your last-name: ");
    scanf("%[^\n]s", lastName);
    getchar();

    printf("\nEnter your email: ");
    scanf("%[^\n]s", email);
    getchar();

    while (1) {
        printf("\nSet up your 4-digit pin: ");
        scanf("%d", &pin);

        if (pin < 1000 || 9999 < pin) {
            printf("\nPlease select 4-digit pin itself");
            continue;
        } 

        printf("\nConfirm your 4-digit pin: ");
        scanf("%d", &confirmPin);

        if (pin != confirmPin) {
            printf("\nPlease confirm pin correctly");
        } else {
            break;
        }
    }

    struct UserBox object;
    strcpy(object.firstName, firstName);
    strcpy(object.lastName, lastName);
    strcpy(object.email, email);
    strcpy(object.mobileNumber, mobileNumber);
    object.pin = pin;

    int isWriteSuccessfull = writeUserDataIntoFile(object);
    if (isWriteSuccessfull == 1) {
        printf("\nRegistered successfully\n");
    } else {
        printf("\nThere is some probelm encountered while storing");
    }
}

void handleRegister() {
    printf("\nEnter your mobile number (without any gaps inbetween): ");
    char mobileNumber[12];
    scanf("%[^\n]s", mobileNumber);
    getchar();

    int isUserAlreadyPresent = isMobileNumberPresentInDatabase(mobileNumber);

    if (isUserAlreadyPresent == 1) {
        printf("\nUser already registered, kindly please login\n");
        return;
    } 
    collectDetailsFromUserAndStoreInDatabase(mobileNumber);  
}

int isPinMatching(char mobileNumber[], int pin) {
    FILE *ptr = fopen("userObjects.bin", "rb");
    if (ptr == NULL) {
        printf("\nSomething went wrong");
        return 0;
    }

    struct UserBox object;
    while (fread(&object, sizeof(struct UserBox), 1, ptr) == 1) {
        if (compareTwoMobileNumbers(mobileNumber, object.mobileNumber) == 1 && object.pin == pin) {
            return 1;
        }
    }

    fclose(ptr);
    return 0;
}

void handleLogin() {
    printf("\nEnter your mobile number (without any gaps inbetween): ");
    char mobileNumber[12];
    scanf("%[^\n]s", mobileNumber);
    getchar();

    int isUserAlreadyPresent = isMobileNumberPresentInDatabase(mobileNumber);

    if (isUserAlreadyPresent == 0) {
        printf("\nKindly please Register before logging in");
        return;
    } 

    int attempts = 3;
    while(attempts > 0) {
        int pin;
        printf("\nEnter 4-digit pin: ");
        scanf("%d", &pin);

        if (isPinMatching(mobileNumber, pin) == 1) {
            break;
        } else {
            printf("\nIncorrect-pin");
        }
        attempts--;
    }

    if (attempts > 0) {
        printRecursiveMenu();
    } else {
        printf("\nYou've exhausted your max limit of passwords");
    }
}





