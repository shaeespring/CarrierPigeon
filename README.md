# Carrier Pigeon
Carrier Pigeon is a terminal based read and write to-do list. 

Inspired by Trello and the line "Nothing to do!" after running sudo dnf upgrade --refresh

# Functionalies:

- [x] "pigeonfly (listname) -m (message)" to write to a file containing to do lists. Entering a valid message should prompt user to add an optional due date
- [x] "pigeondrop -a" will show all available lists
- [x] "pigeondrop (listname)" will read all items from a given list
- [ ] "pigeondrop -ws (or windowsill)" should read all items across all lists due in the next 2 days
- [x] "pigeonshred (listname)" will remove an entire list of tasks with a congratulatory message.
- [x] "pigeonshred (listname) (task)" will complete an item with a congratulatory message. 
- [ ] "pigeonpet (listname)" should open a TUI for editing a list with more options all at once (shred, fly, drop, and duedate editing)
- [ ] "morning" should allow users to view notification settings



# Notifications:

  carrierpigeon will send non-clickable, removable notifications upon login/computer start. 
  All available to-do items due in the next 2 days (which in a future update, can be changed based on user choice with "morning")
Notification Setup:

"Your Windowsill:

 -(item) -complete by (due date)

 -(item) -complete by (due date)

 ... etc"

Windowsill is sorted based on time (earliest date first)

# Setup

  To run carrierpigeon:
  1. clone the repository
  2. cd into the directory "CarrierPigeon"
  3a. running the command "make all" to make all relevant object files.
  3b. optionally running "make (command)" will make the object file for a specific command (pigeonfly, pigeonshred, or pigeondrop)
  4. to reset any commands run, and to start from new, "make allclean" will reset all object files. This will erase any lists being used.







