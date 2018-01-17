// @!@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// @!@ @ TCP PROXY project
// @!@ @
// @!@ @ NAME
// @!@ @ ====
// @!@ @ ProxyTcp: simulate exchange and permits to simulate exchange disconnections.
// @!@ @
// @!@ @
// @!@ @
// @!@ @ SYNOPSIS:
// @!@ @ =========
// @!@ @
// @!@ @ ./ProxyTcp -PortToBind <PortToBind> -ExchangeIp <ExchangeIp> -ExchangePort <ExchangePort> { OPTIONS }
// @!@ @
// @!@ @
// @!@ @
// @!@ @ MANDATORY PARAMETERS
// @!@ @ ====================
// @!@ @
// @!@ @ PortToBind: the port that the feedhandler should connect to (instead
// @!@ @             of the exchange's port).
// @!@ @
// @!@ @ ExchangeIp: (not mandatory in trunk mode) Ip address of the stock exchange server.
// @!@ @
// @!@ @ ExchangePort: (not mandatory in trunk mode) port of the stock exchange server.
// @!@ @
// @!@ @
// @!@ @
// @!@ @ OPTIONS
// @!@ @ =======
// @!@ @
// @!@ @
// @!@ @ -h | --help :  display the options and explanations
// @!@ @
// @!@ @ -v | --version : display the software version.
// @!@ @
// @!@ @ -trunk: the proxy will echo any received data back, useful to simulate the exchange when real exchange is not available.
// @!@ @
// @!@ @ -quiet_trunk: the proxy will behave as a trunk (see '-trunk' option) but instead of echoing all data received, it will
// @!@ @               trash silently all data received. Useful when one want to simulate an exchange that never answer any request
// @!@ @	       even though the connection succeeded.
// @!@ @
// @!@ @
// @!@ @ -ConnectDelaySec <DelaySec> : wait n seconds before forwarding the connection request to the exchange
// @!@ @
// @!@ @
// @!@ @ -record <file.replay> : records data coming from the exchange in the file whose name was provided.
// @!@ @                         Only available in proxy mode (not in trunk mode).
// @!@ @
// @!@ @
// @!@ @ -replay <file.replay> : permits to replay the data sequence that occured after the login.
// @!@ @                         Only available in trunk mode.
// @!@ @
// @!@ @
// @!@ @ -no_strict_content : during a replay, this option permits the feedhandler to send 
// @!@ @		      messages with the same size, but a different content (useful if the message
// @!@ @		      contains some date or time for example).	
// @!@ @		      The default behavior is to consider that the feedhandler MUST send us exactly the same	
// @!@ @		      data as it was recorded.	
// @!@ @
// @!@ @ -fsync : during a recording, force the tool to flush the replay data to disk every time
// @!@ @          it receives something. This option is only meaningful in '-record' mode.
// @!@ @
// @!@ @
// @!@ @ -speed <SpeedChoice> : this parameter permits to replay faster. It is only meaningful in '-replay' mode.	
// @!@ @
// @!@ @ -ignore_checksum_error : attempt to replay the file even if the file has not a valid checksum.
// @!@ @ 		          Only meaningful in '-replay' mode 	
// @!@ @ 
// @!@ @ -skip_replay_file_analysis : the tool analyses the replay file before attempting to replay it. 
// @!@ @ 	                          If the replay file is big, then you will have to wait before replay 
// @!@ @                              is possible. use this option avoid this waiting.  The drawback is 
// @!@ @							  that you will not have a full progress indicator while replaying the file.	
// @!@ @
// @!@ @ -no_stop_after_replay_end : when the replay is finished, this option permits to wait for a new 
// @!@ @							 client connection and do the replay again with this new client without
// @!@ @							 having to restart the tool	
// @!@ @ NORMAL MODE
// @!@ @ ===========
// @!@ @ In normal mode, the proxy will forward connections requests incoming from
// @!@ @ the 'PortToBind' port to the couple <ExchangeIp, ExchangePort>
// @!@ @ Then after connection establishment, all data will be forwarded from and
// @!@ @ to the sock exchange and the feedhandler.
// @!@ @ 
// @!@ @  ---------------    ------------------      /---------\ 
// @!@ @  |             |    |                |     /           \
// @!@ @  | FeedHandler | -> | Proxy (normal) | ->  |  Stock    |
// @!@ @  |             |    |                |     |  Exchange |
// @!@ @  ---------------    ------------------      -----------
// @!@ @ 
// @!@ @ 
// @!@ @ 
// @!@ @ 
// @!@ @ PROXY MODE WITH RECORD
// @!@ @ ======================
// @!@ @ In Record mode, all data exchanged between Feedhandler and exchanger
// @!@ @ server are recorded to a replay file.
// @!@ @ Notice that the login protocol does not need to be known in advance
// @!@ @ by the proxy that will learn the protocol whatever it is.
// @!@ @ 
// @!@ @ ---------------    ------------------          _________
// @!@ @ |             | -> |                |  Save   /         \
// @!@ @ | FeedHandler |    | Proxy (record) | ------> | Replay  |
// @!@ @ |             | <- |                |         | File    |
// @!@ @ ---------------    ------------------         -----------
// @!@ @ 
// @!@ @ 
// @!@ @ 
// @!@ @
// @!@ @ TRUNK MODE
// @!@ @ ===========
// @!@ @ In trunk mode, the proxy will emulate an "echo stock exchange" so that
// @!@ @ all received data will be sent back toward the initial sender, which 
// @!@ @ permits to test in standalone using 2 instances of ProxyTcp as follows:
// @!@ @
// @!@ @  ---------------    ------------------    -------------------
// @!@ @  |             |    |                |    |                 | -->\  
// @!@ @  | FeedHandler | -> | Proxy (normal) | -> | Proxy (trunk)   |     |
// @!@ @  |             |    |                |    | (fake exchange) | <--/
// @!@ @  ---------------    ------------------    -------------------
// @!@ @
// @!@ @
// @!@ @
// @!@ @
// @!@ @ TRUNK MODE WITH REPLAY
// @!@ @ ======================
// @!@ @ In trunk replay mode, the previously recorded file is replayed
// @!@ @ including all the login protocol that is emulated.
// @!@ @
// @!@ @
// @!@ @ ---------------    ------------------          _________
// @!@ @ |             | -> |                |   Load  /         \
// @!@ @ | FeedHandler |    | Proxy (trunk)  | <------ | Replay  |  
// @!@ @ |             | <- |                |         | File    |
// @!@ @ ---------------    ------------------         -----------
// @!@ @
// @!@ @
// @!@ @
// @!@ @
// @!@ @ FAQ
// @!@ @ ====
// @!@ @ 	HOW TO SIMULATE DISCONNECTIONS ?
// @!@ @ 	--------------------------------
// @!@ @ 	you can use ctrl-C to break the connection between FH <-> PROXY and
// @!@ @ 	PROXY <-> EXCHANGE.
// @!@ @
// @!@ @
// @!@ @ 	HOW TO STOP THE PROXY ?
// @!@ @ 	-----------------------
// @!@ @ 	press ctrl-C more than 3 times within a time frame of 1 second.
// @!@ @
// @!@ @
// @!@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#include "./argv_104.h"

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

using namespace std::literals::chrono_literals;

/////////////////////////////////////
argv_119 *	g_ProxyPtr		= nullptr;
size_t		argv_137	= 0;
/////////////////////////////////////

argv_110::argv_110() {
	;
}

void argv_110::argv_210() {
	argv_180 = std::chrono::system_clock::now();
}

void argv_110::argv_214() {
	argv_182 = std::chrono::system_clock::now();
}

uint64_t argv_110::argv_138() {
	auto DurationUsec = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - argv_180);
	return (DurationUsec.count());
}

