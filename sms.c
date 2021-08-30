/**
  * File Name: sms.c
  * Title: Student Management System
  * Author: - Aditya Timilsina
  			- Aviyanshu Adhikari
  			- Binit K.C
  * Date: 2078/05/09
*/

//Header Files
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include"rlutil.h"
#include "consolesettings.h"  //fullscreen() and font(font_size,font_weight)

int option, i;      // Option for main menu option
char temp_gender;  //temp_gender to convert m and f to uppercase

//User account related funcitons
void admin_panel();
void create_account();
void view_account();
void delete_account();

//Record Related Function Declarations
char yes_no1, yes_no2, yes_no3;
void openfile(char[]);
void add();
void view_filter();
void edit();
void del();
void search();
void view_datas();
void eng_stream();

void thank_you_end();
//File Declarations
FILE *fp, *tempfp, *fuac; // fp/tempfp = for record fiels, fuac = for user account file

//Structure Declarations
struct user_account
{
    char name[30];
    char email[30];
    char username[20];
    char password[20];
    int role;
} u;
struct Student
{
    char student_name[30];
    char roll[20];
    char father_name[30];
    char mother_name[30];
    struct date
    {
        int year;
        int month;
        int day;
    } dob;
    char gender;
    char phone_number[20];
    char email[50];
    char address_district[30];
    char address_town[30];
    char document_number[30];
}S;

//Todays Date print Functin
void date_of_today()
{

    char cur_date[128];
    time_t      t;
    struct tm*  ptm;
    t = time(NULL);
    ptm = localtime(&t);
    strftime(cur_date, 128, "%d-%b-%Y", ptm);
    printf("Date : %s\n", cur_date);
}

//Loader(PULCHOWK) Function
void loader(int time)
{
    //https://patorjk.com/software/taag/#p=display&f=Big&t=Pulchowk%20Campus
    setColor(BLUE);
    printf("\n\t   ______      _      _                   _       _____                                 ");
    Sleep(time);
    setColor(RED);
    printf("\n\t   | ___ \\    | |    | |                 | |     /  __ \\                                ");
    Sleep(time);
    setColor(GREEN);
    printf("\n\t   | |_/ /   _| | ___| |__   _____      _| | __  | /  \\/ __ _ _ __ ___  _ __  _   _ ___ ");
    Sleep(time);
    setColor(YELLOW);
    printf("\n\t   |  __/ | | | |/ __| '_ \\ / _ \\ \\ /\\ / / |/ /  | |    / _` | '_ ` _ \\| '_ \\| | | / __|");
    Sleep(time);
    setColor(RED);
    printf("\n\t   | |  | |_| | | (__| | | | (_) \\ V  V /|   <   | \\__/\\ (_| | | | | | | |_) | |_| \\__ \\");
    Sleep(time);
    setColor(MAGENTA);
    printf("\n\t   \\_|   \\__,_|_|\\___|_| |_|\\___/ \\_/\\_/ |_|\\_\\   \\____/\\__,_|_| |_| |_| .__/ \\__,_|___/");
    Sleep(time);
    setColor(BLUE);
    printf("\n\t                                                                       | |              ");
    Sleep(time);
    setColor(GREEN);
    printf("\n\t                                                                       |_|              ");
    Sleep(time);
    setColor(WHITE);
    gotoxy(85,10);
    date_of_today();
}

