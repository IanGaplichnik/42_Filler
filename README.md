# 42_Filler
https://user-images.githubusercontent.com/70972514/185442223-1ea18f2e-d4ad-463a-bdb2-34d31479caf5.mov
Filler is a project, aimed to create a player, competing with another player at a Battle Arena! <br>
The rules of the game are simple:
<ul>
  <li>Two players are given 1 square each on a rectangular map.</li>
  <li>Players take turns and place a "card" on a map.</li>
  <li>Each "card" has free squares and taken squares.</li>
  <li>Card should be placed, so that only 1 taken square of the card is overlapping with 1 taken square of players territory on the map.</li>
  <li>Taken square of the card can not overlap with the taken square of the enemy on the map.</li>
  <li>If the player can not insert any piece, the same player is out of the game, but the game continues.</li>
  <li>Player, that was able to place more pieces, wins.</li>
</ul>
Players receive their numbers, initial positions, the current state of the map, and the piece to be inserted via STDIN, and insert the piece, using 

```printf("%d %d\n");```

where ```%d``` and ```%d``` represent X and Y positions on the map, where the top left corner of the piece is placed.

## Usage

Virtual machine (aka Battle Arena) requires at least 1 player and a map, which are passed as parameters. <br>
The virtual machine, maps, and players are provided by the school and can be found in the ```resources/``` folder. <br>
For example:
```resources/filler_vm -f resources/maps/map00 -p2 ./igaplich.filler -p1 resources/players/carli.filler```

To compile ```igaplich.filler```, run ```make```. The executable will be compiled and can be used with the virtual machine.

After each turn, the new state of the map is printed to the STDOUT. At the end of the game, Virtual Machine notifies, which player has won.

## Player's algorithm

```igaplich.filler``` is an algorithm, done in C language. Depending on the state of the game, it either tracks the position of the last inserted piece by the enemy and the inserted piece is as close as possible to it, or, based on a generated heatmap, it finds the closest position to any piece of an enemy.

## Visualizer

Following the process of the game in the terminal is not very pleasant, hence I've additionally built a Python Script, to help me to visualize the state of the game. It has simple controls implemented: pause and speed controls. UI helps to visually differentiate between players with different colors, which can be easily changed. The size of the window can be changed with 1 number and the whole UI will adapt to the new size.

## Visualizer Usage

To use a visualizer, the output of the game is piped to the script.

For instance:
```resources/filler_vm -f resources/maps/map02 -p1 ./igaplich.filler -p2 resources/players/carli.filler | python3 visualizer/vis.py```

Use arrows to control speed, spacebar to pause the game, and ESC to quit.


https://user-images.githubusercontent.com/70972514/185442279-4eda70d5-2985-473d-9bc2-602debe52a37.mov
