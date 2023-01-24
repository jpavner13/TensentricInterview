# Tensentric Interview
This repository contains the code for my solution to the Tensentric Internship coding problem for a summer 2023 internship.

Id like to preface this by saying I had a lot of fun wokring through this problem. I made a few adjustments, assumptions, and improvements to the reccomended path of solving this problem based on the given information. I'm looking forward to discussing them with you on Tuesday, January 24th!

Although my solution is not nessicarily the easiest way to go about solving this problem, I wanted to use this opportunity to show off some of my skills including object oriented programming (classes, instances, etc.), data structures, algorithms, pointers, vectors, matricies, command line control and shells, array manipulation, optimization based on physical constraints, string manipulation, refrences, random testing, and abstraction. 

I wrote this program in c++ since that is the language that Tensentric generally uses. To compile the program, run:

            g++ -std=c++11 main.cpp Puck.cpp Hungarian.cpp -o run

...and to run the program, run:

            ./run

After running the program, you will be prompted with the following menu:

            ========= Menu =========
            1: Run random test
            2: Run manual test
            3: Quit
            Enter number 1-3.

To make a selection, enter an integer 1 through 3 corrisponding with your choice. Random test will create a random instance for you, while a manual test will walk you through creating an instance with your own numbers. After running a random instance, or finishing creating a manual instance, it will display the output of the function. It will be in the format of the following:

            Running random test...
            8 pucks were created.
            Initial state of pucks: 
      
The first thing it will print is the initial state and cordinates of the created pucks.

            ======================================= Puck 0 =======================================
            x Cordinate: 455
            y Cordinate: 164
            Has Worked?: 0
            =======================================================================================
                                                                          |   |     
                                                                        \       /   
                                                                         \     /    
                                                                          \   /     
                                                                           \ /      
            ======================================= Puck 1 =======================================
            x Cordinate: 476
            y Cordinate: 340
            Has Worked?: 0
            =======================================================================================
                                                                          |   |     
                                                                        \       /   
                                                                         \     /    
                                                                          \   /     
                                                                           \ /      
            ======================================= Puck 2 =======================================
            x Cordinate: 194
            y Cordinate: 477
            Has Worked?: 0
            =======================================================================================
                                                                          |   |     
                                                                        \       /   
                                                                         \     /    
                                                                          \   /     
                                                                           \ /      
            ======================================= Puck 3 =======================================
            x Cordinate: 31
            y Cordinate: 333
            Has Worked?: 0
            =======================================================================================
                                                                          |   |     
                                                                        \       /   
                                                                         \     /    
                                                                          \   /     
                                                                           \ /      
            ======================================= Puck 4 =======================================
            x Cordinate: 87
            y Cordinate: 96
            Has Worked?: 0
            =======================================================================================
                                                                          |   |     
                                                                        \       /   
                                                                         \     /    
                                                                          \   /     
                                                                           \ /      
            ======================================= Puck 5 =======================================
            x Cordinate: 42
            y Cordinate: 199
            Has Worked?: 0
            =======================================================================================
                                                                          |   |     
                                                                        \       /   
                                                                         \     /    
                                                                          \   /     
                                                                           \ /      
            ======================================= Puck 6 =======================================
            x Cordinate: 302
            y Cordinate: 107
            Has Worked?: 0
            =======================================================================================
                                                                          |   |     
                                                                        \       /   
                                                                         \     /    
                                                                          \   /     
                                                                           \ /      
            ======================================= Puck 7 =======================================
            x Cordinate: 463
            y Cordinate: 313
            Has Worked?: 0
            =======================================================================================