//Main Program
void main()
{
	//creats files folder if do not exist
	mkdir("files");
	
    //User Account Related Variable Declarations
    char uname[20],pass[20], starpassword;
    int j, check_account=0;

    //Loading Screen Part
    fullscreen();
    font(26,1000);
    loader(100);
    setBackgroundColor(RED);
    setColor(GREEN);
    gotoxy(40,18);
    printf("***Student Management System***");
    setColor(WHITE);
    setBackgroundColor(BLACK);
    gotoxy(52,25);
    printf("Loading....");
    for(i=0; i<50; i++)
    {
        gotoxy(32+i,27);
        printf("%c",219);     //177 or 219
        Sleep(30);
    }
    system("cls");
    loader(0);

    //Login Part
    fuac=fopen("files\\account.txt","rb+");
    if(fuac==NULL)
    {
        printf("\"File not found\"");
    }
    i=0;
    while(i<5)
    {
        check_account=0,j=0;
        gotoxy(35, 15);
        printf("<<<ENTER YOUR LOGIN INFORMATION>>>\n\n");
        gotoxy(40,18);
        printf("Enter Username : ");
        scanf("%s",uname);
        gotoxy(40,20);
        printf("Enter Password : ");
        //Making password unseen (***)
        while(1)
        {
            starpassword = getch();
            if(starpassword == 13)
            {
                pass[j] = '\0';
                break;
            }
            else if(starpassword == 8)
            {
                if(j>0)
                {
                    j--;
                    printf("\b \b");
                }
            }
            else if(starpassword == 9)
                continue;
            else
            {
                pass[j] = starpassword;
                j++;
                printf("*");
            }
        }
        //Checking if password and username are correct
        while(fread(&u, sizeof(struct user_account), 1, fuac))
        {
            if(strcmp(u.username, uname) == 0 && strcmp(u.password, pass)==0)
            {
                check_account = 1;
                break;
            }
            else
            {
                check_account = 2;
            }
        }
        if(check_account == 1)
        {
            break;
        }
        if(check_account == 2)
        {
            gotoxy(33,22);
            printf("Username Or Password is Incorrect :(");
            gotoxy(42,24);
            printf("Try Again...");
            getch();
            system("cls");
            loader(0);
        }
        rewind(fuac);
        i++;
    }
    fclose(fuac);

    /*
    User Role
    Admin = 0
    User = 1
    */

    if(check_account == 1)
    {
        if(u.role==0)
        {
            //Admin Screen Starts here....
            while(1)
            {
                system("cls");
                loader(0);
                gotoxy(38,11);
                setBackgroundColor(RED);
                setColor(GREEN);
                printf("***Student Management System***");
                setColor(WHITE);
                setBackgroundColor(BLACK);
                gotoxy(80,11);
                printf("Welcome! %s (Admin)", u.name);
                //MAIN MENU
                printf("\n\n    ------------------------------------\n");
                printf("   %c",179);
                setBackgroundColor(BLUE);
                printf("          ## MAIN MENU ##           ");
                setBackgroundColor(BLACK);
                printf("%c\n",179);
                printf("   %c            ===========             %c\n",179,179);
                printf("   %c                                    %c\n",179,179);
                printf("   %c  [1] View/Filter Student Records   %c\n",179,179);
                printf("   %c  [2] Add Student Record            %c\n",179,179);
                printf("   %c  [3] Edit Student Record           %c\n",179,179);
                printf("   %c  [4] Delete Student Record         %c\n",179,179);
                printf("   %c  [5] Search Student Record         %c\n",179,179);
                printf("   %c  [6] Admin Panel                   %c\n",179,179);
                printf("   %c  [7] Exit                          %c\n",179,179);
                printf("    ------------------------------------\n");
                printf("\n\n\t\t\tSelect the required option:\t");
                scanf("%d", &option);
                switch(option)
                {
                case 1:
                    view_filter();
                    break;
                case 2:
                    add();
                    break;
                case 3:
                    edit();
                    break;
                case 4:
                    del();
                    break;
                case 5:
                    search();
                    break;
                case 6:
                    admin_panel();
                    break;
                case 7:
                	thank_you_end();
                    exit(1);
                    break;
                default:
                    printf("\t\tInvalid Entry!!!\n");
                    printf("\t\tPress ENTER to try again.....\n");
                    getch();
                    break;
                }
            }
        }
        else
        {
            //User Screen Starts here....
            while(1)
            {
                system("cls");
                loader(0);
                gotoxy(38,11);
                setBackgroundColor(RED);
                setColor(GREEN);
                printf("***Student Management System***");
                setColor(WHITE);
                setBackgroundColor(BLACK);
                gotoxy(80,11);
                printf("Welcome! %s (User)", u.name);
                //MAIN MENU
                printf("\n\n    ------------------------------------\n");
                printf("   %c",179);
                setBackgroundColor(BLUE);
                printf("          ## MAIN MENU ##           ");
                setBackgroundColor(BLACK);
                printf("%c\n",179);
                printf("   %c            ===========             %c\n",179,179);
                printf("   %c                                    %c\n",179,179);
                printf("   %c  [1] View/Filter Student Records   %c\n",179,179);
                printf("   %c  [2] Search Student Record         %c\n",179,179);
                printf("   %c  [3] Exit                          %c\n",179,179);
                printf("    ------------------------------------\n");
                printf("\n\n\t\t\tSelect the required option:\t");
                scanf("%d", &option);
                switch(option)
                {
                case 1:
                    view_filter();
                    break;
                case 2:
                    search();
                    break;
                case 3:
                	thank_you_end();
                    exit(1);
                    break;
                default:
                    printf("\t\tInvalid Entry!!!\n");
                    printf("\t\tPress ENTER to try again.....\n");
                    getch();
                    break;
                }
            }
        }
    }
    if(i==5)
    {
        printf("\n\n\n\t\t\tTOO MANY TRIES. CONTACT ADMIN FOR FURTHER PROCESS.");
        getch();
    }
}

