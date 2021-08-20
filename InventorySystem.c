#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Product
{
    char name[31], maker[31];
    float price;
    int quantity;
};

int main(int argc, char **argv){

    //program currently can acoomadte 100 entries
    struct Product inv[100]; //array of Product structures
    FILE *fp = fopen(argv[1], "r"); //file read only pointer
    char buffer[100]; //
    char select; //used for switch case for menu
    char tempName[31]; //used to store user input when searching array
    int lines = 0; //keeps track of how many records are in the structure
    int i, j; //counter in for loops
    int temp; // used to mark how many entries exist in original text file
    int found; // used to mark if an item is found or not during search

    if(fp == NULL) { // file doesn't exist, exit application
      printf("The file name you entered cannot be accessed.\nExiting the application.\n");
      return 1;
    }
    else { //  file exists
      printf("File opened successfully.\n");
    }

    //read original contents of text file into Product structure
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        sscanf(buffer, "%s %s %f %d", inv[lines].name, inv[lines].maker, &inv[lines].price, &inv[lines].quantity);
        lines++;
        temp = lines;
      }

    while (select != '0'){

      /*Print menu options for user to interface with*/
      printf("\nEnter the number of the desired operation or 0 to quit:\n");
      printf("(1)Print Inventory\n(2)Search by Product Name\n(3)Add a Product\n(0)Exit\n");
      /*Capture user input and set switch case variable*/
      scanf(" %c", &select);

      switch (select){
        /*User input is 1, call print contents of txt file*/
        case '1':
        //print the contents of Product structure
          for (i = 0; i < lines; i++) {
            printf("Item Name: %s Manufactuer: %s Price: %.2f Quantity: %d\n",
                      inv[i].name, inv[i].maker, inv[i].price, inv[i].quantity);
            }
          break;

        /*User input is 2, search for entry by product name*/
        case '2':
          printf("\nEnter the name of the product to search for:\n");
          scanf(" %s", tempName); //store input in tempName
          found = 0; //set marker to false
          for (j = 0; j < lines; j++) {
            if (strcmp(inv[j].name, tempName) == 0) {
                        found = 1; //mark as true if condition is met
                        break;
              }
            }

          if (found == 1){ //print product info if it exists
            printf("Product found!\n");
            printf("Item Name: %s Manufactuer: %s Price: %.2f Quantity: %d\n",
                      inv[j].name, inv[j].maker, inv[j].price, inv[j].quantity);
            }
          else{ // product not in array structure
            printf("Product not found.\n");
            }
          break;

        /*User input is 3, add new entry to Product structure*/
        case '3':
          //capture user input and store to proper index in structure
          printf("\nCreate a new product entry:\nSPACES NOT ALLOWED\n");
          printf("Enter the Item Name:\n");
          scanf(" %s", inv[lines].name);
          printf("Enter the Manufacturer:\n");
          scanf(" %s", inv[lines].maker);
          printf("Enter the Price:\n");
          scanf(" %f", &inv[lines].price);
          printf("Enter the Quantity:\n");
          scanf(" %d", &inv[lines].quantity);

          //print back the new entry to confirm
          printf("The new product entry is:\n");
          printf("Item Name: %s Manufactuer: %s Price: %.2f Quantity: %d\n",
                    inv[lines].name, inv[lines].maker, inv[lines].price, inv[lines].quantity);
          lines++; //increment line counter to accomodate new entry
          break;

        /*User input is 0, will break the while loop and exit the program*/
        case '0': break;

        //if any other input is recieved, return to top of while loop
        default:
            printf("Invalid input, please try again.\n");
            break;
      }
    }

    fclose(fp); //close read only fp
    fp = fopen(argv[1], "a+"); //open file again in write-able mode

    //write the new items in the structure back to the text file before closing
    for (i = temp; i < lines; i++) {
        fprintf(fp, "%s %s %.2f %d\n", inv[i].name, inv[i].maker, inv[i].price, inv[i].quantity);
      }

    //close the file
    fclose(fp);
    printf("\nExiting the application. Thank you!\n");
    return 0;
}
