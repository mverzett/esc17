---
title: School exercise environment
layout: main
---

The goal of this step is for you to get confident with the ESC working
environment and check that everything is correctly set up for the
school exercises.

If something doesn't work as expected, please ask one of the
organizers.

When using these computing resources you agree to comply with the [INFN
computing rules](http://www.ac.infn.it/accesso_risorse_informatiche/en_regulations.pdf).

## Wi-Fi access

Make sure you are using the INFN-Captive WiFi or eduroam networks and
not the CEUB WiFi network. Only the INFN-Captive or eduroam networks
will allow to connect to the ESC computers.

## SSH access to school computers

You have been assigned a personal account, with a username of the form
studentNM, where NM is a number between 01 and 30. In the following,
when you see studentNM, replace it with your personal account. You
should also have received the corresponding password.

Similarly you have been assigned a computer, named esc-XY, where XY is
a number between 01 and 60. In the following, when you see esc-XY,
replace it with the name of the host assigned to you.

Another machine, named urania, is available for the exercises
involving the use of GPUs. urania is shared among all the students.

To log on esc-XY and urania you have to first log into a gateway
server, named esc-gw.pd.infn.it, with the username and password of
studentNM.

	[me@mylaptop ~]$ ssh -X studentNM@esc-gw.pd.infn.it
	studentNM@esc-gw.pd.infn.it's password: 
	Last login: ...
	[studentNM@esc-gw ~]$ 

The `-X` option forwards the X11 display.

From esc-gw you can log into esc-XY and urania in a password-less way,
thanks to an SSH key already generated for you and available in the
`.ssh` directory (files `id_rsa` and `id_rsa.pub`).

	[studentNM@esc-gw ~]$ ssh esc-XY
	Last login: ...
	
	                 Welcome to ESC16
	
	 Exercises Material: http://infn-esc.github.io/esc16
	[studentNM@esc-XY ~]$ 

If you want you can do it in one step.

    [me@mylaptop ~]$ ssh -tX studentNM@esc-gw.pd.infn.it ssh esc-XY
	studentNM@esc-gw.pd.infn.it's password: 
	Last login: ...
	
	                 Welcome to ESC16
	
	 Exercises Material: http://infn-esc.github.io/esc16
	[studentNM@esc-XY ~]$ 

Similarly for urania.

Your shell is [`bash`](http://www.gnu.org/s/bash).

Your home directory is shared between esc-gw, esc-XY and urania, but
please use esc-gw exclusively as a bridge to log into esc-XY and
urania.

<div class="alert alert-danger" role="alert">
<strong>IMPORTANT NOTE:</strong> The student computers will be uninstalled on Friday
evening and all data on them will be destroyed. Please make sure you make
a copy of everything valuable by the end of the Friday session!
</div>

## School material

All the school material is included in a git repository. Get it using:

    [studentNM@esc-XY ~]$ git clone https://github.com/infn-esc/esc16.git

## Testing the environment

1. Log into esc-XY.

2. Check the following commands and the respective outputs.

		[studentNM@esc-XY ~]$ c++ -dumpversion
		6.2.0
		[studentNM@esc-XY ~]$ valgrind --version
		valgrind-3.10.0
		[studentNM@esc-XY ~]$ igprof -h
		igprof [options] program [options]
		
		Options to igprof:
		-h, --help                  	this help message
		...
		[studentNM@esc-XY ~]$ which igprof-navigator
		/usr/bin/igprof-navigator

3. Create a web area where you will put output from some exercises:

		[studentNM@esc-XY ~]$ mkdir -p ~/public_html/cgi-bin/data
		[studentNM@esc-XY ~]$ cp $(which igprof-navigator) ~/public_html/cgi-bin/igprof-navigator.py
		[studentNM@esc-XY ~]$ echo "<html><body><a href='cgi-bin/igprof-navigator.py'>My igprof reports</a></body></html>" > ~/public_html/index.html
		[studentNM@esc-XY ~]$ chmod 755 ~/public_html/cgi-bin

4. View `http://esc-gw.pd.infn.it:61100/~studentNM/` in your web browser; you
   should see the basic page you created above. Click on the link to
   profiles, it should produce some output -- for now it will in fact
   display an error message due to lack of profiles.

## Editing source code

### Editing locally

On esc-XY you can find several editors available, such as vim, emacs,
gedit, nano. If the X display is available, graphical editors
will open a window on your laptop; the network latency however may not
be good enough to give you a fine experience.

### Editing remotely

Alternatively you could edit the source code for the exercises on your
laptop, synchronizing the files with the ESC machines. Some options
are presented below.

First of all you should simplify your use of SSH to connect to ESC
resources.

If you run Linux, you could for example copy the SSH credentials
available on esc-gw onto your laptop and configure SSH to use them
when logging into esc-gw.

	[me@mylaptop ~]$ mkdir esc_ssh
	[me@mylaptop ~]$ scp studentNM@esc-gw.pd.infn.it:.ssh/id_rsa esc_ssh
	[me@mylaptop ~]$ scp studentNM@esc-gw.pd.infn.it:.ssh/id_rsa.pub esc_ssh
	[me@mylaptop ~]$ chmod 600 esc_ssh/id_rsa
	[me@mylaptop ~]$ cat >> .ssh/config <<EOF
	> 
	> Host esc-gw
	> HostName esc-gw.pd.infn.it
	> User studentNM
	> IdentityFile ~/esc_ssh/id_rsa
	> ForwardX11 yes
	> EOF
	[me@mylaptop ~]$ ssh esc-gw
	Last login: ...
	[studentNM@esc-gw ~]$ 

### Using scp

You can copy files remotely using scp, in both directions.

	[me@mylaptop ~]$ scp exercise.cc @esc-gw:
	[me@mylaptop ~]$ scp @esc-gw:exercise2.cc .

### Using sshfs

You can mount your ESC home directory on your laptop via sshfs.

	[me@mylaptop ~]$ mkdir esc_workspace
	[me@mylaptop ~]$ sshfs esc-gw: esc_workspace
	[me@mylaptop ~]$ vi esc_workspace/exercise.cc
	[me@mylaptop ~]$ ssh esc-gw ls
	exercise.cc

To unmount use `fusermount -u ~/esc_workspace`.

### Using rsync

You can synchronize your local workspace with the one you keep on the
ESC system using [rsync](http://rsync.samba.org/). The synchronization
can work in both directions, so you can use it for example to save all
your work on your laptop at the end of the week.

To synchronize the remote workspace on the ESC system with your
locally-modified one you can do:

	[me@mylaptop ~]$ mkdir esc_workspace
	[me@mylaptop ~]$ vi esc_workspace/exercise.cc
	[me@mylaptop ~]$ rsync -av -e ssh esc_workspace esc-gw:
	[me@mylaptop ~]$ ssh esc-gw ls esc_workspace/exercise.cc
	esc_workspace/exercise.cc

Similarly, if you make modifications to the remote ESC workspace you
can synchronize your local one:

    [me@mylaptop ~]$ rsync -av -e ssh esc-gw:esc_workspace esc_workspace

Please refer to the rsync manual to fully understand the meaning of
the different options, so to avoid mistakes that could cause loss of
data.