void admin_panel()
{
    int admin_choice;
    system("cls");
    loader(0);
    gotoxy(38,11);
    setBackgroundColor(RED);
    setColor(GREEN);
    printf("***Student Management System***");
    setColor(WHITE);
    setBackgroundColor(BLACK);
    gotoxy(78,11);
    printf("Welcome! %s (Admin)", u.name);
    //MAIN MENU
    printf("\n\n    ------------------------------------\n");
    printf("   %c",179);
    setBackgroundColor(BLUE);
    printf("          ## MAIN MENU ##           ");
    setBackgroundColor(BLACK);
    printf("%c\n",179);
    printf("   %c            ===========             %c\n",179,179);
    printf("   %c                                    %c\n",179,179);
    printf("   %c  [1] Create New User Account       %c\n",179,179);
    printf("   %c  [2] View Accounts                 %c\n",179,179);
    printf("   %c  [3] Delete Account                %c\n",179,179);
    printf("   %c  [4] Exit                          %c\n",179,179);
    printf("    ------------------------------------\n");
    printf("\n\n\t\t\tSelect the required option:\t");
    scanf("%d", &admin_choice);
    switch(admin_choice)
    {
    case 1:
        create_account();
        break;
    case 2:
        view_account();
        break;
    case 3:
        delete_account();
        break;
    case 4:
    	break;
    default:
        printf("\t\tInvalid Entry!!!\n");
        printf("\t\tPress ENTER to try again.....\n");
        getch();
        break;
    }
}

void create_account()
{
    struct user_account U;
    char ch, affirm[20];
    //Creating account
    system("cls");
    gotoxy(45,3);
    setBackgroundColor(BLUE);
    puts("## Create Account ##\n");
    setBackgroundColor(BLACK);
    printf("\n\tEnter Full Name:\t");
    fflush(stdin);
    gets(U.name);
    printf("\n\tEnter Email :\t\t");
    fflush(stdin);
    gets(U.email);
    printf("\n\tEnter Username:\t\t");
    fflush(stdin);
    gets(U.username);
    //Password Section
password:
    //OriginaL Password
    printf("\n\tEnter Password:\t\t");
    i=0;
    while(1)
    {
        ch=getch();
        if(ch==13)
        {
            U.password[i]='\0';
            break;
        }
        else if(ch==8)
        {
            if(i>0)
            {
                i--;
                printf("\b \b");
            }
        }
        else if(ch==9)
            continue;
        else
        {
            U.password[i]=ch;
            i++;
            printf("*");
        }
    }
    //Password for Confirmation
    i=0;
    printf("\n\tReenter password for confirmation: ");
    while(1)
    {
        ch=getch();
        if(ch==13)
        {
            affirm[i]='\0';
            break;
        }
        else if(ch==8)
        {
            if(i>0)
            {
                i--;
                printf("\b \b");
            }
        }
        else if(ch==9)
            continue;
        else
        {
            affirm[i]=ch;
            i++;
            printf("*");
        }
    }
    /*
    printf("\n\nOriginal Password: %s",U.password);
    printf("\nReentered Password : %s",affirm);*/
    //Checking for password match
    if(strcmp(U.password,affirm)!=0)
    {
        printf("\n\n\tPassword Do not Match !!\n");
        goto password;
    }
    printf("\n\n\tEnter your role (Admin:0 or User:1):\t");
    scanf("%d", &U.role);
    printf("\n");
    fuac = fopen ("files\\account.txt", "ab+");
    fseek(fuac, 0, SEEK_END);
    fwrite(&U, sizeof(U), 1, fuac);
    fclose (fuac);
    gotoxy(40,20);
    printf("Account Created Successfully!!!");
    gotoxy(75,25);
    printf("Press any key to continue...");
    getch();
}

void view_account()
{
    struct user_account U;
    system("cls");
    gotoxy(45,3);
    setBackgroundColor(BLUE);
    puts("## View Accounts ##\n");
    setBackgroundColor(BLACK);
    fuac=fopen("files\\account.txt","rb");
    printf("\n\n\n\tThe account list is : ");
    printf("\n\n\t=============================================================================================\n");
    printf("\tName\t\t\tEmail\t\t\t\tUsername\tPassword\tRole");
    printf("\n\t=============================================================================================\n");
    while(fread(&U, sizeof(U), 1, fuac)==1)
    {
        printf("\t%-20s\t%-30s\t%-15s\t*****\t\t",U.name,U.email,U.username);
        if(U.role == 0)
        {
            printf("Admin\n");
        }
        else
        {
            printf("User\n");
        }

    }
    getch();
    fclose(fuac);
}

