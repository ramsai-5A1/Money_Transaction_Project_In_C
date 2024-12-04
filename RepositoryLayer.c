# include <stdio.h>
# include <string.h>
# include "userBox.c"
# include "UtilityLayer.c"
# include "constants.c"
# include "BankAccount.c"

int isMobileNumberPresentInDatabaseRepositoryLayer(char mobileNumber[]) {
    FILE *ptr = fopen("userObjects.bin", "rb");
    if (ptr == NULL) {
        printf("\nSomething went wrong");
        return 0;
    }

    struct UserBox object;
    while (fread(&object, sizeof(struct UserBox), 1, ptr) == 1) {
        if (compareTwoMobileNumbersUtilityLayer(object.mobileNumber, mobileNumber) == 1) {
            return 1;
        }
    }

    fclose(ptr);
    return 0;
}

int isPinMatchingRepositoryLayer(char mobileNumber[], int pin) {
    FILE *ptr = fopen("userObjects.bin", "rb");
    if (ptr == NULL) {
        printf("\nSomething went wrong");
        return 0;
    }

    struct UserBox object;
    while (fread(&object, sizeof(struct UserBox), 1, ptr) == 1) {
        if (compareTwoMobileNumbersUtilityLayer(mobileNumber, object.mobileNumber) == 1 && object.pin == pin) {
            return 1;
        }
    }

    fclose(ptr);
    return 0;
}

void printAllUsersDetailsRepositoryLayer() {
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

int writeUserDataIntoFileRepositoryLayer(char firstName[50], char lastName[50], char email[50], char mobileNumber[12], int pin) {
    struct UserBox object;
    strcpy(object.firstName, firstName);
    strcpy(object.lastName, lastName);
    strcpy(object.email, email);
    strcpy(object.mobileNumber, mobileNumber);
    object.pin = pin;

    FILE *ptr = fopen("userObjects.bin", "ab");
    if (ptr == NULL) {
        printf("\nSomething went wrong");
        return 0;
    }

    fwrite(&object, sizeof(struct UserBox), 1, ptr);
    fclose(ptr);

    return 1;
}

int linkBankAccountsRepositoryLayer(char mobileNumber[], int option) {
    printf("\nYou've selected: %s", allBanks[option - 1]);
    FILE *ptr = fopen("accountsInformation.bin", "ab");
    if (ptr == NULL) {
        printf("\nSomething went wrong");
        return 0;
    }
    int found = 0;
    struct BankAccount object;
    while (fread(&object, sizeof(struct BankAccount), 1, ptr) == 1) {
        if (compareTwoMobileNumbersUtilityLayer(mobileNumber, object.mobileNumber) == 1) {
            printf("\nTodo logic here");
            found = 1;
            break;
        }
    }

    if (found == 0) {
        strcpy(object.mobileNumber, mobileNumber);
        object.bankAccounts[0] = allBanks[option - 1];
        fwrite(&object, sizeof(struct BankAccount), 1, ptr);
        printf("\nInserted a fresh record successfully");
    }
    fclose(ptr);
    return 1;
}


