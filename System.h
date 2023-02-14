
char curr_pass[8];

ll create_admin_id(){
    ifstream in;
    Admin a;
    in.open("admins.txt", ios::in);
    vector < ll > v;
    in.read((char*)&a, sizeof(a));
    
    while(!in.eof()){
    v.push_back(a.id);
    in.read((char*)&a, sizeof(a)); 
    }
    int real_id = 2001;
    sort(v.begin(), v.end());
    for(int i = 0; i < v.size(); i++){
        if(real_id == v[i]){
            real_id++;
        }
        else break;
    }
    in.close();
    return real_id;
}

char* get_curr_pass(){
    ifstream in;
    ATM atm;
    in.open("system.txt", ios::in);
    in.read((char*) &atm, sizeof(atm));
    in.close();
    strcpy(curr_pass, atm.password);
    return curr_pass;
}

void delete_Admin(ll id){
    ifstream in("admins.txt", ios::in);
    ofstream out("temp.txt", ios::out);
    Admin a;
    set_color(h, 12);
    if(in.is_open())
    {
        bool exist = false;
        in.read((char*)& a, sizeof(a));
        while(!in.eof()){
          if(a.id != id){
            out.write((char*) &a, sizeof(a));
          }
          else exist = true;
          in.read((char*)& a, sizeof(a));
        }
        in.close();
        out.close();
        remove("admins.txt");
        rename("temp.txt", "admins.txt");
        if(!exist) cout << "Not exist....\n";
    }
    else cout << "Can't open the specified file...\n";
}

void DeleteAllAdmins(){
    ifstream in("admins.txt", ios::in);
    ofstream out("temp.txt", ios::out);
    in.close();
    out.close();
    remove("admins.txt");
    rename("temp.txt", "admins.txt");
}

vector < Admin > Get_Resignation_Requests(){
    ifstream in;
    in.open("admins.txt", ios::in);
    Admin A_temp;
    vector < Admin > v;
    if(in.is_open()){
        in.read((char*) &A_temp, sizeof(A_temp));
        while(!in.eof()){
            if(A_temp.resignation) v.push_back(A_temp);
            in.read((char*) &A_temp, sizeof(A_temp));
        }
        in.close();
    }
    else {
        set_color(h, 12);
        cout << "\n\t\tCan't open the specified file :(\a\n";
        set_color(h, 15);
    }
    return v;
}

void Resignation_Requests(int i, bool first_req = true){
    system("cls");
    set_color(h, 4);
    cout << "\n" << string(36, ' ') << "Resignation Requests\n";
    cout << string(34, ' ') << "________________________\n\n";
    set_color(h, 15);
    cout << "\t\t" << string(56, '-') << "\n";
    vector < Admin > requests = Get_Resignation_Requests();
    if(i >= sz(requests) && !first_req){
        set_color(h, 6);
        cout << "\n\t\tEnd of resignation requests list.\n";
        Press_any_key();
        return;
    }
    if(!sz(requests)){
        set_color(h, 2);
        cout << "\n\t\tThere is no resignation requests.\n";
        Press_any_key();
    }
    else {
        if(first_req)
        {   
            set_color(h, 6);
            cout << "\n\t\tThere is " << sz(requests) << " resignation requests.\n";
            set_color(h, 15);
            cout << "\n\t\t1. Show requests"; set_color(h, 8); cout << "\n\t\t0. Go back"; set_color(h, 15);
            cout << "\n\n\t\tEnter: ";
            int opt; cin >> opt;
            if(opt == 0) return;
            else if(opt == 1){
                Resignation_Requests(0, false);
                return;
            }
            else {
                set_color(h, 12);
                cout << "\n\t\tInvalid option"; printing("...!\n");
                Press_any_key();
                return;
            }
        }
        show:
        set_color(h, 3);
        cout << "\n\t\tRequet #" << i + 1 << "\n";
        set_color(h, 11);
        cout << "\t\tName: " << requests[i].name << "  ID: " << requests[i].id << "\n";
        cout << "\t\tReason: "; set_color(h, 6); cout << requests[i].reason << "\n";
        set_color(h, 15);
        cout << "\n\t\t1. Accept\n\t\t2. Refuse\n\t\t3. Skip";
        set_color(h, 8); cout << "\n\t\t0. Exit\n"; set_color(h, 15);
        cout << "\n\t\tEnter: ";
        int opt; cin >> opt;
        switch(opt)
        {
            case 0:
              return;
            case 1:
              delete_Admin(requests[i].id);
              set_color(h, 10);
              cout << "\n\t\tThis admin no longer exists\n";
              Press_any_key();
              Resignation_Requests(i, false);
              break;
            case 2:
              requests[i].resignation = false;
              memset(requests[i].reason, '\0', 200);
              updateAdmin(requests[i]);
              set_color(h, 10);
              cout << "\n\t\tThe request has been rejected successfully\n";
              Press_any_key();
              Resignation_Requests(i, false);
              break;
            case 3:
              Resignation_Requests(i + 1, false);
              break;
            default:
              set_color(h, 12);
              cout << "\n\t\tInvalid option"; printing("...!\n");
              Press_any_key();
        }
    }
}

