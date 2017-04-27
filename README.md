# Universe
It's just a little university project that turned out to be quite fun thing.  
The project is simple simulation of animals and plants moving, multiplying and fighting with other species.
As you can see in [instructions pdf](instr.pdf) (unfortunately polish only :/) it had to be a turn-based console app, 
but I made it real-time and graphic (organisms are represented by sprites). It's coded in my own OpenGL-based graphic library [FHL](https://github.com/Crisspl/FHL).
My OpenGL knowledge is rather poor, so don't expect much efficiency :D (also the game itself isn't well-optimized - maybe I will fix it later).  
Even though it's mainly just a simulation, you can interact with it by moving a Human.  
  
A few assumptions on which the game works:  
* There are 50 random organisms (full list of organisms can be found in pdf) spawned on start
* Animals are moving towards nearest organism with equal velocity, but if the nearest is organism of the same type,
then it'll be chosen only if it's "able to multiply" (prolific?). However there are some exceptions from this rule mentioned below
  * Fox never moves towards organism stronger than him
  * CyberSheep (I'm not the one who made up this name :| however I'm really sorry) firstly moves towards SosnowskiBorches (probably misspelled)
  * Antelope moves 2 times faster than others
  * Turtle moves 4 times slower than others
* Fights:
  * When two sprites collides, the fight begins (if they are not not same type)
  * Stronger wins. If they're equally strong, wins the one which attacked
  * Plant gets killed always - no matter if attacker animal dies or not
  * Which one is the attacker is determined by initiative. If their initiatives are equal, the attacker is older organisms
    * animal vs plant: animal always is the attacker
  * Turtle blocks all organisms with strength <5
  * Antelope has 50% chance to avoid fight with stronger organisms (jump off some little distance)
  * SosnowskiBorch can be eaten only by CyberSheep
  * WolfBerries has 99 strength, however it can be eaten on same rules as others (doesn't kill everything absolutely)
  * Guarana when eaten, gives the eater +3 strength (without time limit)
* Multiplying:
  * Animals are multiplying when two of the same type collides
  * For animals there's 5s cooldown after multiplying to be "abe to multiply" again
  * Plants are multiplying (or rather trying to) independently every 5s with 50% chance - i.e. it doesn't need second plant
    * Sowthistle tries to multiply ever (5./3)s, but has only 20% chance
  * Organism's age is:
    * For plants: (age of "parent") + 1
    * For animals: age of one of its parent (randomly - I mean it isn't really handled in code which parent) + 1
  * Child is spawned 100 units (pixels?) form parent(s) in random direction
## Keys:
**Arrows** - move Human  
**WSAD** - move background camera  
**Mouse** - rotate background camera  
**Q** - make Human commit suicide (in case you just want to watch the simulation :D)  
**P** - activate Human superpower (+10 strength and decreasing every second, then 5s cooldown)  
**R** - restart simulation  
**X** - hide (and pause) simulation  
  
---
  
![](/img/img.png?raw=true)