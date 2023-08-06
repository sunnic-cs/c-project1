#include <stdio.h>
#include <conio.h> // getch
#include <string.h> // Strcpy, Strcmp, Strlen
#include <stdlib.h> //includes functions involving memory allocation, process control, system(cls)
#include <Windows.h> 
#include <sys/stat.h>
// DISABLING WARNING
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

struct id
{
    char donate_code[30];
    char distribute_code[30];
    struct id* next;
};

struct donate
{
    char item_name[30];
    char item_id[30];
    char donator[30];
    char donate_id[30];
    int shipment;
    float quantity;
    struct donate* next;
    // struct node* start; points to the first node of the linked list in the file
}*start = NULL;

struct distribute
{
    char distributed_item[30];
    float distributed_quant;
    char hospital[30];
    char distribute_id[30];
    char donation_did[30];
    struct distribute* next;
    // struct node* start; points to the first node of the linked list in the file
};


// function to write new donation record to file
void inventory_new() {
    // declaring linked list
    struct donate *curr=NULL;
    char save;
    // function prototype
    void id_update(int idtype);
    // referencing curr and start to NULL
    curr = start = NULL;
    // Append to first node

    if (start == NULL)
    {
        void data_entry_donation();
        //Allocating memory
        curr = start = (struct donate*)malloc(sizeof(struct donate));
        while (getchar() != '\n');
            // data entry
        data_entry_donation();
    }
    printf("Do you want to save the file ? 'y' to continue\n");
    scanf_s("%c", &save,1); while (getchar() != '\n');
    if (save == 'y') {
        id_update(1);
        void writetoFile(char filename[], donate* start);
        char file[] = "donation.txt";
        writetoFile(file, start);
    }
}

//function to add more record to file
void inventory_add() {
    // declaring linked list
    struct donate* curr = NULL;
    char save;
    // referencing curr and start to NULL
    void appendtoFile(char filename[], donate * start); // function prototype
    void id_update(int idtype);
    struct donate* read_LinkedList(char filename[]);
    void data_entry_donation();
    char file[] = "donation.txt";
    read_LinkedList(file); 
    //Allocating memory
    curr = start = (struct donate*)malloc(sizeof(struct donate));
    while (getchar() != '\n');
    // data entry
    data_entry_donation();
    printf("Do you want to save the file ? 'y' to continue\n");
    scanf_s("%c", &save, 1); while (getchar() != '\n');
    if (save == 'y') {
        id_update(1);
        void appendtoFile(char filename[], donate * start);
        char file[] = "donation.txt";
        appendtoFile(file, start);
    }
}

// function to generate the first id
void id_gen() {
    FILE* fpt;
    fopen_s(&fpt, "id.txt", "w");
    if (fpt == NULL)
    {
        printf("\n Error in opening file!");
        _getch();
    }
    else {
        fprintf(fpt, "0DOID ; 0DIID");
        if (fwrite != 0)
        {
            printf("\n ID has been Generated succesfully! \n");
            _getch();
        }
        else
        {
            printf("Error While Writing\n");
            _getch();
        }
    }
    fclose(fpt);
}

//function to update the id
void id_update(int idtype) {
    char t1[100];
    char t2[100];
    FILE* fpt;
    fopen_s(&fpt, "id.txt", "r");
    if (fpt == NULL) {
        printf("Error");
        _getch();
    }
    fscanf(fpt, "%s ; %s", t1, t2); 
    
    freopen("id.txt","w",fpt);
    if (fpt == NULL) {
        printf("Error in opening the file");
        _getch();
    }
    else {
        // atoi() = Converting from string to Integer from stdlib.h
        if (idtype == 1) {
            int new_t1 = atoi(t1) + 1; // Updated Donate ID
            int new_t2 = atoi(t2);
            fprintf(fpt, "%dDOID ; %dDIID", new_t1, new_t2);
        }
        else if (idtype == 2) {
            int new_t1 = atoi(t1);
            int new_t2 = atoi(t2) + 1; // Updated Distribute ID
            fprintf(fpt, "%dDOID ; %dDIID", new_t1, new_t2);
        }
    }
    _getch();
    fclose(fpt);
}

// function to read id
struct id* id_read(int idtype) {
    struct id* curr = NULL;
    char t1[100];
    char t2[100];

