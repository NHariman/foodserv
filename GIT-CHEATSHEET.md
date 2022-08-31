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

### Only merge a specific file with main:

```bash
We can simply give git checkout the name of the feature branch1 and the paths to the specific files that we want to add to our master branch.

$ git branch
* master
  twitter_integration

$ git checkout twitter_integration app/models/avatar.rb db/migrate/20090223104419_create_avatars.rb test/unit/models/avatar_test.rb test/functional/models/avatar_test.rb

$ git status
# On branch master
# Changes to be committed:
#   (use "git reset HEAD <file>..." to unstage)
#
#	new file:   app/models/avatar.rb
#	new file:   db/migrate/20090223104419_create_avatars.rb
#	new file:   test/functional/models/avatar_test.rb
#	new file:   test/unit/models/avatar_test.rb

$ git commit -m "'Merge' avatar code from 'twitter_integration' branch"
[master]: created 4d3e37b: "'Merge' avatar code from 'twitter_integration' branch"
4 files changed, 72 insertions(+), 0 deletions(-)
create mode 100644 app/models/avatar.rb
create mode 100644 db/migrate/20090223104419_create_avatars.rb
create mode 100644 test/functional/models/avatar_test.rb
create mode 100644 test/unit/models/avatar_test.rb
```
