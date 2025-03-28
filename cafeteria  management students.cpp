
/**
 *  || cafteria management system   
 */

#include <iostream>
#include<fstream>
#include<windows.h>
#include<cstdlib>
#include <ctime>
#include <string>

using namespace std;


bool isFileExist();
void drawLogin();
void drawMenu(); 
void tickStudent();
void shiftWorker();
void changePassword();
void getCurrentWorker();
int getTotalTick();
void closeCafe();
void exitSystem();
void manageStudent();
void saveToFile();


//student class //
class Student {
	private:
		string name;
		string id;
		string department;
		bool blockedStatus;
		bool useStatus;
    public:
    	char gender;
    	Student(string name,string id,char gender,string department)
    	{
			this->name=name;
			this->id=id;
			this->gender=gender;
			this->department=department;
			this->blockedStatus=false;
			this->useStatus=false;
		}
		
		//empty constructor
		Student(){}
		
		//get student name 
		string getStudentName(){
			return this->name;
		}
		
		//get student id
		string getStudentId()
		{
			return this->id;
		}
		
	
		
		//get department 
		string getDepartment(){
			return this->department;
		}
		
		//check  if blocked 
		bool isBlocked(){
			return this->blockedStatus;
		}
		
		//check if student used cafe
		bool usedCafe(){
			return this->useStatus;
		}
		
		//block the student
		void block(){
			this->blockedStatus=true;
		}
		
		//unblock student 
		void unblock(){
			this->blockedStatus=false;
		}
		
		//tick student 
		void tickStudent(){
			this->useStatus=true;
		}
		
		//reset used cafe 
		void resetUsage()
		{
			this->useStatus=false;
		}
};



//cafeguard class 
class CafeGuard{
	private:
		string name;
		string password;
		bool currentWorker;
string idg;
    public:
	    CafeGuard(string name,string password)
	{
		this->name=name;
		this->password=password;
		this->currentWorker=false;
	}
	
	 CafeGuard(){}
	
	//get worker name 
	string getName()
	{
		return this->name;
	}
	
	//get id 
	string getPassword()
	{
		return this->password;
	}
	
	//change password for the worker 
	void changePassword(string password)
	{
		this->password=password;
	}
	string getId()
	{
	return this->idg;
	}
	
	//current worker !!!!
	bool isCurrentWorker()
	{
		return this->currentWorker;
	}
	
	//set current worker 
	void setCurrentworker()
	{
		this->currentWorker=true;
	}
	
	void resetShift()
	{
		this->currentWorker=false;
	}
	
	//check if the user is valid worker !!!!
	bool isvalidWorker(string name,string password)
	{
		if(this->name==name && this->password==password)
			return true;
		else 
			return false;
	}
	
	
};





Student* studentList;
CafeGuard* guardList;
CafeGuard currentWorker;
int currentWorkerIndex=0;
int studentsize;
int cafeGuardSize;

int totaltick;


/**
 * 
 * load users and variables
 * if there is no file created, it will create a new student,guards etc.. list 
 * else it will read from the file  ...  
 * 
 *
 */
bool isFileExist()
{
	ifstream out1;
	ifstream out2;
	
	out1.open("student file.txt",ios_base::in);
	
	out2.open("worker file.txt",ios_base::in);
	
	
	if(out1.is_open() && out2.is_open() )
	{
		out1.close();
		out2.close();
		return true;
	} else {
		return false;
	}
}