//---------------------------------------------
void argv_121::argv_126 () {
	fprintf (stderr, "===========================\n");
	fprintf (stderr, "  TCP PROXY & REPLAY TOOL\n");
	fprintf (stderr, "  Version 0.15, containing :\n");
	fprintf (stderr, "===========================\n");
	fprintf (stderr, "    [2011_01_26] - added    - TCP proxy to simulate disconnection from the exchange\n");
	fprintf (stderr, "    [2011_03_22] - added    - Add an option to turn the trunk into a quiet server\n");
	fprintf (stderr, "    [2011_03_23] - fixed    - disconnection request not properly handled when in trunk mode\n");
	fprintf (stderr, "    [2011_04_22] - added    - TCP recorder to emulate login protocol\n");
	fprintf (stderr, "    [2011_04_22] - added    - TCP replayer to emulate login + exchange protocol\n");
	fprintf (stderr, "    [2011_04_22] - modified - avoid exiting when exchange connection is not possible\n");
	fprintf (stderr, "    [2011_04_22] - added    - Added '-fsync' option\n");
	fprintf (stderr, "    [2011_04_26] - fixed    - socket leak when exchange connection fails\n");	
	fprintf (stderr, "    [2011_04_26] - modified - replay file format modification to reduce size\n");
	fprintf (stderr, "    [2011_04_26] - added    - added '-speed' option\n");	
	fprintf (stderr, "    [2011_04_26] - added    - added the '-ignore_checksum_error' option\n");
	fprintf (stderr, "    [2011_05_18] - added    - added the '-skip_replay_file_analysis' option\n");
	fprintf (stderr, "    [2011_05_18] - added    - added the '-no_stop_after_replay_end' option\n");
	fprintf (stderr, "    [2011_06_01] - fixed    - the -ignore_checksum_error option does not behave properly when replay file size has changed\n");
	fprintf (stderr, "    [2011_06_27] - fixed    - avoid looping when a write error occurs\n");
	fprintf (stderr, "\n");
}


//  ./a.out -PortToBind <PortToBind> -ExchangeIp <ExchangeIp> -ExchangePort <ExchangePort> { -trunk }
argv_118::argv_118 () {
	argv_165            = 0;
	argv_151            = "";
	argv_152          = 0;
	argv_185             = false;
	argv_166		= false;		
	argv_170			= false;
	argv_175			= false;
	argv_164		= false;	
	argv_154				= false;
	argv_145       = 0; // no delay => forward connection toward exchange immediately        
	argv_176			= 1;
	argv_157	= false;
	argv_178= false;		
	argv_163	= false;
}

//---------------------------------------
// one parsed line 
void argv_120::Reset () {
	argv_177 = 0;
}

argv_120::argv_120 () {
	Reset ();
}

//---------------------------------------
bool argv_121::argv_115 (uint8_t * i_Buf1, uint8_t * i_Buf2, int32_t i_Size) {
	bool bret = true;
	for (int32_t i=0 ; bret && (i<i_Size) ; i++) {
		if (i_Buf1[i] != i_Buf2[i]) {
			bret = false;
		}
	}
	return (bret);
}

int32_t	argv_121::argv_116 (const char *s1, const char *s2) {
#if defined (_WIN32) || defined (_WIN64)
	return (_stricmp(s1, s2));
#elif defined (_LINUX)
	return (strcasecmp(s1, s2));
#endif // #if defined (_WIN32) || defined (_WIN64)
}

bool argv_121::argv_130(const char * i_Filename) {
	bool bret = true;
#if defined (_WIN32) || defined (_WIN64)
	if (0 == DeleteFile (i_Filename)) {
		bret = false;
		fprintf(stderr, "+++ Error: failed to erase the file '%s' (GetLastError=%d)\n", i_Filename, GetLastError());
	}
#elif defined (_LINUX)
	int32_t iret = unlink(i_Filename);
	if (iret) {
		bret = false;
		fprintf(stderr, "+++ Error: failed to erase the file '%s' (%s)\n", i_Filename, strerror(errno));
	}
#endif // #if defined (_WIN32) || defined (_WIN64)
	return (bret);
}

bool argv_121::argv_134 (SOCKET i_Sockfd) {
	bool bret = true;
	int32_t on = 1;
	if (setsockopt (i_Sockfd, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on))) {
#if defined (_WIN32) || defined (_WIN64)
		fprintf(stderr, "+++ Error: setsockopt::SO_REUSEADDR failed (GetLastError=%d)\n", GetLastError());
#elif defined (_LINUX)
		fprintf(stderr, "+++ Error: setsockopt::SO_REUSEADDR failed (%s)\n", strerror(errno));
#endif // #if defined (_WIN32) || defined (_WIN64)
		bret = false;
	}
	return (bret);
}

void argv_121::argv_124(const char * i_Msg, char * i_Buf, int32_t size, bool i_NoEol) {
	int32_t NbTodo = size;
	if (NbTodo > argv_189) {
		NbTodo = argv_189;
	}
	unsigned char * ucptr = (unsigned char *)i_Buf;
	fprintf(stderr, "%s : %d bytes -> [", i_Msg, size);
	for (int32_t i = 0; i < NbTodo; i++) {
		if ((i + 1) < NbTodo) {
			fprintf(stderr, "0x%02X,", ucptr[i]);
		}
		else {
			fprintf(stderr, "0x%02X", ucptr[i]);
		}
	}
	if (size > NbTodo) {
		fprintf(stderr, "...(%d bytes more)", size - NbTodo);
	}
	if (i_NoEol) {
		fprintf(stderr, "]");
	}
	else {
		fprintf(stderr, "]\n");
	}
}

void argv_121::argv_209(std::string const & i_line, std::string const & i_separator, std::vector<std::string> & i_vector_fields) {
	i_vector_fields.clear();
	std::string::size_type last_pos = 0;
	std::string::size_type pos;
	size_t separator_size = i_separator.size();
	while (1) {
		pos = i_line.find(i_separator, last_pos);
		std::string s = i_line.substr(last_pos, pos - last_pos);
		// if std::string is composed of spaces only, discard it
		bool OnlySpace = true;
		for (size_t i = 0; i < s.size(); i++) {
			if (!isspace(s[i])) {
				OnlySpace = false;
			}
		}
		if (!OnlySpace) {
			i_vector_fields.push_back(s);
		}
		if (pos == std::string::npos)
			break;
		last_pos = pos + separator_size;
	}
}

bool argv_121::argv_199 (SOCKET i_Sockfd, char * i_Buffer, int32_t i_NbToRead) {
	bool bret = true;
	int32_t NbRemaining = i_NbToRead;
	int32_t NbRead = 0;
	int32_t TotalNbRead = 0;	
	int32_t Flag = 0;
#if defined(_LINUX)
	Flag = MSG_NOSIGNAL;
#endif // _LINUX

	while (bret && (NbRemaining > 0)) {
		NbRead = recv (i_Sockfd, &i_Buffer[TotalNbRead], NbRemaining, Flag);
		if (NbRead < 0) {
            if (errno == EINTR) {
	            continue;
        	}
            else {
#if defined (_WIN32) || defined (_WIN64)
				fprintf(stderr, "+++ Error: read error (GetLastError=%d)\n", GetLastError());
#elif defined (_LINUX)
				fprintf(stderr, "+++ Error: read error (errno=%s)\n", strerror(errno));
#endif // #if defined (_WIN32) || defined (_WIN64)
	        	bret = false;
        	}
		}
		else if (NbRead == 0) {
			fprintf (stderr, "Connection closed by peer\n");	
			bret = false;
		}	
		else {
			NbRemaining -= NbRead;
			TotalNbRead += NbRead;
		}
	}
	return (bret);
}

bool argv_121::argv_205 (SOCKET i_Sockfd, uint8_t * i_Buffer, size_t i_NbToSend) {
	bool bret = true;
	size_t NbWritten = 0;
	size_t TotalNbDone = 0;
	size_t NbRemaining = i_NbToSend;
	int32_t Flag = 0;
#if defined(_LINUX)
	Flag = MSG_NOSIGNAL;
#endif // _LINUX
	while (bret && (NbRemaining > 0)) {
		NbWritten = send (i_Sockfd, (const char *) &i_Buffer[TotalNbDone], (int32_t) NbRemaining, Flag);
		if (NbWritten < 0) {
			if (errno == EINTR) {
				continue;
			}
			else {
#if defined (_WIN32) || defined (_WIN64)
				fprintf(stderr, "+++ Error: write error (GetLastError=%d)\n", GetLastError());
#elif defined (_LINUX)
				fprintf(stderr, "+++ Error: write error (errno=%s)\n", strerror(errno));
#endif // #if defined (_WIN32) || defined (_WIN64)
				bret = false;
			}
		}	
		else {
			NbRemaining -= NbWritten;
			TotalNbDone += NbWritten;	
		}
	}
	return (bret);
}

