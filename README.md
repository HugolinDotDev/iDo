# Todoit

C remake of a first year Python project.  
⚠️ Development in progress...

## 📒 How to use

### Use

1. Compile with `$ make main`
2. Execute with `$ ./build/todoit`
3. Clean object files with `$ make clean`
4. (Clean object files and executable with `$ make mrproper`)

### Commands

⚠️ *tasks.csv file must be in the current folder you are working on.*  
Current working commands are :  

* `$ todoit h`          : Print help
* `$ todoit ls`         : Print tasks
* `$ todoit la`         : Print tasks in elegant way
* `$ todoit find <id>`  : Print the task which correspond to id
* `$ todoit tick <id>`  : Complete the task which correspond to id
* `$ todoit ntick <id>` : Uncomplete the task which correspond to id

## 📋 Todo for now

* Better handle error cases
* Valid inputs
* Add task
* Find task(s) with filter
* Sort tasks with filter
* Edit task
* Remove task

## 🙏 Acknowledgements

Special thanks to the best C teacher [@aranega](https://github.com/aranega) 🧞‍♂️

## ⚖️ MIT License