    FILE* fpt;
    fopen_s(&fpt, "id.txt", "r");
    if (fpt == NULL) {
        printf("Error");
        _getch();
    }
    else {
        fscanf(fpt, "%s ; %s", t1, t2); // Reading from file
        curr = (struct id*)malloc(sizeof(struct id));

        if (idtype == 1) {
            strcpy(curr->donate_code, t1);
        }
        else if (idtype == 2) {
            strcpy(curr->distribute_code, t2);
        }
    }
    fclose(fpt);
    return curr;
}

// function to get input from user about donation record
void data_entry_donation() {
    int idtype = 1; // this indicate to the donation file
    //initialize curr
    struct donate* curr = NULL;
    struct id* idcurr = NULL;
    curr = start = (struct donate*)malloc(sizeof(struct donate));
    //data entry
    printf("Enter Item Name:\n");
    scanf("%[^\n]s",curr->item_name); while (getchar() != '\n');   
    printf("Supplier Code:\n");   
    scanf("%s", curr->item_id); while (getchar() != '\n');
    printf("Donate by:\n");;
    scanf("%[^\n]s", curr->donator); while (getchar() != '\n');
    printf("No of Shipment:\n");
    scanf("%d", &curr->shipment); while (getchar() != '\n');
    printf("Qty:\n");
    scanf("%f", &curr->quantity); while (getchar() != '\n');
    idcurr = id_read(idtype);
    int idnum = atoi(idcurr->donate_code)+1;
    printf("Donation ID : %dDOID", idnum);
    // end data entry
    printf("\n\t Data Entry Succeed!\n");
}

// function to append data to file
void appendtoFile(char filename[], donate* start) {
    struct donate* curr = start;
    struct id* idcurr = id_read(1);
    FILE* fpt;
    fopen_s(&fpt, filename, "a");
    if (fpt == NULL)
    {
        printf("\n Error in opening file!");
        _getch();
    }
    else {
        // Writing to file
        fprintf(fpt, "%s ; %s ; %s ; %d ; %f ; %s\n", curr->item_name, curr->item_id, curr->donator, curr->shipment, curr->quantity, idcurr->donate_code);
        curr->next = NULL;

        if (fwrite != 0)
        {
            printf("\n Records has been saved succesfully! \n");
            _getch();
        }
        else
        {
            printf("Error While Writing\n");
            _getch();
        }
    }
    fclose(fpt);
}

// function to write data to file
void writetoFile(char filename[], donate* start) {
    struct donate* curr = start;
    struct id* idcurr = id_read(1);

    FILE* fpt;
    fopen_s(&fpt, filename, "w");
    if (fpt == NULL)
    {
        printf("\n Error in opening file!");
    }
    else {
        fprintf(fpt, "%s ; %s ; %s ; %d ; %f ; %s\n", curr->item_name, curr->item_id, curr->donator, curr->shipment, curr->quantity, idcurr->donate_code);
        curr->next = NULL;

        if (fwrite != 0)
        {
            printf("\n Record has been written succesfully! \n");
        }
        else
        {
            printf("Error While Writing\n");
        }
    }
    fclose(fpt);
    _getch();
}

// function to search item record based on donation id
void search_id() {
    struct donate* read_LinkedList(char filename[]); // function prototype
    char file[] = "donation.txt";
    start = read_LinkedList(file);
    struct donate* curr = NULL;
    curr = start;
    char id[10];
    int flag = 0;

    printf("Input Donation ID = ");
    scanf("%s", id); while (getchar() != '\n');
    do {
        if (strcmp(id, curr->donate_id) == 0) {
            printf("Match is found\n");
            printf("1.Item Name : %s\n", curr->item_name);
            printf("2.Supplier Code : %s\n", curr->item_id);
            printf("3.Donator : %s\n", curr->donator);
            printf("4.Shipment : %d\n", curr->shipment);
            printf("5.Quantity : %.1f Millions\n", curr->quantity);
            printf("6.Donation ID : %s\n", curr->donate_id);
            flag = 1;
            break;
        }
        curr = curr->next;
    } while (curr != NULL);
    if (flag == 0) {
        printf("Item not found");
    }
    _getch();
}