void delete_account()
{
    struct user_account U;
    char delemail[20], filename[10];
    int datafound=0;

    //Deleting a record from a file
    system("cls");
    gotoxy(45,3);
    setBackgroundColor(BLUE);
    puts("## Delete Account ##\n");
    setBackgroundColor(BLACK);
    fuac=fopen("files\\account.txt","rb+");
    printf("\n\tEnter the email whose account is to be deleted:\t");
    fflush(stdin);
    gets(delemail);
    printf("\n\tSearching");
    for(i=0; i<50; i++)
    {
        printf(".");
        Sleep(15);
    }
    rewind(fuac);
    printf("\n");
    while(fread(&U, sizeof(U), 1, fuac)==1)
    {
        if(strcmp(U.email, delemail)==0)
        {
            datafound=1;

            //Record of the account to be deleted

            system("cls");
            printf("\n\tThe details of the Account:\n");
            printf("\n\tName :\t");
            puts(U.name);
            printf("\n\tEmail :\t");
            puts(U.email);
            printf("\n\tUsername :\t");
            puts(U.password);
            printf("\n\tPassword :\t *****\n");
            printf("\n\tRole :\t");
            if(U.role == 0)
            {
                printf("Admin");
            }
            else
            {
                printf("User");
            }
        }
    }
    rewind(fuac);

    //record found
    if(datafound==1)
    {
        // AFFIRMATION FOR DELETING
        printf("\n\n\tAre you sure you want this account deleted? Press Y for yes or N for no:\t");
        yes_no1=getchar();
        if(yes_no1=='Y' || yes_no1=='y')
        {
            // DELETING FILE
            tempfp=fopen("files\\temporary.txt","wb");
            while(fread(&U, sizeof(U), 1, fuac)==1)
            {
                if(strcmp(U.email, delemail) != 0)
                {
                    fwrite(&U, sizeof(U), 1, tempfp);
                }
            }
            fclose(fuac);
            fclose(tempfp);
            remove("files\\account.txt");
            rename("files\\temporary.txt","files\\account.txt");
			printf("\n\tDeleting");
	        for(i=0; i<50; i++)
	        {
	            printf(".");
	            Sleep(15);
	        }
	        printf("\n\n\t\tThe account has been successfully deleted!!!\n");
        }
    }
    else
    //Record not found
    {
        printf("\n\tACCOUNT NOT FOUND\t");
        fclose(fuac);
    }
    printf("\n\tPress any key to continue to the main menu.....");
    getch();
}


//Adding Records Function
void add()
{
    int check;
    char stream[10];
    //ADDING RECORD TO THE FILES
starting_stream_add_record:
    system("cls");
    system("color 0b");
    setBackgroundColor(GREEN);
    printf("\n\n\n\tADDING RECORD SECTION\n\n\n");
    setBackgroundColor(BLACK);
    eng_stream();
    fflush(stdin);
    printf("\n\t=>  ");
    gets(stream);
    strupr(stream);
    if(strcmp(stream, "EXIT")==0 || strcmp(stream, "exit")==0)
    {
        printf("\n\n\tPress any key to go to main menu...");
        goto end_of_function;
    }
    openfile(stream);
    if(fp==NULL)
    {
        fclose(fp);
        goto starting_stream_add_record;
    }
    fseek(fp, 0, SEEK_END);
    system("cls");
    printf("\t");
    puts(stream);
    printf("\n\tPlease Enter all the requirements:\n");
    printf("\n\tStudent's name:\t");
    fflush(stdin);
    gets(S.student_name);
    printf("\n\tEnter the roll numbers of the student:\t");
    fflush(stdin);
    gets(S.roll);
    strupr(S.roll);
    printf("\n\tFather's name:\t");
    fflush(stdin);
    gets(S.father_name);
    printf("\n\tMother's name:\t");
    fflush(stdin);
    gets(S.mother_name);
    printf("\n\tDate of Birth in YYYY MM DD(e.g. 2060 06 29):\t");
    scanf("%d%d%d", &S.dob.year, &S.dob.month, &S.dob.day);
gender_1:
    printf("\n\tGender Male:M or Female:F:\t");
    fflush(stdin);
    scanf(" %c", &temp_gender);
    S.gender = toupper(temp_gender);
    if(S.gender=='M' || S.gender=='F')
        check=1;
    else
    {
        printf("\n\tPlease enter valid option!!!\n");
        goto gender_1;
    }
    printf("\n\tPhone number:\t");
    fflush(stdin);
    gets(S.phone_number);
    printf("\n\tEmail address:\t");
    fflush(stdin);
    gets(S.email);
    printf("\n\tPermanent address\n");
    printf("\n\tDistrict (e.g. Kathmandu):\t");
    fflush(stdin);
    gets(S.address_district);
    printf("\n\tTown (e.g. Babarmahal):\t");
    fflush(stdin);
    gets(S.address_town);
    printf("\n\tEnter identification document number (e.g Citizenship number):\t");
    fflush(stdin);
    gets(S.document_number);
    fwrite(&S, sizeof(S), 1, fp);
    printf("\n\tAdding record into file");
    for(i=0; i<50; i++)
    {
        printf(".");
        Sleep(15);
    }
    printf("\n\n\tRecord successfully added!!!\n");
    printf("\n\tPress any key to continue to the main menu....");
    fclose(fp);
end_of_function:
    getch();
}

