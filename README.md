![Nutucoin Logo](src/qt/res/images/nutucoin_logo_horizontal.png)

"MAKE LIFE EASIER"

[![Build Status](https://api.travis-ci.com/nutucoin/NutucoinV2.svg?branch=master)](https://travis-ci.com/nutucoin/NutucoinV2?branch=master) [![GitHub version](https://badge.fury.io/gh/nutucoin%2FNutucoinV2.png)](https://badge.fury.io/gh/nutucoin%2FNutucoinV2.png) [![HitCount](http://hits.dwyl.io/nutucoin/NutucoinV2.svg)](http://hits.dwyl.io/nutucoin/NutucoinV2.svg)
<a href="https://twitter.com/intent/follow?screen_name=nutucoin"><img src="https://img.shields.io/twitter/follow/nutucoin.svg?style=social&logo=twitter" alt="follow on Twitter"></a>

[![Build history](https://buildstats.info/travisci/chart/nutucoin/NutucoinV2?branch=master)](https://travis-ci.com/nutucoin/NutucoinV2?branch=master)

[Website](http://nutucoin.com) — [Official Pool](http://nutucoin.club/) — [Block Explorer](http://explorer.nutucoin.club:3001/) — [Blog](https://www.reddit.com/r/Nutucoin) — [Forum](https://bitcointalk.org/index.php?topic=4357466.0) — [Twitter](http://twitter.com/nutucoin) — [Facebook](http://www.facebook.com/nutucoin) — [Discord](https://discord.gg/tQTDGq6)

Features
=============
Nutucoin is a blockchain solutions and services ecosystem that focuses on designing and building enterprise ready security and privacy products. Its features include ASIS/FPGA resistance, adjust difficulty every block, anti-quantum computers, segwit, HD wallet and block pruning. It runs on Bitcoin Core 0.18+ technology. The mining process is available for everyone due to its powerful algorithm X16Rv2. 

Now, the team is planning to implement "tracing" feature with IoT devices supported, called NTrace, a blockchain that will trace back the original of a product as well as all middle-men, product condition at each step before reaching end users/consumers. It can be applied in logistics, pharma supply chain, food supply chain, medical devices supply chain, manufacturing operations, etc.

## Mission and vision
<img src="https://github.com/nutucoin/NutucoinV2/blob/development/src/qt/res/images/mission_vision.png">

## Coin Specifications
### Mainnet

| Specification | Value |
|:-----------|:-----------|
| Total Blocks | `10,000,000 (around 13,477,606 NTU)` |
| Swapping Number | `4,325,000 NTU` |
| Block Size | `4MB (Max)` |
| Block Time | `150s` |
| Reward | `6 NTU, reduce 10% each year, no reduce when it reaches 0.4 NTU` |
| Dev fee | `0%` dev fee for 1st year. `10%` reward after 1st year |
| Port | `49638` |
| RPC Port | `49639` |
| Legaxy Address start with | `N` |
| p2sh-segwit address start with | `S` |
| Bech32 address start with | `BN` |
| Private key start with | `P` or `Q` |

### Testnet

| Specification | Value |
|:-----------|:-----------|
| Total Blocks | `10,000,000 (around 13,477,606 NTU)` |
| Swapping Number | `1,000 NTU` |
| Block Size | `4MB (Max)` |
| Block Time | `60s` |
| Reward | `6 NTU, reduce 10% after 10000 blocks, no reduce when it reaches 0.4 NTU` |
| Dev fee | `0%` dev fee for first `10000` blocks. `10%` reward after `10000` blocks |
| Port | `49640` |
| RPC Port | `49639` |
| Legaxy Address start with | `n` |
| p2sh-segwit address start with | `s` |
| Bech32 address start with | `TNB` |
| Private key start with | `J` |

## Running Nutucoin Wallet
### Window

a)Download Nutucoin wallet at `https://github.com/nutucoin/NutucoinV2/releases`

b)Run `nutucoin-qt.exe` as normal window application

### Linux
#### Desktop/Laptop PC

a)Download Nutucoin wallet at `https://github.com/nutucoin/NutucoinV2/releases`

b)Install all required dependencies for running nutucoin desktop wallet (This step should be executed only for the **first** time running Nutucoin wallet)
```
    wget https://raw.githubusercontent.com/nutucoin/NutucoinV2/master/building/install-dependencies.sh
    chmod a+x install-dependencies.sh
    ./install-dependencies.sh
```

c)Launch nutucoin desktop wallet
```
    ./nutucoin-qt
```