void loadUser()
{
	//if data file exist read from the file
	if(isFileExist())
	{
		//read from file! normal mode
		ifstream st;
		st.open("student file.txt");
		
		//read the size of studentlist and guardlist!!!!
		st>>studentsize;
		
		
	    //intialize array with that size 
	    studentList=new Student[studentsize];
	    
	    
		//read each student class properties! from file and 
		for(int i=0;i<studentsize;i++)
		{
			bool blockstatus;
			bool usestatus;
			string name;
			string id;
			string department;
			char gender;
			
            //read boleans 
            st>>blockstatus;
            st>>usestatus;
            
            //read name
            st.ignore();
			getline(st,name);
			
			//read id
			st>>id;
			
			//read department 
			st.ignore();
			getline(st,department);
			
			//read gender 
			st>>gender;
			
			
			//change to the class!!!
			Student student=Student(name,id,gender,department);
			(blockstatus) ? student.block() : student.unblock();
			(usestatus) ? student.tickStudent(): student.resetUsage();
			
			studentList[i]=student;	
			
			
		}
		st.close();
		
		//continue reading guards
		//write name,password ,currentWorker
		ifstream wr;
		wr.open("worker file.txt");
		
		wr>>cafeGuardSize;
		
	    //intialize array with that size 
	    
	    guardList=new CafeGuard[cafeGuardSize];
	    
		
		for(int i=0;i<cafeGuardSize;i++)
		{
			bool currentW;
			string name;
			string password;
			
			//currentW
			wr>>currentW;
			
			//get password and name 
			wr.ignore();
			getline(wr,name);
			getline(wr,password);
			
			//convert to c 
			CafeGuard guard=CafeGuard(name,password);
			(currentW) ? guard.setCurrentworker() :guard.resetShift();
			guardList[i]=guard;
		}
		
	wr.close();// close file of worker
		
		//get current worker 
		getCurrentWorker();
		//get total ticks 
		totaltick=getTotalTick();
	} else {
		// create fresh data  !
		//array of student class!
		
	Student students[]={
      Student("gammo wakuma","ru01",'m',"IT"),
      Student("lewi tadesse","ru02",'m',"IT"),
      Student("lemma dagne","ru03",'m',"IT"),
      Student("lalisa hora","ru04",'m',"IT"),
      Student("sami birhanu","ru05",'m',"IT"),
      Student("hasset mulgeta","ru06",'f',"IT"),
      Student("hawi atomsa","ru07",'f',"IT"),
      
      
      Student("bacha guta","ru08",'m',"software engineering"),
      Student("midhaksaa chala","ru09",'m',"computer science"),
      Student("gogsa abbashoma","ru10",'m',"information science"),
      Student("genet abebe","ru11",'f',"computer science"),
	   Student("daniel birhanu","ru12",'m',"cs")
    };
    
    //continue workers  
    CafeGuard guards[]={
      CafeGuard("hambisaa","123456"),
      CafeGuard("lataa ","1234"),
      CafeGuard("firaol","123"),
      CafeGuard("Guuttatsa ","gutata123"),
      CafeGuard("habtamu","12")};
		
		
		
		//set the current worker
		
		guards[0].setCurrentworker();
		currentWorker=guards[0];
		
		//calculate the length of the array
		studentsize=sizeof(students)/sizeof(students[0]);
		cafeGuardSize=sizeof(guards)/sizeof(guards[0]);
		
		
			studentList=new Student[studentsize];
		for(int i=0;i<studentsize;i++)
		{
			studentList[i]=students[i];
		}
		
		guardList=new CafeGuard[cafeGuardSize];
		for(int i=0;i<cafeGuardSize;i++)
		{
			guardList[i]=guards[i];
		}
		
		totaltick=0;
		
		//save to the file!!!!
		saveToFile();
		
	}
	
}


void timess() {
    string mealTime;
    
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int currentHour = ltm->tm_hour;
    int currentMinute = ltm->tm_min;
    int currentSecond = ltm->tm_sec;

    if (currentHour >= 7 && currentHour < 12) {
        mealTime = "morning breakfast";
    } else if (currentHour >= 12 && currentHour < 15) {
        mealTime = "lunch";
    } else if (currentHour >= 18 && currentHour < 21) {
        mealTime = "dinner";
    }

    cout << "Current Time: " << currentHour << ":" << currentMinute << ":" << currentSecond <<endl;
    cout << "Meal Time: " << mealTime <<endl;
}

/**
 * get the current worker !!!!
 **/