void Change_System_Password(){
    char pass[20], newp[20], confirm[20];
    cout << "\n\t\tEnter current password: ";
    set_password(pass, 20);
    if(!strcmp(pass, get_curr_pass())){
        cout << "\t\tEnter new password: ";
        set_password(newp, 20);
        cout << "\t\tConfirm password: ";
        set_password(confirm, 20);
        if(!strcmp(newp, confirm)){
            fstream in("system.txt", ios::in | ios::out);
            ATM atm;
            in.read((char*) &atm, sizeof(atm));
            strcpy(atm.password, newp);
            int currp = in.tellg();
            in.seekp(currp - sizeof(atm), ios::beg);
            in.write((char*) &atm, sizeof(atm));
            in.close();
            set_color(h, 10);
            cout << "\n\t\tPassword has been changed successfully...\n";
        }
        else {
            set_color(h, 12);
            cout << "\n\t\tYour confirm password doesn't match!\n";
        }
    }
    else {
        set_color(h, 12);
        cout << "\n\t\tIncorrect password :(\a\n";
    }
}

void Operations_On_Users(){
    system("cls");
    cout << "\n" << string(40, ' ') << "Explore Users\n";
    cout << string(38, ' ') << string(17, '_') << "\n\n";
    cout << "\t\t" << string(56, '-') << "\n";
    ll id;
    User temp;
    cout << "\n\t\t1. Show all users\n\t\t2. Find user\n\t\t3. Add user\n\t\t4. Delete user\n\t\t5. Delete all users";
    set_color(h, 8); cout << "\n\t\t0. Go back"; set_color(h, 15); cout << "\n\n\t\tEnter: ";
    int opt;
    cin >> opt;
    switch(opt)
    {
        case 0:
          return;
        case 1:
          system("cls");
          cout << "\n" << string(38, ' ') << "All Users\n";
          cout << string(36, ' ') << "_____________\n\n";
          cout << "\t\t" << string(56, '-') << "\n";
          PrintAllUsers();
          Press_any_key();
          Operations_On_Users();
          break;
        case 2:
          system("cls");
          cout << "\n" << string(38, ' ') << "Search User\n";
          cout << string(36, ' ') << "_______________\n\n";
          cout << "\t\t" << string(56, '-') << "\n";
          cout << "\n\t\tEnter ID to find: ";
          cin >> temp.id;
          if(is_exist(temp)) print_user(getUser(temp, 1));
          else {
              set_color(h, 12);
              cout << "\n\t\tThere is no user with id = " << temp.id << " :(\a\n";
          }
          Press_any_key();
          Operations_On_Users();
          break;
        case 3:
          system("cls");
          cout << "\n" << string(38, ' ') << "Add User\n";
          cout << string(36, ' ') << "____________\n\n";
          cout << "\t\t" << string(56, '-') << "\n";
          Add_User();
          Press_any_key();
          Operations_On_Users();
          break;
        case 4:
          cout << "\n\t\tEnter ID to delete: ";
          cin >> temp.id;
          set_color(h, 12);
          if(is_exist(temp)){
              set_color(h, 6);
              cout << "\n\t\tYou are about to delete this user account... Are you sure?! (Y|N) : ";
              char conf; cin >> conf;
              set_color(h, 10);
              if(tolower(conf) == 'y'){
                  deleteUser(temp);
                  set_color(h, 10);
                  cout << "\n\t\tUser has been deleted successfully...\n";
              }
              else cout << "\n\t\tOperation cancelled successfully...\n";
          }
          else cout << "\n\t\tThere is no user with id: " << temp.id << " :(\a\n";
          Press_any_key();
          Operations_On_Users();
          break;
        case 5:
          set_color(h, 6);
          cout << "\n\t\tYou are about to delete all users... Are you sure?! (Y|N) : ";
          char conf; cin >> conf;
          set_color(h, 10);
          if(tolower(conf) == 'y'){
              deleteAllUsers();
              cout << "\n\t\tAll users have been deleted successfully...\n";
          }
          else cout << "\n\t\tOperation cancelled successfully...\n";
          Press_any_key();
          Operations_On_Users();
          break;
        default:
          set_color(h, 12);
          cout << "\t\tInvalid option\n";
          Press_any_key();
          Operations_On_Users();
    }
}
 
