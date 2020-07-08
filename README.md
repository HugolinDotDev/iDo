# Todoit

A simple todo list program to manage easily your tasks on different projects.
⚠️ Development in progress...

## 📒 Manual

### Use

1. Compile with `$ make main`
2. Execute with `$ ./build/todoit`
3. Clean object files with `$ make clean`
4. (Clean object files and executable with `$ make mrproper`)

### Commands

⚠️ *tasks.csv file must be in the current folder you are working on.*  
Current working commands are :  

* `$ todoit h`                         : Print help
* `$ todoit ls`                        : Print tasks
* `$ todoit la`                        : Print tasks prettier
* `$ todoit find <id>`                 : Print the task which correspond to id
* `$ todoit tick <id>`                 : Complete the task which correspond to id
* `$ todoit ntick <id>`                : Uncomplete the task which correspond to id
* `$ todoit rm <id>`                   : Remove a task definitely
* `$ todoit edit <id> <field> <value>` : Edit a task, editable fields are below 
    * priority/p -> task's priority
    * end/e -> task's deadline date

## 📋 Todo for now

* Add task
* Find task(s) with filter
* Sort tasks with filter when printing
* Edit task's text

## 🙏 Acknowledgements

Special thanks to the best C teacher [@aranega](https://github.com/aranega) 🧞‍♂️

## ⚖️ MIT License
