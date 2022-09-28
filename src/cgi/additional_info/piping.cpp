int fd_write[2];
    int fd_read[2];
    pid_t pid;
    char line[MAXLINE];

    if ( (pipe(fd_write) < 0) || (pipe(fd_read) < 0) )
    {
        cerr << "PIPE ERROR" << endl;
        return -2;
    }
    if ( (pid = fork()) < 0 )
    {
        cerr << "FORK ERROR" << endl;
        return -3;
    }
    else  if (pid == 0)     // CHILD PROCESS
    {
        close(fd_write[1]);
        close(fd_read[0]);

        if (fd_write[0] != STDIN_FILENO)
        {
            if (dup2(fd_write[0], STDIN_FILENO) != STDIN_FILENO)
            {
                cerr << "dup2 error to stdin" << endl;
            }
            close(fd_write[0]);
        }

        if (fd_read[1] != STDOUT_FILENO)
        {
            if (dup2(fd_read[1], STDOUT_FILENO) != STDOUT_FILENO)
            {
                cerr << "dup2 error to stdout" << endl;
            }
            close(fd_read[1]);
        }

        if ( execl("path/PROGRAM B", "PROGRAM B", (char *)0) < 0 )
        {
            cerr << "system error" << endl;
            return -4;
        }

        return 0;
    }
    else        // PARENT PROCESS
    {
        int rv;
        close(fd_write[0]);
        close(fd_read[1]);

        if ( write(fd_write[1], PROGRAM_B_INPUT, strlen(PROGRAM_B_INPUT) ) != strlen(PROGRAM_B_INPUT) )
        {
            cerr << "READ ERROR FROM PIPE" << endl;
        }

        if ( (rv = read(fd_read[0], line, MAXLINE)) < 0 )
        {
            cerr << "READ ERROR FROM PIPE" << endl;
        }
        else if (rv == 0)
        {
            cerr << "Child Closed Pipe" << endl;
            return 0;
        }

        cout << "OUTPUT of PROGRAM B is: " << line;

        return 0;
    }
    return 0;
}