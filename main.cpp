
	
#include<iostream>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#include<mysql.h>
#include<mysqld_error.h>

using namespace std;



int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;



class db_response

{
    public:
    static void ConnectionFunction()
    {
        conn = mysql_init(0);
        if(conn)
        {
            cout<< "DATABASE CONNECTED :)" <<endl;
            cout<< "press any key to continue..."<<endl;

            system("cls");
        }
        else
        cout<<"FAILED TO CONNECT :("<< mysql_errno(conn) << endl;
        conn = mysql_real_connect(conn, "localhost", "root", "Sam@1209", "oops", 3306, NULL, 0);
        if(conn)
        {
            cout<<"DATA BASE CONNECTED TO MYSQL :)" <<conn<<endl;
            cout<<"press any key to continue.."<<endl;
            system("cls");
        }
        else
        cout<<"FAILED TO CONNECT :("<< mysql_errno(conn) << endl;
    }

};

void ADD_ITEM_DATABASE();
void SHOW_ALL_ITEMS();
void ITEMS_IN_STOCK();
void FIND_INSTRUMENT();
void EDIT_ITEM();
void REMOVE_ITEM();
void CREATE_ORDER();
void SOLD_ITEMS();
int main(){

	system("color  B0");
	system("cls");
    system("title Music Store Management Program");

	
	db_response::ConnectionFunction();
	int chooseOneFromMenu =0;
	char exitSurity;  
    cout << "\n\n\n\t\t\t\t     **************************************************";
    cout << "\n\n\n\t\t\t\t              MUSIC STORE MANAGEMENT SYSTEM            ";
    cout << "\n\n\n\t\t\t\t     **************************************************";
    cout << "\n-------MUSIC STORE MENU-----" << endl;
    cout << "\n1. ADD NEW INSTRUMENT." << endl;
    cout << "2. SOLD ITEMS." << endl;
    cout << "3. ITEMS IN STOCK." << endl;
    cout << "4. FIND MUSIC INSTRUMENTS." << endl;
    cout << "5. EDIT ITEM." << endl;
    cout << "6. REMOVE ITEM." << endl;
    cout << "7. SHOW ALL ITEMS MENU." << endl;
    cout << "8. CREATE ORDER." << endl;
    cout << "9. EXIT." << endl;
    
    cout << "\nCHOOSE ONE: ";
    cin >> chooseOneFromMenu;

    switch (chooseOneFromMenu)
    {
    case 1:
    	ADD_ITEM_DATABASE(); 
        break;
    case 2:
    	SOLD_ITEMS();
        break;
    case 3:
    	ITEMS_IN_STOCK();

        break;
    case 4:
    	FIND_INSTRUMENT();
   
        break;
    case 5:
       EDIT_ITEM();
        break;
    case 6:
         REMOVE_ITEM();
        break;
    case 7:
    	SHOW_ALL_ITEMS();  
     
        break;
    case 8:
        CREATE_ORDER();
        break;
    case 9:
        ExitProgram:
       
        cout << "Program terminating. Are you sure? (y/N): ";
        cin >> exitSurity;
        if (exitSurity == 'y' || exitSurity == 'Y') {
            return 0;
        }else if (exitSurity == 'n' || exitSurity == 'N') {
            system("cls");
            main();
        }else {
            cout << "Next time choose after read the corresponding line." << endl;
            goto ExitProgram;
        }
        break;
    default:
        cout << "Please choose between 1 - 7. Press Enter To Continue...";
        getch();
        system("cls");
        main();
        break;
    }
    return 0;
}