bool argv_121::argv_114(SOCKET i_SocketFd) {
	bool bret = true;
#if defined (_WIN32) || defined (_WIN64)
	closesocket (i_SocketFd);
#elif defined (_LINUX)
	if (close (i_SocketFd) < 0) {
		bret = false;
	}
#endif // #if defined (_WIN32) || defined (_WIN64)
	return (bret);
}

//--------------------------------------
argv_122::argv_122()
{
	argv_169 	= false;
	argv_173	= false;
	argv_155			= 0;
	argv_156		= 0;
	argv_148		= 1;
	argv_184	= 0;
	argv_160	= 0;	
}

void argv_122::argv_214 () {
	if (argv_169) {
		argv_215 ();
	}
}

bool argv_122::argv_212 (const char * i_Filename, int32_t i_Speed, bool i_IgnoreChecksumError, bool i_SkipReplayFileAnalysis)
{
	bool bret = true;
	argv_157 = i_IgnoreChecksumError;
	if (argv_169) {
		fprintf (stderr, "+++ Error: argv_122::argv_212 - illegal when record in progress !\n");
		bret = false;
	}
	if (argv_173) {
		fprintf (stderr, "+++ Error: argv_122::argv_212 - illegal when replay already in progress !\n");
		bret = false;
	}
	else {
		double ExtractedVersion;
		argv_153 = fopen (i_Filename, "rb");
		if (! argv_153) {
			fprintf (stderr, "+++ Error: failed to open replay file ! (%s)\n", i_Filename);
			bret = false;
		}
		else {
			if (i_SkipReplayFileAnalysis) {
				fprintf (stderr, "*** Warning : replay file checksum skipped (no progress bar will be displayed while replaying)\n");
			}
			else {
				bret = argv_220 ();
			}

			if (bret) {
				if ( ! argv_193 (ExtractedVersion)) {
					bret = false;
				}
				else {
					argv_179 = i_Speed;	
					argv_173 = true;
					fprintf (stderr, "Replay start at speed %d...[OK]\n", argv_179);				
					argv_160 = 0;
				}
			}
		}
	}
	return (bret);	
}	

bool argv_122::argv_220() {
	bool bret = true;
	char BufTmp[argv_109];
	long CurrentHeadPos = ftell(argv_153);
	rewind(argv_153);

	bool 	 HashLineFound = false;
	uint64_t ComputedHash = 0;
	uint64_t ComputedHashedSize = 0;
	argv_184 = 0;

	uint64_t        HashFromFile;
	uint64_t        HashedSizeFromFile;

	fprintf(stderr, "Analyzing replay file...(use the '-skip_replay_file_analysis' option to skip this step)\n");
	char * cptr = fgets(BufTmp, argv_109, argv_153);
	argv_121 ReplayHelper;
	while (cptr) {
		char * occurenceChecksumKeyword = strstr(BufTmp, "Checksum|");
		if (!occurenceChecksumKeyword) { // do not count the last line
			argv_219(BufTmp, ComputedHash, ComputedHashedSize);
#if defined (_WIN32) || defined (_WIN64)
			char * OccurenceFhToXKeyword = StrStrI (BufTmp, argv_135);
			char * OccurenceXToFhKeyword = StrStrI (BufTmp, argv_136);
#elif defined (_LINUX)
			char * OccurenceFhToXKeyword = strcasestr(BufTmp, argv_135);
			char * OccurenceXToFhKeyword = strcasestr(BufTmp, argv_136);
#endif // #if defined (_WIN32) || defined (_WIN64)
			if (OccurenceFhToXKeyword || OccurenceXToFhKeyword) {
				argv_184++;
			}
		}
		else { // retrieve the checksum saved in the replay file.
			std::vector<std::string> vTmp;
			ReplayHelper.argv_209(BufTmp, "|", vTmp);
			if (vTmp.size() != 3) {
				fprintf(stderr, "+++ Error: argv_220 - malformed checksum line\n");
				bret = false;
			}
			else {
				HashLineFound = true;
				HashFromFile = atol(vTmp[1].c_str());
				HashedSizeFromFile = atol(vTmp[2].c_str());
			}
		}
		cptr = fgets(BufTmp, argv_109, argv_153);
	}
	if (!HashLineFound) {
		if (!argv_157) {
			fprintf(stderr, "+++ Error: argv_220 - could not find hash line from replay file !\n");
			fprintf(stderr, "(try the '-ignore_checksum_error' option to force the replay and bypass this error\n");
			bret = false;
		}
		else {
			fprintf(stderr, "*** Warning: argv_220 - could not find hash line from replay file ! (Ignoring checksum error)\n");
		}
	}
	else {
		if (ComputedHash != HashFromFile) {
			if (!argv_157) {
				fprintf(stderr, "+++ Error: argv_220 - file corrupted ! (hash mismatch: expected %llu, got %llu)\n", HashFromFile, ComputedHash);
				bret = false;
			}
			else {
				fprintf(stderr, "*** Warning: argv_220 - file corrupted ! (hash mismatch: expected %llu, got %llu)\n", HashFromFile, ComputedHash);
			}
		}
		if (ComputedHashedSize != HashedSizeFromFile) {
			if (!argv_157) {
				fprintf(stderr, "+++ Error: argv_220 - file corrupted ! (size mismatch: expected %llu, got %llu)\n", HashedSizeFromFile, ComputedHashedSize);
				bret = false;
			}
			else {
				fprintf(stderr, "*** Warning: argv_220 - file corrupted ! (size mismatch: expected %llu, got %llu)\n", HashedSizeFromFile, ComputedHashedSize);
			}
		}
	}
	if (bret) {
		std::cerr << "Number of entries to replay: " << argv_184 << "\n";
		fprintf(stderr, "replay file checksum...[OK|Expected:%llu_%llu Obtained: %llu_%llu]\n", HashFromFile, HashedSizeFromFile, ComputedHash, ComputedHashedSize);
	}

	fseek(argv_153, CurrentHeadPos, SEEK_SET);
	return (bret);
}

// BEEMEAL_TCP_REPLAY|0.10
// or
// BEEMEAL_TCP_REPLAY|1.00|2011|4|28|13|27| -> Year|Month|Day|Hour|Minute|
bool argv_122::argv_193 (double& o_ProtocolVersion) {
	bool bret = true;
	char BufTmp[argv_109];
	char * cptr = fgets (BufTmp, argv_109, argv_153);
	if (! cptr ) {
		fprintf (stderr, "+++ Error: erroneous file format (magic extraction failed) ! \n");
		bret = false;
	}
	else {
		argv_148 = 1;
		std::string BufAsStr (BufTmp); 	
		std::vector<std::string> v_Fields;
		argv_121 ReplayHelper;
		ReplayHelper.argv_209 (BufAsStr, "|", v_Fields);
		if (v_Fields.size() != 2) {
			fprintf (stderr, "+++ Error: invalid number of fields for Magic line\n");
			bret = false;
		}
		else if (argv_218 != v_Fields[0]) {
			fprintf (stderr, "+++ Error: erroneous file format !\n");
			bret = false;
		}
		else {
			o_ProtocolVersion = atof(v_Fields[1].c_str());
			if (argv_197 != o_ProtocolVersion) {
				fprintf (stderr, "+++ Error: replay file version not compatible ! (Expected version: %.02lf, obtained version: %.02lf)\n", argv_197, o_ProtocolVersion);
				bret = false;
			}	
			else {
				fprintf (stderr, "Replay file version: %.02lf\n", o_ProtocolVersion);
			}
		}
	}
	return (bret);
}

