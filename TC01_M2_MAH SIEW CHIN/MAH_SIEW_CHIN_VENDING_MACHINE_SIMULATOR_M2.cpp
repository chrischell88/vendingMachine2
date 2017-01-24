/*************************************
 Program:   MAH_SIEW_CHIN_VENDING_MACHINE_SIMULATOR_M2.cpp
 Course:    Programming Fundamentals
 Year:      2014/15 Trimester 2
 Name:      MAH SIEW CHIN
 ID:        1132702455
 Lecture:   TC01
 Lab:       TT01
 Email:     chris88chris88@hotmail.com
 Phone:     012-329 7678
 *************************************/

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;



vector <string> drink_name;
vector <float> drink_price;
vector <int> iniUnit_drink;

string displayname; //drink name
float displayPrice;  // drink price
int display_iniUnit; // initial unit of drink
int display_max_can; // maximum of unit of drink purchase
int notes_20; //qty RM20.00 in storage bin
int notes_10; //qty RM10.00 in storage bin
int notes_5; //qty RM5.00 in storage bin
int notes_1; //qty RM1.00 in storage bin
int coins_50; //qty RM0.50 in storage bin
int coins_20; //qty RM0.20 in storage bin
int coins_10; //qty RM0.10 in storage bin



void userPurchaseMenu();
void adminMenu();
void set_name_price_qty();
void set_maximum_bought();
void ini_machine_money();
void change_admin_password();
void clear_trans_record();
void create_product();
void modify_product();
void display_product();
void recordTransaction(string drinkname_pur, float drinkprice_pur, int pur_qty, float total_amount , int notes_20, int notes_10,
                       int notes_5, int notes_1, int coins_50, int coins_20,int coins_10);
void view_TransactionRecord();

bool hasInit = false;

int main()
{


    int selection;
    bool quit = false;


    //main menu
    system("cls");
    cout << "==============================================" << endl;
    cout << "   Welcome to MMU drink Vending Machine"   << endl;
    cout << "==============================================" << endl;
    cout << "1. User Purchase Menu" << endl;
    cout << "2. Admin Menu" << endl << endl;
    cout << "Enter your choice (1-2) : ";
    cin >> selection;

    do
    {

        if(selection == 1)
        {
            userPurchaseMenu();
        }
        else if (selection == 2)
        {
            adminMenu();
        }
        else
        {
            cout << endl;
            cout << "Invalid choice !" << endl;
            cout << "Please re-enter correct choice : ";
            cin >> selection;
        }
    }
    while(quit == false);


    return 0;
}