void view_filter()
{
    int view_ch,filter_ch, data_found=0;
    char stream[10], start_letter, search_district[20];
starting_view_filter_record:
    system("cls");
    system("color 0b");
    setBackgroundColor(GREEN);
    printf("\n\n\n\tVIEW RECORD SECTION\n\n\n");
    setBackgroundColor(BLACK);
    eng_stream();
    printf("\n\t=>  ");
    fflush(stdin);
    gets(stream);
    strupr(stream);
    if(strcmp(stream, "EXIT")==0 || strcmp(stream, "exit")==0)
    {
        printf("\n\n\tPress any key to go to main menu...");
        goto end_of_function;
    }
    openfile(stream);
    if(fp==NULL)
    {
        fclose(fp);
        goto starting_view_filter_record;
    }
    fseek(fp, 0, SEEK_SET);
    rewind(fp);
    printf("\n\n\t[1] View All Records");
    printf("\n\t[2] View Record by filtering");
    printf("\n\n\tEnter your choice : ");
view_choice:
    scanf("%d",&view_ch);
    switch(view_ch)
    {
    case 1:
        system("cls");
        font(22,500);
        printf("\n\nAll Student Records of %s\n",stream);
        printf("Roll NO.   Student Name   Guardian Name     DOB    Gender  Phone\tEmail     \t\t Address\n");
        while(fread(&S, sizeof(S), 1, fp)==1)
        {
            printf("%s  %s\t %s\t  %d/%d/%d   %c\t  %s  %s\t%s,%s\n",S.roll,S.student_name,S.father_name,S.dob.year,S.dob.month,S.dob.day,S.gender,S.phone_number,S.email,S.address_town,S.address_district);
        }
        break;
    case 2:
        system("cls");
        printf("\n\n\tFilter Student Records of %s\n",stream);
        printf("\n\n\t[1] Show Student record which start with specific letter");
        printf("\n\t[2] Show Student record of specific district");
        printf("\n\n\tEnter your choice : ");
filter_choice:
        scanf("%d",&filter_ch);
        switch(filter_ch)
        {
        case 1:
            printf("\n\n\tFilter Student Records of %s\n",stream);
            printf("\n\n\tShow Student record which start with specific letter");
            printf("\n\n\tEnter the starting letter : ");
            scanf(" %c",&start_letter);
            system("cls");
            printf("\n\n\tFilter Student Records of %s\n",stream);
            printf("\n\n\tThe records with starting letter of student of %c are: \n\n\n",start_letter);
			printf("Roll NO.   Student Name   Guardian Name     DOB    Gender  Phone\tEmail      Address\n");
            while(fread(&S, sizeof(S), 1, fp)==1)
            {
                if(start_letter==S.student_name[0] || toupper(start_letter)==S.student_name[0])
                {
                    data_found = 1;
                    printf("%s  %s\t %s\t  %d/%d/%d   %c\t  %s  %s\t%s,%s\n",S.roll,S.student_name,S.father_name,S.dob.year,S.dob.month,S.dob.day,S.gender,S.phone_number,S.email,S.address_town,S.address_district);
                }
            }
            if(data_found==0)
                printf("\n\n\n\tNo records found with that letter :(");
            break;
        case 2:
            printf("\n\n\tFilter Student Records of %s\n",stream);
            printf("\n\n\tShow Student record of specific district");
            printf("\n\n\tEnter the district : ");
            fflush(stdin);
            gets(search_district);
            system("cls");
            printf("\n\n\tFilter Student Records of %s\n",stream);
            printf("\n\n\tThe records with district %s are :- \n\n\n",search_district);
			printf("Roll NO.   Student Name   Guardian Name     DOB    Gender  Phone\tEmail      Address\n");
            while(fread(&S, sizeof(S), 1, fp)==1)
            {
                if(strcmp(search_district,S.address_district)==0)
                {
                    data_found = 1;
                    printf("%s  %s\t %s\t  %d/%d/%d   %c\t  %s  %s\t%s,%s\n",S.roll,S.student_name,S.father_name,S.dob.year,S.dob.month,S.dob.day,S.gender,S.phone_number,S.email,S.address_town,S.address_district);
                }
            }
            if(data_found==0)
                printf("\n\n\n\tNo records found with that address :(");
            break;
        default:
            printf("\n\tInvalid Format!! Try again....\n\n");
            printf("\tEnter choice again : ");
            goto filter_choice;
        }
        break;
    default:
        printf("\n\tInvalid Format!! Try again....\n\n");
        printf("\tEnter choice again : ");
        goto view_choice;
    }
    fclose(fp);
end_of_function:
    getch();
    system("cls");
    font(26,1000);
}

