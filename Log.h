#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <string>
#include <vector>

/**
 * @def PUSH_LOG_STACK
 * @brief Pushes the logging stack with the function name that called it
 */
#define PUSH_LOG_STACK \
	Log::Push( __FUNCTION__ );

/**
 * @def POP_LOG_STACK
 * @brief Pops the logging stack
 */
#define POP_LOG_STACK \
	Log::Pop();

/**
 * @class Log
 * @brief Basic logging class
 * @author Jimmy Thompson
 *
 * @version $Revision: 1.1 $
 * @date $Date: 2012/09/08 - 14:25:00 $
 * 
 * @details Logging class to deal with basic string messages and macro-based
 * @details stack tracing. Something quick I made to handle logging in my own
 * @details programs; made to be basic.
 */
class Log {
	public:
		static const enum Type {
			FATAL,
			ERROR,
			WARN,
			INFO,
			DEBUG
		};

	private:
		Type m_threshold;
		bool m_initialised;
		std::string m_fileName;
		std::vector<std::string> m_stack;
		std::ofstream m_stream;

		Log();
		Log(const Log&);
		~Log();

		static Log& get();

		void write( const std::string& message );
		bool log( const Type type, const std::string& message );

		Log& operator=(const Log&);

	public:
		static const char* TypeToString(Type type);

		static bool Initialise( const std::string& fileName );
		static bool Finalise();

		static void SetThreshold( Type type );
		static bool Fatal( const std::string& message );
		static bool Error( const std::string& message );
		static bool Warn( const std::string& message );
		static bool Info( const std::string& message );
		static bool Debug( const std::string& message );

		static std::string Peek();
		static bool Push(const std::string& input);
		static std::string Pop();
		static void PrintStackTrace();
};

#endif