//user menu
void userPurchaseMenu()
{

    float amt_paid = 0.00; //initialized amount paid RM0.00
    char amt_insert; //variable for amount insert
    float change = 0.00; //variable for amount change dispense
    float return_change = 0.00;  //variable for amount return
    float total_amount = 0.00; // variable for total amount purchase
    int qty_dispensed_ringgit20 = 0; //initialized quantity dispense zero units for RM20.00
    int qty_dispensed_ringgit10 = 0; //initialized quantity dispense zero units for RM10.00
    int qty_dispensed_ringgit5 = 0; //initialized quantity dispense zero units for RM5.00
    int qty_dispensed_ringgit1 = 0; //initialized quantity dispense zero units for RM1.00
    int qty_dispensed_cts50 = 0; //initialized quantity dispense zero units for RM0.50
    int qty_dispensed_cts20 = 0; //initialized quantity dispense zero units for RM0.20
    int qty_dispensed_cts10 = 0; //initialized quantity dispense zero units for RM0.10
    int unDisp_n20 = 0; //initialized qty unable dispense zero unit for RM 20.00
    int unDisp_n10 = 0; //initialized qty unable dispense zero unit for RM 10.00
    int unDisp_n5 = 0; //initialized qty unable dispense zero unit for RM 5.00
    int unDisp_n1 = 0; //initialized qty unable dispense zero unit for RM 1.00
    int unDisp_c50 = 0; //initialized qty unable dispense zero unit for RM 0.50
    int unDisp_c20 = 0; //initialized qty unable dispense zero unit for RM 0.20
    int unDisp_c10 = 0; //initialized qty unable dispense zero unit for RM 0.30
    int purchase; //select type of drink
    int pur_qty =0;//qty of drink purchased

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout << setprecision(2);

    if(!hasInit)
    {
        hasInit = true;

        ifstream inventory_name;
        ifstream inventory_price;
        ifstream inventory_iniUnit;
        inventory_name.open("product_name.txt");
        inventory_price.open("product_price.txt");
        inventory_iniUnit.open("product_iniUnit.txt");
        inventory_price.setf(ios::fixed);
        inventory_price.setf(ios::showpoint);
        inventory_price.precision(2);

        if((inventory_name.fail()) && (inventory_price.fail()) && (inventory_iniUnit.fail()))
        {
            cout << "Input file opening failed.\n";
            exit(1);
        }

        //in stream drink name from file into vector
        while(!inventory_name.eof())
        {
            getline(inventory_name, displayname);
            if(displayname =="")
            {
                continue;
            }
            drink_name.push_back(displayname);
        }

        inventory_name.close();
        //in stream drink price from file into vector
        while((!inventory_price.eof()) && (inventory_price >> displayPrice))
        {
            drink_price.push_back(displayPrice);
        }

        inventory_price.close();
        //in stream initial unit of drink from file into vector
        while((!inventory_iniUnit.eof()) && (inventory_iniUnit >>display_iniUnit))
        {
            iniUnit_drink.push_back(display_iniUnit);
        }

        inventory_iniUnit.close();

        ifstream maximum_cans_bought;
        maximum_cans_bought.open("maximum_can.txt");
        ifstream machine_storage_bin;
        machine_storage_bin.open("storage_bin.txt");

        if((maximum_cans_bought.fail()) &&(machine_storage_bin.fail()))
        {
            cout << "Input file opening failed.\n";
            exit(1);
        }

        //in stream maximum of unit of drink purchase from file into variable
        maximum_cans_bought >> display_max_can;
        maximum_cans_bought.close();

        //in stream each money storage bin from file into variable
        machine_storage_bin >> notes_20 >> notes_10 >> notes_5 >> notes_1
                            >> coins_50 >> coins_20 >> coins_10;
        machine_storage_bin.close();


    }

    system("cls");
    cin.sync();

    //display drink menu and drink price
    for(int i=0 ; i<drink_name.size(); i++)
    {
        cout << (i+1) << "\t" << drink_name[i] << "\t" << drink_price[i] <<
             (iniUnit_drink[i] == 0 ? "\t[Sold Out]" : "") << endl;
    }


    cout << endl;
    cout << "Enter your selection : " ;
    cin >> purchase;
    cin.sync();
    cout << "Enter how many cans you want to buy (Maximum is "<< display_max_can <<") : ";
    cin >> pur_qty;
    cin.sync();

    string drinkname_pur;
    drinkname_pur = drink_name[purchase-1];

    float drinkprice_pur;
    drinkprice_pur = drink_price[purchase-1];
    total_amount = drink_price[purchase-1]*pur_qty;

    if ((pur_qty > 0) && (pur_qty <= display_max_can))
    {
        //amount insert menu for insert amount while amount paid is less than drink price
        while (amt_paid < total_amount)
        {
            system("cls");
            //Amount insert page
            cout << "Purchase of " << drink_name[purchase - 1] << "\t" <<": RM" << drink_price[purchase - 1] << " x " << pur_qty << endl;
            cout << "Total amount" << "\t\t" << ": RM" << total_amount << endl;
            cout << "Amount paid " << "\t\t" << ": RM" << amt_paid << endl << endl;
            cout << "Insert" << endl;
            cout << "a)" << "\t" << "RM 20.00" << endl;
            cout << "b)" << "\t" << "RM 10.00" << endl;
            cout << "c)" << "\t" << "RM  5.00" << endl;
            cout << "d)" << "\t" << "RM  1.00" << endl;
            cout << "e)" << "\t" << "RM  0.50" << endl;
            cout << "f)" << "\t" << "RM  0.20" << endl;
            cout << "g)" << "\t" << "RM  0.10" << endl;
            cout << "h)" << "\t" << "" << "Cancel order" << endl << endl;
            cout << "Pay (a to g) => ";
            cin  >> amt_insert;
            cin.sync();

            //update the amount paid and quantity in storage bin according selection make
            if (((amt_insert == 'A') || (amt_insert == 'a') && (notes_20 < 20)))
            {
                amt_paid = amt_paid + 20;
                notes_20+=1;
            }
            else if (((amt_insert == 'B') || (amt_insert == 'b')) && (notes_10 < 20))
            {
                amt_paid = amt_paid + 10;
                notes_10+=1;
            }
            else if (((amt_insert == 'C') || (amt_insert == 'c')) && (notes_5 < 20))
            {
                amt_paid = amt_paid + 5;
                notes_5 += 1;
            }
            else if (((amt_insert == 'D') || (amt_insert == 'd')) && (notes_1 < 20))
            {
                amt_paid = amt_paid + 1;
                notes_1 +=1;
            }

            else if (((amt_insert == 'E') || (amt_insert == 'e')) && (coins_50 < 20))
            {
                amt_paid = amt_paid + 0.50;
                coins_50 += 1;
            }
            else if (((amt_insert == 'F') || (amt_insert == 'f')) && (coins_20 < 20))
            {
                amt_paid = amt_paid + 0.20;
                coins_20 += 1;
            }
            else if (((amt_insert == 'G') || (amt_insert == 'g')) && (coins_10 < 20))
            {
                amt_paid = amt_paid + 0.10;
                coins_10 += 1;
            }
            //user can cancel order either had insert some amount or none as long as not more than or equal to MMU Lychee price
            else if ((amt_insert == 'H') || (amt_insert == 'h'))
            {
                //Order canceled page
                cout << endl;
                cout << "Order Canceled !" << endl << endl;
                cout << "Payment returned : RM " << amt_paid << endl << endl;

                //calculate amount return to user if the user had insert some amount and update the qty of storage bin accordingly
                while (abs(amt_paid) > 0.0001)
                {
                    if (amt_paid >= 20.00)
                    {
                        amt_paid = amt_paid - 20;
                        notes_20-=1;
                    }
                    else if (amt_paid >= 10.00)
                    {
                        amt_paid = amt_paid - 10;
                        notes_10 -=1;
                    }
                    else if (amt_paid >= 5.00)
                    {
                        amt_paid = amt_paid - 5;
                        notes_5 -=1;
                    }
                    else if (amt_paid >= 1.00)
                    {
                        amt_paid = amt_paid - 1;
                        notes_1 -=1;
                    }
                    else if (amt_paid  >= 0.50)
                    {
                        amt_paid = amt_paid - 0.50;
                        coins_50 -=1;
                    }
                    else if (amt_paid >= 0.20)
                    {
                        amt_paid = amt_paid - 0.20;
                        coins_20 -=1;
                    }
                    else
                    {
                        amt_paid = amt_paid - 0.10;
                        coins_10 -=1;
                    }
                }


                system("pause");
                main(); //return to main menu

            }
            else
            {
                //amt_paid won't store in the full storage bin and only return payment for storage bin less than 20 units//
                cout << "Sorry  !" << endl;
                cout << "Payment returned : " << amt_paid << endl << endl;

                //display full for notes and coins that their storage bin is full
                if (notes_20 >= 20)
                    cout << "RM 20.00 full" << endl;
                if (notes_10 >= 20)
                    cout << "RM 10.00 full" << endl;
                if (notes_5 >= 20)
                    cout << "RM 5.00 full" << endl;
                if (notes_1 >= 20)
                    cout << "RM 1.00 full" << endl;
                if (coins_50 >= 20)
                    cout << "RM 0.50 full" << endl;
                if (coins_20 >= 20)
                    cout << "RM 0.20 full" << endl;
                if (coins_10 >= 20)
                    cout << "RM 0.10 full" << endl;

                //calculate amount return due to full storage bin and update the storage bin accordingly
                while (abs(amt_paid) > 0.0001)
                {
                    if (amt_paid >= 20.00)
                    {
                        amt_paid = amt_paid - 20;
                        notes_20-=1;
                    }
                    if (amt_paid >= 10.00)
                    {
                        amt_paid = amt_paid - 10;
                        notes_10 -=1;
                    }
                    if (amt_paid >= 5.00)
                    {
                        amt_paid = amt_paid - 5;
                        notes_5 -=1;
                    }
                    if (amt_paid >= 1.00)
                    {
                        amt_paid = amt_paid - 1;
                        notes_1 -=1;
                    }
                    if (amt_paid >= 0.50)
                    {
                        amt_paid = amt_paid - 0.50;
                        coins_50 -=1;
                    }
                    if (amt_paid >= 0.20)
                    {
                        amt_paid = amt_paid - 0.20;
                        coins_20 -=1;
                    }
                    if (amt_paid >= 0.10)
                    {
                        amt_paid = amt_paid - 0.10;
                        coins_10 -=1;
                    }
                }

                //update storage bin into file
                ofstream machine_storage_bin;
                machine_storage_bin.open("storage_bin.txt");
                machine_storage_bin.clear();
                machine_storage_bin.seekp(0, ios::beg);
                machine_storage_bin << notes_20 << "\n" << notes_10 << "\n" << notes_5 << "\n" << notes_1
                            << "\n" << coins_50 << "\n" << coins_20 << "\n" << coins_10 << "\n";

                machine_storage_bin.close();

                system("pause");
                main(); //return to main menu
            }
        }
    }
    else
    {
        cout<<"Invalid selection or exceeded maximum cans allowed.";
        exit(0);
    }


    change = amt_paid - total_amount; //calculate the balance change after amount insert

    //if balance change is zero, display order success and update the initial qty of the drink
    if (abs(change) < 0.0001)
    {
        //Order success page
        system("cls");
        iniUnit_drink[purchase-1] = iniUnit_drink[purchase-1] - pur_qty ;
        cout << "Order Success !" << endl << endl;

        //update storage bin into file
        ofstream machine_storage_bin;
        machine_storage_bin.open("storage_bin.txt");
        machine_storage_bin.clear();
        machine_storage_bin.seekp(0, ios::beg);
        machine_storage_bin << notes_20 << "\n" << notes_10 << "\n" << notes_5 << "\n" << notes_1
                            << "\n" << coins_50 << "\n" << coins_20 << "\n" << coins_10 << "\n";

        machine_storage_bin.close();

        //update initial unit of drink into file
        ofstream inventory_iniUnit;
        inventory_iniUnit.open("product_iniUnit.txt");

        for(int i=0; i<iniUnit_drink.size(); i++)
        {
            inventory_iniUnit << iniUnit_drink[i] << endl;
        }

        inventory_iniUnit.close();

        //call for record transaction function
        recordTransaction(drinkname_pur, drinkprice_pur, pur_qty, total_amount, notes_20, notes_10, notes_5, notes_1,
                          coins_50, coins_20, coins_10);


        system ("pause");
        main();
    }



    //calculate balance change if more than zero by qty dispensed accordingly and update storage bin
    while (abs(change) > 0.0001)
    {

        if ((change >= 20.00) && (notes_20 > 0))
        {
            change = change - 20;
            qty_dispensed_ringgit20 +=1;
            notes_20 -=1;
        }
        else if ((change >= 10.00) && (notes_10 > 0))
        {
            change = change - 10;
            qty_dispensed_ringgit10 +=1;
            notes_10 -=1;
        }
        else if ((change >= 5.00) && (notes_5 > 0))
        {
            change = change - 5;
            qty_dispensed_ringgit5 +=1;
            notes_5-=1;
        }
        else if ((change >= 1.00) && (notes_1 > 0))
        {
            change = change - 1;
            qty_dispensed_ringgit1 +=1;
            notes_1 -=1;
        }
        else if ((change + 0.0001 >= 0.50) && (coins_50 > 0)) //added 0.0001 due to floating point can't calculate accurate amount
        {
            change = change - 0.50;
            qty_dispensed_cts50 +=1;
            coins_50 -=1;
        }
        else if ((change + 0.0001 >= 0.20) && (coins_20 > 0)) //added 0.0001 due to floating point can't calculate accurate amount
        {
            change = change - 0.20;
            qty_dispensed_cts20 +=1;
            coins_20 -=1;
        }
        else if ((change + 0.00001 >= 0.10)&& (coins_10 >0)) //added 0.0001 due to floating point can't calculate accurate amount
        {
            change = change - 0.10;
            qty_dispensed_cts10 +=1;
            coins_10 -=1;
        }
        else //calculate amount return if one of the initial qty of storage bin found empty in qty dispense calculation and update storage bin
        {

                //recalculate the change available if one of the storage bin found zero
                change = 0;
                change = amt_paid - total_amount; //calculate the balance change after amount insert
                cout << change << endl;

                //add back the previous storage bin deducted fomr the previous stage storage bin found zeo for the change
                notes_20 = notes_20 + qty_dispensed_ringgit20;
                notes_10 = notes_10 + qty_dispensed_ringgit10 ;
                notes_5 = notes_5 +  qty_dispensed_ringgit5;
                notes_1 = notes_1 + qty_dispensed_ringgit1;
                coins_50 = coins_50 + qty_dispensed_cts50;
                coins_20 = coins_20 + qty_dispensed_cts20;
                coins_10 = coins_10 + qty_dispensed_cts10;

                qty_dispensed_ringgit20 = 0;
                qty_dispensed_ringgit10 = 0;
                qty_dispensed_ringgit5 = 0;
                qty_dispensed_ringgit1 = 0;
                qty_dispensed_cts50 = 0;
                qty_dispensed_cts20 = 0;

                while (abs(change) > 0.0001)
                {
                    if ((change >= 20.00) && (notes_20 > 0))
                    {
                        change = change - 20;
              		 	qty_dispensed_ringgit20 +=1;
                        notes_20 -=1;
                    }
                    else if ((change >= 10.00) && (notes_10 > 0))
                    {
                        change = change - 10;
                        qty_dispensed_ringgit10 +=1;
                        notes_10 -=1;
                    }
                    else if ((change >= 5.00) && (notes_5 > 0))
                    {
                        change = change - 5;
                        qty_dispensed_ringgit5 +=1;
                        notes_5-=1;
                    }
                    else if ((change >= 1.00) && (notes_1 > 0))
            		{
                        change = change - 1;
                        qty_dispensed_ringgit1 +=1;
                        notes_1 -=1;
                    }
                    else if ((change + 0.00001 >= 0.10)&& (coins_10 >0)) //added 0.0001 due to floating point can't calculate accurate amount
                    {
                        change = change - 0.10;
                        qty_dispensed_cts10 +=1;
                        coins_10 -=1;
                    }
                    else if ((change + 0.0001 >= 0.20) && (coins_20 > 0)) //added 0.0001 due to floating point can't calculate accurate amount
                    {
                        change = change - 0.20;
                        qty_dispensed_cts20 +=1;
                        coins_20 -=1;
                    }
                    else if ((change + 0.0001 >= 0.50) && (coins_50 > 0)) //added 0.0001 due to floating point can't calculate accurate amount
            		{
                        change = change - 0.50;
                        qty_dispensed_cts50 +=1;
                        coins_50 -=1;
                    }
                    else
                    {

                        //Payment returned page
                        system ("cls"); //clear screen
                        cout << fixed << setprecision(2);
                        cout << "Purchase of " << drink_name[purchase - 1] << "\t" <<": RM" << drink_price[purchase - 1] << " x " << pur_qty << endl;
              	  		cout << "Total amount" << "\t\t" << ": RM" << total_amount << endl;
                        cout << "Amount paid " << "\t\t" << ": RM" << amt_paid << endl << endl;
                        cout << "Payment returned    " << setw(3) << "" << "RM" << amt_paid << endl << endl;

                        notes_20 = notes_20 + qty_dispensed_ringgit20;
                        notes_10 = notes_10 + qty_dispensed_ringgit10;
                        notes_5 = notes_5 + qty_dispensed_ringgit5;
                        notes_1 = notes_1 + qty_dispensed_ringgit1;
                        coins_50 = coins_50 + qty_dispensed_cts50;
                        coins_20 = coins_20 + qty_dispensed_cts20;
                        coins_10 = coins_10 + qty_dispensed_cts10;

                        return_change = amt_paid - total_amount; //calculate amount return

                        //display amount return change according notes and coins
                        while (abs(return_change) > 0.0001)
                        {

                            if (return_change >= 20.00)
                            {
                                return_change = return_change - 20;
                                unDisp_n20 +=1;
                            }
                            else if (return_change >= 10.00)
                            {
                                return_change = return_change - 10;
                                unDisp_n10 +=1;
                            }
                            else if (return_change >= 5.00)
                            {
                                return_change = return_change - 5;
                                unDisp_n5 +=1;
                            }
                            else if (return_change >= 1.00)
                            {
                                return_change = return_change - 1;
                                unDisp_n1 +=1;
                            }
                            else if (return_change >= 0.50)
                            {
                                return_change = return_change - 0.50;
                                unDisp_c50 +=1;
                            }
                            else if (return_change >= 0.20)
                            {
                                return_change = return_change - 0.20;
                                unDisp_c20 +=1;
                            }
                            else
                            {
                                return_change = return_change - 0.10;
                                unDisp_c10 +=1;
                            }

                        }
                        //display unable dispense message
                        if(unDisp_n20 > 0)
                            cout << "Unable to dispense RM 20.00 x  " << unDisp_n20 << endl;
                        if(unDisp_n10 > 0)
                            cout << "Unable to dispense RM 10.00 x  " << unDisp_n10 << endl;
                        if(unDisp_n1 > 0)
                            cout << "Unable to dispense RM 1.00 x  " << unDisp_n1 << endl;
                        if(unDisp_c50 > 0)
                            cout << "Unable to dispense RM 0.50 x  " << unDisp_c50 << endl;
                        if(unDisp_c20 > 0)
                            cout << "Unable to dispense RM 0.20 x  " << unDisp_c20 << endl;
                        if(unDisp_c10 > 0)
                 		   cout << "Unable to dispense RM 0.10 x  " << unDisp_c10 << endl;

                        //update storage bin accordingly from amount paid return
                        while (abs(amt_paid) > 0.0001)
                        {
                            if (amt_paid >= 20.00)
                            {
                                amt_paid = amt_paid - 20;
                                notes_20 -=1;
                            }
                            else if (amt_paid >= 10.00)
                            {
                                amt_paid = amt_paid - 10;
                                notes_10 -=1;
                            }
                            else if (amt_paid >= 5.00)
                            {
                                amt_paid = amt_paid - 5;
                                notes_5 -=1;
                            }
                            else if (amt_paid >= 1.00)
                            {
                                amt_paid = amt_paid - 1;
                                notes_1 -=1;
                            }
                            else if (amt_paid >= 0.50)
                            {
                                amt_paid = amt_paid - 0.50;
                                coins_50 -=1;
                            }
                            else if (amt_paid >= 0.20)
                            {
                                amt_paid = amt_paid - 0.20;
                                coins_20 -=1;
                            }
                            else
                            {
                                amt_paid = amt_paid - 0.10;
                                coins_10 -=1;
                            }
                        }
                            system("pause");
                            main();
                    }

                }

                //change dispensed menu for display total qty dispensed accordingly if all storage bin is available to dispense accordingly
                if ((qty_dispensed_ringgit20 > 0)||(qty_dispensed_ringgit10 > 0) || (qty_dispensed_ringgit5 > 0)
                    || (qty_dispensed_ringgit1 > 0)|| (qty_dispensed_cts50 > 0)||
                    (qty_dispensed_cts20 > 0) || (qty_dispensed_cts10 > 0))
                {
                    //Change dispensed page
                    system("cls"); //clear screen
                    iniUnit_drink[purchase-1] = iniUnit_drink[purchase-1] - pur_qty ; //order success and update initial qty drink
                    cout << fixed << setprecision(2);
                    cout << "Purchase of " << drink_name[purchase - 1] << "\t" <<": RM" << drink_price[purchase - 1] << " x " << pur_qty << endl;
                    cout << "Total amount" << "\t\t" << ": RM" << total_amount << endl;
                    cout << "Amount paid " << "\t\t" << ": RM" << amt_paid << endl << endl;
                    cout << "Order Success !" << endl << endl;
                    cout << "Change dispensed" << endl;

                    //display qty dispensed accordingly
                    if (qty_dispensed_ringgit20 > 0)
                        cout << "RM20.00 x " << qty_dispensed_ringgit20 << endl;
                    if (qty_dispensed_ringgit10 > 0)
                        cout << "RM10.00 x " << qty_dispensed_ringgit5 << endl;
                    if (qty_dispensed_ringgit5 > 0)
                        cout << "RM5.00 x " << qty_dispensed_ringgit5 << endl;
                    if (qty_dispensed_ringgit1 > 0)
                        cout << "RM1.00 x " << qty_dispensed_ringgit1 << endl;
                    if (qty_dispensed_cts50 > 0)
                        cout << "RM0.50 x " << qty_dispensed_cts50 << endl;
                    if (qty_dispensed_cts20 > 0)
                        cout << "RM0.20 x " << qty_dispensed_cts20 << endl;
                    if (qty_dispensed_cts10 > 0)
                        cout << "RM0.10 x " << qty_dispensed_cts10 << endl;

                    //update storage bin into file
                    ofstream machine_storage_bin;
                    machine_storage_bin.open("storage_bin.txt");
                    machine_storage_bin.clear();
                    machine_storage_bin.seekp(0, ios::beg);
                    machine_storage_bin << notes_20 << "\n" << notes_10 << "\n" << notes_5 << "\n" << notes_1
                                        << "\n" << coins_50 << "\n" << coins_20 << "\n" << coins_10 << "\n";
                    machine_storage_bin.close();

                    //update initial unit of drink into file
                    ofstream inventory_iniUnit;
                    inventory_iniUnit.open("product_iniUnit.txt");

                    for(int i=0; i<iniUnit_drink.size(); i++)
                    {
                        inventory_iniUnit << iniUnit_drink[i] << endl;
                    }

                    inventory_iniUnit.close();

                    //call for record transaction function
                    recordTransaction(drinkname_pur, drinkprice_pur, pur_qty, total_amount, notes_20, notes_10, notes_5, notes_1,
                                        coins_50, coins_20, coins_10);

                    system("pause");
                    main(); //return main menu
                }

            }
    }

    //change dispensed menu for display total qty dispensed accordingly if all storage bin is available to dispense accordingly
    if ((qty_dispensed_ringgit20 > 0)||(qty_dispensed_ringgit10 > 0) || (qty_dispensed_ringgit5 > 0)
                || (qty_dispensed_ringgit1 > 0)|| (qty_dispensed_cts50 > 0)||
                (qty_dispensed_cts20 > 0) || (qty_dispensed_cts10 > 0))
    {
        //Change dispensed page
        system("cls"); //clear screen
        iniUnit_drink[purchase-1] = iniUnit_drink[purchase-1] - pur_qty ; //order success and update initial qty drink
        cout << fixed << setprecision(2);
        cout << "Purchase of " << drink_name[purchase - 1] << "\t" <<": RM" << drink_price[purchase - 1] << " x " << pur_qty << endl;
        cout << "Total amount" << "\t\t" << ": RM" << total_amount << endl;
        cout << "Amount paid " << "\t\t" << ": RM" << amt_paid << endl << endl;
        cout << "Order Success !" << endl << endl;
        cout << "Change dispensed" << endl;

        //display qty dispensed accordingly
        if (qty_dispensed_ringgit20 > 0)
            cout << "RM20.00 x " << qty_dispensed_ringgit20 << endl;
        if (qty_dispensed_ringgit10 > 0)
            cout << "RM10.00 x " << qty_dispensed_ringgit5 << endl;
        if (qty_dispensed_ringgit5 > 0)
            cout << "RM5.00 x " << qty_dispensed_ringgit5 << endl;
        if (qty_dispensed_ringgit1 > 0)
            cout << "RM1.00 x " << qty_dispensed_ringgit1 << endl;
        if (qty_dispensed_cts50 > 0)
            cout << "RM0.50 x " << qty_dispensed_cts50 << endl;
        if (qty_dispensed_cts20 > 0)
            cout << "RM0.20 x " << qty_dispensed_cts20 << endl;
        if (qty_dispensed_cts10 > 0)
            cout << "RM0.10 x " << qty_dispensed_cts10 << endl;

        //update storage bin into file
        ofstream machine_storage_bin;
        machine_storage_bin.open("storage_bin.txt");
        machine_storage_bin.clear();
        machine_storage_bin.seekp(0, ios::beg);
        machine_storage_bin << notes_20 << "\n" << notes_10 << "\n" << notes_5 << "\n" << notes_1
                            << "\n" << coins_50 << "\n" << coins_20 << "\n" << coins_10 << "\n";
        machine_storage_bin.close();

        //update initial unit of drink into file
        ofstream inventory_iniUnit;
        inventory_iniUnit.open("product_iniUnit.txt");

        for(int i=0; i<iniUnit_drink.size(); i++)
        {
            inventory_iniUnit << iniUnit_drink[i] << endl;
        }

        inventory_iniUnit.close();

        //call for record transaction function
        recordTransaction(drinkname_pur, drinkprice_pur, pur_qty, total_amount, notes_20, notes_10, notes_5, notes_1,
                            coins_50, coins_20, coins_10);

        system("pause");
        main(); //return main menu

    }


    return;
}



