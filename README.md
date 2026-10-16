# CS310FA26
section 2 and 3 of D/S

## Lab 1.2
For this lab, I used Person as the main base class and Student and Instructor as the classes that inherit from it. This helped me understand how inheritance and polymorphism can be used to organize different types of objects while still having them share some of the same functions.

//Exceptions
I used ValidationError to catch information that should not be accepted. For example, the program checks for things like a bad email, an ID that is not positive, an empty name or office, and an invalid graduation year. I also used it when JSON data is missing information or has something invalid.

//CSV Escaping
The csv_escape function helps make sure the CSV output is formatted correctly. It checks for things like commas, quotation marks, and new lines. If those are found, it adds quotation marks around the value and handles any quotation marks already inside of it.

//Challenge Extensions
For my first challenge, I completed the Round-trip JSON Parsing challenge. I added from_json functions to Student and Instructor. This allows the program to turn an object into JSON and then use that JSON to create the object again. I also added tests to make sure it works and catches missing information.

For my second challenge, I worked on Strong Exception Safety. I made sure the program checks the data when objects are being created and when JSON is being read. If something is wrong with the data, the program throws a ValidationError instead of creating an invalid object.