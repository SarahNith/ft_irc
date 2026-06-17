*This project has been created as part of the 42 curriculum by agouin, skuor* 

# FT_IRC

## Description


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
When irssi is running, you have to connect to the server with the port and the password you set at the launch of the server.
Once the connection with the server is established, Irssi will fill the PASS, NICK and USER automatically.

### Usage commands on Irssi

```bash
#Creating and/or joining a channel
/join <#channel>

#Changing your nickname
/nick <your new nickname>

#Sending a private message to someone
/msg <nickname> <your message>

#Adding, removing or updating the channel topic
/topic <new topic>
/topic -delete <#channel>

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



``` 


## Resources
https://modern.ircdocs.horse/#irc-concepts
https://www.rfc-editor.org/info/rfc1459/
https://irssi.org/



https://claude.ai/new - AI was mainly used for a better understanding of key concepts and subject requirements throughout the project.