//record transaction
void recordTransaction(string drinkname_pur, float drinkprice_pur, int pur_qty, float total_amount , int notes_20, int notes_10,
                       int notes_5, int notes_1, int coins_50, int coins_20,int coins_10)
{
    fstream record_data("transaction.csv", ios::in |ios::out| ios::app);
    record_data.setf(ios::fixed);
    record_data.setf(ios::showpoint);
    record_data.precision(2);

    if(record_data.fail())
    {
        cout << "Input file opening failed.\n";
        exit(1);
    }

    record_data << drinkname_pur << "," << drinkprice_pur << "," << pur_qty << "," << total_amount << ","
                << notes_20 << "," << notes_10 << "," << notes_5 << "," << notes_1 << ","
                << coins_50 << "," << coins_20 << "," << coins_10 << endl;

    record_data.close();
}


//admin menu
void adminMenu()
{
    string password_input, password;
    int selection_1;

    ifstream admin_password;
    admin_password.open("password.txt");

    if(admin_password.fail())
    {
        cout << "Input file opening failed.\n";
        exit(1);
    }

    //input stream admin password from file to variable
    admin_password >> password;

    system("cls");
    cout << "Enter your password : ";
    cin >> password_input;

    //Admin menu
    if(password_input == password)
    {
        system("cls");
        cout << "========================================================" << endl;
        cout << "                   Admin Menu                           " << endl;
        cout << "========================================================" << endl;
        cout << "1. Set name, price, initial units of drinks" << endl;
        cout << "2. Set maximum number of cans can be bought" << endl;
        cout << "3. Set the initial amount of money in the machine" << endl;
        cout << "4. View transaction record" << endl;
        cout << "5. Clear transaction record" << endl;
        cout << "6. Change admin password" << endl;
        cout << "7. Exit Admin Menu" << endl;
        cout << "8. End the program" << endl << endl;
        cout << "Enter your selection (1-8): ";
        cin >> selection_1;
        system("cls");
    }
    else
    {
        //output message password wrong and return main menu
        cout << endl;
        cout << "Invalid password !" << endl;
        system("pause");
        main();
    }

    if(selection_1 == 1)
        set_name_price_qty();
    else if (selection_1 == 2)
        set_maximum_bought();
    else if (selection_1 == 3)
        ini_machine_money();
    else if (selection_1 == 4)
        view_TransactionRecord();
    else if (selection_1 == 5)
        clear_trans_record();
    else if (selection_1 == 6)
        change_admin_password();
    else if (selection_1== 7)
        main();
    else if (selection_1 == 8)
    {
        cout << "Program Ended..." << endl;
        exit(1);
    }
    else
    {
        cout << "Invalid selection !" << endl;
    }


    admin_password.close();
    system("pause");
    main();
    return;
}