void getCurrentWorker()
{
	for(int i=0;i<cafeGuardSize;i++)
	{
		CafeGuard worker=guardList[i];
		if(worker.isCurrentWorker())
		{
			currentWorker=worker;
			currentWorkerIndex=i;
		    break;
		}
		
	}
	
}


/**
 * find a worker index  by name and password from the worker list.
 *   -1 return 
 */
int findWorker(string username,string password)
{
	
	for(int i=0;i<cafeGuardSize;i++)
	{
		if(guardList[i].isvalidWorker(username,password))
			return i;
	}
	
	return -1;
}



/**
 * change current worker to the next 
 * 
 */
void shiftWorker()
{
	//reset current worker guard and make current worker nex guard !
	guardList[currentWorkerIndex].resetShift();
	currentWorkerIndex=(currentWorkerIndex+1)%cafeGuardSize;
    guardList[currentWorkerIndex].setCurrentworker();
    currentWorker= guardList[currentWorkerIndex];
    
}


void clearScreen()
{	system("cls");
    cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
	cout<<"%%%%%%  CAFTERIA MANAGEMENT SYSTEM ,ACTIVE USER |"<<currentWorker.getName()<<"| 2024 Jimma!"<<endl;
	cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl<<endl;    
}

/**
 * LOGIN BANNER
 */
void showLoginBanner()
{
	system("cls");
    cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
	cout<<"%%%%%%  WELCOME TO CAFTERIA MANAGEMENT SYSTEM"<<endl;
	cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl<<endl;   
}


/**
 * wait for the keypress 
 */
void waitforKey()
{
	//wai for key press !
    int input;
    cin>>input;
}

/***
 * input options 
 * take inpput from users and return the result 
 */
int inputOption()
{
	int input;
	cin>>input;
	return input;
}


/**
 * save to the file.
 * used on close , on exit and onTick completed & load user!!!!
 * file mode is opened in text format and truncated. 
 */
void saveToFile()
{
	ofstream file;
	//open the file in normal mode and truncate the content 
	file.open("student file.txt",ios::out | ios::trunc);
	if(!file.is_open())
	{
		cout<<"something went wrong while opening the file....!press any number to continue! "<<endl;
		waitforKey();
	} else {
		
		/**Write data to the file!
		 * open in normal mode!
		 * write size of student and worker in first  and second  position using normal mode 	 
		 */
		file<<"student size :"<<studentsize<<endl;
		//file<<cafeGuardSize<<endl;
		//write each student data one by one, 
		for(int i=0;i<studentsize;i++)
		{
			//write block status,use status, name,id,department, and gender 
			file<<"the blocked student:"<<studentList[i].isBlocked()<<endl;
			file<<"the used cafe student :"<<studentList[i].usedCafe()<<endl;
			file<<"the student name :"<<i+1<<"."<<studentList[i].getStudentName()<<endl;
			file<<"student id :"<<studentList[i].getStudentId()<<endl;
			file<<"student departement :"<<studentList[i].getDepartment()<<endl;
			file<<"student gender :"<<studentList[i].gender<<endl;

		}
		file.close();
	}
		ofstream file1;
	//open the file in normal mode and truncate the content 
	file1.open(" worker fil''e.txt",ios::out | ios::trunc);
	if(!file1.is_open())
	{
		cout<<"something went wrong while opening the file....!press any number to continue! "<<endl;
		waitforKey();
	} else {
		file1<<"size of worker :"<<cafeGuardSize<<endl;
		//write each worker data
		for(int i=0;i<cafeGuardSize;i++)
		{
			//write currentWorker,name,password 
			file1<<"current worker :"<<guardList[i].isCurrentWorker()<<endl;
			file1<<"worker name :"<<guardList[i].getName()<<endl;
			file1<<"worker password :"<<guardList[i].getPassword()<<endl;
		}
		
		file1.close();
		
	}
}


/**
 * draw menu 
 * 
 */
