

int compareTwoMobileNumbersUtilityLayer(char mobile1[], char mobile2[]) {
    for (int index = 0; index < 10; index++) {
        if (mobile1[index] != mobile2[index]) {
            return 0;
        }
    }
    return 1;
}