void add_admin(){
    ofstream fout("admins.txt", ios::out | ios::app);
    Admin a;
    cout << "\n\t\tEnter admin name: ";
    cin >> a.name;
    cout << "\t\tEnter admin age: ";
    cin >> a.age;
    g:
    cout << "\t\tEnter admin gender(M/F): ";
    cin >> a.gender;
    a.gender = tolower(a.gender);
    if(a.gender != 'f' && a.gender != 'm'){
        goto g;
    }
    p:
    set_color(h, 15);
    char pass[8];
    cout << "\t\tEnter admin password [4 charctars]: ";
    set_password(pass, 4);
    if(length(pass) != 4){
        set_color(h, 12);
        cout << "\n\t\tPassword must contain <4 charcters>\n\n";
        goto p;
    }
    c:
    set_color(h, 15);
    cout << "\t\tConfirm password: ";
    char confirm[8];
    set_password(confirm, 4);
    if(!strcmp(pass, confirm)){
        strcpy(a.password, pass);
        a.id = create_admin_id();
        set_color(h, 10);
        cout << "\n\t\tAdmin account has been created successfully...\n";
        set_color(h, 2);
        cout << "\t\tHis ID is: " << a.id << "\n";
    }
    else {
        set_color(h, 12);
        cout << "\n\t\tconfirm password doesn't match!\n\n";
        goto c;
    }
    fout.write((char*)&a, sizeof(a));
    fout.close();
}

void print_admin(Admin a, int n = 0){
    int col = (a.resignation ? 12 : 9);
    set_color(h, col);
	string g = (a.gender == 'm' ? "Mr. " : "Mrs. ");
    cout << "\t\t\t____________";
    cout << "Admin #" << n;      //Admin #1
    cout << string(16, '_');
    cout << "\n\t\t\t|" << setw(36) << "|\n";
    cout << "\t\t\t|Name: "             << setw(10) << "| " << g << a.name  << setw(20 - (length(a.name) + sz(g))) << "|\n"
         << "\t\t\t|----------------------------------|\n"
		 << "\t\t\t|ID: "               << setw(12) << "| " << a.id         << setw(16) << "|\n"
         << "\t\t\t|----------------------------------|\n"
         << "\t\t\t|Age: "      << setw(11)  << "| " << a.age << setw(20 - sz(to_string(a.age))) << "|\n"
         << "\t\t\t|----------------------------------|\n"
         << "\t\t\t|Password: "          << setw(6)  << "| " << a.password  << setw(16) << "|\n"
         << "\t\t\t|__________________________________|\n\n";
}

void PrintAllAdmins(){
    ifstream in;
    Admin a;
	int n = 1;
    set_color(h, 12);
    in.open("admins.txt", ios::in);
    if(in.is_open())
    {
       in.read((char*)&a, sizeof(a));
       while(!in.eof()){
	      print_admin(a, n++);
          in.read((char*)&a, sizeof(a)); 
       }
    }
    else cout << "\n\t\tCan't open the specifeid file :(\a\n";
    in.close();
}

