# Highway Simulation 
A simulation for the "Attiki Odos" Highway, implemented for the class ***"Object Oriented Programming"***

## "Attiki Odos" Highway description

Attiki Odos has one starting, one final and several intermediate interchanges. On the starting interchange vehicles can only enter the highway; on the final one they can only exit the highway; whereas on the intermediate ones vehicles can both enter and exit the highway.  

Attiki Odos is consisted of *NSegs* segments among its interchanges. There are *NSegs + 1* interchanges in total, starting from interchange *#0* (initial) to interchange *#NSegs* (final). Every highway segment has a specific vehicle capacity which can be different from each other. 

For each interchange, except for the final one, there is a number of tolls for vehicles in order to enter the highway segment, that starts from the particular interchange. The number of tolls can be different for each interchange. In every interchange there are both normal and e-tolls (e-pass).

In a particular highway state there is a number of vehicles moving in every highway segment. Some of them are in a "ready to exit the segment" state. Those that have as their destination, their current segment's exit interchange, will exit the highway at its next state. Those that have as their destination, a next interchange exit, will move to the next highway segment at its next state. The rest of the vehicles, that are not in a "ready to exit the segment" state, will remain at the same highway segment at its next state. There is also a number of vehicles waiting to enter a highway segment from the segment's entrance tolls. In every segment toll a different number of vehicles might wait to enter the segment. From all vehicles that will be in a highway segment at the new state, a *Percent* of those will then go over to a "ready to exit the segment" state.

To create the new highway state, the simulation works from its end to the start. The vehicles that have as their destination the final interchange will exit the highway. Then, the vehicles that are in "ready to move between segments" state will move from the previous to the next highway segment, as long as the next highway segment's capacity is not surpassed. If it is not possible for all of them to move to the next segment, only a number of them will do it in order not to surpass the segment's capacity. After this, if there is still available space (capacity is not surpassed) maximum *K* new vehicles will enter the highway segment from normal tolls and maximum *2K* new vehicles from e-tolls. However, the segment's capacity should still not be surpassed. This means that it is possible, only a percent of vehicles (same for every toll) to enter the segment at a particular highway state. If less than maximum vehicles were able to enter, *K* will be reduced by 1 for the particular interchange at the next highway state. If the maximum number of vehicles were able to enter the segment (*3K* in total), then *K* will be increased by 1 for the particular interchange at the next highway state.

The initial highway state is randomly generated. 

In every simulation circle, the number of vehicles waiting to enter the highway, from a toll, is randomly selected. 

## Output

The simulation proceeds from the final to the starting segment. In a particular highway segment state:

- If the number of vehicles, entering a segment from its interchange, is less than the number of vehicles waiting to enter from it, then ***"Delays on entrance of interchange 'Interchange ID' "*** is printed.

- Additionally, if the number of vehicles, moving between the segments connecting a interchange, is less than the number of those that are in "a ready to move" state, then ***"Delays after interchange 'Interchange ID' "*** is also printed. 

- Otherwise, ***"Keep a safe distance in the segment after interchange 'Interchange ID' "*** is printed.

## Input 

Highway segments' capacities are read from the standard input.

The following are passed as command line arguments:

- ***N***: Number of simulation circles
- ***NSegs***: Number of highway segments
- ***K***: Maximum number of vehicles that can enter a highway segment from a normal toll. Initially, *K* is the same for all tolls (*2K* for e-tolls).
- ***Percent***: The percent of vehicles in a segment (same for all segments) that go over to "ready to exit the segment" state, on the next highway state.


## Tools Used
- **C++** with the Standard Template Library (**STL**)
- **makefile** for separate and easy compilation

## How to run

```
make (to compile)
./highway_sim <NSegs> <K> <N> <Percent>
make clean (to delete all .o files)
```