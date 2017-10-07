## Computer Graphics Project 1

### Git Basics
---
#### Branching
1. Make a Branch
  * The branch should have a meaning full name.
  * From the command line
  ```bash
  git checkout -b new-branch
  ```
2. Push branch after creation
  * Once created you need to push your local branch to remote.
  ```bash
  git push -u origin new-branch
  ```
3. After working on the branch localy once ready push all changes to remote.
  * Never commit anything to master
  ```
  git add .
  git commit
  ```
  * Push changes
  ```
  git push
  ```
4. After pushing all changes to remote create a pull request.
