#ifndef argv_107
#define argv_107

#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <cstdint>
#include <ctype.h>
#include <chrono>
#include <thread>
#include <iostream>
#if defined (_WIN32) || defined (_WIN64)
	#include <Windows.h>
	#include <Shlwapi.h>
	//#include <WinSock2.h>
#elif defined (_LINUX)
	#include <errno.h>
	#include <signal.h>
	#include <arpa/inet.h>
	#include <sys/time.h>
	#include <sys/socket.h>
	#include <sys/time.h>
	#include <sys/types.h>
	#include <unistd.h>
	typedef int32_t SOCKET;
#endif // #if defined (_WIN32) || defined (_WIN64)

const int32_t		argv_188				= 1024;
const int32_t		argv_109					= 65536;
const int32_t		argv_207			= 256;
const int32_t		argv_189	= 16;
const uint32_t	argv_142		= 256;

const char argv_218[] 						= "BEEMEAL_TCP_REPLAY";
const char argv_135[]		= "S->C";
const char argv_136[]		= "C->S";
const double argv_197				= 1.0; // protocol version

typedef enum argv_200
{
	argv_201,
	argv_202,
} argv_203;

enum argv_222 {
	argv_129 = 0,
	argv_127,
	argv_128,
};

class argv_110
{
private:
	std::chrono::time_point<std::chrono::system_clock> argv_180;
	std::chrono::time_point<std::chrono::system_clock> argv_182;

public:
	argv_110();
	void argv_210();
	void argv_214();
	uint64_t argv_138();
};

//  ./a.out -PortToBind <PortToBind> -ExchangeIp <ExchangeIp> -ExchangePort <ExchangePort> { -trunk }
class argv_118
{
private:
	argv_118(const argv_118&) = delete;
	argv_118& operator= (const argv_118&) = delete;

public:
	int32_t			argv_165;
	std::string		argv_151;
	int32_t			argv_152;
	bool			argv_185;
	bool			argv_170;
	bool			argv_164;
	bool			argv_154;
	std::string		argv_168;
	std::string		argv_172;
	bool			argv_175;
	bool			argv_166;
	int32_t			argv_145;
	int32_t			argv_176;
	bool			argv_157;
	bool			argv_178;
	bool			argv_163;

	argv_118();
};

// one parsed line 
class argv_120
{
public:
	argv_203 	argv_149;
	uint64_t			argv_183;
	uint32_t			argv_177;
	uint8_t				argv_144[argv_109];

	void Reset();
	argv_120();
};

class argv_121
{
public:
	bool	argv_115(uint8_t * i_Buf1, uint8_t * i_Buf2, int32_t i_Size);
	bool	argv_134(SOCKET i_Sockfd);
	void	argv_124(const char * i_Msg, char * i_Buf, int32_t size, bool i_NoEol = false);
	void	argv_209(std::string const & i_line, std::string const & i_separator, std::vector<std::string> & i_vector_fields);
	bool	argv_199(SOCKET i_Sockfd, char * i_Buffer, int32_t i_NbToRead);
	bool	argv_205(SOCKET i_Sockfd, uint8_t * i_Buffer, size_t i_NbToSend);
	bool	argv_114(SOCKET i_SocketFd);
	int32_t	argv_116(const char *s1, const char *s2);
	bool	argv_130(const char * i_Filename);
	void	argv_126();
	void	argv_125();
	bool	argv_192(int32_t argc, char **argv, argv_118& o_ProxyEnv);
	void	argv_217 ();
	void	argv_213();
};


class argv_122
{
private:
	uint64_t		argv_155;
	uint64_t		argv_156;
	int32_t			argv_148;
	uint32_t		argv_162;
	uint32_t		argv_184;
	uint32_t		argv_160;
	bool			argv_154;
	int32_t			argv_179;
	bool    		argv_157;
	argv_110		argv_143;

	struct timeval	argv_181;
	FILE *  		argv_153;
	bool			argv_169;
	bool			argv_173;
	std::string		argv_167;

	void 			argv_219(const char * i_buffer, uint64_t& io_hash, uint64_t& io_HashedSize);
	bool 			argv_193(double& o_Version);
	bool 			argv_220();
	bool 			argv_191(int32_t i_LineNo, const char * i_Buffer, argv_203& o_Direction, uint64_t& o_TimestampUsec, uint32_t& o_Size, uint8_t * o_BufResult);

public:
	argv_122();
	void			argv_214();
	bool			argv_211(const char * i_Filename, bool i_FsyncModeActivated);
	bool			argv_215();
	bool			argv_108(argv_203 i_direction, char * i_Buf, int32_t size);

	bool			argv_212(const char * i_Filename, int32_t i_Speed, bool i_IgnoreChecksumError, bool i_SkipReplayFileAnalysis);
	void			argv_216();
	bool 			argv_140(argv_120& o_Entry, int32_t& o_NbReplayEntryDone, int32_t& o_TotalNbReplayEntry);
};

class argv_119
{
private:
	fd_set				rset;
	fd_set				rset_dirty;
	SOCKET				argv_187;
	char				argv_144[argv_109];
	int32_t				argv_159;
	argv_120		argv_171;
	struct sockaddr_in	argv_113;
	SOCKET				argv_158;
	SOCKET				argv_146;
	SOCKET				argv_147;
	size_t				argv_161;
	argv_122		argv_174;
	argv_118			argv_150;

	bool				argv_194(std::string IpToConnectTo, int32_t PortToConnectTo);
	bool				argv_196(int32_t PortToBind);
	bool				argv_221(std::string IpToConnectTo, int32_t PortToConnectTo);
	bool				argv_131();
	bool				argv_132();
	bool				argv_133();
	bool				argv_198(SOCKET, SOCKET);
	int32_t				argv_111();
	void				argv_195();
	bool				argv_112();

public:
	argv_119();
	~argv_119();
	bool    argv_204();
	void    argv_141();
	void	argv_214();
	argv_118& argv_139();
};

#endif // argv_107