bool argv_190 (char i_Nibble, uint8_t& o_Result) {
	bool bret = true;
	switch (i_Nibble) {
		case '0': o_Result = 0;		break;
		case '1': o_Result = 1;		break;
		case '2': o_Result = 2;		break;
		case '3': o_Result = 3;		break;
		case '4': o_Result = 4;		break;	
		case '5': o_Result = 5;		break;	
		case '6': o_Result = 6;		break;
		case '7': o_Result = 7;		break;
		case '8': o_Result = 8;		break;
		case '9': o_Result = 9;		break;
		case 'A': case 'a': o_Result = 10;	break;
		case 'B': case 'b': o_Result = 11;	break;
		case 'C': case 'c':  o_Result = 12;	break;
		case 'D': case 'd':  o_Result = 13;	break;
		case 'E': case 'e':  o_Result = 14;	break;
		case 'F': case 'f':  o_Result = 15;	break;

		default:
			fprintf (stderr, "+++ Error: bad nibble value ! (nibble was '%c')\n", i_Nibble);
			bret = false;
	}
	return (bret);	
}

// "FF" -> 255
bool argv_117 (const std::string& i_str, uint8_t& o_Result) {
	bool bret = true;
	if (i_str.size() != 2) {
		fprintf (stderr, "+++ Error: bad nibble ! (std::string length incorrect for '%s')\n", i_str.c_str());
		bret = false;
	}	
	else {
		uint8_t Msb, Lsb;
		bret = 	argv_190 (i_str[0], Msb);
		if (bret) {
			bret = argv_190 (i_str[1], Lsb);
			if (bret) {
				o_Result = (Msb * 16) + Lsb;
			}
		}
	}	
	return (bret);		
}	


// FH->X|12302752|5|6162630D0A
bool argv_122::argv_191 (int32_t i_LineNo, const char * i_Buffer, argv_203& o_Direction, uint64_t& o_TimestampUsec, uint32_t& o_Size, uint8_t * o_BufResult) {
	bool bret = true;
	std::string BufAsStr (i_Buffer);	
	std::vector<std::string> v_Fields;
	argv_121 ReplayHelper;
	ReplayHelper.argv_209 (BufAsStr, "|", v_Fields);
	size_t NbField = v_Fields.size();
	if (NbField  < 3) {
		fprintf (stderr, "+++ Error: while parsing line %d (invalid number of fields)\n", i_LineNo);
		bret = false;
	}
	else {
		argv_121 ReplayHelper;
		if (ReplayHelper.argv_116(v_Fields[0].c_str(), argv_135) == 0) {
			o_Direction = argv_201;
		}
		else if (ReplayHelper.argv_116(v_Fields[0].c_str(), argv_136) == 0) {
			o_Direction = argv_202;
		}
		else if (strstr (i_Buffer, "Checksum|")) {
			bret = false; // end reached
		}
		else {
			fprintf (stderr, "+++ Error: bad direction encountered while parsing line %d!\n", i_LineNo);
			fprintf (stderr, "+++ line was '%s'", i_Buffer);
			bret = false;
		}
		if (bret) {
			o_TimestampUsec = atoi (v_Fields[1].c_str());		
			o_Size		= atoi (v_Fields[2].c_str());
			// all hexa bytes are stored contiguously in a single std::string
			if ((v_Fields[3].size() %2) != 0) {
				fprintf (stderr, "+++ Error: at line %d: invalid number of nibbles on line ! (Number of nibbles=%Id)\n", i_LineNo, v_Fields[3].size());
				fprintf (stderr, "+++ line was : '%s'\n", v_Fields[3].c_str());
				bret = false;
			}
			else {
				size_t NbNibble = v_Fields[3].size();
				std::string ByteAsStr;
				uint8_t	HexValue;
				int32_t     BufferIndex = 0;
				for (size_t i=0 ; bret && (i<NbNibble) ; i += 2) {
					ByteAsStr = "";
					ByteAsStr += v_Fields[3][i];
					ByteAsStr += v_Fields[3][i+1];				

					bret = argv_117 (ByteAsStr, HexValue);
					if (bret) {
						o_BufResult[BufferIndex] = HexValue;
						BufferIndex++;
					}
				}
			}
		}
	}	
	return (bret);
}

bool argv_122::argv_140 (argv_120& o_Entry, int32_t& o_NbReplayEntryDone, int32_t& o_TotalNbReplayEntry) {
	bool bret = true;
	char tmp[argv_109];
	argv_148++;	
	char * cptr = fgets (tmp, argv_109, argv_153);
	if (! cptr) {
		fprintf (stderr, "Replay finished\n");
		bret = false;
	}
	else {
		o_Entry.Reset ();
		bret = argv_191 (argv_148, tmp, o_Entry.argv_149, o_Entry.argv_183, o_Entry.argv_177, o_Entry.argv_144);
		if (bret) {
			argv_160++;
			o_NbReplayEntryDone  = argv_160;
			o_TotalNbReplayEntry = argv_184;
		}
	}
	return (bret);
}

void argv_122::argv_216 () {
	if (argv_173) {
		fprintf (stderr, "stopping replay now\n");
		fclose (argv_153);
		argv_173 = false;
	}
}