// function to add to the quantity of specific item
void donation_add() {
    struct donate* read_LinkedList(char filename[]); // function prototype
    char file[] = "donation.txt";
    start = read_LinkedList(file); // Reading each node from linked list
    struct donate* curr = NULL;
    curr = start;
    float quant_add;
    char id[10];
    int flag = 0;

    printf("Input Donation ID = "); // Asking for search key
    scanf("%s", id); while (getchar() != '\n');
    do {      
        // Comparing Search key with data in linked list
        if (strcmp(id, curr->donate_id) == 0) {
            printf("Match is found\n");
            printf("1.Item Name : %s\n", curr->item_name);
            printf("2.Supplier Code : %s\n", curr->item_id);
            printf("3.Donator : %s\n", curr->donator);
            printf("4.Shipment : %d\n", curr->shipment);
            printf("5.Quantity : %.1f Millions\n", curr->quantity);
            printf("6.Donation ID : %s\n", curr->donate_id);
            flag = 1;
            printf("Quantity to be added : \n");
            scanf("%f", &quant_add); while (getchar() != '\n');
            curr->quantity = curr->quantity + quant_add;
            curr->shipment = curr->shipment + 1;
            printf("New Quantity is : %.1f Millions\n", curr->quantity);
            break;
        }
        curr = curr->next; // next node     
    } while (curr != NULL);

    if (flag == 1) {
        // Updating donation.txt
        FILE* fpt;
        fopen_s(&fpt, "donation.txt", "w");
        if (fpt == NULL) {
            printf("Error in opening file");
        }
        else {
            // Rewriting to donation.txt file node by node
            do {
                fprintf(fpt, "%s ; %s ; %s ; %d ; %f ; %s\n", curr->item_name, curr->item_id, curr->donator, curr->shipment, curr->quantity, curr->donate_id);
                curr = curr->next;
            } while (curr != NULL);
            // Testing whether file is written
            if (fwrite != 0)
            {
                printf("\n Record has been updated succesfully! \n");
            }
            else
            {
                printf("Error While Writing\n");
            }
        }
        curr = start;
        fclose(fpt);
    }
    else if (flag == 0) {
        printf("Item not found");
    }
    _getch();
}

// function to show donation record on output
void view_donation() {
    int no = 0;
    struct donate* curr = NULL;
    struct donate* read_LinkedList(char filename[]);  // function prototype

    printf("\n Displaying All Data in donation.txt\n\n");
    printf("\n =====================================================================================================================================================");
    printf("\n %-5s  %-30s  %-20s  %-20s  %-20s  %-30s %-30s", "NO", "Item Name", "Supplier Code", "Donator", "Shipment", "No.Quantity(Millions)", "Donation ID");
    printf("\n =====================================================================================================================================================");
    char file[] = "donation.txt";
    curr = read_LinkedList(file);
    do
    {
        no++;
        printf("\n %-5d  %-30s  %-20s  %-20s  %-20d  %-30.1f  %-30s", no, curr->item_name, curr->item_id, curr->donator, curr->shipment, curr->quantity, curr->donate_id);
        curr = curr->next;
    } while (curr != NULL);
    _getch();
}



struct donate* read_LinkedList(char filename[]) {
    struct donate* curr = NULL;
    struct donate* tempstart = NULL;

    FILE* fpt;
    fopen_s(&fpt, filename, "r");

    if (fpt == NULL) {
        printf("Error\n");
        _getch();
    }
    else {
        char t[100], t2[100], t3[100], t6[100];
        int t4;
        float t5;

        //Reading Linked List from file
        while (fscanf(fpt, "%[^\n;] ; %s ; %[^\n;] ; %d ; %f ; %s\n", t, t2, t3, &t4, &t5, t6) != EOF)
        {
            if (tempstart == NULL) { // First node
                tempstart = curr = (struct donate*)malloc(sizeof(struct donate));
            }
            else { // Next node
                curr->next = (struct donate*)malloc(sizeof(struct donate));
                curr = curr->next;
            }
            strcpy(curr->item_name, t);
            strcpy(curr->item_id, t2);
            strcpy(curr->donator, t3);
            curr->shipment = t4;
            curr->quantity = t5;
            strcpy(curr->donate_id, t6);
            curr->next = NULL;  // NULL is for comparison with end of linked list
        }
    }
    fclose(fpt);
    return tempstart;



    
}

