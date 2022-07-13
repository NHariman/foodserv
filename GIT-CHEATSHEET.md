# Git cheatsheet

To begin working on anything new in the project, or changing existing things create a branch off the stable master branch. 

- View all existing branches: `git branch -a`
- Creating (and switch to) a new branch: `git checkout -b branchNameHere`
- Changing to master branch: `git checkout master`

**:exclamation:REMINDER:exclamation: ALWAYS CHECK IF YOU ARE ON YOUR WORKING BRANCH, THE * IS NEXT TO THE WORKING BRANCH: `git branch -a`**

Add commit and push new code on the branch you are working on, this will only be on this working branch NOT on the master.

Once done with changes and additions it is time to merge.
- Switch back into the master branch: `git checkout master`
- Start the merging in the master branch: `git merge -no-ff branchNameHere` (-no-ff tells git we want to retain all commit messages prior to the merge)
- Push your work: `git push`

Clean up the branch that is merged in, this is no longer needed.
- Delete a merged branch: `git branch -d branchNameHere`
