# iDo

A simple todo list program wrote in C to manage easily your tasks on different projects.  
⚠️ Development in progress...

## 📒 Manual

### Use

1. Compile with `$ make main`
2. Execute with `$ ./build/ido`
3. Clean object files with `$ make clean`
4. (Clean object files and executable with `$ make mrproper`)

### Commands

⚠️ *For now, tasks.csv file must be in the current folder you are working on.*  
Current working commands are :  

* `$ ido`                             : Show application details
* `$ ido <id>`                        : Same as find command
* `$ ido help/h`                      : Print help
* `$ ido ls`                          : Print tasks
* `$ ido la`                          : Print tasks prettier
* `$ ido find/f <id>`                 : Print the task which correspond to id
* `$ ido tick/t <id>`                 : Complete the task which correspond to id
* `$ ido ntick/nt <id>`               : Uncomplete the task which correspond to id
* `$ ido rm <id>`                     : Remove a task definitely
* `$ ido edit/e <id> <flag> <value>`  : Edit a task, editable flags are below 
    * -text OR -t -> task's text (max 200 characters, must not include ';')
    * -priority OR -p -> task's priority
    * -end OR -e -> task's deadline date

## 📋 Todo for now

* Add task
* Refacto commands interface
* Find task(s) with filter
* Sort tasks with filter when printing
* Initialize a project

## 🙏 Acknowledgements

Special thanks to the best C teacher [@aranega](https://github.com/aranega) 🧞‍♂️

## ⚖️ MIT License
