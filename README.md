# Raycast

The point of this project is to try and create my very own 3d graphics engine utilizing the "Raycasting" method. I will be using the SFML library for all visuals on screen.

UPDATE:
I've finished this project! I was able to create a functional raycasting engine which draws walls properly depending on player position and perspective using the SFML graphics library. Notable things I learned:

  -Code cleanliness, my first run through it was very difficult to get a working prototype. I had messy, verbose, redundant code all over the place. When I did finally get the raycasting working, I decided to rewrite most of the program for readbility and future proofing should anyone want to add and to reinforce good coding practice. I learned the value of cleaning up your code and never accepting an algorithm just because it works. It always can be better!
  
  -Array indexing, my first few builds were erroring out at certain angles (90, 180, 270, 360) and I was getting crashes that were difficult to pinpoint. Turns out, due to the way the trig functions work, tangent was returning values close to infinity so the raycaster was checking for someting like array [122325][3] and erroring out. Learning to properly clamp any index values you want to check against an array saved me a lot of headache and stopped crashes.
  
  -Application layers, Originally I was going to create a mammoth of a main function which would do nearly everything, but I opted for dividing things up into classes wherever it made sense. Letting the camera class handle drawing rays/checking collision, having the minimap class track player position and angle as well as giving player a visual map of their location, and having an application function to handle events and call all relevant functions when needed in the core gameloop. In the end, my main function was only 13 lines of code!


With that, I'm calling this project complete. Of course there's always more you can add. Future improvements could be adding texture mapping to the walls so they're not all solid green, giving the player the ability to rock the camera up and down and not just turn side to side, or even adding walls that aren't perfect squares! There's a lot of potential here but I'm going to move onto a new project.

If you'd like to try out my raycaster, download a zip of the git, extract and navigate to release. Run Raycast.exe. Press Q to quit at any time or just end the application.