//set drink name , drink price and initial qty of drink menu
void set_name_price_qty()
{
    int input;

    cout << "=====================================" << endl;
    cout << "           Inventory Menu            " << endl;
    cout << "=====================================" << endl;
    cout << "1. Create Product         " << endl;
    cout << "2. Modify Product         " << endl;
    cout << "3. Display Product Details" << endl;
    cout << "4. Exit Inventory Menu    " << endl;
    cout << "Enter your choice (1-4) : ";
    cin >> input;

    if(input == 1)
    {
        create_product();
    }
    else if (input== 2)
    {
        modify_product();
    }
    else if (input== 3)
    {
        display_product();
    }
    else if (input== 4)
    {
        main();
    }
    else
    {
        cout << "Invalid input";
    }

    return;
}

//create product menu
void create_product()
{
    ifstream inventory_refno;
    ifstream inventory_name;
    ifstream inventory_price;
    ifstream inventory_iniUnit;

    inventory_refno.open("ref_no.txt", ios::in | ios::out);
    inventory_name.open("product_name.txt");
    inventory_price.open("product_price.txt");
    inventory_iniUnit.open("product_iniUnit.txt");

    int temp_ref_no;
    char add_item = 'y';
    char decision;
    string temp_drinkname;
    float temp_drinkprice;
    int temp_ini_can;
    int choice;


    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout << setprecision(2);

    if((inventory_name.fail()) && (inventory_refno.fail())&& (inventory_price.fail()) && (inventory_iniUnit.fail()))
    {
        cout << "Input file opening failed.\n";
        exit(1);
    }

    system("cls");

    //input stream refno from file into variable to track number of type of drink which initialised 1
    inventory_refno >> temp_ref_no;

    if (temp_ref_no <= 11)
    {
        //create product page
        while((add_item == 'Y') || (add_item == 'y')&& (temp_ref_no <= 11))
        {
            cout << "Maximum store for ten types of drinks only." << endl << endl;
            cin.ignore();
            cout << "Enter product name : ";
            getline(cin, temp_drinkname);
            cin.sync();
            cin.ignore();
            drink_name.push_back(temp_drinkname);
            cout << "Enter product price : ";
            cin >> temp_drinkprice;
            cin.sync();
            cin.ignore();
            drink_price.push_back(temp_drinkprice);
            cout << "Enter product initial unit/can : ";
            cin >> temp_ini_can;
            cin.sync();
            cin.ignore();
            iniUnit_drink.push_back(temp_ini_can);
            cout << "Do you want save the new product added ? : ";
            cin >> decision;
            cin.sync();

            //update new record
            if((decision == 'Y') || (decision == 'y'))
            {


                ofstream inventory_refno;
                ofstream inventory_name;
                ofstream inventory_price;
                ofstream inventory_iniUnit;

                inventory_name.clear(); // *** clear the eof flag
                inventory_price.clear();
                inventory_iniUnit.clear();
                inventory_refno.clear();
                inventory_name.seekp(0, ios::cur);
                inventory_price.seekp(0, ios::cur);
                inventory_iniUnit.seekp(0, ios::cur);
                inventory_refno.seekp(0, ios::beg);


                inventory_refno.open("ref_no.txt");
                inventory_name.open("product_name.txt", ios::app);
                inventory_price.open("product_price.txt", ios::app);
                inventory_iniUnit.open("product_iniUnit.txt", ios::app);

                inventory_price.setf(ios::fixed);
                inventory_price.setf(ios::showpoint);
                inventory_price.precision(2);

                //output stream to the file
                inventory_name << drink_name[temp_ref_no-1] << endl;
                inventory_price << drink_price[temp_ref_no-1] << endl;
                inventory_iniUnit << iniUnit_drink[temp_ref_no-1] << endl;
                temp_ref_no+=1;
                inventory_refno << temp_ref_no;

                inventory_name.close();
                inventory_price.close();
                inventory_iniUnit.close();
                inventory_refno.close();

                cout << "Saved successfully." << endl << endl;
            }
            else
            {
                cout << "New Item not added." << endl;
            }

            cout << "Add Item ? (Y/N): " ;
            cin >> add_item;
            cin.sync();
        }
    }
    else
    {
        cout << "Exceeded the maximum number of types of drinks" << endl;
        system("pause");
        inventory_name.close();
        inventory_price.close();
        inventory_iniUnit.close();
        inventory_refno.close();
        main();
    }

    inventory_name.close();
    inventory_price.close();
    inventory_iniUnit.close();
    inventory_refno.close();
    cout << "Program exit now..." << endl;

    return;
}