//Edit Records Function
void edit()
{
    char editroll[10], stream[10];
    int datafound, recordno, check;
starting_stream_edit_record:
    system("cls");
    system("color 0b");
    setBackgroundColor(GREEN);
    printf("\n\n\n\tEDITING RECORD SECTION\n\n\n");
    setBackgroundColor(BLACK);
    eng_stream();
    printf("\n\t=>  ");
    fflush(stdin);
    gets(stream);
    strupr(stream);
    if(strcmp(stream, "EXIT")==0 || strcmp(stream, "exit")==0)
    {
        printf("\n\n\tPress any key to go to main menu...");
        goto end_of_function;
    }
    openfile(stream);
    if(fp==NULL)
    {
        fclose(fp);
        goto starting_stream_edit_record;
    }
    fseek(fp, 0, SEEK_SET);
    rewind(fp);
    printf("\n\tEnter the roll number of the student whose record is to be edited:\t");
    fflush(stdin);
    gets(editroll);
    strupr(editroll);
    printf("\n\n\tThe edit roll is %s",editroll);
    datafound=0;
    recordno=0;
    while(fread(&S, sizeof(S), 1, fp)==1)
    {
        if(strcmp(S.roll, editroll)==0)
        {
            datafound=1;
            //Current Record display
            system("cls");
            printf("\n\n\n\tEDITING RECORD SECTION\n\n\n");
            printf("\n\tCurrent record:\n");
            view_datas();
            printf("\n\n\tPress any key to edit.....\n");
            getch();

            //Enter Edited Record
            system("cls");
            printf("\n\n\n\tEDITING RECORD SECTION\n\n\n");
            printf("\n\tEnter information to be edited:\n");
            printf("\n\tPlease enter all the requirements:\n");
            printf("\n\tStudent's name:\t");
            fflush(stdin);
            gets(S.student_name);
            printf("\n\tEnter the roll numbers of the student:\t");
            fflush(stdin);
            gets(S.roll);
            strupr(S.roll);
            printf("\n\tFather's name:\t");
            fflush(stdin);
            gets(S.father_name);
            printf("\n\tMother's name:\t");
            fflush(stdin);
            gets(S.mother_name);
            printf("\n\tDate of Birth in YYYY/MM/DD(e.g. 2060 06 29):\t");
            scanf("%d%d%d", &S.dob.year, &S.dob.month, &S.dob.day);
gender_1:
            printf("\n\tGender Male:M or Female:F:\t");
            fflush(stdin);
            scanf(" %c", &temp_gender);
            S.gender = toupper(temp_gender);
            if(S.gender=='M' || S.gender=='F')
                check=1;
            else
            {
                printf("\n\tPlease enter valid option!!!");
                goto gender_1;
            }
            printf("\n\tPhone number:\t");
            fflush(stdin);
            gets(S.phone_number);
            printf("\n\tEmail address:\t");
            fflush(stdin);
            gets(S.email);
            printf("\n\tPermanent address\n");
            printf("\n\tDistrict (e.g. Kathmandu):\t");
            fflush(stdin);
            gets(S.address_district);
            printf("\n\tTown (e.g. Babarmahal):\t");
            fflush(stdin);
            gets(S.address_town);
            printf("\n\tEnter identification document number (e.g Citizenship number):\t");
            fflush(stdin);
            gets(S.document_number);

            //Editing Record
            printf("\n\tDo you want to check your modification? Press Y for yes or N for no:\t");
            fflush(stdin);
            yes_no1=getchar();
            if(yes_no1=='Y' || yes_no1=='y')
            {
                system("cls");
                printf("\n\n\n\tEDITING RECORD SECTION\n\n\n");

                //displaying modified record

                printf("\n\tModified record\n");
                view_datas();
                printf("\n");
            }

            //affirmation for editing
            printf("\n\tAre you done with editing? Press Y for yes or N for no:\t");
            fflush(stdin);
            yes_no2=getchar();

            //if user enters YES for editing
            if(yes_no2=='Y' || yes_no2=='y')
            {
                check=2;
                fseek(fp, sizeof(S)*recordno, SEEK_SET);
                if(fwrite(&S, sizeof(S), 1, fp)==1)
                {
                    printf("\n\tEditing");
                    for(i=0; i<50; i++)
                    {
                        printf(".");
                        Sleep(15);
                    }
                    printf("\n\tThe record has been modified!!!\n");
                    break;
                }
            }

            //if user enters NO for editing
            else
            {
                edit();
            }
        }
        recordno++;
    }

    //IF RECORD IS NOT PRESENT

    if(datafound==0)
    {
        printf("\n\tRECORD NOT FOUND!!!\n");
        printf("\n\tPress any key to continue to main menu.....");
    }
    fclose(fp);
end_of_function:
    getch();
}