void SHOW_ALL_ITEMS()
{
    system("cls");

    // Variables
    char choose;


    cout << "Welcome To Music Store" << endl << endl;
    cout << "Show All Items Menu" << endl << endl;

    qstate = mysql_query(conn, "select * from musicinfo_db");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            cout << "id: " << row[0] <<"\ntype: " << row[1] << "\ninstrument: " << row[2] << "\nbrand: " << row[3] << "\nprice: " << row[4] << "\nquantity: " << row[5] << endl << endl;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }


    cout << "Press 'm' to Menu and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else
    {
        exit(0);
    }
}
void ADD_ITEM_DATABASE()
{
    // Initial Load
    system("cls");
    // Initial Load End

    // Variables

    string type = "";
    string instrument = "";
    string brand = "";
    int price = 0;
    int quantity = 0;
    char choose;
    // Variables End

    cout << "Welcome To Music Store" << endl << endl;
    cout << "Add New Item Menu" << endl << endl;

    cin.ignore(1, '\n');
    cout << "Enter Type of Instrument: ";
    getline(cin, type);
    cout << "Enter Instrument Name: ";
    getline(cin, instrument);
    cout << "Enter brand: ";
    getline(cin, brand);
    cout << "Enter Price: ";
    cin >> price;
    cout << "Enter Quantity: ";
    cin >> quantity;

    stringstream streamPrice, streamQuan;
    string sprice, squan;
    streamPrice << price;
    streamPrice >> sprice;
    streamQuan << quantity;
    streamQuan >> squan;


    string insert_query = "insert into musicinfo_db ( type, instrument, brand, price, quantity) values ('"+type+"','"+instrument+"','"+brand+"','"+sprice+"','"+squan+"')";

    const char* q = insert_query.c_str(); 

    qstate = mysql_query(conn, q);

    if (!qstate)
    {
        cout << endl << "Successfully added in database..." << endl;
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    // Exit Code
    cout << "Press 'm' to Menu and 'a' to Insert Again Or Any Other key to exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else if (choose == 'a' || choose == 'A')
    {
        ADD_ITEM_DATABASE();
    }
    else
    {
        exit(0);
    }
}

void ITEMS_IN_STOCK()
{
    system("cls");

    // Variables
    char choose;
    // Variables End

    cout << "Welcome To Music Store" << endl << endl;
    cout << "Items In Stock Menu" << endl << endl;

    qstate = mysql_query(conn, "select Instrument, brand, price, quantity from musicinfo_db");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res)))
        {
            if (atoi(row[3]) > 0)
            {
                cout << "instrument: " << row[0] << "\nbrand: " << row[1] << "\nprice: " << row[2] << "\nquantity: " << row[3] << endl << endl;
            }
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    cout << "Press 'm' to Menu and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else
    {
        exit(0);
    }
}

void FIND_INSTRUMENT()
{
    system("cls");

    // Variables
    char choose;
    string input;
    // Variables End

    cout << "Welcome To Music Store" << endl << endl;
    cout << "Find Music Menu" << endl << endl;

    cout << "Find by \n1. Instrument \n2. Type\n3. Brand\nAny other number to Menu" << endl;
    cout << "Choose One: "; 
	cin >> choose;
    system("cls");

    cin.ignore(1, '\n');
    if (choose == '1')
    {
        cout << "Enter Instrument Name: "; getline(cin, input);
        string findbyinstrument_query = "select * from musicinfo_db where instrument like '"+input+"%'";
        const char* qi = findbyinstrument_query.c_str();
        qstate = mysql_query(conn, qi);
    }

    else if (choose == '2')
    {
        cout << "Enter Type: "; getline(cin, input);
        string findbytype_query = "select * from musicinfo_db where type like '"+input+"%'";
        const char* qt = findbytype_query.c_str();
        qstate = mysql_query(conn, qt);
    }
    else if (choose == '3')
    {
        cout << "Enter Brand: "; getline(cin, input);
        string findbybrand_query = "select * from musicinfo_db where brand like '"+input+"%'";
        const char* qb = findbybrand_query.c_str();
        qstate = mysql_query(conn, qb);
    }
    else
    {
        goto ExitMenu;
    }

    cout << endl;
    if (choose == '1' || choose == '2' || choose == '3' )
    {
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while ((row = mysql_fetch_row(res)))
            {
                cout << "id: " << row[0] <<  "\ntype: " << row[1] << "\ninstrument: " << row[2] << "\nbrand: " << row[3] << "\nprice: " << row[4] << "\nquantity: " << row[5] << endl << endl;
            }
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }
    }

    ExitMenu:
    cout << "Press 'm' to Menu, 'a' to Search again and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else if (choose == 'a' || choose == 'A')
    {
        FIND_INSTRUMENT();
    }
    else
    {
        exit(0);
    }
}