//modify product page
void modify_product()
{

    int tem_ref_no;
    char decision_1;
    string tem_drinkname;
    string mod_drinkname;
    float tem_drinkprice;
    float mod_drinkprice;
    int tem_ini_can;
    int mod_ini_can;
    int choice_1;


    ifstream inventory_name;
    ifstream inventory_price;
    ifstream inventory_iniUnit;

    inventory_name.open("product_name.txt");
    inventory_price.open("product_price.txt");
    inventory_iniUnit.open("product_iniUnit.txt");

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout << setprecision(2);
    inventory_price.setf(ios::fixed);
    inventory_price.setf(ios::showpoint);
    inventory_price.precision(2);

    if((inventory_name.fail()) && (inventory_price.fail()) && (inventory_iniUnit.fail()))
    {
        cout << "Input file opening failed.\n";
        exit(1);
    }
    cin.ignore();

    //input stream drink name from file into vector
    while(!inventory_name.eof())
    {

        getline(inventory_name, tem_drinkname);
        if(tem_drinkname =="")
        {
             continue;
        }
        drink_name.push_back(tem_drinkname);
    }

    inventory_name.close();
    //input stream drink price from file into vector
    while((!inventory_price.eof()) && (inventory_price >> tem_drinkprice))
    {
        drink_price.push_back(tem_drinkprice);
    }

    inventory_price.close();
    //input stream initial unit of drink from file into vector
    while((!inventory_iniUnit.eof()) && (inventory_iniUnit >> tem_ini_can))
    {
        iniUnit_drink.push_back(tem_ini_can);
    }

    inventory_iniUnit.close();


    system("cls");

    //display drink name menu for modify
    for(int i=0 ; i<drink_name.size() ; i++)
    {
        cout << (i+1) << "\t" << drink_name[i] << endl;
    }

    cout << "Enter the product name you want to modify (1- " << drink_name.size() << " ) ? : ";
    cin >> choice_1;
    cin.sync();
    cin.ignore();
    cout << "Enter Drink Name : ";
    getline(cin, mod_drinkname);
    cin.sync();
    cin.ignore();
    cout << "Enter price : ";
    cin >> mod_drinkprice;
    cin.sync();
    cout << endl;
    cout << "Enter initial units/can : ";
    cin >> mod_ini_can;
    cin.sync();
    cout << endl;

    //update modify details into vector
    drink_name[choice_1-1] = mod_drinkname;
    drink_price[choice_1-1] = mod_drinkprice;
    iniUnit_drink[choice_1-1] = mod_ini_can;

    ofstream inventory_name_ouput;
    ofstream inventory_price_output;
    ofstream inventory_iniUnit_output;

    inventory_name_ouput.open("product_name.txt");
    inventory_price_output.open("product_price.txt");
    inventory_iniUnit_output.open("product_iniUnit.txt");

    //update record into file
    for(int j=0; j < drink_name.size(); j++)
    {
        cin.sync();
        inventory_name_ouput << drink_name[j] << endl;
    }


    //update record into file
    for(int k=0; k< drink_price.size(); k++)
    {
        cin.sync();
        inventory_price_output << drink_price[k] << endl;
    }

    //update record into file
    for(int l=0; l< iniUnit_drink.size(); l++)
    {
        cin.sync();
        inventory_iniUnit_output << iniUnit_drink[l] << endl;

    }

    cout << "Successfully modified.." << endl;

    drink_name.clear();
    drink_price.clear();
    iniUnit_drink.clear();
    inventory_name.close();
    inventory_price.close();
    inventory_iniUnit.close();

    return;
}