void drawMenu()
{
 int option=0;
 while(option!=5)
 {
 clearScreen();
 cout<<">>>>>>>>> please select the correct option"<<endl<<endl;
 cout<<"1.TICK STUDENT\n2.BLOCK || UNBLOCK STUDENT\n3.CLOSE CAFE\n4.CHANGE YOUR PASSWORD\n5.EXIT\n";
 
 option=inputOption();
 switch(option)
 {
	 case 1:
	 	tickStudent();
	 	break;
	 case 2:
	 	manageStudent();
	 	break;
	 case 3:
	 	closeCafe();
	 	break;
	 case 4:
	 	changePassword();
	 	break;
	 case 5:
	 	exitSystem();
	 	break;
	 default:
	 	cout<<"Incorrect option. press any number to continue!"<<endl;
        waitforKey();
 }
 }
	
}


/**
 * draw the login page 
 * 
 */
void drawLogin()
{
 
  showLoginBanner();
  string username;
  string password;
 cout<<"please insert your username, Inorder to Login:";	
 getline(cin,username);
 cout<<"please insert your password and press enter key:";
 getline(cin,password);
 //check 
  int worker=findWorker(username,password); 
  if(worker==-1)
  {
  	cout<<"\nIncorrect login or invalid user!"<<endl;
    return;
  } else if(currentWorker.getName()!=guardList[worker].getName())
  {
  	cout<<" \nYou'r shift is not now! please return later!"<<endl;
  } else {
	  drawMenu();
  }
  	
 
}


/**
 * get student by id ,  -1 if there is no such id !!!
 */

int getStudentById(string id)
{
	for(int i=0;i<studentsize;i++)
	{
		if(studentList[i].getStudentId()==id)
			return i;
	}
	
	return -1;
}

/**
 * get total tick, 
 * based on studentlist array  
 * 
 */
int getTotalTick()
{
	int total=0;
	for(int i=0;i<studentsize;i++)
	{
		if(studentList[i].usedCafe())
			total++;
	}
	
	return total;
}


/***
 * tickstudent 
 * function called when student tick option selected!!!!
 * 
 */
void tickStudent()
{
  string id="";
  //stop if user pressed -1 
  while(id!="-1")
  {
  	clearScreen();
	cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\n";
  	cout<<"Total Number of Student's ticked===="<<totaltick<<"/"<<studentsize<<"\n\n\n";
    cout<<(studentsize-totaltick)<<" student's left"<<"\n\n\n";
    cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\n";
    
    cout<<"please Insert correct id,  Insert {-1} to go to home:";
    cin>>id;
    if(id=="-1")
	{
		return;
	} else {
		int currentStudent=getStudentById(id);
		if(currentStudent==-1)
		{
			clearScreen();
			cout<<"There is no record with id "<<id<<" press any number to continue!"<<endl<<endl;
			waitforKey();
		}	
		else {
			//id is valid. 
			//check for digge and if id blocked 
			if(studentList[currentStudent].usedCafe() ||studentList[currentStudent].isBlocked())
			{
				
				clearScreen();
				 Beep(523,500);
				cout<<"The student is blocked or already used the cafe!"<<" press any number to continue!"<<endl<<endl;
			
				waitforKey();
			} else {
				clearScreen();
				//tick student 
				Beep(1000,200);
				studentList[currentStudent].tickStudent();
				totaltick++;
				//print student info.  
				cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\n\n";
				cout<<"Student Name: "<<studentList[currentStudent].getStudentName()<<"\n";
				cout<<"Student Department: "<<studentList[currentStudent].getDepartment()<<"\n";
				cout<<"Student Gender: "<<studentList[currentStudent].gender<<"\n";
				timess() ;
				cout<<"STUDENT IS NOW CHECKED AND ALLOWED TO ENTER!!!!"<<"\n";
				cout<<"press any number to continue"<<endl;
				waitforKey();
			}
		}
	}
	
	

	 //CHECK IF ALL STUDENT TICKED !!!
	if(totaltick>=studentsize)
	{
		clearScreen();
		cout<<"All students already used a cafe "<<totaltick<<"/"<<studentsize<<endl;
		// reset all student's status for the next 
		for(int i=0;i<studentsize;i++)
		{
			studentList[i].resetUsage();
		}
		//shift worker 
		shiftWorker();
		//save to file and exit program!!!! 
		saveToFile();
		//free resource
		delete []studentList;
		delete []guardList;
		cout<<"press any number to continue!"<<endl;
		waitforKey();
		exit(0); 	
	}
  }
  	
}


