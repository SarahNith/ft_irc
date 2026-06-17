*This project has been created as part of the 42 curriculum by agouin, skuor* 

# FT_IRC

## Description
ft_irc is an implementation of an IRC (Internet Relay Chat) server, written in C++98. The goal of this project is to understand and reproduce, at a low level, how a real-time text communication protocol actually works: handling multiple concurrent client connections, parsing and validating raw IRC messages, and managing channels and user permissions.

The server supports client authentication via password, nickname/username registration, joining and leaving channels, sending and receiving both private and channel messages, and the full set of channel operator commands — KICK, INVITE, TOPIC, and MODE (invite-only, topic restriction, channel key, user limit, and operator privilege).

## Instructions

1. ```bash
	make
	``` 
	For compilation

2. ```bash
	./ircserv <port> <password>
	``` 
	Launches the server

3. ```bash
	irssi
	``` 
Once you launch the server, you have to open a new terminal and start irssi, which is the client we will use to connect to the server.

4. ```bash
	/connect 127.0.0.1 <port> <password>
	``` 
When irssi is running, you have to connect to with the port and the password you set at the launch of the server.
Once the connection with the server is established, Irssi will fill the PASS, NICK and USER automatically.

### Usage commands on Irssi
```bash
#Creating and/or joining a channel
/join <#channel>

##Leaving all channels at once
/quote JOIN 0

#Changing your nickname
/nick <your new nickname>

#Sending a private message to someone
/msg <user> <your message>

#Adding, removing or updating the channel topic
/topic <new topic>
/topic -delete <#channel>

#Inviting someone to a channel
/invite <user> <#channel>

#Kicking someone from the channel (you have to be an operator)
/kick [<#channel>] <user> [<reason>]

#Leaving a channel
/part [<message>]

#Leaving the server
/quit [<message>]

#Changing modes:
##Adding/Removing a channel password
/mode +k <password>
/mode -k

##Adding, removing or updating the maximum user capacity of the channel
/mode +l <count>
/mode -l

##Setting/unsetting the "Invite only" mode
/mode <#channel> +i
/mode <#channel> -i

##Setting/removing the restrictions of the TOPIC command to channel operators
/mode +t
/mode -t

##Giving/taking channel operator privilege
/mode <#channel> +o <user>
/mode <#channel> -o <user>
``` 

### Bonus
#### File transfer
```bash
#Sending a file
/dcc send <user> <"path to file">

#Receiving a file
/dcc get <user> <file>
``` 

#### Bot
1. ```bash
	make bot
	``` 
Compiling bot

2. ```bash
	./bot/ircBot 127.0.0.1 <port> <password>  
	``` 
Launching the bot

## Resources
https://modern.ircdocs.horse/#irc-concepts
https://www.rfc-editor.org/info/rfc1459/
https://irssi.org/
https://claude.ai/new - AI was mainly used for a better understanding of key concepts and subject requirements throughout the project.