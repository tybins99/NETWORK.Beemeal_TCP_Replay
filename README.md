____
# TCP PROXY project
### Date  		: 2018/01/17
### Version		: V1.0.0
#### Protection: Beemeal Source Shadow (V1.0.0)
____

### __NAME__
ProxyTcp: simulate exchange and permits to simulate exchange disconnections.



### __SYNOPSIS__
./ProxyTcp -PortToBind <PortToBind> -ExchangeIp <ExchangeIp> -ExchangePort <ExchangePort> { OPTIONS }



### __MANDATORY PARAMETERS__
PortToBind: the port that the feedhandler should connect to (instead
            of the exchange's port).

ExchangeIp: (not mandatory in trunk mode) Ip address of the stock exchange server.

ExchangePort: (not mandatory in trunk mode) port of the stock exchange server.



### __OPTIONS__

-h | --help :  display the options and explanations

-v | --version : display the software version.

-trunk: the proxy will echo any received data back, useful to simulate the exchange when real exchange is not available.

-quiet_trunk: the proxy will behave as a trunk (see '-trunk' option) but instead of echoing all data received, it will
              trash silently all data received. Useful when one want to simulate an exchange that never answer any request
	       even though the connection succeeded.


-ConnectDelaySec <DelaySec> : wait n seconds before forwarding the connection request to the exchange


-record <file.replay> : records data coming from the exchange in the file whose name was provided.
                        Only available in proxy mode (not in trunk mode).


-replay <file.replay> : permits to replay the data sequence that occured after the login.
                        Only available in trunk mode.


-no_strict_content : during a replay, this option permits the feedhandler to send 
		      messages with the same size, but a different content (useful if the message
		      contains some date or time for example).	
		      The default behavior is to consider that the feedhandler MUST send us exactly the same	
		      data as it was recorded.	

-fsync : during a recording, force the tool to flush the replay data to disk every time
         it receives something. This option is only meaningful in '-record' mode.


-speed <SpeedChoice> : this parameter permits to replay faster. It is only meaningful in '-replay' mode.	

-ignore_checksum_error : attempt to replay the file even if the file has not a valid checksum.
		          Only meaningful in '-replay' mode 	

-skip_replay_file_analysis : the tool analyses the replay file before attempting to replay it. 
	                          If the replay file is big, then you will have to wait before replay 
                             is possible. use this option avoid this waiting.  The drawback is 
							  that you will not have a full progress indicator while replaying the file.	

-no_stop_after_replay_end : when the replay is finished, this option permits to wait for a new 
							 client connection and do the replay again with this new client without
							 having to restart the tool	
							 
### __NORMAL MODE__
In normal mode, the proxy will forward connections requests incoming from
the 'PortToBind' port to the couple <ExchangeIp, ExchangePort>
Then after connection establishment, all data will be forwarded from and
to the sock exchange and the feedhandler.

 ---------------    ------------------      /---------\ 
 |             |    |                |     /           \
 | FeedHandler | -> | Proxy (normal) | ->  |  Stock    |
 |             |    |                |     |  Exchange |
 ---------------    ------------------      -----------




### __PROXY MODE WITH RECORD__
In Record mode, all data exchanged between Feedhandler and exchanger
server are recorded to a replay file.
Notice that the login protocol does not need to be known in advance
by the proxy that will learn the protocol whatever it is.

---------------    ------------------          _________
|             | -> |                |  Save   /         \
| FeedHandler |    | Proxy (record) | ------> | Replay  |
|             | <- |                |         | File    |
---------------    ------------------         -----------




### __TRUNK MODE___
In trunk mode, the proxy will emulate an "echo stock exchange" so that
all received data will be sent back toward the initial sender, which 
permits to test in standalone using 2 instances of ProxyTcp as follows:

 ---------------    ------------------    -------------------
 |             |    |                |    |                 | -->\  
 | FeedHandler | -> | Proxy (normal) | -> | Proxy (trunk)   |     |
 |             |    |                |    | (fake exchange) | <--/
 ---------------    ------------------    -------------------




### __TRUNK MODE WITH REPLAY__
In trunk replay mode, the previously recorded file is replayed
including all the login protocol that is emulated.


---------------    ------------------          _________
|             | -> |                |   Load  /         \
| FeedHandler |    | Proxy (trunk)  | <------ | Replay  |  
|             | <- |                |         | File    |
---------------    ------------------         -----------


### __windows compilation__
You will need Visual studio (at least 2017)
	
#### __Linux compilation__
	You must define the following preprocessor parameter: _LINUX
	g++ ProxyTcpReplay.cpp -D_LINUX -o ProxyTcpReplay.exe

### __FAQ__
#### __HOW TO SIMULATE DISCONNECTIONS ?__
	you can use ctrl-C to break the connection between FH <-> PROXY and
	PROXY <-> EXCHANGE.


#### __HOW TO STOP THE PROXY ?__
	press ctrl-C more than 3 times within a time frame of 1 second.


