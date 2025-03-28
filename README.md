Student Cafe Registration System
Description
The Student Cafe Registration System is a C++ application for managing student registrations at a cafe. It allows users to register students, search for their information, and display all registered students, utilizing file handling for efficient data storage.

Features
1. Student Class
Attributes: ID, Name, Registration Time.
Methods:
getId(): Retrieves the student's ID.
getName(): Retrieves the student's name.
getRegistrationTime(): Returns the registration time.
getFormattedRegistrationTime(): Converts registration time to a readable format.
2. CafeRegistration Class
File Operations: Opens cafe_registration.txt in append mode.
Methods:
registerStudent(): Registers a new student.
storeStudentToFile(): Writes a student's info to file.
searchStudentByID(): Finds a student by ID.
getAllStudents(): Retrieves all registered students.
generateAllStudentsTable(): Displays a table of student IDs and registration times.
3. Main Function
Entry point of the program:
Creates an instance of CafeRegistration.
Displays a menu for:
Option 1: Register a new student.
Option 2: Search for a student by ID.
Option 3: Display all registered students.
Option 4: Exit the program.
Prompts the
