#include<iostream>
#include<curses.h>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<unistd.h>
using namespace std;

class employee{
    private:
        // Variables for employee details
        char name[30];
        char id[5];
        char designation[10];
        int age;
        int ctc;
        int experience;

        // Utility functions
        void waitForEnter(void){
            cout<<"\n\n\n Press enter to go back \n\n";
            cin.get();
            cin.get();
        }

        // Functions to perform desired actions
        void listEmployees(void){
            system("clear");
            FILE *file;
            file= fopen("data.txt", "r");
            cout<<"\n name  id  designation\n";
            while(fscanf(file, "%s %s %s %d %d %d", &name[0], &id[0] , &designation[0], &age, &ctc, &experience)!= EOF)
                cout<<"\n"<<name<<"\t"<<id<<"\t"<<designation;
            fclose(file);
            waitForEnter();
        }

        void showDetails(void){
            system("clear");
            FILE *file;
            char checkId[5];
            cout<<"Enter employee id: ";
            cin>>checkId;
            file= fopen("data.txt", "r");
            while(fscanf(file, "%s %s %s %d %d %d", &name[0], &id[0] , &designation[0], &age, &ctc, &experience)!=EOF)
                if(strcmp(checkId,id)==0){
                    cout<<"\nname: "<<name;
                    cout<<"\nid: "<<id;
                    cout<<"\ndesignation: "<<designation;
                    cout<<"\nage: "<<age;
                    cout<<"\nctc: "<<ctc;
                    cout<<"\nexperience: "<<experience;
                }
            fclose(file);
            waitForEnter();
        }

        void editExisting(void){
            system("clear");
            char checkId[5];
            cout<<"Enter employee id: ";
            cin>>checkId;
            char newDesignation[10];
            cout<<"Enter new designation: ";
            cin>>newDesignation;
            int newCtc;
            cout<<"Enter new CTC: ";
            cin>>newCtc;
            FILE *file, *tempfile;
            file= fopen("data.txt", "r");
            tempfile= fopen("temp.txt", "w");
            while(fscanf(file, "%s %s %s %d %d %d", &name[0], &id[0] , &designation[0], &age, &ctc, &experience)!=EOF){
                if(strcmp(checkId, id)==0)
                    fprintf(tempfile, "%s %s %s %d %d %d \n", name, id, newDesignation, age, newCtc, experience );
                else
                    fprintf(tempfile, "%s %s %s %d %d %d \n", name, id, designation, age, ctc, experience );
            }
            fclose(file);
            fclose(tempfile);
            int isRemoved= remove("data.txt");
            int isRenamed= rename("temp.txt", "data.txt");
            waitForEnter();
        }

        void addNewEmployee(void){
            system("clear");
            cout<<"\n Enter Name of Employee: ";
            cin>>name;
            cout<<"\n Enter Employee ID: ";
            cin>>id;
            cout<<"\n Enter Designation: ";
            cin>>designation;
            cout<<"\n Enter Employee Age: ";
            cin>>age;
            cout<<"\n Enter Employee CTC: ";
            cin>>ctc;
            cout<<"\n Enter Employee Experience: ";
            cin>>experience;

            char ch;
            cout<<"\nEnter 'y' to save above information\n";
            cin>>ch;
            if(ch=='y'){
                FILE  *file;
                file= fopen("data.txt","a");
                fprintf(file, "%s %s %s %d %d %d \n", name, id, designation, age, ctc, experience );
                fclose(file);
                cout<<"\nNew Employee has been added to database\n";
            }
            else
                addNewEmployee();
            waitForEnter();
        }

        void deleteEmployeeDetails(void){
            system("clear");
            char checkId[5];
            cout<<"Enter employee id: ";
            cin>>checkId;
            char ch;
            cout<<"Enter 'y' to confirm deletion \n";
            cin>>ch;
            if(ch=='y'){
                FILE *file, *tempfile;
                file= fopen("data.txt", "r");
                tempfile= fopen("temp.txt", "w");
                while(fscanf(file, "%s %s %s %d %d %d", &name[0], &id[0] , &designation[0], &age, &ctc, &experience)!=EOF)
                    if(strcmp(checkId, id)!=0)
                        fprintf(tempfile, "%s %s %s %d %d %d \n", name, id, designation, age, ctc, experience );
                fclose(file);
                fclose(tempfile);
                int isRemoved= remove("data.txt");
                int isRenamed= rename("temp.txt", "data.txt");
                cout<<"\nDeletion Successful\n";
                waitForEnter();
            }
            else
                deleteEmployeeDetails();
        }


    public:
        // Function to serve as end point
        void options(void){
            while(true){
                system("clear");
                // Options to choose an action
                cout<<"\n   1   To see list of employees";
                cout<<"\n   2   To see employee details";
                cout<<"\n   3   To edit existing employee details";
                cout<<"\n   4   To add new employee details";
                cout<<"\n   5   To remove an employee details";
                cout<<"\n   0   To exit     ";
                cout<<"\n\n\n   Please choose what would you like to do: ";

                // Taking the action input
                int choice;
                cin>>choice;
                // Calling relevant function as per choice
                switch (choice) {
                    case 0:
                        cout<<"Good Bye :) !";
                        usleep(100000);
                        return;
                    case 1:
                        listEmployees();
                        break;
                    case 2:
                        showDetails();
                        break;
                    case 3:
                        editExisting();
                        break;
                    case 4:
                        addNewEmployee();
                        break;
                    case 5:
                        deleteEmployeeDetails();
                        break;
                    default:
                        cout<<"\n Sorry! I don't understand that! \n";
                        break;
                }

            }
        }

};

int main(){
    // Call the options function
    employee e;
    e.options();
    return 0;
}