//display product details
void display_product()
{
    fstream inventory_name("product_name.txt", ios::in | ios::out| ios::app);
    fstream inventory_price("product_price.txt", ios::in | ios::out| ios::app);
    fstream inventory_iniUnit("product_iniUnit.txt", ios::in | ios::out| ios::app);

    char next;
    char next_1;
    char next_2;

    if((inventory_name.fail())&& (inventory_price.fail()) && (inventory_iniUnit.fail()))
    {
        cout << "Input file opening failed.\n";
        exit(1);
    }

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout << setprecision(2);

    system("cls");

    //display type of drink record
    inventory_name.get(next);
    cout << "Product name" << endl;
    while((!inventory_name.eof()))
    {
        cout << next;
        inventory_name.get(next);
    }

    cout << endl << endl;
    cout << "Product price according by product name sequence" << endl;

    //display drink price details
    inventory_price.get(next_1);
    while((!inventory_price.eof()))
    {
        cout << next_1;
        inventory_price.get(next_1);
    }

    cout << endl << endl;

    //display initial unit of drink details
    inventory_iniUnit.get(next_2);
    cout << "Product initial unit/can according by product name sequence" << endl;
    while((!inventory_iniUnit.eof()))
    {
        cout << next_2;
        inventory_iniUnit.get(next_2);
    }


    inventory_name.close();
    inventory_price.close();
    inventory_iniUnit.close();

    return;
}

