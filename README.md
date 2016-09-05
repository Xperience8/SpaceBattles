# SpaceBattles
Windows, Unreal Engine, Solo project

Space Battles is a shooter game, where player is controlling spaceship. There are planets, which should be freed. Around every planet are space stations which must be destroyed to free the planet, but space stations are protected with barrier, which makes them invulnerable, but they are spawning spaceships, which are trying to destroy player. When player destroys all of them, the barrier around space station will be gone and he can finally destroy space station. Player can shoot projectiles, which make small damage, but their are unlimited. He can shoot rockets, which make big damage and automatically hit target, but they are limited. Player can boost spaceship to higher speed, but only for a limited time. When enemy spaceship is destroyed, it will drop pickup(restore HP, restore rockets, temporary barrier).

AI

When spaceships are chasing player, they don't use pathfinding, because in the space, there are not predefined paths. They are moving directly toward player. This philosophy makes a lot of problems, because spaceships didn't see planets or space stations(which are static), but they didn't see each other too. They destroy each other without player. Because of that I've created a custom dynamic avoidance collision system. It has two versions. The first version is avoidance with static objects, which is using raycasting from high distance(I've wanted smooth avoiding). If spaceship finds static obstacle, it will compute the quickest path around it. The second version is avoidance with dynamic objects. It will use direction of every spaceship, which is nearby and computes new free direction.