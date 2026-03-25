# Carrier Pigeon

Carrier Pigeon is a terminal based read and write to-do list.

Inspired by Trello and the line "Nothing to do!" after running sudo dnf upgrade --refresh

# Current Goal:

- [ ] Create simple locally run webpage with navigation to lists
- [ ] Create Dockerfile to build and run everything with a simple command
- [x] Run CLI with a simple command

# CLI Setup
  DEV
  1. in the top level folder, make all or cd into backend and run make all
  2. cd into backend
  3. Run commands such as pigeonfly <listname> -m <task>

# Web-based Setup

- in the top level folder, make all 
- From the toplevel folder, run ./middleware/socket 
- navigate to http://localhost:3666/index.html

# Notifications (Future Implementation):

carrierpigeon will send non-clickable, removable notifications upon login/computer start.
All available to-do items due in the next 2 days (which in a future update, can be changed based on user choice with "morning")
Notification Setup:

"Your Windowsill:

-(item) -complete by (due date)

-(item) -complete by (due date)

... etc"

Windowsill is sorted based on time (earliest date first)