//view transaction record page
void view_TransactionRecord()
{
    fstream output("transaction.csv", ios::in | ios::out);

    if(output.fail())
    {
        cout << "Input file opening failed.\n";
        exit(1);
    }
    char next;
    output.get(next);
    //display transaction record details from file
    while((!output.eof()))
    {
        cout << next;
        output.get(next);
    }
    return;
}

//set maximum unit of drink purchased
void set_maximum_bought()
{
    int maximum_can;
    fstream maximum_cans_bought("maximum_can.txt", ios::in | ios::out);

    if(maximum_cans_bought.fail())
    {
        cout << "Input file opening failed.\n";
        exit(1);
    }

    //input stream maximum unit of purchased from file into variable
    maximum_cans_bought >> maximum_can;
    maximum_cans_bought.clear() ; // *** clear the eof flag

    cout << "Maximum number of can which can be bought/transaction : " << maximum_can << endl;
    cout << "Enter a number of can you want to change (max 5 cans/transaction) : ";
    cin >> maximum_can;
    cin.sync();


    //maximum purchased allow 5 cans per transaction only
    while(maximum_can > 5)
    {
        cout << endl;
        cout << "Exceeded number of maximum can, please enter again : ";
        cin >> maximum_can;
        cin.sync();

    }

    //output the modify record into file
    maximum_cans_bought.seekp(0, ios::beg);
    maximum_cans_bought << maximum_can;

    cout <<endl;
    cout << "Modify Successfully." << endl;
    cout << "Maximum number of can which can be bought/transaction : " << maximum_can << endl << endl;

    maximum_cans_bought.close();

    return;
}