//function to show distribution record on output
void view_distribution() {
    int no = 0;
    struct distribute* curr = NULL;
    struct distribute* read_LinkedList1(char filename[]);  // function prototype

    printf("\n Displaying All Data in dist.txt\n\n");
    printf("\n =====================================================================================================================================================");
    printf("\n %-5s  %-30s  %-20s  %-20s  %-20s  %-30s", "NO", "Item Name", "Donation ID", "Hospital", "Distributed Quantity(Millions)", "Distribution ID");
    printf("\n =====================================================================================================================================================");
    char file[] = "dist.txt";
    curr = read_LinkedList1(file);
    do
    {
        no++;
        printf("\n %-5d  %-30s  %-20s  %-20s  %-30.1f  %-30s", no, curr->distributed_item, curr->donation_did, curr->hospital, curr->distributed_quant, curr->distribute_id);
        curr = curr->next;
    } while (curr != NULL);
    _getch();
}

// function to read distribute linked list
struct distribute* read_LinkedList1(char filename[]) {
    FILE* fpt;
    fopen_s(&fpt, filename, "r");

    if (fpt == NULL) {
        printf("Error");
        _getch();
    }

    struct distribute* curr = NULL;
    struct distribute* tempstart = NULL;

    char t[100], t2[100], t3[100], t6[100];
    float t5;

    //Reading Linked List from file
    while (fscanf(fpt, "%[^\n;] ; %s ; %[^\n;] ; %f ; %s\n", t, t2, t3, &t5, t6) != EOF)
    {
        if (tempstart == NULL) { // First node
            tempstart = curr = (struct distribute*)malloc(sizeof(struct donate));
        }
        else { // Next node
            curr->next = (struct distribute*)malloc(sizeof(struct distribute));
            curr = curr->next;
        }
        strcpy(curr->distributed_item, t);
        strcpy(curr->donation_did, t2);
        strcpy(curr->hospital, t3);
        curr->distributed_quant = t5;
        strcpy(curr->distribute_id, t6);
        curr->next = NULL;  // NULL is for comparison with end of linked list
    }
    fclose(fpt);
    return tempstart;
}

// function to do distribution
void distribution_add(char mode[]) {
    struct donate* read_LinkedList(char filename[]); // function prototype
    char file[] = "donation.txt";
    start = read_LinkedList(file); // Reading each node from linked list donation
    struct donate* curr = NULL;
    struct id* idcurr = NULL;
    curr = start;
    float quant_dist;
    char id[10], hospital[30];
    int flag = 0;

    printf("Input Donation ID of Item to be Distributed = "); // Asking for search key
    scanf("%s", id); while (getchar() != '\n');
    do {
        // Comparing Search key with data in linked list
        if (strcmp(id, curr->donate_id) == 0) {
            system("cls");
            printf("Match is found\n");
            printf("Donation ID : %s\n", curr->donate_id);
            printf("Item Name : %s\n", curr->item_name);
            printf("Current Quantity : %.1f Millions\n", curr->quantity);
            printf("Quantity to be distributed : \n");
            scanf("%f", &quant_dist); while (getchar() != '\n');
            if (curr->quantity<=quant_dist){
                flag = 2;
                printf("Quantity Exceed the Stock! Please Try again\n");
            } else { 
                flag = 1;
                printf("Distribution/Hospital Target : \n");
                scanf("%[^\n]s",hospital); while (getchar() != '\n');
                curr->quantity = curr->quantity - quant_dist;
                printf("New Quantity is : %.1f Millions\n", curr->quantity);
                // Distribution ID function
                id_update(2);
                idcurr = id_read(2);
                printf("Distribution ID is %s", idcurr->distribute_code);
                // Writing on dist.txt file
                FILE* dispt;
                fopen_s(&dispt, "dist.txt", mode);
                if (dispt == NULL) {
                    printf("Error in opening file");
                }
                else {
                    // printing to file
                    fprintf(dispt, "%s ; %s ; %s ; %f ; %s\n", curr->item_name, curr->donate_id, hospital, quant_dist, idcurr->distribute_code);
                    // Testing whether file is written
                    if (fwrite != 0)
                    {
                        printf("\n Distribution Record has been updated succesfully! \n");
                    }
                    else
                    {
                        printf("Error While Writing\n");
                    }
                }
                fclose(dispt);
            }     
            break;
        }
        curr = curr->next; // next node     
    } while (curr != NULL);

    if (flag == 1) {
        // Updating donation.txt
        FILE* fpt;
        fopen_s(&fpt, "donation.txt", "w");
        if (fpt == NULL) {
            printf("Error in opening file");
        }
        else {
            curr = start; // Move to first node
        // Rewriting to donation.txt file node by node
            do {
                fprintf(fpt, "%s ; %s ; %s ; %d ; %f ; %s\n", curr->item_name, curr->item_id, curr->donator, curr->shipment, curr->quantity, curr->donate_id);
                curr = curr->next;
            } while (curr != NULL);
            // Testing whether file is rewritten
            if (fwrite != 0)
            {
                printf("\n Donation Record has been updated succesfully! \n");
            }
            else
            {
                printf("Error While Writing\n");
            }
        }
        fclose(fpt);    
    }
    else if (flag == 0) {
        printf("Item not found");
    }
    _getch();
}