#### Ubuntu Cloud VM (remote VM)

**1) Nutucoin wallet GUI**

a) Install Desktop Environment and VNC Server
```
    sudo apt update
    sudo apt install xfce4 xfce4-goodies
    sudo apt install tightvncserver
```

To complete the VNC server’s initial configuration after installation, use the vncserver command to set up a secure password and create the initial configuration files:
```
    vncserver
```

You’ll be prompted to enter and verify a password to access your machine remotely:
```
    Output
    You will require a password to access your desktops.
    
    Password:
    Verify:
```

The password must be between six and eight characters long. Passwords more than 8 characters will be truncated automatically.

Once you verify the password, you’ll have the option to create a a view-only password. Users who log in with the view-only password will not be able to control the VNC instance with their mouse or keyboard. This is a helpful option if you want to demonstrate something to other people using your VNC server, but this isn’t required.

The process then creates the necessary default configuration files and connection information for the server:
```
    Output
    Would you like to enter a view-only password (y/n)? n
    xauth:  file /home/sammy/.Xauthority does not exist
    
    New 'X' desktop is your_hostname:1
    
    Creating default startup script /home/sammy/.vnc/xstartup
    Starting applications specified in /home/sammy/.vnc/xstartup
    Log file is /home/sammy/.vnc/your_hostname:1.log
```

Configure the VNC Server
```
    vncserver -kill :1
```

Before you modify the xstartup file, back up the original:
```
    mv ~/.vnc/xstartup ~/.vnc/xstartup.bak
```

Now create a new xstartup file and open it in your text editor:
```
    nano ~/.vnc/xstartup
```

Commands in this file are executed automatically whenever you start or restart the VNC server. We need VNC to start our desktop environment if it’s not already started. Add these commands to the file:
```
    #!/bin/bash
    xrdb $HOME/.Xresources
    startxfce4 &
```

To ensure that the VNC server will be able to use this new startup file properly, we’ll need to make it executable:
```
    sudo chmod +x ~/.vnc/xstartup
```

Restart the VNC server:
```
    vncserver
```
b) Configure VNC as a System Service

We need to set up the VNC server as a systemd service so we can start, stop, and restart it as needed, like any other service. This will also ensure that VNC starts up when your server reboots.

Create a new unit file called `/etc/systemd/system/vncserver@.service` using your favorite text editor:
```
    sudo nano /etc/systemd/system/vncserver@.service
```

Add the following lines to the file. Be sure to change the value of `User`, `Group`, `WorkingDirectory`, and the username in the value of `PIDFILE` to match your username:
```
    [Unit]
    Description=Start TightVNC server at startup
    After=syslog.target network.target
    
    [Service]
    Type=forking
    User=nutucoin
    Group=nutucoin
    WorkingDirectory=/home/nutucoin
    
    PIDFile=/home/sammy/.vnc/%H:%i.pid
    ExecStartPre=-/usr/bin/vncserver -kill :%i > /dev/null 2>&1
    ExecStart=/usr/bin/vncserver -depth 24 -geometry 1280x800 :%i
    ExecStop=/usr/bin/vncserver -kill :%i
    
   [Install]
   WantedBy=multi-user.target
```
Make the system aware of the new unit file:
```
    sudo systemctl daemon-reload
```
Enable the unit file:
```
    sudo systemctl enable vncserver@1.service
```
Stop the current instance of the VNC server if it’s still running:
```
    vncserver -kill :1
```
Start it again:
```
    sudo systemctl start vncserver@1
```
You can verify that it started correctly with this command:
```
    sudo systemctl status vncserver@1
```
If it started correctly, the output should look like this:
```
    vncserver@1.service - Start TightVNC server at startup
    Loaded: loaded (/etc/systemd/system/vncserver@.service; indirect; vendor preset: enabled)
    Active: active (running) since Mon 2019-08-29 18:13:53 UTC; 2min 14s ago
    Process: 22322 ExecStart=/usr/bin/vncserver -depth 24 -geometry 1280x800 :1 (code=exited, status=0/SUCCESS)
    Process: 22316 ExecStartPre=/usr/bin/vncserver -kill :1 > /dev/null 2>&1 (code=exited, status=0/SUCCESS)
    Main PID: 22330 (Xtightvnc)
    ...
```
c) Connect to VNC server with any VNC client software

