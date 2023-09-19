Atomic Threat
===============
Unreal Engine 5.1.1
===============
Gameplay:
===============
The goal is to shoot down enemy missiles by pressing LMB along the flight path of an enemy target, defend cities, score as many points as possible, go through 31 rounds, finish the game with the most points scored.

Technical Description:
===============
The main game logic is written in C++, the following classes are implemented:

-AtomicGameMode - responsible for the game session rules, the round order, determining the main player, monitors the number of rockets on the scene and in the SpawnManager.

-AtomicPawn - spawns with the player launcher, passing control from the AtomicPlayerController to the PlayerLauncherGridElement.

-AtomicPlayerController - add UMG to the player's Screen Space, initiates camera shake.

-AtomicPlayerState - keeps the earned points of the main player during one game session.

-RocketBase - the base class of the rocket, has a ProjectileMovement component, creates a Target Class at the specified coordinates and flies to it, upon reaching the target destroys itself and the Target Class.

--DefenceRocket - inherited from RocketBase, the rocket that the player launches, upon reaching the target creates a DefenseExplosion in place of the target (Sphere Trace that gets points from the targets it hits and destroys them).

--EnemyRocket - inherited from RocketBase, destroys the player's cities.

--MultiEnemyRocket - inherited from RocketBase, the spawner of EnemyRockets, when the decay time is reached begins spawning a random amount of EnemyRockets and destroys itself.

---PlaneEnemyRocket - inherited from MultiEnemyRocket, is a MultiEnemyRocket spawner, when the decay time is reached creates one MultiEnemyRocket.

-DefenceExplosion - creates a temporary SphereTrace at self world location, which disappears after the time specified in Class Defaults.

-GridBase - a grid that can create the specified number of GridElementBase Subclasses at scene, can be a platform for creating and holding any GridElement type.

-GridElementBase - the base grid element which can be used as a platform for any gameplay elements that can be managed by GridBase.

--CityGridElement - inherited from GridElementBase, a game element which is essentially the player's health amount, if destroyed can be restored by AtomicGameMode if the player has 10000 points, each subsequent city recovery will cost 10000*(Recovery Nums).

--LauncherBaseGridElement - inherited from GridElementBase, can spawn derived classes from RocketBase.

---PlayerLauncherGridElement - inherited from LauncherBaseGridElement, on begin play spawns AtomicPawn and Ammo, can launch DefenseRocket by player action, can be destroyed like CityGridElement, along with its destruction, clears the number of available missiles in Ammo, at the beginning of each round recoveries for free along with Ammo.

-SpawnManager - gets rows from the Difficulty Data Table (missiles amount, difficulty value, missiles types), based on the round number obtained from the AtomicGameMode the SpawnManager starts spawns the specified number of missiles with the difficulty value specified in the DT_Difficulty at the beginning of the each round, at first round calls the creation function of GridElements SubClasses in all GridBase Instances on scene, which references must be included in instance values of SpawnManager.