It will then show the distance vector. This is a 2D vector of the distance of each parking spot that should be occupied from each puck. The rows are for each puck and the columns are for each parking spot. The vector is filled with the distance between the corrisponding puck and parking spot.

            Distance Vector (in mm):
            140.431 206.206 306.791 275.465 155.824 38.4838 109.731 186.657
            68.8186 180.488 298.69  336.476 237.857 169.517 285.545 330.72
            287.063 206.313 177.553 297.33  315.349 373.209 474.305 430.262
            390.397 271.017 152.611 213.565 309.467 418.007 475.237 383.262
            390.519 294.932 224.199 125.32  228.965 343.431 334.94  216.021
            391.261 277.065 171.012 139.302 258.699 378.477 402.747 293.061
            226.214 193.01  228.327 142.172 73.0274 138.755 127.016 47.0425
            44.9222 163.518 283.298 312.695 210.376 139.778 256.628 300.962

It will then show the optimal space to move each puck to to minimize the total distance to moved by the pucks. It might not be the closest spot to each puck to optimise movement. The first number is the puck ID, and the second number is the space the puck should be moved to.

            Optimal Puck-Space movement Vector:
            0,6     1,0     2,1     3,2     4,4     5,3     6,7     7,5

It will then display the total (and minimum possible) distance moved by all of the pucks to the most optimal parking spot.

            Total movement distance: 1092.56 mm
      
It will then display the new state of the pucks with the first puck displayed being in parking spot 1, the second being in 2, etc. Any empty parking spaces will be filled with a "NULL PUCK." Notice that the pucks have been moved to their most optimal spaces by now.

            After moving puck state: 
            ======================================= Puck 1 =======================================
            x Cordinate: 420
            y Cordinate: 300
            Has Worked?: 0
            =======================================================================================
                                                                          |   |     
                                                                        \       /   
                                                                         \     /    
                                                                          \   /     
                                                                           \ /      
            ======================================= Puck 2 =======================================
            x Cordinate: 300
            y Cordinate: 300
            Has Worked?: 0
            =======================================================================================
                                                                          |   |     
                                                                        \       /   
                                                                         \     /    
                                                                          \   /     
                                                                           \ /      
            ======================================= Puck 3 =======================================
            x Cordinate: 180
            y Cordinate: 300
            Has Worked?: 0
            =======================================================================================
                                                                          |   |     
                                                                        \       /   
                                                                         \     /    
                                                                          \   /     
                                                                           \ /      
            ======================================= Puck 5 =======================================
            x Cordinate: 180
            y Cordinate: 180
            Has Worked?: 0
            =======================================================================================
                                                                          |   |     
                                                                        \       /   
                                                                         \     /    
                                                                          \   /     
                                                                           \ /      
            ======================================= Puck 4 =======================================
            x Cordinate: 300
            y Cordinate: 180
            Has Worked?: 0
            =======================================================================================
                                                                          |   |     
                                                                        \       /   
                                                                         \     /    
                                                                          \   /     
                                                                           \ /      
            ======================================= Puck 7 =======================================
            x Cordinate: 420
            y Cordinate: 180
            Has Worked?: 0
            =======================================================================================
                                                                          |   |     
                                                                        \       /   
                                                                         \     /    
                                                                          \   /     
                                                                           \ /      
            ======================================= Puck 0 =======================================
            x Cordinate: 420
            y Cordinate: 60
            Has Worked?: 0
            =======================================================================================
                                                                          |   |     
                                                                        \       /   
                                                                         \     /    
                                                                          \   /     
                                                                           \ /      
            ======================================= Puck 6 =======================================
            x Cordinate: 300
            y Cordinate: 60
            Has Worked?: 0
            =======================================================================================
                                                                          |   |     
                                                                        \       /   
                                                                         \     /    
                                                                          \   /     
                                                                           \ /      
            ======================================= NULL PUCK =======================================
            x Cordinate: 180
            y Cordinate: 60
            Has Worked?: NULL
            =======================================================================================