void EDIT_ITEM()
{
    system("cls");

    
   
    string type = "";
    string instrument = "";
    string brand = "";
    string items[300];
    string price = "";
    string quantity = "";
    char choose;
    int itemId;
    bool HaveException = false;
    bool NotInDatabase = false;
    int indexForId = 0;

    
    string storeid="";
    string storetype = "";
    string storeinstrument = "";
    string storebrand = "";
    string storeprice = "";
    string storequantity = "";
     
    

    cout << "Welcome To Music Store" << endl << endl;
    cout << "Edit Item Menu" << endl << endl;

    qstate = mysql_query(conn, "select id, instrument from musicinfo_db");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        cout << "ID\tInstrument\n" << endl;
        while ((row = mysql_fetch_row(res)))
        {
            cout << row[0] << "\t" << row[1] << endl;
            items[indexForId] = row[0];
            indexForId++;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    try
    {
        cout << endl;
        cout << "Enter Item ID: ";
        cin >> itemId;
        cout << endl;
    }
    catch (exception e)
    {
        cout << "Please Enter a valid NUMBER." << endl;
        HaveException = true;
        goto ExitMenu;
    }

    if (HaveException == false)
    {
        stringstream streamid;
        string strid;
        streamid << itemId;
        streamid >> strid;

        for (int i = 0; i < indexForId; i++)
        {
            if (strid != items[i])
            {
                NotInDatabase = true;
            }
			else
            {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false)
        {
            string findbyid_query = "select * from musicinfo_db where id = '"+strid+"'";
            const char* qd = findbyid_query.c_str();
            qstate = mysql_query(conn, qd);

            if (!qstate)
            {
                res = mysql_store_result(conn);
                cout << endl;
                while ((row = mysql_fetch_row(res)))
                {
                   cout <<"id:"<< row[0]<< "\ntype:" << row[1] << "\ninstrument:" << row[2] << "\nBrand:" << row[3] << "\nprice:" << row[4] << "\nquantity:" << row[5] << endl << endl;
                
                    storeid = row[0];
                    storetype = row[1];
                    storeinstrument = row[2];
                    storebrand = row[3];
                    storeprice = row[4];
                    storequantity = row[5];
                }
            }
            else
            {
                cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
            }

            cin.ignore(1, '\n');

            cout << "Enter Type (No to not change): ";
            getline(cin, type);
            if (type == "no" || type == "No")
            {
                type = storetype;
            }
            cout << "Enter Instrument Name (No to not change): ";
            getline(cin, instrument);
            if (instrument == "no"||  instrument == "No")
            {
                instrument = storeinstrument;
            }
            cout << "Enter brand (No to not change): ";
            getline(cin, brand);
            if (brand == "no" ||  brand == "No")
            {
                brand = storebrand;
            }
            cout << "Enter Price (No to not change): ";
            cin >> price;
            if (price == "no" ||  price == "No")
            {
               price = storeprice;
            }
            cout << "Enter Quantity (No to not change): ";
            cin >> quantity;
            if (quantity == "no"  || quantity == "No")
            {
                quantity = storequantity;
            }

            string update_query = "update musicinfo_db set type ='"+type+"' , instrument = '"+instrument+"', brand= '"+brand+"', price = '"+price+"', quantity = '"+quantity+"' where id = '"+strid+"'";
            const char* qu = update_query.c_str();
            qstate = mysql_query(conn, qu);

            if (!qstate)
            {
                cout << endl << "Successfully Saved In Database..." << endl;
            }
            else
            {
                cout << "Failed To Update!" << mysql_errno(conn) << endl;
            }

        }
        else
        {
            cout << "Item Not Found in database." << endl;
        }
    }

    ExitMenu:
    cout << "Press 'm' to Menu, 'e' to edit another item and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else if (choose == 'e' || choose == 'E')
    {
        EDIT_ITEM();
    }
    else
    {
        exit(0);
    }
}

void REMOVE_ITEM()
{
    system("cls");

    // Variables
    char choose;
    int itemId;
    string items[5000];
    int indexForId = 0;
    bool HaveException = false;
	bool NotInDatabase = false;
    // Variables End

    cout << "Welcome To Music Store" << endl << endl;
    cout << "Remove Item Menu" << endl << endl;

    qstate = mysql_query(conn, "select id, instrument from musicinfo_db");
    if (!qstate)
    {
        res = mysql_store_result(conn);
        cout << "ID\tInstrument\n" << endl;
        while ((row = mysql_fetch_row(res)))
        {
            cout << row[0] << "\t" << row[1] << endl;
            items[indexForId] = row[0];
            indexForId++;
        }
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    try
    {
        cout << endl;
        cout << "Enter Item ID: ";
        cin >> itemId;
        cout << endl;
    }
    catch (exception e)
    {
        cout << "Please Enter a valid NUMBER." << endl;
        HaveException = true;
        goto ExitMenu;
    }

    if (HaveException == false)
    {
        stringstream streamid;
        string strid;
        streamid << itemId;
        streamid >> strid;

        for (int i = 0; i < indexForId; i++)
        {
            if (strid != items[i])
            {
                NotInDatabase = true;
            }
			else
            {
                NotInDatabase = false;
                break;
            }
        }

        if (NotInDatabase == false)
        {
            string delete_query = "delete from musicinfo_db where id = '"+strid+"'";
            const char* qr = delete_query.c_str();
            qstate = mysql_query(conn, qr);

            if (!qstate)
            {
                cout << "Successfully Deleted From Database." << endl;
            }
            else
            {
                cout << "Failed To Delete!" << mysql_errno(conn) << endl;
            }

        }
        else
        {
            cout << "Item Not Found in database." << endl;
        }
    }
    ExitMenu:
    cout<<"Press 'm to Menu, 'd' to delete another item and any other key to Exit:";
    cin>>choose;
    if(choose == 'm' ||  choose == 'M')
    {
        main();
    }
    else if(choose == 'd' || choose == 'D')
    {
        REMOVE_ITEM();
    }
    else
    {
        exit(0);
    }
}
     void SOLD_ITEMS()
     {
        system("cls");

        char choose;
        cout<<"Welcome to music store"<< endl <<endl;
        cout<<"Sold Items Menu"<< endl <<endl;

        qstate = mysql_query(conn," select id,type,instrument,brand,price,sum(quantity)from solditem_db group by instrument");
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while ((row = mysql_fetch_row(res)))
            {
               cout<< "id:"<<row[0]<< "\ntype:"<< row[1] << "\ninstrument:"<<row[2]<< "\nbrand:"<<row[3] <<"\nprice:"<<row[4]<<"\nquantity:"<<row[5]<<endl<<endl;
            }

        }
        else
        {
            cout<< "Query Execution Problem!" << mysql_errno(conn) << endl;

        }

        cout<<"Press 'm' to Menu and any other key to Exit:";
        cin>>choose;
        if (choose == 'm' || choose =='M')
        {
            main();
        }
        else
        {
            exit(0);
        }

     }
     
void CREATE_ORDER()
{
	system("cls");
	char choose;
	string getid = "";
	string itemid[5000];
	string instrument[5000];
	char chooseEditorBuy;
	int itemIndex = 0;
	float totalprice = 0.0;
	bool purchase,itemFalse= false;
	char chooseEditOrBuy;
	string storeid[5000];
	string storeinstrument[5000];
	string storetype[5000];
	string storebrand[5000];
	string storeprice[5000];
	string storequantity[5000];
	int storeIndex = 0,storeIndexN=0;
	cout << "Welcome To Music Store" << endl <<endl;
	cout<<  "Show All Items Menu " << endl <<endl;
	
	qstate = mysql_query(conn,"select * from musicinfo_db");
	if(!qstate)
	{
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res)))
		{
			if(atoi(row[5])> 0)
			{
			  cout << "id:"	<<row[0]<<"\ntype:"<<row[1]<<"\ninstrument:"<<row[2]<<"\nbrand:"<<row[3]<<"\nprice"<<row[4]<<endl<<endl;
			  storeid[storeIndex] = row[0];
			  storetype[storeIndex] = row[1];
			  storeinstrument[storeIndex] = row[2];
			  storebrand[storeIndex] = row[3];
			  storeprice[storeIndex] = row[4];
			  storequantity[storeIndex] = row[5];
			  storeIndex;
			}
		}
	}
	else
	{
		cout <<"Query Execution Problem :("<<mysql_errno(conn) <<endl;
	}
	for(itemIndex = 0;;itemIndex++)
	{
		cout<<"Enter a instrument ID's (e to exit):";
		cin>>getid;
		if(getid == "e")
		{
			break;
		}
		else
		{
			for(int i = 0; i<storeIndex; i ++)
			{
				if(getid == storeid[i])
				{
					itemid[itemIndex] = getid;;
					itemFalse = false;
					break;
				}
				else
				{
					itemFalse = true;
				}
			}
			if(itemFalse == true)
			{
				cout << "Enter a valid number." << endl;
				itemIndex--;
				itemFalse = false;
			}
		}
	}
	cout << "You choose this instrument id's:";
	for(int i = 0;i<itemIndex;i++)
	{
		cout<<itemid[i] << " ";
	}
	CHOOSEEDITORBUY:
	cout<<endl<<"Do you want to edit items(a) or buy this items(b):";
	cin>>chooseEditOrBuy;
	
	if(chooseEditOrBuy == 'a')
	{
		for(int i = 0;;i++)
		{
			cout<<"Remove item id's( e to exit):";
			cin>>getid;
			if(getid == "e")
			{
				break;
			}
			else
			{
				for(int j =0;j < itemIndex;j++)
				{
					if(itemid[j] == getid)
					{
						for(int k = j; k<itemIndex;k++)
						{
							itemid[k] = itemid[k+1];
						}
						itemid[itemIndex--] ="\0";
					}
				}
			}
		}
		cout<<"You choose this instrument id's";
		for(int i = 0; i<itemIndex;i++)
		{
			cout<<itemid[i] << " ";
		}
		goto CHOOSEEDITORBUY;
	}
	else if(chooseEditOrBuy == 'b')
	{
		for(int i = 0;i<itemIndex; i++)
		{
			for(int j = 0;j<storeIndex;j++)
			{
				if(itemid[i] == storeid[j])
				{
					qstate = mysql_query(conn,"select quantity from musicinfo_db");
					if(!qstate)
					{
						res = mysql_store_result(conn);
						while((row = mysql_fetch_row(res)))
						{
							if(atoi(row[0]) > 0)
							{
								storequantity[storeIndexN] = row[0];
								storeIndexN++;
							}
						}
						storeIndexN = 0;
					}
					else
					{
						cout<<"Query Execution Problem!" << mysql_errno(conn) << endl;
					}
					totalprice += strtof((storeprice[j]).c_str(),0);
					float quan1 = strtof((storequantity[j]).c_str(),0);
					quan1 -=1;
					float quan2 = strtof((storequantity[j]).c_str(),0);
					float quan = quan2 -quan1;
					string getResult;
					stringstream strquan;
					strquan << quan;
					strquan >> getResult;
					
					string getQuan1;
					stringstream strquan1;
					strquan1 << quan1;
					strquan1 >> getQuan1;
					
					string insert_query="insert into solditem_db(type,instrument,brand,price,quantity) values('"+storetype[j]+"','"+storeinstrument[j]+"','"+storebrand[j]+"','"+storeprice[j]+"','"+getResult+"')";
					purchase = true;
					
					const char* q = insert_query.c_str();
					qstate = mysql_query(conn,q);
					if(!qstate)
					{
						purchase = true;
					}
					else
					{
						cout<<"Query Execution Problem!"<<mysql_errno(conn)<<endl;
					}
					
					string update_query = "update musicinfo_db set quantity = '"+getQuan1+"'' where id = '"+storeid[j]+"' ";
					const char* qu = update_query.c_str();
					qstate = mysql_query(conn,qu);
					if(qstate)
					{
						cout<< "Failed to Update!" <<mysql_errno(conn)<<endl;
					}
				}
			}
	    }
	    if(purchase == true)
	    {
	    	cout << endl << "Purchase Succesfully Done." << endl;
	    	cout << endl << "Total Price:" << totalprice <<endl;
		}
	}
	cout<<endl<< "Press 'm' to Menu and any other key to exit." <<endl;
	cin>>choose;
	if(choose == 'm' || choose == 'M')
	{
		main();
	}
	else
	{
		exit(0);
	}
}