d) Open terminal in the remote server in VNC client software

e) Download Nutucoin wallet at https://github.com/nutucoin/NutucoinV2/releases

f) Install all required dependencies for running nutucoin desktop wallet (This step should be executed only for the **first** time running Nutucoin wallet)
```
    wget https://raw.githubusercontent.com/nutucoin/NutucoinV2/master/building/install-dependencies.sh
    chmod a+x install-dependencies.sh
    ./install-dependencies.sh
```

g) Launch nutucoin desktop wallet
```
    ./nutucoin-qt
```

h) Enjoy it!!!

**2) Nutucoin wallet command**

a) Connect VM via ssh

b) Download Nutucoin wallet at https://github.com/nutucoin/NutucoinV2/releases

c) Install all required dependencies for running nutucoin desktop wallet (This step should be executed only for the **first** time running Nutucoin wallet)
```
    wget https://raw.githubusercontent.com/nutucoin/NutucoinV2/master/building/install-dependencies.sh
    chmod a+x install-dependencies.sh
    ./install-dependencies.sh
```

d) Launch nutucoin desktop wallet
```
    ./nutucoin-qt
```
### OSX

a)Install the `OS X` command line tools:
```
    xcode-select --install
```
When the popup appears, click `Install`.

If you're running macOS `Mojave 10.14`/`Xcode 10.0` or later, and want to use the depends system, you'll also need to use the following script to install the macOS system headers into `/usr/include`.

```
    open /Library/Developer/CommandLineTools/Packages/macOS_SDK_headers_for_macOS_10.14.pkg
````

Then install `Homebrew`
```
    /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

b) Download Nutucoin wallet at https://github.com/nutucoin/NutucoinV2/releases

c) Install all required dependencies for running nutucoin desktop wallet (This step should be executed only for the **first** time running Nutucoin wallet)
```
    curl https://raw.githubusercontent.com/nutucoin/NutucoinV2/master/building/mac_dependencies.sh -o mac_dependencies.sh
    chmod a+x mac_dependencies.sh
    ./mac_dependencies.sh
```

d) Launch nutucoin desktop wallet
```
    ./nutucoin-qt
```

## Building Nutucoin Wallet
### Window

a)Install `Ubuntu 18.04.3 LTS`

b)Install `git`
```
    sudo apt update
    sudo apt install git
```

c)Checkout nutucoin repository:
```
    git clone https://github.com/nutucoin/NutucoinV2.git
    sudo chmod -R a+rw NutucoinV2
    cd NutucoinV2
```

d)Build Nutucoin Wallet
```
    ./building/build_win.sh
```

e) All the binary will be located at `release` folder

### Linux

a)Checkout nutucoin repository:
```
    git clone https://github.com/nutucoin/NutucoinV2.git
    sudo chmod -R a+rw NutucoinV2
    cd NutucoinV2
```

b)Build Nutucoin Wallet
```
    ./building/build_linux.sh
```

c) All the binary will be located at `release` folder
```
    cd ./release
    ls -lah
```

Sample output:
```
total 19M
drwxr-xr-x  2 tran tran 4,0K Thg 9  1 20:40 .
drwxr-xr-x 16 tran tran 4,0K Thg 9  1 20:40 ..
-rwxr-xr-x  1 tran tran 467K Thg 9  1 20:40 nutucoin-cli
-rwxr-xr-x  1 tran tran 6,3M Thg 9  1 20:40 nutucoind
-rwxr-xr-x  1 tran tran  12M Thg 9  1 20:40 nutucoin-qt
```
### OSX

a)Checkout nutucoin repository:
```
    git clone https://github.com/nutucoin/NutucoinV2.git
    sudo chmod -R a+rw NutucoinV2
    cd NutucoinV2
```

b)Build Nutucoin Wallet
```
    ./building/build_mac.sh
```

c) All the binary will be located at `release` folder
```
    cd ./release
    ls -lah
```

Sample output:
```
total 36704
drwxr-xr-x   5 nht  staff   170B Sep  3 22:11 .
drwxr-xr-x  44 nht  staff   1.5K Sep  3 22:11 ..
-rwxr-xr-x   1 nht  staff   320K Sep  3 22:11 nutucoin-cli
-rwxr-xr-x   1 nht  staff    12M Sep  3 22:11 nutucoin-qt
-rwxr-xr-x   1 nht  staff   6.1M Sep  3 22:11 nutucoind
```