//Delete Records Function
void del()
{
    char stream[10], delroll[10], filename[10];
    int datafound=0;

    //Deleting a record from a file
starting_stream_delete_record:
    system("cls");
    system("color 0b");
    setBackgroundColor(GREEN);
    printf("\n\n\n\tDELETING RECORD SECTION\n\n\n");
    setBackgroundColor(BLACK);
    eng_stream();
    fflush(stdin);
    printf("\n\t=>  ");
    gets(stream);
    strupr(stream);
    strcpy(filename,stream);
    if(strcmp(stream, "EXIT")==0 || strcmp(stream, "exit")==0)
    {
        printf("\n\n\tPress any key to go to main menu...");
        goto end_of_function;
    }
    openfile(stream);
    if(fp==NULL)
    {
        fclose(fp);
        goto starting_stream_delete_record;
    }
    printf("\n\tEnter the roll number of student whose record is to be deleted:\t");
    fflush(stdin);
    gets(delroll);
    strupr(delroll);
    printf("\n\tSearching");
    for(i=0; i<50; i++)
    {
        printf(".");
        Sleep(15);
    }
    printf("\n");
    while(fread(&S, sizeof(S), 1, fp)==1)
    {
        if(strcmp(S.roll, delroll)==0)
        {
            datafound=1;

            //Record of the account to be deleted
            system("cls");
            view_datas();
        }
    }
    rewind(fp);

    //record found
    if(datafound==1)
    {
        // AFFIRMATION FOR DELETING
        printf("\n\n\tAre you sure you want this record deleted? Press Y for yes or N for no:\t");
        yes_no3=getchar();
        if(yes_no3=='Y' || yes_no3=='y')
        {
            // DELETING FILE
            tempfp=fopen("files\\temporary.txt","wb");
            while(fread(&S, sizeof(S), 1, fp)==1)
            {
                if(strcmp(S.roll, delroll) != 0)
                {
                    fwrite(&S, sizeof(S), 1, tempfp);
                }
            }
            fclose(fp);
            fclose(tempfp);
            if(strcmp(filename, "BCE")==0)
            {
                remove("files\\BCE.txt");
                rename("files\\temporary.txt","files\\BCE.txt");
                fp=fopen("files\\BCE.txt", "rb+");
            }
            else if(strcmp(filename, "BEL")==0)
            {
                remove("files\\BEL.txt");
                rename("files\\temporary.txt","files\\BEL.txt");
                fp=fopen("files\\BEL.txt", "rb+");
            }
            else if(strcmp(filename, "BEI")==0)
            {
                remove("files\\BEI.txt");
                rename("files\\temporary.txt","files\\BEI.txt");
                fp=fopen("files\\BEI.txt", "rb+");
            }
            else if(strcmp(filename, "BCT")==0)
            {
                remove("files\\BCT.txt");
                rename("files\\temporary.txt","BCT.txt");
                fp=fopen("files\\BCT.txt", "rb+");
            }
            else if(strcmp(filename, "BME")==0)
            {
                remove("files\\BME.txt");
                rename("files\\temporary.txt","files\\BME.txt");
                fp=fopen("files\\BME.txt", "rb+");
            }
            else if(strcmp(filename, "BCH")==0)
            {
                remove("files\\BCH.txt");
                rename("files\\temporary.txt","files\\BCH.txt");
                fp=fopen("files\\BCH.txt", "rb+");
            }
            else if(strcmp(filename, "BAS")==0)
            {
                remove("files\\BAS.txt");
                rename("files\\temporary.txt","files\\BAS.txt");
                fp=fopen("files\\BAS.txt", "rb+");
            }
            else if(strcmp(filename, "BArch")==0)
            {
                remove("files\\BARCH.txt");
                rename("files\\temporary.txt","files\\BArch.txt");
                fp=fopen("files\\BARCH.txt", "rb+");
            }
            printf("\n\tDeleting");
            for(i=0; i<50; i++)
            {
                printf(".");
                Sleep(15);
            }
            system("cls");
            printf("\n\tThe record has been successfully deleted!!!\n");
            printf("\n\tPress any key to continue to the main menu....");
        }
    }

    //Record not found

    if(datafound==0)
    {
        printf("\n\tRECORD NOT FOUND\t");
        printf("\n\tPress any key to continue to the main menu.....");
    }
    fclose(fp);
end_of_function:
    getch();
}

void search()
{
    char stream[10], searchroll[10];
    int search=0;

    //searching for a record in a file
starting_stream_search_record:
    system("cls");
    system("color 0b");
    setBackgroundColor(GREEN);
    printf("\n\n\n\tSEARCHING RECORD SECTION\n\n\n");
    setBackgroundColor(BLACK);
    eng_stream();
    fflush(stdin);
    printf("\n\t=>  ");
    gets(stream);
    strupr(stream);
    if(strcmp(stream, "EXIT")==0 || strcmp(stream, "exit")==0)
    {
        printf("\n\n\tPress any key to go to main menu...");
        goto end_of_function;
    }
    openfile(stream);
    if(fp==NULL)
    {
        fclose(fp);
        goto starting_stream_search_record;
    }
    printf("\n\tEnter the roll number of student whose record is to be searched:\t");
    fflush(stdin);
    gets(searchroll);
    strupr(searchroll);
    rewind(fp);
    printf("\n\tSearching");
    for(i=0; i<50; i++)
    {
        printf(".");
        Sleep(15);
    }
    while(fread(&S, sizeof(S), 1, fp)==1)
    {
        if(strcmp(S.roll, searchroll)==0)
        {
            search=1;
            system("cls");
            printf("\n\n\tRECORD FOUND!!!\n");
            view_datas();
            break;
        }
    }

    //RECORD NOT FOUND
    if(search==0)
    {
        printf("\n\n\tRECORD NOT FOUND!!!\n");
    }
    printf("\n\n\t\tPress any key to continue to the main menu....");
    fclose(fp);
end_of_function:
    getch();
}