//money storage bin page
void ini_machine_money()
{
    int notes_20 = 0;
    int notes_10 = 0;
    int notes_5 = 0;
    int notes_1 = 0;
    int coins_50 = 0;
    int coins_20 = 0;
    int coins_10 = 0;
    int selection = 0;


    fstream machine_storage_bin("storage_bin.txt", ios::in | ios::out);


    if(machine_storage_bin.fail())
    {
        cout << "Input/output file opening failed.\n";
        exit(1);
    }

    //input stream each money storage bin from file into variable
    machine_storage_bin >> notes_20 >> notes_10 >> notes_5 >> notes_1 >> coins_50 >> coins_20 >> coins_10;
    machine_storage_bin.clear() ; // *** clear the eof flag


    //money storage bin menu
    cout << "=======================================================================" << endl;
    cout << "No." << "   " << "Amount  " << "   " << "Current Quantity" << endl;
    cout << "=======================================================================" << endl;
    cout << "1."  << "   " << "RM 20.00" << "   " <<  notes_20 << endl;
    cout << "2."  << "   " << "RM 10.00" << "   " <<  notes_10 << endl;
    cout << "3."  << "   " << "RM  5.00" << "   " <<  notes_5  << endl;
    cout << "4."  << "   " << "RM  1.00" << "   " <<  notes_1  << endl;
    cout << "5."  << "   " << "RM  0.50" << "   " <<  coins_50 << endl;
    cout << "6."  << "   " << "RM  0.20" << "   " <<  coins_20 << endl;
    cout << "7."  << "   " << "RM  0.10" << "   " <<  coins_10 << endl;
    cout << "8."  << "   " << "Exit    " << endl << endl;
    cout << "Enter which storage bin you want to modify (1-7): ";
    cin >> selection;
    cin.sync();

    do
    {
        cout << "Maximum store 20 units only in each storage bin" << endl << endl;

        switch(selection)
        {
        case 1:
            cout << "Enter quantity : ";
            cin >> notes_20;
            cin.sync();
            break;
        case 2:
            cout << "Enter quantity : ";
            cin >> notes_10;
            cin.sync();
            break;
        case 3:
            cout << "Enter quantity : ";
            cin >> notes_5;
            cin.sync();
            break;
        case 4:
            cout << "Enter quantity : ";
            cin >> notes_1;
            cin.sync();
            break;
        case 5:
            cout << "Enter quantity : ";
            cin >> coins_50;
            cin.sync();
            break;
        case 6:
            cout << "Enter quantity : ";
            cin >> coins_20;
            cin.sync();
            break;
        case 7:
            cout << "Enter quantity : ";
            cin >> coins_10;
            cin.sync();
            break;
        case 8:
            main();
        default:
            cout << "Invalid input !";
            cin.sync();
            cin.ignore();
        }

    }
    while ((notes_20 > 20) || (notes_10 > 20) || (notes_5 > 20) ||
            (notes_1 > 20) || (coins_50 > 20) || (coins_20 > 20) ||
            (coins_10 > 20));

    //output stream modify record details into file
    machine_storage_bin.clear();
    machine_storage_bin.seekp(0, ios::beg);
    machine_storage_bin << notes_20 << "\n" << notes_10 << "\n" << notes_5 << "\n" << notes_1
                        << "\n" << coins_50 << "\n" << coins_20 << "\n" << coins_10 << "\n";

    system("cls");

    //display modified record
    cout << "Modify Successfully..." << endl << endl;
    cout << "=======================================================================" << endl;
    cout << "No." << "   " << "Amount  " << "   " << "Current Quantity" << endl;
    cout << "=======================================================================" << endl;
    cout << "1."  << "   " << "RM 20.00" << "   " <<  notes_20 << endl;
    cout << "2."  << "   " << "RM 10.00" << "   " <<  notes_10 << endl;
    cout << "3."  << "   " << "RM  5.00" << "   " <<  notes_5  << endl;
    cout << "4."  << "   " << "RM  1.00" << "   " <<  notes_1  << endl;
    cout << "5."  << "   " << "RM  0.50" << "   " <<  coins_50 << endl;
    cout << "6."  << "   " << "RM  0.20" << "   " <<  coins_20 << endl;
    cout << "7."  << "   " << "RM  0.10" << "   " <<  coins_10 << endl;

    machine_storage_bin.close();

    return;
}

//clear content of the file page
void clear_trans_record()
{
    char input_file_name [20]; //variable for user to key in the
    //file name that wanted to clear the content
    char decision;
    ifstream input_file;
    cout << "Enter the file name you want to clear the contents with type "
         << "of file extension." << endl;
    cout << "Example: file_name.txt (maximum of 19 characters). " << endl << endl;
    cout << "File name : ";
    cin >> input_file_name;
    cin.sync();

    input_file.open(input_file_name);

    if(input_file.fail())
    {
        cout << "Input file opening failed.\n";
        exit(1);
    }

    cout << endl;
    cout << "Are you sure you want to clear the contents of this file "
         << input_file_name << "? (Y/N) : ";
    cin >> decision;
    cin.sync();

    //the content of file that user key in will erase
    if((decision == 'Y') || (decision == 'y'))
    {
        input_file.close();
        input_file.open(input_file_name, ios::out | ios::trunc);
        cout << input_file_name << " contents successfully cleared." << endl << endl;
    }
    else
    {
        cout << input_file_name << " file contents unchanged." << endl << endl;
    }

    input_file.close();

    return;
}

//change admin password page
void change_admin_password()
{
    string new_password, reconfirm_password;

    cout <<"Enter new admin password : ";
    cin >> new_password;
    cin.sync();
    cout << "Reconfirm your new admin password : ";
    cin >>reconfirm_password;
    cin.sync();

    //update new password
    if (new_password == reconfirm_password)
    {
        cout << endl;
        cout << "Successfully changed admin password." << endl;
        ofstream newpassword("password.txt");
        newpassword << new_password;
        newpassword.close();
    }
    else
    {
        cout << endl;
        cout << "The password you typed doesn't match." << endl;
    }

    return;
}

