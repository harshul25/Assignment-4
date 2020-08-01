# Assignment-4
This is the last Assignment for CP386

Project Title: Assignment #4

Motivation: We have tried to implement Banker's Algorithm to avoid deadlock with multiple instances of a resource type. 

Installation: We used Xcode and VScode editors to type out our programs. However, we ran and tested it using an Ubuntu terminal on our virtual machine. 

Note: Please ensure to include the .txt file (named 'sample4_in.txt') provided in the repository. 

Screenshots:

Individual Contribution:
Jiachun was responsible for creating modules which could read the text file, read user inputs from the terminal and check for the safe state, by simply checking the inputs entered by the user. 

Harshul was responsible for creating functions which found the safe state using banker's algorithm and also making the thread function. 

Features:

- Use banker's algorithm to avoid deadlock

-Checks if the given requests are safe to execute.

-Also shows the available resources after the execution of a thread. 

Tests: 

The number of customers is: 3 
Maximum Resources:
7 5 3 
3 2 2 
9 0 2 
2 2 2 
4 3 3 
Available Resources:
3 3 2 
Enter a Command: RQ0010
Request Completed!
Enter a Command: RQ1200
Request Completed!
Enter a Command: RQ2302
Request Completed!
Enter a Command: RQ3211
Request Completed!
Enter a Command: RQ4002
Request Completed!
Enter a Command: *
Allocated Resources:
0 1 0 
2 0 0 
3 0 2 
2 1 1 
0 0 2 
Maximum Resources:
7 5 3 
3 2 2 
9 0 2 
2 2 2 
4 3 3 
Needed Resources:
7 4 3 
1 2 2 
6 0 0 
0 1 1 
4 3 1 
Available Resources:
3 3 2 
Enter a Command: Run
--> Customer 1 :
	 Allocated Resources: 2 0 0 
	 Needed Resources: 1 2 2 
	 Availible Resources: 3 3 2 
	 New Thread with ID 1 is started.
	 Thread with ID 1 is finished.
	 Thread is releasing resources...
	 New Availible Resources: 5 3 2 
--> Customer 3 :
	 Allocated Resources: 2 1 1 
	 Needed Resources: 0 1 1 
	 Availible Resources: 5 3 2 
	 New Thread with ID 3 is started.
	 Thread with ID 3 is finished.
	 Thread is releasing resources...
	 New Availible Resources: 7 4 3 
--> Customer 4 :
	 Allocated Resources: 0 0 2 
	 Needed Resources: 4 3 1 
	 Availible Resources: 7 4 3 
	 New Thread with ID 4 is started.
	 Thread with ID 4 is finished.
	 Thread is releasing resources...
	 New Availible Resources: 7 4 5 
--> Customer 0 :
	 Allocated Resources: 0 1 0 
	 Needed Resources: 7 4 3 
	 Availible Resources: 7 4 5 
	 New Thread with ID 0 is started.
	 Thread with ID 0 is finished.
	 Thread is releasing resources...
	 New Availible Resources: 7 5 5 
--> Customer 2 :
	 Allocated Resources: 3 0 2 
	 Needed Resources: 6 0 0 
	 Availible Resources: 7 5 5 
	 New Thread with ID 2 is started.
	 Thread with ID 2 is finished.
	 Thread is releasing resources...
	 New Availible Resources: 10 5 7 

Enter Command: Exit

Code Example:

Authors: Jiachun Xiang & Harshul Mehta 

Credits:
We would like to give credits to our textbook:
Operating System Concepts”, 10th Edition; Abraham Silberschatz, Peter B.  Galvin, Greg Gagne; 2018; John Wiley and Sons.

We also took some inspiration from the website GeekforGeeks:
https://www.geeksforgeeks.org/bankers-algorithm-in-operating-system-2/

Finally, we would like to thank Dr Sukhjit Singh Sehra for teaching about banker's algorithm and many essential concepts about multi-threading which helped us complete the assignment. 

License: MIT License