void Operations_On_Admins(){
    system("cls");
    cout << "\n" << string(40, ' ') << "Explore Admins\n";
    cout << string(38, ' ') << string(18, '_') << "\n\n";
    cout << "\t\t" << string(56, '-') << "\n";
    cout << "\n\t\t1. Show all admins\n\t\t2. Find admin\n\t\t3. Add admin\n\t\t4. Delete admin\n\t\t5. Delete all admins\n\t\t6. Resignation requests";
    set_color(h, 8); cout << "\n\t\t0. Go back"; set_color(h, 15); cout << "\n\n\t\tEnter: ";
    ll opt, id; cin >> opt;
    switch(opt)
    {
        case 0:
          return;
        case 1:
          system("cls");
          cout << "\n" << string(38, ' ') << "All Admins\n";
          cout << string(36, ' ') << "______________\n\n";
          cout << "\t\t" << string(56, '-') << "\n";
          PrintAllAdmins();
          Press_any_key();
          Operations_On_Admins();
          break;
        case 2:
          system("cls");
          cout << "\n" << string(38, ' ') << "Search Admin\n";
          cout << string(36, ' ') << "________________\n\n";
          cout << "\t\t" << string(56, '-') << "\n";
          cout << "\n\t\tEnter ID of admin: ";
          cin >> id;
          if(A_is_exist(id)) print_admin(getAdmin(id));
          else {
              set_color(h, 12);
              cout << "\n\t\tThere is no admin with id = " << id << " :(\a\n";
          }
          Press_any_key();
          Operations_On_Admins();
          break;
        case 3:
          system("cls");
          cout << "\n" << string(38, ' ') << "Add Admin\n";
          cout << string(36, ' ') << "_____________\n\n";
          cout << "\t\t" << string(56, '-') << "\n";
          add_admin();
          Press_any_key();
          Operations_On_Admins();
          break;
        case 4:
          cout << "\n\t\tEnter ID of admin to delete: ";
          cin >> id;
          set_color(h, 12);
          if(A_is_exist(id)){
            set_color(h, 6);
            cout << "\n\t\tYou are about to delete this admin... Are you sure?! (Y|N) : ";
            char conf; cin >> conf;
            set_color(h, 10);
            if(tolower(conf) == 'y'){
                delete_Admin(id);
                cout << "\n\t\tAdmin has been deleted successfully...\n";
            }
            else cout << "\n\t\tOperation cancelled successfully...\n";
          }
          else cout << "\n\t\tThere is no admin with ID = " << id << " :(\a\n";
          Press_any_key();
          Operations_On_Admins();
          break;
        case 5:
          set_color(h, 6);
          cout << "\n\t\tYou are about to delete all admins... Are you sure?! (Y|N) : ";
          char conf; cin >> conf;
          set_color(h, 10);
          if(tolower(conf) == 'y'){
              DeleteAllAdmins();
              cout << "\n\t\tAll Admins have been deleted successfully...\n";
          }
          else cout << "\n\t\tOperation cancelled successfully...\n";
          Press_any_key();
          Operations_On_Admins();
          break;
        case 6:
          Resignation_Requests(0);
          Operations_On_Admins();
          break;
        default:
          set_color(h, 12);
          cout << "\n\t\tInvalid option...\a\n";
          Press_any_key();
          Operations_On_Admins();
    }
}

void system_loged_in(){
    system("cls");
    set_color(h, 15);
    cout << "\n";
    cout << string(40, ' ') << "SYSTEM\n";
    cout << string(38, ' ') << "__________\n\n";
    int opt;
    cout << "\n\t\t[1] Admins\n\t\t[2] Users\n\t\t[3] Change password";
    set_color(h, 8);
    cout << "\n\n\t\t[0] Return to main menu";
    set_color(h, 15);
    cout << "\n\n\t\tEnter: ";
    cin >> opt;
    if(opt == 0) return;
    else if(opt == 1){
        Operations_On_Admins();
        system_loged_in();
    }
    else if(opt == 2){
        Operations_On_Users();
        system_loged_in();
    }
    else if(opt == 3){
        Change_System_Password();
        Press_any_key();
        system_loged_in();
    }
    else {
        set_color(h, 12);
        cout << "\n\t\tWrong choice...\a\n";
        Press_any_key();
        system_loged_in();
    }
}

void system_mode(){
    ll cntPass = 1;
	s:
    set_color(h, 8);
	cout << "\n\t\tEnter password: ";
  	char pass[20];
  	set_password(pass, 20);
	if(!strcmp(pass, get_curr_pass())){
		system_loged_in();
        return;
	}
	else {
        set_color(h, 12);
		cout << "\n\t\tIncorrect password :(\a\n";
		if(cntPass++ == 3){
            cout << "\n\t\tLogin failed.. Access denyed :(\a\n";
            goto end;
        }
		goto s;
	}
    end:
    Press_any_key();
}