void view_datas()
{
	printf("\n\tThe details of the student:\n");
    printf("\n\tStudent's name:\t");
    puts(S.student_name);
    printf("\n\tStudent's roll number:\t");
    puts(S.roll);
    printf("\n\tFather's name:\t");
    puts(S.father_name);
    printf("\n\tMother's name:\t");
    puts(S.mother_name);
    printf("\n\tDate of Birth in YYYY/MM/DD:\t%d/%d/%d", S.dob.year, S.dob.month, S.dob.day);
    printf("\n\tGender:\t");
    printf(" %c", S.gender);
    printf("\n\tPhone number:\t%s", S.phone_number);
    printf("\n\tEmail address:\t");
    puts(S.email);
    printf("\n\tPermanent address\n");
    printf("\n\tDistrict:\t");
    puts(S.address_district);
    printf("\n\tTown:\t");
    puts(S.address_town);
    printf("\n\tIdentification document number:\t");
    puts(S.document_number);
}

void eng_stream()
{
    printf("\n\tEnter the stream of the student in the specified format:\n\n");
    printf("\t[BEI] - BE in Electronics, Communication and Information Engineering.\n");
    printf("\t[BCE] - BE in Civil Engineering.\n");
    printf("\t[BEL] - BE in Electrical Engineering.\n");
    printf("\t[BCT] - BE in Computer Engineering.\n");
    printf("\t[BME] - BE in Mechanical Engineering.\n");
    printf("\t[BCH] - BE in Chemical Engineering.\n");
    printf("\t[BAS] - BE in Aerospace Engineering.\n");
    printf("\t[BArch] - Bachelors in Architecture.\n");
    printf("\tEXIT OR exit to exit.\n");
}

// function to open files related to different streams

void openfile(char stream[])   //return fp==NULL if entered wrong stream
{
    if(strcmp(stream, "BCE")==0)
	{
		fp=fopen("files\\BCE.txt","rb+");
		if(fp==NULL)
            fp=fopen("files\\BCE.txt", "wb+");
	}
	else if(strcmp(stream, "BEL")==0)
	{
		fp=fopen("files\\BEL.txt","rb+");
            if(fp==NULL)
            fp=fopen("files\\BEL.txt", "wb+");
	}
	else if(strcmp(stream, "BEI")==0)
	{
		fp=fopen("files\\BEI.txt","rb+");
            if(fp==NULL)
            fp=fopen("files\\BEI.txt", "wb+");
	}
	else if(strcmp(stream, "BCT")==0)
	{
		fp=fopen("files\\BCT.txt","rb+");
            if(fp==NULL)
            fp=fopen("files\\BCT.txt", "wb+");
	}
	else if(strcmp(stream, "BME")==0)
	{
		fp=fopen("files\\BME.txt","rb+");
            if(fp==NULL)
            fp=fopen("files\\BME.txt", "wb+");
	}
		else if(strcmp(stream, "BCH")==0)
	{
		fp=fopen("files\\BCH.txt","rb+");
            if(fp==NULL)
            fp=fopen("files\\BCH.txt", "wb+");
	}
		else if(strcmp(stream, "BAS")==0)
	{
		fp=fopen("files\\BAS.txt","rb+");
            if(fp==NULL)
            fp=fopen("files\\BAS.txt", "wb+");
	}
		else if(strcmp(stream, "BARCH")==0)
	{
		fp=fopen("files\\BARCH.txt","rb+");
            if(fp==NULL)
            fp=fopen("files\\BARCH.txt", "wb+");
	}
    else
    {
        printf("\n\tINVALID FORMAT\n");
        printf("\n\tPlease enter the specified format\n");
        printf("\n\tPress any key to continue to the main menu....");
        getch();
        fp=NULL;
    }
}

void thank_you_end()
{
	system("cls");
	setColor(GREEN);
	gotoxy(75,18);
	printf("    --------------------------------\n");
	gotoxy(75,19);
	printf("   %c A program by:                  %c\n",179,179);
    gotoxy(75,20);
	printf("   %c                                %c\n",179,179);
    gotoxy(75,21);
	printf("   %c  -> Binit K.C                  %c\n",179,179);
    gotoxy(75,22);
	printf("   %c  -> Aditya Timalsina           %c\n",179,179);
    gotoxy(75,23);
	printf("   %c  -> Aviyanshu Adhikari         %c\n",179,179);
    gotoxy(75,24);
	printf("    --------------------------------\n");
	hidecursor();
	for(i=1;i<7;i++)
	{
		setColor(i);
		gotoxy(40,10);
		printf("___                                 ");
		gotoxy(40,11);
		printf(" ) ( _   _   _ ( _   \\_) _        |");
		gotoxy(40,12);
		printf("(   ) ) (_( ) ) )\\    / (_) (_(   o");
		Sleep(200);
	}
	getch();
}