It will then display the proccess of preforming "work()" on each puck and moving them through the parking spaces. 

            Moving and preforming Work:
            Puck 1 -----> Puck 2 -----> Puck 3 -----> Puck 5 -----> Puck 4 -----> Puck 7 -----> Puck 0 -----> Puck 6 -----> NULL -----> 


            Working on Puck 1:
            Puck 1 -----> Puck 2 -----> Puck 3 -----> Puck 5 -----> Puck 4 -----> Puck 7 -----> Puck 0 -----> Puck 6 -----> NULL -----> 
            Puck 1 has worked.
            Puck 2 -----> Puck 3 -----> Puck 5 -----> Puck 4 -----> Puck 7 -----> Puck 0 -----> Puck 6 -----> NULL -----> Puck 1 -----> 
            Closing gaps:
            Puck 2 -----> Puck 3 -----> Puck 5 -----> Puck 4 -----> Puck 7 -----> Puck 0 -----> Puck 6 -----> Puck 1 -----> NULL -----> 


            Working on Puck 2:
            Puck 2 -----> Puck 3 -----> Puck 5 -----> Puck 4 -----> Puck 7 -----> Puck 0 -----> Puck 6 -----> Puck 1 -----> NULL -----> 
            Puck 2 has worked.
            Puck 3 -----> Puck 5 -----> Puck 4 -----> Puck 7 -----> Puck 0 -----> Puck 6 -----> Puck 1 -----> NULL -----> Puck 2 -----> 
            Closing gaps:
            Puck 3 -----> Puck 5 -----> Puck 4 -----> Puck 7 -----> Puck 0 -----> Puck 6 -----> Puck 1 -----> Puck 2 -----> NULL -----> 


            Working on Puck 3:
            Puck 3 -----> Puck 5 -----> Puck 4 -----> Puck 7 -----> Puck 0 -----> Puck 6 -----> Puck 1 -----> Puck 2 -----> NULL -----> 
            Puck 3 has worked.
            Puck 5 -----> Puck 4 -----> Puck 7 -----> Puck 0 -----> Puck 6 -----> Puck 1 -----> Puck 2 -----> NULL -----> Puck 3 -----> 
            Closing gaps:
            Puck 5 -----> Puck 4 -----> Puck 7 -----> Puck 0 -----> Puck 6 -----> Puck 1 -----> Puck 2 -----> Puck 3 -----> NULL -----> 


            Working on Puck 5:
            Puck 5 -----> Puck 4 -----> Puck 7 -----> Puck 0 -----> Puck 6 -----> Puck 1 -----> Puck 2 -----> Puck 3 -----> NULL -----> 
            Puck 5 has worked.
            Puck 4 -----> Puck 7 -----> Puck 0 -----> Puck 6 -----> Puck 1 -----> Puck 2 -----> Puck 3 -----> NULL -----> Puck 5 -----> 
            Closing gaps:
            Puck 4 -----> Puck 7 -----> Puck 0 -----> Puck 6 -----> Puck 1 -----> Puck 2 -----> Puck 3 -----> Puck 5 -----> NULL -----> 


            Working on Puck 4:
            Puck 4 -----> Puck 7 -----> Puck 0 -----> Puck 6 -----> Puck 1 -----> Puck 2 -----> Puck 3 -----> Puck 5 -----> NULL -----> 
            Puck 4 has worked.
            Puck 7 -----> Puck 0 -----> Puck 6 -----> Puck 1 -----> Puck 2 -----> Puck 3 -----> Puck 5 -----> NULL -----> Puck 4 -----> 
            Closing gaps:
            Puck 7 -----> Puck 0 -----> Puck 6 -----> Puck 1 -----> Puck 2 -----> Puck 3 -----> Puck 5 -----> Puck 4 -----> NULL -----> 


            Working on Puck 7:
            Puck 7 -----> Puck 0 -----> Puck 6 -----> Puck 1 -----> Puck 2 -----> Puck 3 -----> Puck 5 -----> Puck 4 -----> NULL -----> 
            Puck 7 has worked.
            Puck 0 -----> Puck 6 -----> Puck 1 -----> Puck 2 -----> Puck 3 -----> Puck 5 -----> Puck 4 -----> NULL -----> Puck 7 -----> 
            Closing gaps:
            Puck 0 -----> Puck 6 -----> Puck 1 -----> Puck 2 -----> Puck 3 -----> Puck 5 -----> Puck 4 -----> Puck 7 -----> NULL -----> 


            Working on Puck 0:
            Puck 0 -----> Puck 6 -----> Puck 1 -----> Puck 2 -----> Puck 3 -----> Puck 5 -----> Puck 4 -----> Puck 7 -----> NULL -----> 
            Puck 0 has worked.
            Puck 6 -----> Puck 1 -----> Puck 2 -----> Puck 3 -----> Puck 5 -----> Puck 4 -----> Puck 7 -----> NULL -----> Puck 0 -----> 
            Closing gaps:
            Puck 6 -----> Puck 1 -----> Puck 2 -----> Puck 3 -----> Puck 5 -----> Puck 4 -----> Puck 7 -----> Puck 0 -----> NULL -----> 


            Working on Puck 6:
            Puck 6 -----> Puck 1 -----> Puck 2 -----> Puck 3 -----> Puck 5 -----> Puck 4 -----> Puck 7 -----> Puck 0 -----> NULL -----> 
            Puck 6 has worked.
            Puck 1 -----> Puck 2 -----> Puck 3 -----> Puck 5 -----> Puck 4 -----> Puck 7 -----> Puck 0 -----> NULL -----> Puck 6 -----> 
            Closing gaps:
            Puck 1 -----> Puck 2 -----> Puck 3 -----> Puck 5 -----> Puck 4 -----> Puck 7 -----> Puck 0 -----> Puck 6 -----> NULL -----> 