// function to do addition and distribution
int update_data() {
    int ans;
    do {
        system("cls");
        printf("1. Add to the quantity by Donation ID\n");
        printf("2. Distribute the item by Donation ID\n");
        printf("3. Input New Distribution List\n");
        printf("4. Back To MENU\n");
        printf("Choice --> ");
        scanf("%d", &ans); while (getchar() != '\n');
        switch (ans) {
        case 1:
        {
            donation_add();
            break;
        }
        case 2:
        {
            char mode[] = "a";
            distribution_add(mode);
            break;
        }
        case 3:
        {
            char mode[] = "w";
            distribution_add(mode);
            break;
        }
        case 4:
        {
            break;
        }
        default:
            printf("Invalid Choice!");
            _getch();
        }

    } while (ans != 4);
    return 0;
}

// function that show sorted data
void view_all_sorted() {
    void bubbleSort_Donation(struct donate* start);
    void bubbleSort_Distribute(struct distribute* start);
    int no = 0;
    char file0[] = "donation.txt";
    struct donate* curr = read_LinkedList(file0);
    bubbleSort_Donation(curr);
    char file[] = "dist.txt";
    struct distribute* dcurr = NULL;
    struct distribute* tempstart = NULL;
    dcurr = read_LinkedList1(file);
    bubbleSort_Distribute(dcurr);
    printf("\n Displaying Sorted Donation and Its Distribution Records\n\n");
    do
    {
        printf("\n\n\n\n =====================================================================================================================================================");
        printf("\n %-5s  %-30s  %-20s  %-20s  %-20s  %-30s %-30s", "NO", "Item Name", "Supplier Code", "Donator", "Shipment", "Quantity Stored(Millions)", "Donation ID");
        printf("\n =====================================================================================================================================================");
        no++;
        printf("\n %-5d  %-30s  %-20s  %-20s  %-20d  %-30.1f  %-30s", no, curr->item_name, curr->item_id, curr->donator, curr->shipment, curr->quantity, curr->donate_id);
        printf("\n\n =========================================================================================");
        printf("\n %-20s  %-30s  %-20s", "Qty Distributed", "Hospital/Destination", "Distribution ID");
        printf("\n =========================================================================================");
        tempstart = dcurr;
        while (tempstart !=NULL) {
            if (strcmp(curr->donate_id, tempstart->donation_did) == 0) {
                printf("\n %-20.1f  %-30s  %-20s", tempstart->distributed_quant, tempstart->hospital, tempstart->distribute_id);
            }
            tempstart = tempstart->next;
        }
        curr = curr->next;
    } while (curr != NULL);
    _getch();
}


// Bubble sort the donate linked list
void bubbleSort_Donation(struct donate* start)
{
    void swap(struct donate* x, struct donate* y); // function prototype
    int swapped;
    struct donate* curr;
    struct donate* tempcurr = NULL;

    // Checking for empty list 
    if (start == NULL) {
        printf("Record is empty");
        _getch();
    }
    do
    {
        swapped = 0;
        curr = start;
        while (curr->next != tempcurr)
        {
            if (curr->quantity < curr->next->quantity)
            {
                swap(curr, curr->next);
                swapped = 1;
            }
            curr = curr->next;
        }
        tempcurr = curr;
    } while (swapped); // if swapped = 1 then True
}

