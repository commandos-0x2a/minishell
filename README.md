# MINISHELL

### minishell in 3 steps





------------------
### pipeline controll

replace pipeline token with ``NULL`` and make pipe fds to run ``complex_command``

> #### input
> ---------
> tokens
> contain multi pipeline
> #### Examples
> ---------
> ``<< limiter1 < infile cmd1 > outfile | cmd2 | < infile2 cmd3``





-------------------
### complex command

apply redirection and prepare ``argv`` to execute a simple command
> #### input
> ---------
> tokens without pipeline but contain redirection
> #### Examples
> --------------
> - ``<< limiter1 < infile cmd > outfile ``
> - ``cmd2``
> - ``< infile2 cmd3``





-------------------
### simple command

find full path for command 
and expand arguments to run it with ``execve``

> #### input
> -----------
> argv without any pipeline or redirection
> #### Examples
> --------------
> ``cmd arg1 arg2 arg3``