/**
 * bLOCK OR Unblock student!!!!! 
 */
void manageStudent()
{
	clearScreen();
	string command="";
	cout<<"Insert a command to continue!\n\n";
	cout<<"block <id-number>   : this command block specified id\n";
	cout<<"unblock <id-number> : this command unblock specified id\n";
	cout<<"go back             : Return to home page\n";
	string id="";
	while(command!="-1")
	{
        cin>>command>>id;
        if(command=="go" && id=="back")
        	return;
        else if(command=="block" || command=="unblock")
		{
			//process 
			int currentStudent=getStudentById(id);
			if(currentStudent==-1)
			{
				cout<<"invalid id number!"<<endl;
			} else {
				if(command=="block")
				{
					studentList[currentStudent].block();
					cout<<"student successfully blocked!"<<endl;
				} else {
					studentList[currentStudent].unblock();
					cout<<"student successfully unblocked!"<<endl;
				}				
			}
		} else {
			cout<<"invalid command please try again"<<endl;
		}
        
	}
	
}


/**
 * close the cafe !!
 * time up 
 */
 
 
 
 void viewOldPassword() {
    string id;
    cout << "Enter the cafe guard ID: ";
    getline(cin, id);

    bool found = false;
    for (int i = 0; i < cafeGuardSize; i++) {
        if (guardList[i].getId() == id) {
            cout << "Old password: " << guardList[i].getPassword() << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Cafe guard not found." << endl;
    }
}
void closeCafe()
{
	clearScreen();
	cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\n";
  	cout<<"Total Number of Student's ticked===="<<totaltick<<"/"<<studentsize<<"\n\n\n";
    cout<<(studentsize-totaltick)<<" student's left"<<"\n\n\n";
    cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\n";
 	cout<<"Cafe is closed now!!! "<<totaltick<<"/"<<studentsize<<" students used the cafe"<<endl;
	// reset all student's status for the next 
	for(int i=0;i<studentsize;i++)
	 {
	    studentList[i].resetUsage();
     }
	//shift worker 
	shiftWorker();
	//save to file and exit program!!!! 
	saveToFile();
	//free resource
	delete []studentList;
	delete []guardList;
	cout<<"press any number to continue!"<<endl;
	waitforKey();
	exit(0); 
}


/**
 * change the workers password 
 */

void changePassword()
{
	clearScreen();
	string newPass;
	string confirmPass;
	string old;
	cout<<" enter  your old password: \n";
	cin>>old;
	cout<<"please insert your new password, space not allowed:";
	cin>>newPass;
	cout<<"please confirm your new password:";
	cin>>confirmPass;
	
	if(newPass!=confirmPass)
	{
		cout<<"your new password doesn't match, please try again!\n\n";
		cout<<"press any number to continue"<<endl;
		waitforKey();
		return;
	} else {
		guardList[currentWorkerIndex].changePassword(newPass);
		cout<<"Your password is successfully modified\n\n";
		cout<<"press any number to continue"<<endl;
		waitforKey();
		
	}
}

/**
 * exit out  of the system!!!!
 * exit doesn't shift the current worker!!!!!
 */
void exitSystem(){
	//save to file and exit program!!!! 
	saveToFile();
	//free resource
    delete []studentList;
	delete []guardList; 
	exit(0);
	 
}


int main()
{
	loadUser();
	drawLogin();	
	return 0;
}