// Function to swap position of two nodes x and y within donate structure
void swap(struct donate* x, struct donate* y)
{
    float temp = x->quantity;
    x->quantity = y->quantity;
    y->quantity = temp;

    char itemtemp[100];
    strcpy(itemtemp,x->item_name);
    strcpy(x->item_name,y->item_name);
    strcpy(y->item_name,itemtemp);

    int shiptemp = x->shipment;
    x->shipment = y->shipment;
    y->shipment = shiptemp;

    char itemidtemp[30];
    strcpy(itemidtemp, x->item_id);
    strcpy(x->item_id, y->item_id);
    strcpy(y->item_id, itemidtemp);

    char donatortemp[100];
    strcpy(donatortemp, x->donator);
    strcpy(x->donator, y->donator);
    strcpy(y->donator, donatortemp);

    char donateidtemp[100];
    strcpy(itemidtemp, x->donate_id);
    strcpy(x->donate_id, y->donate_id);
    strcpy(y->donate_id, itemidtemp);
}

// Bubble sort the distribute linked list
void bubbleSort_Distribute(struct distribute* start)
{
    void swap1(struct distribute* x, struct distribute* y); // function prototype
    int swapped;
    struct distribute* curr;
    struct distribute* tempcurr = NULL;

    // Checking for empty list 
    if (start == NULL) {
        printf("Record is empty");
        _getch();
    }
    do
    {
        swapped = 0;
        curr = start;
        while (curr->next != tempcurr)
        {
            if (curr->distributed_quant < curr->next->distributed_quant)
            {
                swap1(curr, curr->next);
                swapped = 1;
            }
            curr = curr->next;
        }
        tempcurr = curr;
    } while (swapped); // if swapped = 1 then True
}

// Function to swap position of two nodes x and y within distribute structure
void swap1(struct distribute* x, struct distribute* y)
{
    float temp = x->distributed_quant;
    x->distributed_quant = y->distributed_quant;
    y->distributed_quant = temp;

    char hospitaltemp[100];
    strcpy(hospitaltemp, x->hospital);
    strcpy(x->hospital, y->hospital);
    strcpy(y->hospital, hospitaltemp);

    char distidtemp[100];
    strcpy(distidtemp, x->distribute_id);
    strcpy(x->distribute_id, y->distribute_id);
    strcpy(y->distribute_id, distidtemp);
}

int checkIfFileExists(const char* filename) {
    struct stat buffer;
    int exist = stat(filename, &buffer);
    if (exist == 0) // 0  is sucessful -1 is fail
        return 1;
    else
        return 0;
}

int main() {
    int opt;
    do {
        system("cls");
        printf("\n1. Input New Donation Record");
        printf("\n2. Add Donation Record");
        printf("\n3. View Donation Record");
        printf("\n4. Update Donation Record");
        printf("\n5. Search By Donation Code");
        printf("\n6. View Distribution Record");
        printf("\n7. View List of Donations and Distributions (Bubble Sorted by Quantity)");
        printf("\n8. EXIT");
        printf("\nChoose an option : ");
        scanf("%d", &opt); while (getchar() != '\n');
        switch (opt)
        {
        case 1: {
            id_gen();
            inventory_new();
            break;
        }
        case 2: {
            if (checkIfFileExists("donation.txt") == 1) {
                inventory_add();
            }
            else {
                printf("Please create the file (OPTION 1)");
                _getch();
            }
            break;
        }
        case 3: {
            if (checkIfFileExists("donation.txt") == 1) {
                view_donation();
            }
            else {
                printf("Please create the file (OPTION 1)");
                _getch();
            }
            break;
        }
        case 4: {
            if (checkIfFileExists("donation.txt") == 1) {
                update_data();
            }
            else {
                printf("Please create the file (OPTION 1)");
                _getch();
            }
            break;
        }
        case 5: {
            if (checkIfFileExists("donation.txt") == 1) {
                search_id();
            }
            else {
                printf("Please create the file (OPTION 1)");
                _getch();
            }
            break;
        }
        case 6: {
            if (checkIfFileExists("dist.txt") == 1) {
                view_distribution();
            }
            else {
                printf("Please create the file (Update Data Section)");
                _getch();
            }
            break;
        }
        case 7: {
            if (checkIfFileExists("donation.txt") == 1 && checkIfFileExists("dist.txt")== 1) {
                view_all_sorted();
            }
            else {
                printf("Missing donation/distribution file");
                _getch();
            }
            break;
        }
        case 8: {
            break;
        }
        default:
            printf("\n\t Invalid Option!");
            _getch();
            break;
        }
        } while (opt != 8);    
        return 0;
}
