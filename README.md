# Carrier Pigeon
Carrier Pigeon is a terminal based read and write to-do list. 

Inspired by Trello and the line "Nothing to do!" after running sudo dnf upgrade --refresh

# Functionalies:

- [ ] "pigeonfly (listname) -m (message, enquoted)" to write to a file containing to do lists. Entering a valid message should prompt user to add an optional due date
- [ ] "pigeondrop -a" should show all available lists
- [ ] "pigeondrop (listname)" should read all items from list
- [ ] "pigeondrop -ws (or windowsill)" should read all items across all lists due in the next 2 days
- [ ] "shred (listname) (task)" should complete an item with a congratulatory message. Optionally, 
- [ ] "pigeonpet (listname)" should open a TUI for editing a list with more options all at once (shred, fly, drop, and duedate editing)
- [ ] "morning" should allow users to view notification settings



# Notifications:

  carrierpigeon should send non-clickable, removable notifications upon login/computer start. 
  All available to-do items due in the next 2 days (which in a future update, can be changed based on user choice with "morning")

Notification Setup:

"Your Windowsill:

 -(item) -complete by (due date)

 -(item) -complete by (due date)

 ... etc"

Windowsill is sorted based on time (earliest date first)