bool argv_122::argv_211 (const char * i_Filename, bool i_FsyncModeActivated) {
	bool bret 	= true;
	argv_154 	= i_FsyncModeActivated;

        char DateSuffix[argv_207];
        time_t CurrentTime = time(0);
        struct tm * lt = localtime(&CurrentTime);
        snprintf (DateSuffix, argv_207, ".%d_%02d_%d_%dh%dm%ds", 1900 + lt->tm_year, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
        DateSuffix[argv_207 - 1] = '\0';
        argv_167 = i_Filename;
        argv_167 += DateSuffix;

	if (argv_169) {
		fprintf (stderr, "+++ Error: argv_122::argv_211 - illegal when record already in progress !\n");
		bret = false;
	}
	else if (argv_173) {
		fprintf (stderr, "+++ Error: argv_122::argv_211 - illegal when replay in progress !\n");
		bret = false;
	}
	else {
		argv_153 = fopen (argv_167.c_str(), "wb");
		if ( ! argv_153) {
			fprintf (stderr, "+++ Error: failed to open record file: %s\n", argv_167.c_str());
			bret = false;
		}
		else {
			argv_162 = 0;
			std::string sync_mode_comment;
			if (argv_154) {
				sync_mode_comment = " [FILE SYNC MODE] ";
			}
			fprintf (stderr, "record mode activated succesfuly %s (%s)\n", sync_mode_comment.c_str(), argv_167.c_str());
			argv_169 = true;
			argv_155		   = 0;
			argv_156       = 0;
			// gettimeofday (&argv_181, NULL);
			char tmp[argv_109];
			time_t CurrentTime = time(0);
			struct tm * lt = localtime(&CurrentTime);
			//snprintf (tmp, argv_109, "%s|%.02lf|%d|%d|%d|%d|%d|\n", argv_218, argv_197, 1900+lt->tm_year, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min);
			snprintf (tmp, argv_109, "%s|%.02lf|\n", argv_218, argv_197);
			tmp[argv_109 - 1] = '\0';
			fprintf (argv_153, "%s", tmp);
			argv_219 (tmp, argv_155, argv_156);
			if (argv_154) {
				fflush (argv_153);		
			}

		}
	}
	return (bret);
}

bool argv_122::argv_215() {
	bool bret = true;
	fprintf(stderr, "Stopping record (%u entries recorded)\n", argv_162);
	if (!argv_169) {
		fprintf(stderr, "+++ Error: argv_122::argv_215 - illegal when record not started !\n");
		bret = false;
	}
	else {
		//fprintf (stderr, "Checksum|%llu|%llu|\n", argv_155, argv_156);
		fprintf(argv_153, "Checksum|%llu|%llu|\n", argv_155, argv_156);
		fclose(argv_153);
		argv_169 = false;
		if (argv_162 < 6) { // login only => erase the file
			fprintf(stderr, "*** WARNING: only %u entries in file '%s' => erase it !\n", argv_162, argv_167.c_str());
			argv_121 ReplayHelper;
			if (false == ReplayHelper.argv_130(argv_167.c_str())) {
				fprintf(stderr, "+++ Error: failed to erase the file '%s' (%s)\n", argv_167.c_str(), strerror(errno));
			}
		}
	}
	return (bret);
}

inline void argv_122::argv_219 (const char * i_buffer, uint64_t& io_hash, uint64_t& io_HashedSize) {
	size_t size = strlen (i_buffer);
	for(size_t i=0 ; i<size ; i++) {
		io_hash += i_buffer[i];
	}
	io_HashedSize += size;
}

bool argv_122::argv_108(argv_203 i_direction, char * i_Buf, int32_t size)
{
	bool bret = true;
	if (!argv_169) {
		fprintf(stderr, "+++ Error: argv_122::argv_108 - illegal when record not in progress !\n");
		bret = false;
	}
	else {
		if (0 == argv_162) { // for the first entry, set the time at the first 'add' instead of at argv_211 to avoid waiting
			argv_143.argv_210();
		}
		uint64_t ElapsedUsec = argv_143.argv_138();
		argv_143.argv_210();

		std::string direction_as_str;
		if (argv_201 == i_direction) {
			direction_as_str = argv_135;
		}
		else if (argv_202 == i_direction) {
			direction_as_str = argv_136;
		}
		unsigned char * ucptr = (unsigned char *)i_Buf;
		std::stringstream ioss;
		ioss << direction_as_str << "|" << ElapsedUsec << "|" << size << "|";
		argv_219(ioss.str().c_str(), argv_155, argv_156);
		fprintf(argv_153, ioss.str().c_str());
		char tmp[argv_109];
		for (int32_t i = 0; i < size; i++) {
			snprintf(tmp, argv_109, "%02X", ucptr[i]);
			tmp[argv_109 - 1] = '\0';
			argv_219(tmp, argv_155, argv_156);
			fprintf(argv_153, "%s", tmp);
		}

		argv_219("|\n", argv_155, argv_156);
		fprintf(argv_153, "|\n");
		if (argv_154) {
			fflush(argv_153);
		}
		argv_162++;

	}
	return (bret);
}

//================================
argv_119::argv_119 () {
	argv_121 ReplayHelper;
	ReplayHelper.argv_213();
    argv_161 = 0;
}

argv_119::~argv_119() {
	argv_121 ReplayHelper;
	ReplayHelper.argv_217();
}

void argv_119::argv_141 () {
    argv_161++;
}

int32_t argv_119::argv_111 () {
        int32_t WhatToDo=argv_129;
        if (argv_161 == 1) { // close connection with client
                fprintf (stderr, "********************************************\n");
                fprintf (stderr, "****\n");
                fprintf (stderr, "****\n");
                fprintf (stderr, "****\n");
                fprintf (stderr, "****\n");
                fprintf (stderr, "****\n");
                fprintf (stderr, "**** ORDER TO CLOSE CONNECTION WITH CLIENT\n");
                fprintf (stderr, "****\n");
                fprintf (stderr, "****\n");
                fprintf (stderr, "****\n");
                fprintf (stderr, "****\n");
                fprintf (stderr, "****\n");
                fprintf (stderr, "********************************************\n");
                WhatToDo=argv_127;
        }
        else if (argv_161 > 1) {
                fprintf (stderr, "**** ORDER TO STOP");
                WhatToDo=argv_128;
        }
        return (WhatToDo);
}

bool argv_119::argv_194 (std::string IpToConnectTo, int32_t PortToConnectTo) {
        bool bret = true;
		argv_121 ReplayHelper;
        argv_147 = socket (AF_INET, SOCK_STREAM, 0); 
        if (argv_147 < 0) {
                fprintf (stderr, "+++ failed to create socket with server\n");
        }
        else {
			struct sockaddr_in servaddr;
			memset (&servaddr, 0x00, sizeof(servaddr));  
			servaddr.sin_family = AF_INET;                
			servaddr.sin_addr.s_addr = inet_addr(IpToConnectTo.c_str());  
			servaddr.sin_port = htons(PortToConnectTo);                       
			if (connect (argv_147, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {                
				fprintf (stderr, "+++ Error: failed to connect to server: %s:%d (errno=%s)\n", IpToConnectTo.c_str(), PortToConnectTo, strerror(errno));
				bret = false;                                
				if (argv_147 >= 0) { 
					ReplayHelper.argv_114 (argv_147);
					argv_147 = -1;
				}
			}
			else {
				fprintf (stderr, "Connected to %s:%d\n", IpToConnectTo.c_str(), PortToConnectTo);
			}
        }
        return (bret);
}

void argv_119::argv_214 () {
	argv_174.argv_214 ();
}

argv_118& argv_119::argv_139() {
	return (argv_150);
}

bool argv_119::argv_196 (int32_t PortToBind) {
	bool bret = true;
	fprintf (stderr, "Preparing server (port=%d)\n", PortToBind);
	struct sockaddr_in servaddr;
	argv_158 = -1;
	argv_158 = socket (AF_INET, SOCK_STREAM, 0);
	if (argv_158 < 0) {
		fprintf (stderr, "+++ Error: argv_196 - failed to create socket\n");
		bret = false;
	}
	else {
		argv_121 ReplayHelper;
		bret = ReplayHelper.argv_134 (argv_158);
		if (bret) {
			memset(&servaddr, 0, sizeof(servaddr));       
			servaddr.sin_family         = AF_INET;                  
			servaddr.sin_addr.s_addr    = htonl(INADDR_ANY);   
			servaddr.sin_port           = htons(PortToBind);       
			if ( bind(argv_158, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {                
				fprintf (stderr, "+++ Error: failed to bind port %d\n", PortToBind);
				bret = false;
			}
			else {
				if (listen (argv_158, argv_188) < 0) {                        
					fprintf (stderr, "+++ Error: listen failed\n");
					bret = false;
				}
				else {
					fprintf (stderr, "server listening on port %d\n", PortToBind);
				}
			}
		}
	}
	if ((false == bret) && (argv_158 >= 0)) {
		argv_121 ReplayHelper;
		ReplayHelper.argv_114(argv_158);
		argv_158 = -1;
	}
	return (bret);
}

bool argv_119::argv_198(SOCKET SourceFd, SOCKET DestFd) {
	bool 	bret = true;
	bool	finished = false;
	std::string			SourceName;
	argv_203	direction;
	if (SourceFd == argv_146) {
		SourceName = "Client";
		direction = argv_202;
	}
	else {
		SourceName = "Exchange";
		direction = argv_201;
	}
	std::string DestName;
	if (DestFd == argv_146) {
		DestName = "Client";
	}
	else {
		DestName = "Exchange";
	}
	if (argv_150.argv_185 || argv_150.argv_166) {
		SourceName = "Client";
		DestName = "Trunk";
	}
	fprintf(stderr, "argv_119::argv_198 - SourceName=%s, DestName=%s\n", SourceName.c_str(), DestName.c_str());
	int32_t Flag = 0;
#if defined(_LINUX)
	Flag = MSG_NOSIGNAL;
#endif // _LINUX
	while (bret && (finished == false)) {
		argv_159 = recv (SourceFd, argv_144, argv_109, Flag);
		if (argv_159 < 0) {
			if (errno == EINTR) {
				continue;
			}
			else {
				fprintf(stderr, "+++ Error: read error (errno=%s)\n", strerror(errno));
				bret = false;
			}
		}
		else if (argv_159 == 0) {
			if (SourceFd == argv_146) {
				fprintf(stderr, "+++\n");
				fprintf(stderr, "+++\n");
				fprintf(stderr, "+++\n");
				fprintf(stderr, "+++\n");
				fprintf(stderr, "+++\n");
				fprintf(stderr, "+++\n");
				fprintf(stderr, "+++\n");
				fprintf(stderr, "+++ Error: lost connection with client\n");
				fprintf(stderr, "+++\n");
				fprintf(stderr, "+++\n");
				fprintf(stderr, "+++\n");
				fprintf(stderr, "+++\n");
				fprintf(stderr, "+++\n");
				fprintf(stderr, "+++\n");
			}
			else if (SourceFd == argv_147) {
				fprintf(stderr, "+++\n");
				fprintf(stderr, "+++\n");
				fprintf(stderr, "+++\n");
				fprintf(stderr, "+++\n");
				fprintf(stderr, "+++\n");
				fprintf(stderr, "+++\n");
				fprintf(stderr, "+++ Error: lost connection with Exchange\n");
				fprintf(stderr, "+++\n");
				fprintf(stderr, "+++\n");
				fprintf(stderr, "+++\n");
				fprintf(stderr, "+++\n");
				fprintf(stderr, "+++\n");
				fprintf(stderr, "+++\n");
				fprintf(stderr, "+++\n");
			}
			bret = false;
		}
		else {
			fprintf(stderr, "%s -> PROXY (%d bytes)...", SourceName.c_str(), argv_159);
			finished = true;
			if (argv_150.argv_170) {
				bret = argv_174.argv_108(direction, argv_144, argv_159);
			}
		}
	}

	if (bret && (false == argv_150.argv_166)) {
		int32_t NbWritten;
		finished = false;
		int32_t Flag = 0;
#if defined(_LINUX)
		Flag = MSG_NOSIGNAL;
#endif // _LINUX
		while (bret && (finished == false)) {
			NbWritten = send(DestFd, argv_144, argv_159, Flag);
			if (NbWritten < 0) {
				if (errno == EINTR) {
					continue;
				}
				else {
					fprintf(stderr, "+++ Error: write error (errno=%s)\n", strerror(errno));
					bret = false;
				}
			}
			else if (NbWritten != argv_159) {
				fprintf(stderr, "+++ Error: Read %d bytes, but wrote only %d bytes\n", argv_159, NbWritten);
				bret = false;
			}
			else {
				fprintf(stderr, "PROXY -> %s (%d bytes) -> ", DestName.c_str(), argv_159);
				finished = true;
				argv_121 ReplayHelper;
				ReplayHelper.argv_124("readBuffer", argv_144, argv_159);
			}
		}
	}
	if ((argv_159 > 0) && (true == argv_150.argv_166)) {
		argv_121 ReplayHelper;
		ReplayHelper.argv_124("Trashed received data", argv_144, argv_159);
	}
	if (false == bret) {
		argv_121 ReplayHelper;
		if (argv_146 >= 0) {
			ReplayHelper.argv_114(argv_146);
			argv_146 = -1;
		}
		if (argv_147 >= 0) {
			ReplayHelper.argv_114(argv_147);
			argv_147 = -1;
		}
	}
	return (bret);
}

bool argv_119::argv_133() {
	bool bret = true;
	int32_t TotalNbReplayEntry, NbReplayEntryDone;
	char ProgressBar[argv_207];
	uint64_t SleepDurationUsec;
	bool NoMoreReplayEntry = false;
	argv_121 ReplayHelper;
	while (bret && (false == NoMoreReplayEntry)) {
		bret = argv_174.argv_140(argv_171, NbReplayEntryDone, TotalNbReplayEntry);
		if (bret) {
			if (argv_201 == argv_171.argv_149) { // read n bytes
				SleepDurationUsec = argv_171.argv_183 / argv_150.argv_176;
				snprintf(ProgressBar, argv_207, "%d on %d) Trunk replay: forwarding to FH [synchro: %llu usec]", NbReplayEntryDone, TotalNbReplayEntry, SleepDurationUsec);
				ReplayHelper.argv_124(ProgressBar, reinterpret_cast<char *>(argv_171.argv_144), argv_171.argv_177);
				//usleep (SleepDurationUsec);
				std::this_thread::sleep_for(std::chrono::microseconds(SleepDurationUsec));

				bret = ReplayHelper.argv_205(argv_146, argv_171.argv_144, argv_171.argv_177);
				if (!bret) {
					fprintf(stderr, "argv_119::argv_133 - argv_205 failed@1\n");
				}
			}
			else { // flow from feedhandler to Exchange => read and forward
				snprintf(ProgressBar, argv_207, "%d on %d) Expecting from FH", NbReplayEntryDone, TotalNbReplayEntry);
				ReplayHelper.argv_124(ProgressBar, reinterpret_cast<char *>(&argv_171.argv_144[0]), argv_171.argv_177, true);
				bret = ReplayHelper.argv_199(argv_146, argv_144, argv_171.argv_177);
				if (bret) {
					ReplayHelper.argv_124("...Received", argv_144, argv_171.argv_177, true);
					if (ReplayHelper.argv_115(&argv_171.argv_144[0], reinterpret_cast<uint8_t *>(argv_144), argv_171.argv_177)) {
						fprintf(stderr, "...[SUCCESS]\n");
					}
					else {
						if (!argv_150.argv_164) {
							fprintf(stderr, "...[FAILED: buffer content mismatch]\n");
							fprintf(stderr, "+++ Error: buffer content mismatch ! (use the '-no_strict_content' option to ignore such errors)\n");
							bret = false;
						}
						else {
							fprintf(stderr, "...[WARNING: buffer content mismatch]\n");
						}
					}
				}
				else {
					fprintf(stderr, "...[FAILED recv failed]\n");
				}
			}
			if (false == bret) {
				if (argv_146 >= 0) {
					fprintf(stderr, "+++ Error: closing connection with client now\n");
					argv_121 ReplayHelper;
					ReplayHelper.argv_114(argv_146);
					argv_146 = -1;
				}
			}
		}
		else {
			fprintf(stderr, "No more replay entry\n");
			NoMoreReplayEntry = true;
			std::this_thread::sleep_for(std::chrono::microseconds(1000000));
		}
	}
	if (bret) {
		fprintf(stderr, "trunk replay stopped normally\n");
	}
	else {
		if (!NoMoreReplayEntry) {
			fprintf(stderr, "+++ Error: trunk replay stopped on error ! (see above for details)\n");
		}
		std::this_thread::sleep_for(std::chrono::microseconds(1000000));
	}
	return (bret);
}

bool argv_119::argv_132() {
	bool bret = true;
	if (argv_150.argv_175) {
		bret = argv_133();
		if (!bret) {
			if (argv_146 >= 0) {
				argv_121 ReplayHelper;
				ReplayHelper.argv_114(argv_146);
				argv_146 = -1;
			}
		}
	}
	else {
		while (bret) {
			bret = argv_198(argv_146, argv_146);
		}
	}
	return (bret);
}

void argv_119::argv_195 () {
	FD_ZERO (&rset);
	FD_ZERO (&rset_dirty);

	FD_SET (argv_146, &rset);
	FD_SET (argv_147, &rset);
	rset_dirty = rset;

	argv_187 = argv_146;
	if (argv_147 > argv_187) {
		argv_187 = argv_147;
	}
}

bool argv_119::argv_112() {
	bool bret = true;
	int32_t WhatToDo = argv_111();
	if (argv_127 == WhatToDo) {
		argv_161 = 0;
		argv_137 = 0;
		if (argv_146 >= 0) {
			argv_121 ReplayHelper;
			ReplayHelper.argv_114(argv_146);
			argv_146 = -1;
		}
		if (argv_147 >= 0) {
			argv_121 ReplayHelper;
			ReplayHelper.argv_114(argv_147);
			argv_147 = -1;
		}
		bret = argv_221(argv_150.argv_151, argv_150.argv_152);
		if (bret) {
			argv_195();
		}
	}
	else if (argv_128 == WhatToDo) {
		fprintf(stderr, "<exiting>\n");
		exit(1);
	}
	return (bret);
}

bool argv_119::argv_131() {
	bool bret = true;
	argv_195();

	size_t NbReady;
	struct timeval ta, dirty_ta;
	ta.tv_sec = 1;
	ta.tv_usec = 0;

	while (bret) {
		rset_dirty = rset;
		dirty_ta = ta; // because linux modifies the structure's content

		NbReady = select((int32_t)argv_187 + 1, &rset_dirty, NULL, NULL, &dirty_ta);
		if (NbReady < 0) {
			if (errno == EINTR) {
				continue;
			}
			else {
				fprintf(stderr, "+++ Error: select error (%s)\n", strerror(errno));
				bret = false;
			}
		}
		else if (NbReady == 0) {
			bret = argv_112();
		}
		else { // one or more ready
			if (bret && (FD_ISSET(argv_146, &rset_dirty))) {
				bret = argv_198(argv_146, argv_147);
			}
			if (bret && (FD_ISSET(argv_147, &rset_dirty))) {
				//fprintf (stderr, "argv_147 ready to read\n");
				bret = argv_198(argv_147, argv_146);
			}
			if (bret) {
				bret = argv_112();
			}
		}
	}
	return (bret);
}

bool argv_119::argv_221(std::string IpToConnectTo, int32_t PortToConnectTo) {
	bool bret = true;
	bool ReplayStarted = false;
	if (argv_150.argv_175) {
		bret = argv_174.argv_212(argv_150.argv_172.c_str(), argv_150.argv_176, argv_150.argv_157, argv_150.argv_178);
		if (bret) {
			ReplayStarted = true;
		}
	}
	if (bret) {
		memset(&argv_113, 0x00, sizeof(argv_113));
		fprintf(stderr, "waiting for client connections\n");
		bool ReplayFinished = false;
		while ((!ReplayFinished) && bret) {
			argv_146 = accept(argv_158, nullptr, nullptr);
			if (argv_146 < 0) {
				fprintf(stderr, "+++ Error: accept failed\n");
				bret = false;
			}
			else {
				fprintf(stderr, "new connection established by client\n");
				if ((false == argv_150.argv_185) && (false == argv_150.argv_166)) {
					if (argv_150.argv_145 > 0) {
						fprintf(stderr, "waiting %d seconds before forwarding connection toward %s:%d...\n", argv_150.argv_145, IpToConnectTo.c_str(), PortToConnectTo);
						std::this_thread::sleep_for(std::chrono::seconds(argv_150.argv_145));
					}

					fprintf(stderr, "initiating connection toward Exchange\n");
					bret = argv_194(argv_150.argv_151, argv_150.argv_152);
					if (!bret) {
						fprintf(stderr, "+++ Error: failed to connect to Exchange (IpPort=%s:%d)\n", IpToConnectTo.c_str(), PortToConnectTo);
						fprintf(stderr, "+++ closing connection with client now\n");
						if (argv_146 >= 0) {
							argv_121 ReplayHelper;
							ReplayHelper.argv_114(argv_146);
							argv_146 = -1;
						}
						bret = true;
					}
					else {
						fprintf(stderr, "Connected to the Exchange\n");
						bret = argv_131();
					}
				}
				else { // loopback on itself to perform an echo
					bret = argv_132();
					if (argv_150.argv_175) {
						ReplayFinished = true;
						if (argv_150.argv_163) {
							bret = true; // attempt to restart the replay
						}
					}
				}
			}
			if (argv_150.argv_175) {
				argv_174.argv_216();
				if (argv_150.argv_163) {
					ReplayFinished = false;
					bret = argv_174.argv_212(argv_150.argv_172.c_str(), argv_150.argv_176, argv_150.argv_157, argv_150.argv_178);
				}
			}
			if (argv_150.argv_170) {
				argv_174.argv_215();
				bret = argv_174.argv_211(argv_150.argv_168.c_str(), argv_150.argv_154);
			}
		}
	}
	if (ReplayStarted && (!bret)) {
		argv_174.argv_216();
	}
	return (bret);
}

bool argv_119::argv_204() {
	bool bret = true;
	if (true == argv_150.argv_185) {
		fprintf(stderr, "*** Trunk Mode Activated\n");
	}
	if (true == argv_150.argv_166) {
		fprintf(stderr, "*** Quiet Trunk Mode Activated (All received data will be trashed and will not be mirrored)\n");
	}
	if (argv_150.argv_170) {
		bret = argv_174.argv_211(argv_150.argv_168.c_str(), argv_150.argv_154);
	}
	// wait for new client connection
	if (bret) {
		bret = argv_196(argv_150.argv_165);
		if (bret) {
			bret = argv_221(argv_150.argv_151, argv_150.argv_152);
		}
	}
	return (bret);
}

#if defined (_WIN32) || defined (_WIN64)
BOOL WINAPI argv_206(DWORD signal) {
	if (signal == CTRL_C_EVENT) {
		fprintf(stderr, "* Signal catched\n");
		g_ProxyPtr->argv_141();
		argv_137++;
		if (argv_137 >= 3) {
			fprintf(stderr, "*** main <exiting>\n");
			g_ProxyPtr->argv_214();
			exit(1);
		}
}
	return TRUE;
}
#elif defined (_LINUX)
void argv_206(int32_t signum) {
	fprintf(stderr, "* Signal catched\n");
	g_ProxyPtr->argv_141();
	argv_137++;
	if (argv_137 >= 3) {
		fprintf(stderr, "*** main <exiting>\n");
		g_ProxyPtr->argv_214();
		exit(1);
	}
}
#endif // #if defined (_WIN32) || defined (_WIN64)

void argv_121::argv_213() {
#if defined (_WIN32) || defined (_WIN64)
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 0);
	WSAStartup(sockVersion, &wsaData);
#endif // #if defined (__WINDOWS_OS__)
}

void argv_121::argv_217() {
#if defined (_WIN32) || defined (_WIN64)
	WSACleanup();
#endif // #if defined (__WINDOWS_OS__)
}

void argv_121::argv_125() {
	fprintf(stderr, "\nUsage: ./ProxyTcp -PortToBind <PortToBind> -ExchangeIp <ExchangeIp> -ExchangePort <ExchangePort> { OPTIONS }\n\n");
	fprintf(stderr, "OPTIONS:\n");
	fprintf(stderr, "========\n\n");
	fprintf(stderr, "-trunk                       : the proxy will echo any received data back, useful to simulate the exchange when real exchange is not available.\n\n");
	fprintf(stderr, "-quiet_trunk                 : same as '-trunk' but all data received will be trashed instead of being echoed to the sender.\n\n");
	fprintf(stderr, "-ConnectDelaySec <DelaySec>  : wait n seconds before forwarding the connection request to the exchange\n\n");
	fprintf(stderr, "-record <file.replay>        : records data coming from the exchange in the file whose name was provided.\n");
	fprintf(stderr, "                               Only available in proxy mode (not in trunk mode).\n\n");
	fprintf(stderr, "-fsync                       : during a recording, force the tool to flush the replay data to disk every time\n");
	fprintf(stderr, "                               it receives something. This option is only meaningful in '-record' mode.\n\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "-replay <file.replay>        : permits to replay the data sequence that occured after the login.\n");
	fprintf(stderr, "                               Only available in trunk mode.\n\n");
	fprintf(stderr, "-skip_replay_file_analysis   : the tool analyses the replay file before attempting to replay it. If the replay file\n");
	fprintf(stderr, "                               is big, then you will have to wait before replay is possible. use this option avoid waiting.\n");
	fprintf(stderr, "                               The drawback is that you will not have a full progress indicator while replaying the file.\n\n");
	fprintf(stderr, "-no_stop_after_replay_end    : when the replay is finished, this option permits to wait for a new client connection and do the\n");
	fprintf(stderr, "                               replay again with this new client without having to restart the tool.\n\n");
	fprintf(stderr, "-ignore_checksum_error       : attempt to replay the file even if the file has not a valid checksum.\n");
	fprintf(stderr, "                               This option is useful if the tool was killed for example, and the replay file\n");
	fprintf(stderr, "                               does not contain a checksum line, or when you want to modify the replay file by hand\n");
	fprintf(stderr, "                               (the '-ignore_checksum_error' option is only meaningful in '-replay' mode)\n\n");
	fprintf(stderr, "-speed <SpeedChoice>         : this parameter permits to replay faster. It is only meaningful in '-replay' mode.\n");
	fprintf(stderr, "                               valid range being [2..N]\n\n");
	fprintf(stderr, "-no_strict_content           : during a replay, this option permits the feedhandler to send\n");
	fprintf(stderr, "                               messages with the same size, but a different content (useful if the message\n");
	fprintf(stderr, "                               contains some date or time for example).\n");
	fprintf(stderr, "                               The default behavior is to consider that the feedhandler MUST send us exactly the same\n");
	fprintf(stderr, "                               data as it was recorded. This option is only meaningful if mode is -trunk and -replay\n\n");
	fprintf(stderr, "-h or --help                 : display this help and explanations\n\n");
	fprintf(stderr, "-v or --version              : display the version and it's content\n");
	fprintf(stderr, "\n\n");
}

bool argv_121::argv_192(int32_t argc, char **argv, argv_118& o_ProxyEnv) {
	bool bret = true;
	// to check existence of mandatory parameters
	bool PortToBindFound = false;
	bool ExchangeIpFound = false;
	bool ExchangePortFound = false;

	for (int32_t i = 1; (true == bret) && (i < argc); ) {
		if (strcmp(argv[i], "-PortToBind") == 0) {
			if ((i + 1) >= argc) {
				fprintf(stderr, "+++ Error: missing value for parameter '-PortToBind'\n");
				bret = false;
			}
			else {
				PortToBindFound = true;
				o_ProxyEnv.argv_165 = atoi(argv[i + 1]);
				i = i + 2;
			}
		}
		else if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0)) {
			bret = false;
		}
		else if (strcmp(argv[i], "-ExchangeIp") == 0) {
			if ((i + 1) >= argc) {
				fprintf(stderr, "+++ Error: missing value for parameter '-ExchangeIp'\n");
				bret = false;
			}
			else {
				ExchangeIpFound = true;
				o_ProxyEnv.argv_151 = argv[i + 1];
				i = i + 2;
			}
		}
		else if (strcmp(argv[i], "-ExchangePort") == 0) {
			if ((i + 1) >= argc) {
				fprintf(stderr, "+++ Error: missing value for parameter '-ExchangePort'\n");
				bret = false;
			}
			else {
				ExchangePortFound = true;
				o_ProxyEnv.argv_152 = atoi(argv[i + 1]);
				i = i + 2;
			}
		}
		else if ((strcmp(argv[i], "-v") == 0) || (strcmp(argv[i], "--version") == 0)) {
			argv_121 argv_121;
			argv_121.argv_126();
			exit(0);
		}
		else if (strcmp(argv[i], "-fsync") == 0) {
			o_ProxyEnv.argv_154 = true;
			i++;
		}
		else if (strcmp(argv[i], "-trunk") == 0) {
			o_ProxyEnv.argv_185 = true;
			i++;
		}
		else if (strcmp(argv[i], "-quiet_trunk") == 0) {
			o_ProxyEnv.argv_166 = true;
			i++;
		}
		else if (strcmp(argv[i], "-no_stop_after_replay_end") == 0) {
			o_ProxyEnv.argv_163 = true;
			i++;
		}
		else if (strcmp(argv[i], "-no_strict_content") == 0) {
			o_ProxyEnv.argv_164 = true;
			i++;
		}
		else if (strcmp(argv[i], "-skip_replay_file_analysis") == 0) {
			o_ProxyEnv.argv_178 = true;
			o_ProxyEnv.argv_157 = true;
			i++;
		}
		else if (strcmp(argv[i], "-ConnectDelaySec") == 0) {
			if ((i + 1) >= argc) {
				fprintf(stderr, "+++ Error: missing value for parameter '-ConnectDelaySec'\n");
				bret = false;
			}
			else {
				o_ProxyEnv.argv_145 = atoi(argv[i + 1]);
				i = i + 2;
			}
		}
		else if (strcmp(argv[i], "-record") == 0) {
			if ((i + 1) >= argc) {
				fprintf(stderr, "+++ Error: missing filename for parameter '-record'\n");
				bret = false;
			}
			else {
				o_ProxyEnv.argv_170 = true;
				o_ProxyEnv.argv_168 = argv[i + 1];
				i = i + 2;
			}
		}
		else if (strcmp(argv[i], "-replay") == 0) {
			if ((i + 1) >= argc) {
				fprintf(stderr, "+++ Error: missing filename for parameter '-replay'\n");
				bret = false;
			}
			else {
				o_ProxyEnv.argv_175 = true;
				o_ProxyEnv.argv_172 = argv[i + 1];
				i = i + 2;
			}
		}
		else if (strcmp(argv[i], "-speed") == 0) {
			if ((i + 1) >= argc) {
				fprintf(stderr, "+++ Error: missing filename for parameter '-speed'\n");
				bret = false;
			}
			else {
				o_ProxyEnv.argv_176 = atoi(argv[i + 1]);
				if (o_ProxyEnv.argv_176 < 2) {
					fprintf(stderr, "+++ Error: invalid speed parameter ! (valid range is [2..N]\n");
					bret = false;
				}
				i = i + 2;
			}
		}
		else if (strcmp(argv[i], "-ignore_checksum_error") == 0) {
			o_ProxyEnv.argv_157 = true;
			i++;
		}
		else {
			fprintf(stderr, "+++ Error: unknown parameter '%s'\n", argv[i]);
			bret = false;
		}
	}

	if (true == bret) {
		if (false == PortToBindFound) {
			fprintf(stderr, "+++ Error: missing mandatory parameter : '-PortToBind'\n");
			bret = false;
		}
		if ((false == o_ProxyEnv.argv_185) && (false == o_ProxyEnv.argv_166)) {
			if (false == ExchangeIpFound) {
				fprintf(stderr, "+++ Error: missing mandatory parameter : '-ExchangeIp'\n");
				bret = false;

			}
			if (false == ExchangePortFound) {
				fprintf(stderr, "+++ Error: missing mandatory parameter : '-ExchangePort'\n");
				bret = false;
			}
		}
		if ((true == o_ProxyEnv.argv_185) && (true == o_ProxyEnv.argv_166)) {
			fprintf(stderr, "+++ Error: illegal to activate both '-trunk' and '-quiet_trunk' options at the same time (choose only one of them)\n");
			bret = false;
		}
		if ((o_ProxyEnv.argv_170) && (o_ProxyEnv.argv_185)) {
			fprintf(stderr, "+++ Error: Record mode is only available in proxy mode !\n");
			bret = false;
		}
		if ((o_ProxyEnv.argv_175) && (!o_ProxyEnv.argv_185)) {
			fprintf(stderr, "+++ Error: Replay mode is only available in trunk mode !\n");
			bret = false;
		}
		if ((o_ProxyEnv.argv_170) && (o_ProxyEnv.argv_175)) {
			fprintf(stderr, "+++ Error: Replay mode and Record mode should not be used simultaneously !\n");
			bret = false;
		}
		if (o_ProxyEnv.argv_154 && (!o_ProxyEnv.argv_170)) {
			fprintf(stderr, "+++ Error: '-fsync' option is only meaningful with the '-record' option !\n");
			bret = false;
		}
		if (o_ProxyEnv.argv_157 && (!o_ProxyEnv.argv_175)) {
			fprintf(stderr, "+++ Error: '-ignore_checksum_error' option only available with '-replay' option !\n");
			bret = false;
		}
		if (o_ProxyEnv.argv_163 && (!o_ProxyEnv.argv_175)) {
			fprintf(stderr, "+++ Error: '-no_stop_after_replay_end' option only available with '-replay' option !\n");
			bret = false;
		}
		if (o_ProxyEnv.argv_164 && (!o_ProxyEnv.argv_175)) {
			fprintf(stderr, "+++ Error: '-no_strict_content' option only available with '-replay' option !\n");
			bret = false;
		}
	}
	return (bret);
}

class argv_123
{
public:
	int argv_186;

	argv_123() {
		argv_186 = rand();
	}
};


int32_t main (int32_t argc, char **argv) {
	int32_t iret = 0;
	argv_119 proxy;
#if defined (_WIN32) || defined (_WIN64)
    if (!SetConsoleCtrlHandler(argv_206, TRUE)) {
        fprintf(stderr,"+++ ERROR: Could not set control handler\n"); 
		iret = 1;
	}
#elif defined (_LINUX)
	signal(SIGINT, argv_206);
#endif // #if defined (_WIN32) || defined (_WIN64)
	g_ProxyPtr = &proxy;
	argv_121 ReplayHelper;
	if (ReplayHelper.argv_192 (argc, argv, proxy.argv_139()) == false) {
		ReplayHelper.argv_125();
		iret = 1;
	}
	else {
		proxy.argv_204();
	}
	return (iret);
}