And finally, it will display the ordered list of all the pucks and their information in the order of the parking spaces that they occupy. "Has Worked?:" will be '1' if the puck has been "worked" on.

            Final Arrangement:
            ======================================= Puck 1 =======================================
            x Cordinate: 420
            y Cordinate: 300
            Has Worked?: 1
            =======================================================================================
                                                                          |   |     
                                                                        \       /   
                                                                         \     /    
                                                                          \   /     
                                                                           \ /      
            ======================================= Puck 2 =======================================
            x Cordinate: 300
            y Cordinate: 300
            Has Worked?: 1
            =======================================================================================
                                                                          |   |     
                                                                        \       /   
                                                                         \     /    
                                                                          \   /     
                                                                           \ /      
            ======================================= Puck 3 =======================================
            x Cordinate: 180
            y Cordinate: 300
            Has Worked?: 1
            =======================================================================================
                                                                          |   |     
                                                                        \       /   
                                                                         \     /    
                                                                          \   /     
                                                                           \ /      
            ======================================= Puck 5 =======================================
            x Cordinate: 180
            y Cordinate: 180
            Has Worked?: 1
            =======================================================================================
                                                                          |   |     
                                                                        \       /   
                                                                         \     /    
                                                                          \   /     
                                                                           \ /      
            ======================================= Puck 4 =======================================
            x Cordinate: 300
            y Cordinate: 180
            Has Worked?: 1
            =======================================================================================
                                                                          |   |     
                                                                        \       /   
                                                                         \     /    
                                                                          \   /     
                                                                           \ /      
            ======================================= Puck 7 =======================================
            x Cordinate: 420
            y Cordinate: 180
            Has Worked?: 1
            =======================================================================================
                                                                          |   |     
                                                                        \       /   
                                                                         \     /    
                                                                          \   /     
                                                                           \ /      
            ======================================= Puck 0 =======================================
            x Cordinate: 420
            y Cordinate: 60
            Has Worked?: 1
            =======================================================================================
                                                                          |   |     
                                                                        \       /   
                                                                         \     /    
                                                                          \   /     
                                                                           \ /      
            ======================================= Puck 6 =======================================
            x Cordinate: 300
            y Cordinate: 60
            Has Worked?: 1
            =======================================================================================
                                                                          |   |     
                                                                        \       /   
                                                                         \     /    
                                                                          \   /     
                                                                           \ /      
            ======================================= NULL PUCK =======================================
            x Cordinate: 180
            y Cordinate: 60
            Has Worked?: NULL
            =======================================================================================


            Process Complete.
      
It will then bring you back to the menu and allow you to run more tests.
